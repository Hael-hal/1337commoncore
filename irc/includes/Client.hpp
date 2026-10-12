#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

class Client {
private:
    int         _fd;
    std::string _ip;
    int         _port;
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _hostname;

    bool        _hasEnteredPassword;
    bool        _isRegistered;
    bool        _isQuitting;

    std::string _recvBuffer;

public:
    Client();
    Client(int fd, const std::string& ip, int port);
    Client(const Client& other);
    Client& operator=(const Client& other);
    ~Client();

    // Getters
    int                getFd() const;
    const std::string& getIp() const;
    int                getPort() const;
    const std::string& getNickname() const;
    const std::string& getUsername() const;
    const std::string& getRealname() const;
    const std::string& getHostname() const;
    std::string        getPrefix() const;

    bool               hasPassword() const;
    bool               isRegistered() const;
    bool               isQuitting() const;

    // Setters
    void setNickname(const std::string& nick);
    void setUsername(const std::string& user);
    void setRealname(const std::string& real);
    void setHostname(const std::string& host);
    void setPasswordEntered(bool val);
    void setRegistered(bool val);
    void setQuitting(bool val);

    // Buffer and Communication
    void appendToRecvBuffer(const std::string& data);
    bool extractNextCommand(std::string& command);
    void sendMessage(const std::string& message) const;
};

#endif
