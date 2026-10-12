#include "../../includes/Command.hpp"

void Command::kick(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    std::string nick = client.getNickname();

    if (params.size() < 2) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "KICK"));
        return;
    }

    std::string chanName = params[0];
    std::string targetNick = params[1];
    std::string reason = trailing.empty() ? "Kicked by operator" : trailing;

    Channel* chan = server.getChannel(chanName);
    if (!chan) {
        client.sendMessage(ERR_NOSUCHCHANNEL(nick, chanName));
        return;
    }

    if (!chan->isMember(client.getFd())) {
        client.sendMessage(ERR_NOTONCHANNEL(nick, chanName));
        return;
    }

    if (!chan->isOperator(client.getFd())) {
        client.sendMessage(ERR_CHANOPRIVSNEEDED(nick, chanName));
        return;
    }

    Client* targetClient = server.getClientByNick(targetNick);
    if (!targetClient || !chan->isMember(targetClient->getFd())) {
        client.sendMessage(ERR_USERNOTINCHANNEL(nick, targetNick, chanName));
        return;
    }

    std::string kickMsg = ":" + client.getPrefix() + " KICK " + chanName + " " + targetNick + " :" + reason + "\r\n";
    chan->broadcast(kickMsg);
    chan->removeMember(targetClient->getFd());

    if (chan->getMemberCount() == 0) {
        server.removeChannel(chanName);
    }
}
