#include "../../includes/Command.hpp"

void Command::privmsg(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    std::string nick = client.getNickname();

    if (params.empty()) {
        client.sendMessage(ERR_NORECIPIENT(nick, "PRIVMSG"));
        return;
    }

    std::string message = trailing;
    if (message.empty() && params.size() > 1) {
        message = params[1];
    }

    if (message.empty()) {
        client.sendMessage(ERR_NOTEXTTOSEND(nick));
        return;
    }

    std::vector<std::string> targets = Utils::split(params[0], ',');

    for (size_t i = 0; i < targets.size(); ++i) {
        std::string target = targets[i];

        if (target[0] == '#' || target[0] == '&') {
            // Channel target
            Channel* chan = server.getChannel(target);
            if (!chan) {
                client.sendMessage(ERR_NOSUCHCHANNEL(nick, target));
                continue;
            }
            if (!chan->isMember(client.getFd())) {
                client.sendMessage(ERR_CANNOTSENDTOCHAN(nick, target));
                continue;
            }
            std::string msg = ":" + client.getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n";
            chan->broadcast(msg, client.getFd());
        } else {
            // User target
            Client* targetClient = server.getClientByNick(target);
            if (!targetClient) {
                client.sendMessage(ERR_NOSUCHNICK(nick, target));
                continue;
            }
            std::string msg = ":" + client.getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n";
            targetClient->sendMessage(msg);
        }
    }
}
