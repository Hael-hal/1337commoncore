#include "../../includes/Command.hpp"

void Command::user(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    std::string nick = client.getNickname().empty() ? "*" : client.getNickname();

    if (client.isRegistered()) {
        client.sendMessage(ERR_ALREADYREGISTERED(nick));
        return;
    }

    if (!client.hasPassword()) {
        client.sendMessage(ERR_NOTREGISTERED(nick));
        return;
    }

    if (params.size() < 3 && (params.size() < 1 || trailing.empty())) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "USER"));
        return;
    }

    std::string username = params[0];
    std::string realname = trailing;
    if (realname.empty() && params.size() >= 4) {
        realname = params[3];
    }

    client.setUsername(username);
    client.setRealname(realname);

    checkRegistration(server, client);
}
