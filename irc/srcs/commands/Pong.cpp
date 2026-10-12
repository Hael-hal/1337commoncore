#include "../../includes/Command.hpp"

void Command::pong(Server& server, Client& client, const std::vector<std::string>& params) {
    (void)server;
    (void)client;
    (void)params;
    // PONG message is acknowledged, no state change required.
}
