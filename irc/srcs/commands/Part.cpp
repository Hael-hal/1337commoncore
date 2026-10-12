#include "../../includes/Command.hpp"

void Command::part(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    std::string nick = client.getNickname();

    if (params.empty()) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "PART"));
        return;
    }

    std::string reason = trailing.empty() ? "Leaving" : trailing;
    std::vector<std::string> channels = Utils::split(params[0], ',');

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string chanName = channels[i];
        Channel* chan = server.getChannel(chanName);

        if (!chan) {
            client.sendMessage(ERR_NOSUCHCHANNEL(nick, chanName));
            continue;
        }

        if (!chan->isMember(client.getFd())) {
            client.sendMessage(ERR_NOTONCHANNEL(nick, chanName));
            continue;
        }

        std::string partMsg = ":" + client.getPrefix() + " PART " + chanName + " :" + reason + "\r\n";
        chan->broadcast(partMsg);
        chan->removeMember(client.getFd());

        if (chan->getMemberCount() == 0) {
            server.removeChannel(chanName);
        }
    }
}
