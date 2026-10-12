#include "../../includes/Command.hpp"

void Command::quit(Server& server, Client& client, const std::vector<std::string>& params, const std::string& trailing) {
    std::string reason = "Client Quit";
    if (!trailing.empty()) {
        reason = trailing;
    } else if (!params.empty()) {
        reason = params[0];
    }

    client.setQuitting(true);
    server.disconnectClient(client.getFd(), reason);
}
