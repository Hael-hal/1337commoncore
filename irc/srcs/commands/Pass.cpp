#include "../../includes/Command.hpp"

void Command::pass(Server& server, Client& client, const std::vector<std::string>& params) {
    std::string nick = client.getNickname().empty() ? "*" : client.getNickname();

    if (client.isRegistered()) {
        client.sendMessage(ERR_ALREADYREGISTERED(nick));
        return;
    }
    if (params.empty()) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "PASS"));
        return;
    }

    std::string password = params[0];
    if (password != server.getPassword()) {
        client.sendMessage(ERR_PASSWDMISMATCH(nick));
        return;
    }

    client.setPasswordEntered(true);
    checkRegistration(server, client);
}

void Command::cap(Server& server, Client& client, const std::vector<std::string>& params) {
    (void)server;
    std::string nick = client.getNickname().empty() ? "*" : client.getNickname();
    if (!params.empty() && params[0] == "LS") {
        client.sendMessage(": " + std::string(SERVER_NAME) + " CAP " + nick + " LS :\r\n");
    } else if (!params.empty() && params[0] == "END") {
        // End of CAP negotiation
    }
}
