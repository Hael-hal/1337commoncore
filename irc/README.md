# ft_irc - Internet Relay Chat Server (42 School)

An RFC 1459 / RFC 2812 compliant Internet Relay Chat (IRC) server written in **C++ 98** as part of the 42 School curriculum.

---

## 🛠 Features (Mandatory Part)

- **C++98 Standard Compliance**: Compiled with `-Wall -Wextra -Werror -std=c++98`.
- **Non-blocking I/O & Multiplexing**: Single `poll()` event loop handling all client connections and incoming network events.
- **Client Authentication**:
  - `PASS`: Server password verification.
  - `NICK`: Nickname registration and change handling with collision checks.
  - `USER`: User metadata configuration (username, realname).
  - Welcome sequence with IRC numeric replies (`001`, `002`, `003`, `004`).
- **Channel Operations**:
  - `JOIN`: Join or create channels (creator automatically becomes channel operator `@`).
  - `PART`: Leave channels with optional custom reason.
  - `TOPIC`: View or change channel topic (operator-restricted under mode `+t`).
  - `INVITE`: Invite users to channels (required for invite-only channels `+i`).
  - `KICK`: Eject users from a channel (operator privilege required).
  - `MODE`: Channel mode management:
    - `i`: Set/remove Invite-only channel.
    - `t`: Set/remove operator restrictions on the `TOPIC` command.
    - `k`: Set/remove channel key (password).
    - `o`: Give/take channel operator privilege.
    - `l`: Set/remove channel user limit.
- **Messaging**:
  - `PRIVMSG`: Direct messages to users or broadcast to channel members.
  - `NOTICE`: Automated messaging without error replies.
- **Connection Management**:
  - `PING` / `PONG`: Keepalive and latency verification.
  - `QUIT`: Graceful disconnection and broadcast of quit reasons.
  - Signal handling: Clean shutdown on `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\\).

---

## 📁 Directory Structure

```
ft_irc/
├── Makefile
├── README.md
├── includes/
│   ├── Server.hpp          # Socket initialization, poll loop, client/channel tables
│   ├── Client.hpp          # Client metadata, fd, buffers, auth status
│   ├── Channel.hpp         # Channel membership, operators, topics, modes (+itkol)
│   ├── Command.hpp         # Command dispatcher and command handler prototypes
│   ├── NumericReplies.hpp  # Standard IRC RFC 1459/2812 replies & errors
│   └── Utils.hpp           # Helpers (split, trim, case conversion, validation)
└── srcs/
    ├── main.cpp            # Entry point, argument validation, signal handling
    ├── Server.cpp          # Server implementation, pollfd management, accept/recv
    ├── Client.cpp          # Client buffers and message sending
    ├── Channel.cpp         # Channel members, broadcasting, and modes
    ├── Utils.cpp           # String and time utilities
    └── commands/
        ├── Command.cpp     # Command parser and dispatcher
        ├── Pass.cpp        # PASS & CAP handler
        ├── Nick.cpp        # NICK handler
        ├── User.cpp        # USER handler
        ├── Ping.cpp        # PING handler
        ├── Pong.cpp        # PONG handler
        ├── Quit.cpp        # QUIT handler
        ├── Join.cpp        # JOIN handler
        ├── Part.cpp        # PART handler
        ├── Privmsg.cpp     # PRIVMSG handler
        ├── Notice.cpp      # NOTICE handler
        ├── Topic.cpp       # TOPIC handler
        ├── Mode.cpp        # MODE handler (+i, +t, +k, +o, +l)
        ├── Invite.cpp      # INVITE handler
        └── Kick.cpp        # KICK handler
```

---

## 🚀 Getting Started

### 1. Compilation
Run `make` to compile the executable:
```bash
make
```

### 2. Running the Server
Launch the server specifying a port (1024-65535) and a password:
```bash
./ircserv 6667 password123
```

---

## 🧪 Testing

### Option A: Using `nc` (Netcat)
In a terminal:
```bash
nc -C 127.0.0.1 6667
```
*(Or `nc 127.0.0.1 6667` on macOS)*

Authenticate and test commands:
```irc
PASS password123
NICK user42
USER user42 0 * :Student 42
JOIN #general
PRIVMSG #general :Hello from Netcat!
TOPIC #general :Welcome to 42 IRC
MODE #general +i
PART #general :Leaving now
QUIT :Goodbye
```

### Option B: Using `Irssi`
In another terminal:
```bash
irssi
```
Inside Irssi:
```irc
/connect 127.0.0.1 6667 password123 user42
/join #general
/msg #general Hello from Irssi!
```

---

## 📋 Available Commands Summary

| Command | Syntax | Description |
| :--- | :--- | :--- |
| `PASS` | `PASS <password>` | Authenticates connection with the server password |
| `NICK` | `NICK <nickname>` | Sets or changes client nickname |
| `USER` | `USER <username> <hostname> <server> :<realname>` | Sets client username and real name |
| `JOIN` | `JOIN <#channel> [<key>]` | Joins or creates a channel |
| `PART` | `PART <#channel> [:<reason>]` | Leaves a channel |
| `PRIVMSG` | `PRIVMSG <target> :<message>` | Sends a private message to a user or channel |
| `NOTICE` | `NOTICE <target> :<message>` | Sends a notice without error replies |
| `MODE` | `MODE <#channel> <modes> [<args>]` | Sets channel modes (`+i`, `+t`, `+k`, `+o`, `+l`) |
| `TOPIC` | `TOPIC <#channel> [:<newtopic>]` | Queries or sets the channel topic |
| `INVITE` | `INVITE <nickname> <#channel>` | Invites a user to a channel |
| `KICK` | `KICK <#channel> <nickname> [:<reason>]` | Ejects a user from a channel |
| `PING` | `PING <token>` | Checks server responsiveness |
| `PONG` | `PONG <token>` | Responds to ping |
| `QUIT` | `QUIT [:<reason>]` | Disconnects from the server |
