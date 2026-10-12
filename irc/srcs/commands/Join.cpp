#include "../../includes/Command.hpp"

void Command::join(Server& server, Client& client, const std::vector<std::string>& params) {
    std::string nick = client.getNickname();

    if (params.empty()) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "JOIN"));
        return;
    }

    if (params[0] == "0") {
        // Leave all channels
        server.removeClientFromAllChannels(client.getFd(), "Leaving");
        return;
    }

    std::vector<std::string> channels = Utils::split(params[0], ',');
    std::vector<std::string> keys;
    if (params.size() > 1) {
        keys = Utils::split(params[1], ',');
    }

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string chanName = channels[i];
        std::string chanKey = (i < keys.size()) ? keys[i] : "";

        if (!Utils::isValidChannelName(chanName)) {
            client.sendMessage(ERR_BADCHANMASK(chanName));
            continue;
        }

        Channel* chan = server.getChannel(chanName);
        bool isNewChannel = (chan == NULL);

        if (isNewChannel) {
            chan = &server.createChannel(chanName);
        } else {
            if (chan->isMember(client.getFd())) {
                continue; // Already in channel
            }
            if (chan->isInviteOnly() && !chan->isInvited(client.getFd())) {
                client.sendMessage(ERR_INVITEONLYCHAN(nick, chanName));
                continue;
            }
            if (chan->hasKey() && chan->getKey() != chanKey) {
                client.sendMessage(ERR_BADCHANNELKEY(nick, chanName));
                continue;
            }
            if (chan->hasUserLimit() && chan->getMemberCount() >= chan->getUserLimit()) {
                client.sendMessage(ERR_CHANNELISFULL(nick, chanName));
                continue;
            }
        }

        chan->addMember(&client, isNewChannel);

        std::string joinMsg = ":" + client.getPrefix() + " JOIN :" + chanName + "\r\n";
        chan->broadcast(joinMsg);

        // Topic reply
        if (!chan->getTopic().empty()) {
            client.sendMessage(RPL_TOPIC(nick, chanName, chan->getTopic()));
        }

        // Names reply
        client.sendMessage(RPL_NAMREPLY(nick, chanName, chan->getNamesList()));
        client.sendMessage(RPL_ENDOFNAMES(nick, chanName));
    }
}
