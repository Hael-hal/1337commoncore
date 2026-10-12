#include "../../includes/Command.hpp"

void Command::notice(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    if (params.empty()) return;

    std::string message = trailing;
    if (message.empty() && params.size() > 1) {
        message = params[1];
    }
    if (message.empty()) return;

    std::vector<std::string> targets = Utils::split(params[0], ',');

    for (size_t i = 0; i < targets.size(); ++i) {
        std::string target = targets[i];

        if (target[0] == '#' || target[0] == '&') {
            Channel* chan = server.getChannel(target);
            if (!chan || !chan->isMember(client.getFd())) {
                continue; // NOTICE never sends error replies
            }
            std::string msg = ":" + client.getPrefix() + " NOTICE " + target + " :" + message + "\r\n";
            chan->broadcast(msg, client.getFd());
        } else {
            Client* targetClient = server.getClientByNick(target);
            if (!targetClient) {
                continue; // NOTICE never sends error replies
            }
            std::string msg = ":" + client.getPrefix() + " NOTICE " + target + " :" + message + "\r\n";
            targetClient->sendMessage(msg);
        }
    }
}
