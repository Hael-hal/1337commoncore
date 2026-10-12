#include "../includes/Server.hpp"
#include "../includes/Command.hpp"
#include <cstring>
#include <cerrno>

bool Server::_signalReceived = false;

void Server::signalHandler(int signum) {
    (void)signum;
    std::cout << "\n[Server] Shutdown signal received." << std::endl;
    _signalReceived = true;
}

Server::Server(int port, const std::string& password)
    : _port(port), _password(password), _serverSocket(-1) {
    _creationDate = Utils::getCurrentDateTime();
}

Server::Server(const Server& other) {
    *this = other;
}

Server& Server::operator=(const Server& other) {
    if (this != &other) {
        _port = other._port;
        _password = other._password;
        _serverSocket = other._serverSocket;
        _pollFds = other._pollFds;
        _clients = other._clients;
        _channels = other._channels;
        _creationDate = other._creationDate;
    }
    return *this;
}

Server::~Server() {
    stop();
}

void Server::init() {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0) {
        throw std::runtime_error("Failed to create server socket: " + std::string(strerror(errno)));
    }

    int opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Failed to set SO_REUSEADDR: " + std::string(strerror(errno)));
    }

    if (fcntl(_serverSocket, F_SETFL, O_NONBLOCK) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Failed to set non-blocking on server socket: " + std::string(strerror(errno)));
    }

    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(_port);

    if (bind(_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Failed to bind server socket to port " + Utils::toString(_port) + ": " + std::string(strerror(errno)));
    }

    if (listen(_serverSocket, SOMAXCONN) < 0) {
        close(_serverSocket);
        throw std::runtime_error("Failed to listen on server socket: " + std::string(strerror(errno)));
    }

    struct pollfd pfd;
    pfd.fd = _serverSocket;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    std::cout << "[Server] ft_irc listening on port " << _port << std::endl;
}

void Server::run() {
    while (!_signalReceived) {
        int ret = poll(&_pollFds[0], _pollFds.size(), -1);
        if (ret < 0) {
            if (errno == EINTR && _signalReceived) {
                break;
            }
            std::cerr << "[Error] poll() failed: " << strerror(errno) << std::endl;
            break;
        }

        for (size_t i = 0; i < _pollFds.size(); ++i) {
            if (_pollFds[i].revents == 0)
                continue;

            int currentFd = _pollFds[i].fd;

            if (_pollFds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                if (currentFd == _serverSocket) {
                    std::cerr << "[Error] Server socket error." << std::endl;
                    _signalReceived = true;
                    break;
                } else {
                    disconnectClient(currentFd, "Connection lost");
                    --i;
                    continue;
                }
            }

            if (_pollFds[i].revents & POLLIN) {
                if (currentFd == _serverSocket) {
                    handleNewConnection();
                } else {
                    handleClientMessage(currentFd);
                }
            }
        }
    }
}

void Server::handleNewConnection() {
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    int clientFd = accept(_serverSocket, (struct sockaddr*)&clientAddr, &addrLen);

    if (clientFd < 0) {
        if (errno != EWOULDBLOCK && errno != EAGAIN) {
            std::cerr << "[Warning] accept() failed: " << strerror(errno) << std::endl;
        }
        return;
    }

    if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0) {
        std::cerr << "[Warning] Failed to set client socket non-blocking." << std::endl;
        close(clientFd);
        return;
    }

    std::string clientIp = inet_ntoa(clientAddr.sin_addr);
    int clientPort = ntohs(clientAddr.sin_port);

    _clients[clientFd] = Client(clientFd, clientIp, clientPort);

    struct pollfd pfd;
    pfd.fd = clientFd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    _pollFds.push_back(pfd);

    std::cout << "[Server] New client connected from " << clientIp << ":" << clientPort << " on fd " << clientFd << std::endl;
}

void Server::handleClientMessage(int fd) {
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        disconnectClient(fd, "Client disconnected");
        return;
    }

    buffer[bytesRead] = '\0';
    Client* client = getClientByFd(fd);
    if (!client) return;

    client->appendToRecvBuffer(std::string(buffer, bytesRead));

    std::string command;
    while (client->extractNextCommand(command)) {
        Command::execute(*this, *client, command);
        if (_clients.find(fd) == _clients.end() || client->isQuitting()) {
            break;
        }
    }
}

void Server::disconnectClient(int fd, const std::string& reason) {
    std::map<int, Client>::iterator it = _clients.find(fd);
    if (it == _clients.end()) return;

    std::string nick = it->second.getNickname();
    std::cout << "[Server] Disconnecting client fd " << fd << (nick.empty() ? "" : " (" + nick + ")") << ": " << reason << std::endl;

    removeClientFromAllChannels(fd, reason);

    close(fd);
    _clients.erase(it);

    for (std::vector<struct pollfd>::iterator pIt = _pollFds.begin(); pIt != _pollFds.end(); ++pIt) {
        if (pIt->fd == fd) {
            _pollFds.erase(pIt);
            break;
        }
    }
}

void Server::removeClientFromAllChannels(int fd, const std::string& reason) {
    Client* client = getClientByFd(fd);
    if (!client) return;

    std::string quitMsg = ":" + client->getPrefix() + " QUIT :" + reason + "\r\n";

    std::vector<std::string> channelsToRemove;
    for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->second.isMember(fd)) {
            it->second.broadcast(quitMsg, fd);
            it->second.removeMember(fd);
            if (it->second.getMemberCount() == 0) {
                channelsToRemove.push_back(it->first);
            }
        }
    }

    for (size_t i = 0; i < channelsToRemove.size(); ++i) {
        _channels.erase(channelsToRemove[i]);
    }
}

Client* Server::getClientByFd(int fd) {
    std::map<int, Client>::iterator it = _clients.find(fd);
    if (it != _clients.end()) {
        return &(it->second);
    }
    return NULL;
}

Client* Server::getClientByNick(const std::string& nick) {
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (Utils::toLower(it->second.getNickname()) == Utils::toLower(nick)) {
            return &(it->second);
        }
    }
    return NULL;
}

Channel* Server::getChannel(const std::string& name) {
    std::string lowerName = Utils::toLower(name);
    std::map<std::string, Channel>::iterator it = _channels.find(lowerName);
    if (it != _channels.end()) {
        return &(it->second);
    }
    return NULL;
}

Channel& Server::createChannel(const std::string& name) {
    std::string lowerName = Utils::toLower(name);
    _channels[lowerName] = Channel(name);
    return _channels[lowerName];
}

void Server::removeChannel(const std::string& name) {
    std::string lowerName = Utils::toLower(name);
    _channels.erase(lowerName);
}

bool Server::isNickInUse(const std::string& nick) const {
    for (std::map<int, Client>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (Utils::toLower(it->second.getNickname()) == Utils::toLower(nick)) {
            return true;
        }
    }
    return false;
}

int Server::getPort() const {
    return _port;
}

const std::string& Server::getPassword() const {
    return _password;
}

const std::string& Server::getCreationDate() const {
    return _creationDate;
}

void Server::stop() {
    for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        close(it->first);
    }
    _clients.clear();
    _channels.clear();

    if (_serverSocket >= 0) {
        close(_serverSocket);
        _serverSocket = -1;
    }
    _pollFds.clear();
    std::cout << "[Server] Stopped cleanly." << std::endl;
}
