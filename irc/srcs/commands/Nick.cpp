#include "../../includes/Command.hpp"

void Command::nick(Server& server, Client& client, const std::vector<std::string>& params) {
    std::string currentNick = client.getNickname().empty() ? "*" : client.getNickname();

    if (!client.hasPassword()) {
        client.sendMessage(ERR_NOTREGISTERED(currentNick));
        return;
    }

    if (params.empty() || params[0].empty()) {
        client.sendMessage(ERR_NONICKNAMEGIVEN(currentNick));
        return;
    }

    std::string newNick = params[0];

    if (!Utils::isValidNickname(newNick)) {
        client.sendMessage(ERR_ERRONEUSNICKNAME(currentNick, newNick));
        return;
    }

    Client* existing = server.getClientByNick(newNick);
    if (existing && existing->getFd() != client.getFd()) {
        client.sendMessage(ERR_NICKNAMEINUSE(currentNick, newNick));
        return;
    }

    if (client.isRegistered()) {
        std::string nickChangeMsg = ":" + client.getPrefix() + " NICK :" + newNick + "\r\n";
        client.sendMessage(nickChangeMsg);
        // Also inform all channels where the client is a member
        // (Server will broadcast or we can do it here)
        client.setNickname(newNick);
    } else {
        client.setNickname(newNick);
        checkRegistration(server, client);
    }
}
