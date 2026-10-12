#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"
#include "Utils.hpp"

class Command {
public:
    static void execute(Server& server, Client& client, const std::string& rawLine);

    // Command Handlers
    static void pass(Server& server, Client& client, const std::vector<std::string>& params);
    static void nick(Server& server, Client& client, const std::vector<std::string>& params);
    static void user(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);
    static void cap(Server& server, Client& client, const std::vector<std::string>& params);
    static void ping(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);
    static void pong(Server& server, Client& client, const std::vector<std::string>& params);
    static void quit(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);
    static void join(Server& server, Client& client, const std::vector<std::string>& params);
    static void part(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);
    static void privmsg(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);
    static void notice(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);
    static void topic(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);
    static void mode(Server& server, Client& client, const std::vector<std::string>& params);
    static void invite(Server& server, Client& client, const std::vector<std::string>& params);
    static void kick(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing);

    // Helper for registration completion check
    static void checkRegistration(Server& server, Client& client);
};

#endif
