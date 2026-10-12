#include "../../includes/Command.hpp"
#include <cstdlib>

void Command::mode(Server& server, Client& client, const std::vector<std::string>& params) {
    std::string nick = client.getNickname();

    if (params.empty()) {
        client.sendMessage(ERR_NEEDMOREPARAMS(nick, "MODE"));
        return;
    }

    std::string target = params[0];

    // If target is user mode
    if (target[0] != '#' && target[0] != '&') {
        if (target != nick) {
            client.sendMessage(ERR_USERSDONTMATCH(nick));
            return;
        }
        // Return or ignore user mode
        return;
    }

    // Channel mode
    Channel* chan = server.getChannel(target);
    if (!chan) {
        client.sendMessage(ERR_NOSUCHCHANNEL(nick, target));
        return;
    }

    if (params.size() == 1) {
        client.sendMessage(RPL_CHANNELMODEIS(nick, target, chan->getModesString(), ""));
        return;
    }

    if (!chan->isOperator(client.getFd())) {
        client.sendMessage(ERR_CHANOPRIVSNEEDED(nick, target));
        return;
    }

    std::string modeString = params[1];
    size_t paramIdx = 2;
    char sign = '+';
    std::string appliedModes = "";
    std::string appliedParams = "";

    for (size_t i = 0; i < modeString.length(); ++i) {
        char c = modeString[i];
        if (c == '+' || c == '-') {
            sign = c;
            continue;
        }

        if (c == 'i') {
            chan->setInviteOnly(sign == '+');
            appliedModes += sign;
            appliedModes += 'i';
        } else if (c == 't') {
            chan->setTopicRestricted(sign == '+');
            appliedModes += sign;
            appliedModes += 't';
        } else if (c == 'k') {
            if (sign == '+') {
                if (paramIdx >= params.size()) {
                    client.sendMessage(ERR_NEEDMOREPARAMS(nick, "MODE +k"));
                    continue;
                }
                std::string key = params[paramIdx++];
                chan->setKey(key);
                appliedModes += "+k";
                if (!appliedParams.empty()) appliedParams += " ";
                appliedParams += key;
            } else {
                chan->clearKey();
                appliedModes += "-k";
                if (paramIdx < params.size()) paramIdx++; // consume optional key if provided
            }
        } else if (c == 'o') {
            if (paramIdx >= params.size()) {
                client.sendMessage(ERR_NEEDMOREPARAMS(nick, "MODE +o/-o"));
                continue;
            }
            std::string targetNick = params[paramIdx++];
            Client* targetClient = server.getClientByNick(targetNick);
            if (!targetClient || !chan->isMember(targetClient->getFd())) {
                client.sendMessage(ERR_USERNOTINCHANNEL(nick, targetNick, target));
                continue;
            }
            if (sign == '+') {
                chan->addOperator(targetClient->getFd());
            } else {
                chan->removeOperator(targetClient->getFd());
            }
            appliedModes += sign;
            appliedModes += 'o';
            if (!appliedParams.empty()) appliedParams += " ";
            appliedParams += targetNick;
        } else if (c == 'l') {
            if (sign == '+') {
                if (paramIdx >= params.size()) {
                    client.sendMessage(ERR_NEEDMOREPARAMS(nick, "MODE +l"));
                    continue;
                }
                int limit = std::atoi(params[paramIdx++].c_str());
                if (limit > 0) {
                    chan->setUserLimit(static_cast<size_t>(limit));
                    appliedModes += "+l";
                    if (!appliedParams.empty()) appliedParams += " ";
                    appliedParams += Utils::toString(limit);
                }
            } else {
                chan->clearUserLimit();
                appliedModes += "-l";
            }
        } else {
            std::string modeChar(1, c);
            client.sendMessage(ERR_UNKNOWNMODE(nick, modeChar));
        }
    }

    if (!appliedModes.empty()) {
        std::string modeMsg = ":" + client.getPrefix() + " MODE " + target + " " + appliedModes;
        if (!appliedParams.empty()) {
            modeMsg += " " + appliedParams;
        }
        modeMsg += "\r\n";
        chan->broadcast(modeMsg);
    }
}
