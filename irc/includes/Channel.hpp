#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <map>
#include <set>
#include <vector>
#include "Client.hpp"

class Channel {
private:
    std::string             _name;
    std::string             _topic;
    std::string             _key;
    size_t                  _userLimit;

    // Modes
    bool                    _isInviteOnly;       // +i
    bool                    _isTopicRestricted;  // +t
    bool                    _hasKey;             // +k
    bool                    _hasUserLimit;       // +l

    // Members
    std::map<int, Client*>  _members;            // fd -> Client*
    std::set<int>           _operators;          // fds with op privileges (+o)
    std::set<int>           _invited;            // fds invited to the channel

public:
    Channel();
    Channel(const std::string& name);
    Channel(const Channel& other);
    Channel& operator=(const Channel& other);
    ~Channel();

    // Getters
    const std::string&            getName() const;
    const std::string&            getTopic() const;
    const std::string&            getKey() const;
    size_t                        getUserLimit() const;
    size_t                        getMemberCount() const;
    const std::map<int, Client*>& getMembers() const;
    std::string                   getModesString() const;
    std::string                   getNamesList() const;

    // Mode status getters
    bool isInviteOnly() const;
    bool isTopicRestricted() const;
    bool hasKey() const;
    bool hasUserLimit() const;

    // Membership / Roles
    bool isMember(int fd) const;
    bool isOperator(int fd) const;
    bool isInvited(int fd) const;

    void addMember(Client* client, bool isOp = false);
    void removeMember(int fd);
    void addOperator(int fd);
    void removeOperator(int fd);
    void addInvite(int fd);
    void removeInvite(int fd);

    // Setters
    void setTopic(const std::string& topic);
    void setKey(const std::string& key);
    void clearKey();
    void setUserLimit(size_t limit);
    void clearUserLimit();
    void setInviteOnly(bool val);
    void setTopicRestricted(bool val);

    // Broadcasting
    void broadcast(const std::string& message, int excludeFd = -1) const;
};

#endif
