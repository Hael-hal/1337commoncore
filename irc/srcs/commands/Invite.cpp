#include "../../includes/Command.hpp"

void Command::invite(Server& server, Client& client, const std::vector<std::string>& params) {
    std::string nick = client.getNickname();

    if (params.size() < 2) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "INVITE"));
        return;
    }

    std::string targetNick = params[0];
    std::string chanName = params[1];

    Client* targetClient = server.getClientByNick(targetNick);
    if (!targetClient) {
        client.sendMessage(ERR_NOSUCHNICK(nick, targetNick));
        return;
    }

    Channel* chan = server.getChannel(chanName);
    if (!chan) {
        client.sendMessage(ERR_NOSUCHCHANNEL(nick, chanName));
        return;
    }

    if (!chan->isMember(client.getFd())) {
        client.sendMessage(ERR_NOTONCHANNEL(nick, chanName));
        return;
    }

    if (chan->isInviteOnly() && !chan->isOperator(client.getFd())) {
        client.sendMessage(ERR_CHANOPRIVSNEEDED(nick, chanName));
        return;
    }

    if (chan->isMember(targetClient->getFd())) {
        client.sendMessage(ERR_USERONCHANNEL(nick, targetNick, chanName));
        return;
    }

    chan->addInvite(targetClient->getFd());
    client.sendMessage(RPL_INVITING(nick, targetNick, chanName));

    std::string inviteMsg = ":" + client.getPrefix() + " INVITE " + targetNick + " :" + chanName + "\r\n";
    targetClient->sendMessage(inviteMsg);
}
