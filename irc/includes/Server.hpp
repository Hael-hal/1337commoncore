#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>
#include <iostream>

#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"
#include "Utils.hpp"

class Server {
private:
    int                          _port;
    std::string                  _password;
    int                          _serverSocket;
    std::vector<struct pollfd>   _pollFds;
    std::map<int, Client>        _clients;        // fd -> Client
    std::map<std::string, Channel> _channels;     // lowercase channel name -> Channel
    std::string                  _creationDate;

    static bool                  _signalReceived;

    void handleNewConnection();
    void handleClientMessage(int fd);

public:
    Server(int port, const std::string& password);
    Server(const Server& other);
    Server& operator=(const Server& other);
    ~Server();

    void init();
    void run();
    void stop();

    // Client & Channel management
    void        disconnectClient(int fd, const std::string& reason = "");
    Client*     getClientByFd(int fd);
    Client*     getClientByNick(const std::string& nick);
    Channel*    getChannel(const std::string& name);
    Channel&    createChannel(const std::string& name);
    void        removeChannel(const std::string& name);
    void        removeClientFromAllChannels(int fd, const std::string& reason);
    bool        isNickInUse(const std::string& nick) const;

    // Getters
    int                getPort() const;
    const std::string& getPassword() const;
    const std::string& getCreationDate() const;

    // Signal handler
    static void signalHandler(int signum);
};

#endif
