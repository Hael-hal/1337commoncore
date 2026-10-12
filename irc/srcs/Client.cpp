#include "../includes/Client.hpp"
#include <iostream>

Client::Client()
    : _fd(-1), _ip(""), _port(0), _nickname(""), _username(""), _realname(""), _hostname(""),
      _hasEnteredPassword(false), _isRegistered(false), _isQuitting(false), _recvBuffer("") {}

Client::Client(int fd, const std::string& ip, int port)
    : _fd(fd), _ip(ip), _port(port), _nickname(""), _username(""), _realname(""), _hostname(ip),
      _hasEnteredPassword(false), _isRegistered(false), _isQuitting(false), _recvBuffer("") {}

Client::Client(const Client& other) {
    *this = other;
}

Client& Client::operator=(const Client& other) {
    if (this != &other) {
        _fd = other._fd;
        _ip = other._ip;
        _port = other._port;
        _nickname = other._nickname;
        _username = other._username;
        _realname = other._realname;
        _hostname = other._hostname;
        _hasEnteredPassword = other._hasEnteredPassword;
        _isRegistered = other._isRegistered;
        _isQuitting = other._isQuitting;
        _recvBuffer = other._recvBuffer;
    }
    return *this;
}

Client::~Client() {}

int Client::getFd() const {
    return _fd;
}

const std::string& Client::getIp() const {
    return _ip;
}

int Client::getPort() const {
    return _port;
}

const std::string& Client::getNickname() const {
    return _nickname;
}

const std::string& Client::getUsername() const {
    return _username;
}

const std::string& Client::getRealname() const {
    return _realname;
}

const std::string& Client::getHostname() const {
    return _hostname;
}

std::string Client::getPrefix() const {
    std::string nick = _nickname.empty() ? "*" : _nickname;
    std::string user = _username.empty() ? "*" : _username;
    std::string host = _ip.empty() ? "localhost" : _ip;
    return nick + "!" + user + "@" + host;
}

bool Client::hasPassword() const {
    return _hasEnteredPassword;
}

bool Client::isRegistered() const {
    return _isRegistered;
}

bool Client::isQuitting() const {
    return _isQuitting;
}

void Client::setNickname(const std::string& nick) {
    _nickname = nick;
}

void Client::setUsername(const std::string& user) {
    _username = user;
}

void Client::setRealname(const std::string& real) {
    _realname = real;
}

void Client::setHostname(const std::string& host) {
    _hostname = host;
}

void Client::setPasswordEntered(bool val) {
    _hasEnteredPassword = val;
}

void Client::setRegistered(bool val) {
    _isRegistered = val;
}

void Client::setQuitting(bool val) {
    _isQuitting = val;
}

void Client::appendToRecvBuffer(const std::string& data) {
    _recvBuffer += data;
}

bool Client::extractNextCommand(std::string& command) {
    size_t crlf = _recvBuffer.find("\r\n");
    size_t lf = _recvBuffer.find("\n");

    if (crlf != std::string::npos && (lf == std::string::npos || crlf <= lf)) {
        command = _recvBuffer.substr(0, crlf);
        _recvBuffer.erase(0, crlf + 2);
        return true;
    } else if (lf != std::string::npos) {
        command = _recvBuffer.substr(0, lf);
        _recvBuffer.erase(0, lf + 1);
        // Remove trailing \r if any
        if (!command.empty() && command[command.size() - 1] == '\r') {
            command.erase(command.size() - 1);
        }
        return true;
    }
    return false;
}

void Client::sendMessage(const std::string& message) const {
    if (_fd < 0) return;
    ssize_t bytesSent = send(_fd, message.c_str(), message.length(), 0);
    if (bytesSent < 0) {
        std::cerr << "[Warning] Failed to send message to fd " << _fd << std::endl;
    }
}
