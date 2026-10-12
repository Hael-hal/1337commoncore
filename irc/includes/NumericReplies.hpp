#ifndef NUMERICREPLIES_HPP
#define NUMERICREPLIES_HPP

#define SERVER_NAME "ft_irc.1337"

// Registration Replies (001 - 004)
#define RPL_WELCOME(nick, user, host) (": " + std::string(SERVER_NAME) + " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n")
#define RPL_YOURHOST(nick) (": " + std::string(SERVER_NAME) + " 002 " + nick + " :Your host is " + SERVER_NAME + ", running version 1.0\r\n")
#define RPL_CREATED(nick, date) (": " + std::string(SERVER_NAME) + " 003 " + nick + " :This server was created " + date + "\r\n")
#define RPL_MYINFO(nick) (": " + std::string(SERVER_NAME) + " 004 " + nick + " " + SERVER_NAME + " 1.0 o itkol\r\n")

// Channel Replies (300 series)
#define RPL_CHANNELMODEIS(nick, channel, modes, params) (": " + std::string(SERVER_NAME) + " 324 " + nick + " " + channel + " " + modes + (std::string(params).empty() ? "" : " " + std::string(params)) + "\r\n")
#define RPL_NOTOPIC(nick, channel) (": " + std::string(SERVER_NAME) + " 331 " + nick + " " + channel + " :No topic is set\r\n")
#define RPL_TOPIC(nick, channel, topic) (": " + std::string(SERVER_NAME) + " 332 " + nick + " " + channel + " :" + topic + "\r\n")
#define RPL_INVITING(nick, target, channel) (": " + std::string(SERVER_NAME) + " 341 " + nick + " " + target + " " + channel + "\r\n")
#define RPL_NAMREPLY(nick, channel, users) (": " + std::string(SERVER_NAME) + " 353 " + nick + " = " + channel + " :" + users + "\r\n")
#define RPL_ENDOFNAMES(nick, channel) (": " + std::string(SERVER_NAME) + " 366 " + nick + " " + channel + " :End of /NAMES list.\r\n")

// Error Replies (400 series)
#define ERR_NOSUCHNICK(nick, target) (": " + std::string(SERVER_NAME) + " 401 " + nick + " " + target + " :No such nick/channel\r\n")
#define ERR_NOSUCHCHANNEL(nick, channel) (": " + std::string(SERVER_NAME) + " 403 " + nick + " " + channel + " :No such channel\r\n")
#define ERR_CANNOTSENDTOCHAN(nick, channel) (": " + std::string(SERVER_NAME) + " 404 " + nick + " " + channel + " :Cannot send to channel\r\n")
#define ERR_NORECIPIENT(nick, cmd) (": " + std::string(SERVER_NAME) + " 411 " + nick + " :No recipient given (" + cmd + ")\r\n")
#define ERR_NOTEXTTOSEND(nick) (": " + std::string(SERVER_NAME) + " 412 " + nick + " :No text to send\r\n")
#define ERR_UNKNOWNCOMMAND(nick, cmd) (": " + std::string(SERVER_NAME) + " 421 " + nick + " " + cmd + " :Unknown command\r\n")
#define ERR_NONICKNAMEGIVEN(nick) (": " + std::string(SERVER_NAME) + " 431 " + nick + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(nick, badnick) (": " + std::string(SERVER_NAME) + " 432 " + nick + " " + badnick + " :Erroneous nickname\r\n")
#define ERR_NICKNAMEINUSE(nick, badnick) (": " + std::string(SERVER_NAME) + " 433 " + nick + " " + badnick + " :Nickname is already in use\r\n")
#define ERR_USERNOTINCHANNEL(nick, target, channel) (": " + std::string(SERVER_NAME) + " 441 " + nick + " " + target + " " + channel + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNEL(nick, channel) (": " + std::string(SERVER_NAME) + " 442 " + nick + " " + channel + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(nick, target, channel) (": " + std::string(SERVER_NAME) + " 443 " + nick + " " + target + " " + channel + " :is already on channel\r\n")
#define ERR_NOTREGISTERED(nick) (": " + std::string(SERVER_NAME) + " 451 " + nick + " :You have not registered\r\n")
#define ERR_NEEDMOREPARAMS(nick, cmd) (": " + std::string(SERVER_NAME) + " 461 " + nick + " " + cmd + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTERED(nick) (": " + std::string(SERVER_NAME) + " 462 " + nick + " :Unauthorized command (already registered)\r\n")
#define ERR_PASSWDMISMATCH(nick) (": " + std::string(SERVER_NAME) + " 464 " + nick + " :Password incorrect\r\n")
#define ERR_KEYSET(nick, channel) (": " + std::string(SERVER_NAME) + " 467 " + nick + " " + channel + " :Channel key already set\r\n")
#define ERR_CHANNELISFULL(nick, channel) (": " + std::string(SERVER_NAME) + " 471 " + nick + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_UNKNOWNMODE(nick, mode) (": " + std::string(SERVER_NAME) + " 472 " + nick + " " + mode + " :is unknown mode char to me\r\n")
#define ERR_INVITEONLYCHAN(nick, channel) (": " + std::string(SERVER_NAME) + " 473 " + nick + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(nick, channel) (": " + std::string(SERVER_NAME) + " 475 " + nick + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_BADCHANMASK(channel) (": " + std::string(SERVER_NAME) + " 476 " + channel + " :Bad Channel Mask\r\n")
#define ERR_NOPRIVILEGES(nick) (": " + std::string(SERVER_NAME) + " 481 " + nick + " :Permission Denied- You're not an IRC operator\r\n")
#define ERR_CHANOPRIVSNEEDED(nick, channel) (": " + std::string(SERVER_NAME) + " 482 " + nick + " " + channel + " :You're not channel operator\r\n")
#define ERR_UMODEUNKNOWNFLAG(nick) (": " + std::string(SERVER_NAME) + " 501 " + nick + " :Unknown MODE flag\r\n")
#define ERR_USERSDONTMATCH(nick) (": " + std::string(SERVER_NAME) + " 502 " + nick + " :Cannot change mode for other users\r\n")

#endif
