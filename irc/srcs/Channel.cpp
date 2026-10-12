#include "../includes/Channel.hpp"
#include <sstream>

Channel::Channel()
    : _name(""), _topic(""), _key(""), _userLimit(0),
      _isInviteOnly(false), _isTopicRestricted(true), _hasKey(false), _hasUserLimit(false) {}

Channel::Channel(const std::string& name)
    : _name(name), _topic(""), _key(""), _userLimit(0),
      _isInviteOnly(false), _isTopicRestricted(true), _hasKey(false), _hasUserLimit(false) {}

Channel::Channel(const Channel& other) {
    *this = other;
}

Channel& Channel::operator=(const Channel& other) {
    if (this != &other) {
        _name = other._name;
        _topic = other._topic;
        _key = other._key;
        _userLimit = other._userLimit;
        _isInviteOnly = other._isInviteOnly;
        _isTopicRestricted = other._isTopicRestricted;
        _hasKey = other._hasKey;
        _hasUserLimit = other._hasUserLimit;
        _members = other._members;
        _operators = other._operators;
        _invited = other._invited;
    }
    return *this;
}

Channel::~Channel() {}

const std::string& Channel::getName() const {
    return _name;
}

const std::string& Channel::getTopic() const {
    return _topic;
}

const std::string& Channel::getKey() const {
    return _key;
}

size_t Channel::getUserLimit() const {
    return _userLimit;
}

size_t Channel::getMemberCount() const {
    return _members.size();
}

const std::map<int, Client*>& Channel::getMembers() const {
    return _members;
}

std::string Channel::getModesString() const {
    std::string modes = "+";
    if (_isInviteOnly) modes += "i";
    if (_isTopicRestricted) modes += "t";
    if (_hasKey) modes += "k";
    if (_hasUserLimit) modes += "l";
    return modes.length() > 1 ? modes : "";
}

std::string Channel::getNamesList() const {
    std::string list = "";
    for (std::map<int, Client*>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        if (!list.empty())
            list += " ";
        if (isOperator(it->first))
            list += "@";
        list += it->second->getNickname();
    }
    return list;
}

bool Channel::isInviteOnly() const {
    return _isInviteOnly;
}

bool Channel::isTopicRestricted() const {
    return _isTopicRestricted;
}

bool Channel::hasKey() const {
    return _hasKey;
}

bool Channel::hasUserLimit() const {
    return _hasUserLimit;
}

bool Channel::isMember(int fd) const {
    return _members.find(fd) != _members.end();
}

bool Channel::isOperator(int fd) const {
    return _operators.find(fd) != _operators.end();
}

bool Channel::isInvited(int fd) const {
    return _invited.find(fd) != _invited.end();
}

void Channel::addMember(Client* client, bool isOp) {
    if (!client) return;
    int fd = client->getFd();
    _members[fd] = client;
    if (isOp || _members.size() == 1) {
        addOperator(fd);
    }
    removeInvite(fd);
}

void Channel::removeMember(int fd) {
    _members.erase(fd);
    _operators.erase(fd);
    _invited.erase(fd);
}

void Channel::addOperator(int fd) {
    _operators.insert(fd);
}

void Channel::removeOperator(int fd) {
    _operators.erase(fd);
}

void Channel::addInvite(int fd) {
    _invited.insert(fd);
}

void Channel::removeInvite(int fd) {
    _invited.erase(fd);
}

void Channel::setTopic(const std::string& topic) {
    _topic = topic;
}

void Channel::setKey(const std::string& key) {
    _key = key;
    _hasKey = !key.empty();
}

void Channel::clearKey() {
    _key = "";
    _hasKey = false;
}

void Channel::setUserLimit(size_t limit) {
    _userLimit = limit;
    _hasUserLimit = (limit > 0);
}

void Channel::clearUserLimit() {
    _userLimit = 0;
    _hasUserLimit = false;
}

void Channel::setInviteOnly(bool val) {
    _isInviteOnly = val;
}

void Channel::setTopicRestricted(bool val) {
    _isTopicRestricted = val;
}

void Channel::broadcast(const std::string& message, int excludeFd) const {
    for (std::map<int, Client*>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        if (it->first != excludeFd && it->second) {
            it->second->sendMessage(message);
        }
    }
}
