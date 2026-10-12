#include "../../includes/Command.hpp"
#include <iostream>

void Command::checkRegistration(Server& server, Client& client) {
    if (!client.isRegistered() && client.hasPassword() && !client.getNickname().empty() && !client.getUsername().empty()) {
        client.setRegistered(true);
        std::string nick = client.getNickname();
        std::string user = client.getUsername();
        std::string host = client.getIp();
        
        client.sendMessage(RPL_WELCOME(nick, user, host));
        client.sendMessage(RPL_YOURHOST(nick));
        client.sendMessage(RPL_CREATED(nick, server.getCreationDate()));
        client.sendMessage(RPL_MYINFO(nick));
        std::cout << "[Server] Client fd " << client.getFd() << " registered as " << nick << std::endl;
    }
}

void Command::execute(Server& server, Client& client, const std::string& rawLine) {
    std::string line = Utils::trim(rawLine);
    if (line.empty()) return;

    // Optional leading prefix (e.g. :nick) - ignore from client
    if (line[0] == ':') {
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos)
            line = Utils::trim(line.substr(spacePos + 1));
        else
            return;
    }

    std::string trailing = "";
    size_t colonPos = line.find(" :");
    if (colonPos != std::string::npos) {
        trailing = line.substr(colonPos + 2);
        line = line.substr(0, colonPos);
    }

    std::vector<std::string> tokens = Utils::splitWhitespace(line);
    if (tokens.empty()) return;

    std::string cmdName = Utils::toUpper(tokens[0]);
    std::vector<std::string> params;
    for (size_t i = 1; i < tokens.size(); ++i) {
        params.push_back(tokens[i]);
    }

    // Check if client is registered before allowing most commands
    bool isAuthCmd = (cmdName == "PASS" || cmdName == "NICK" || cmdName == "USER" || cmdName == "CAP" || cmdName == "QUIT");
    if (!client.isRegistered() && !isAuthCmd) {
        std::string nick = client.getNickname().empty() ? "*" : client.getNickname();
        client.sendMessage(ERR_NOTREGISTERED(nick));
        return;
    }

    if (cmdName == "PASS") {
        pass(server, client, params);
    } else if (cmdName == "NICK") {
        nick(server, client, params);
    } else if (cmdName == "USER") {
        user(server, client, params, trailing);
    } else if (cmdName == "CAP") {
        cap(server, client, params);
    } else if (cmdName == "PING") {
        ping(server, client, params, trailing);
    } else if (cmdName == "PONG") {
        pong(server, client, params);
    } else if (cmdName == "QUIT") {
        quit(server, client, params, trailing);
    } else if (cmdName == "JOIN") {
        join(server, client, params);
    } else if (cmdName == "PART") {
        part(server, client, params, trailing);
    } else if (cmdName == "PRIVMSG") {
        privmsg(server, client, params, trailing);
    } else if (cmdName == "NOTICE") {
        notice(server, client, params, trailing);
    } else if (cmdName == "TOPIC") {
        topic(server, client, params, trailing);
    } else if (cmdName == "MODE") {
        mode(server, client, params);
    } else if (cmdName == "INVITE") {
        invite(server, client, params);
    } else if (cmdName == "KICK") {
        kick(server, client, params, trailing);
    } else {
        std::string nick = client.getNickname().empty() ? "*" : client.getNickname();
        client.sendMessage(ERR_UNKNOWNCOMMAND(nick, cmdName));
    }
}
