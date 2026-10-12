#include "../../includes/Command.hpp"

void Command::ping(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    (void)server;
    std::string token = "";
    if (!trailing.empty()) {
        token = trailing;
    } else if (!params.empty()) {
        token = params[0];
    } else {
        std::string nick = client.getNickname().empty() ? "*" : client.getNickname();
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "PING"));
        return;
    }

    client.sendMessage(":" + std::string(SERVER_NAME) + " PONG " + std::string(SERVER_NAME) + " :" + token + "\r\n");
}
