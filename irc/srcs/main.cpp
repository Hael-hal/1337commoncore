#include <iostream>
#include <cstdlib>
#include <csignal>
#include "../includes/Server.hpp"
#include "../includes/Utils.hpp"

static bool isValidPort(const std::string& portStr, int& port) {
    if (portStr.empty()) return false;
    for (size_t i = 0; i < portStr.length(); ++i) {
        if (!std::isdigit(portStr[i])) return false;
    }
    long p = std::atol(portStr.c_str());
    if (p < 1024 || p > 65535) return false;
    port = static_cast<int>(p);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        std::cerr << "Example: " << argv[0] << " 6667 mysecretpass" << std::endl;
        return 1;
    }

    int port = 0;
    if (!isValidPort(argv[1], port)) {
        std::cerr << "Error: Invalid port number '" << argv[1] << "'. Port must be an integer between 1024 and 65535." << std::endl;
        return 1;
    }

    std::string password = argv[2];
    if (password.empty()) {
        std::cerr << "Error: Password cannot be empty." << std::endl;
        return 1;
    }

    // Ignore SIGPIPE to avoid crashing when writing to a closed socket
    std::signal(SIGPIPE, SIG_IGN);

    // Setup termination signal handlers
    std::signal(SIGINT, Server::signalHandler);
    std::signal(SIGQUIT, Server::signalHandler);

    try {
        Server server(port, password);
        server.init();
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "[Fatal Error] " << e.what() << std::endl;
        return 1;
    }

    std::cout << "[Server] Exiting successfully." << std::endl;
    return 0;
}
