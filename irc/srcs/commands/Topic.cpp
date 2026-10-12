#include "../../includes/Command.hpp"

void Command::topic(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    std::string nick = client.getNickname();

    if (params.empty()) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "TOPIC"));
        return;
    }

    std::string chanName = params[0];
    Channel* chan = server.getChannel(chanName);

    if (!chan) {
        client.sendMessage(ERR_NOSUCHCHANNEL(nick, chanName));
        return;
    }

    if (!chan->isMember(client.getFd())) {
        client.sendMessage(ERR_NOTONCHANNEL(nick, chanName));
        return;
    }

    bool hasNewTopic = !trailing.empty() || params.size() > 1;

    if (!hasNewTopic) {
        // Querying current topic
        if (chan->getTopic().empty()) {
            client.sendMessage(RPL_NOTOPIC(nick, chanName));
        } else {
            client.sendMessage(RPL_TOPIC(nick, chanName, chan->getTopic()));
        }
        return;
    }

    // Setting topic
    if (chan->isTopicRestricted() && !chan->isOperator(client.getFd())) {
        client.sendMessage(ERR_CHANOPRIVSNEEDED(nick, chanName));
        return;
    }

    std::string newTopic = trailing.empty() ? params[1] : trailing;
    chan->setTopic(newTopic);

    std::string topicMsg = ":" + client.getPrefix() + " TOPIC " + chanName + " :" + newTopic + "\r\n";
    chan->broadcast(topicMsg);
}
