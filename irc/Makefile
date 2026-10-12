NAME        = ircserv

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98 -Iincludes

SRCS_DIR    = srcs
OBJS_DIR    = obj

SRCS        = $(SRCS_DIR)/main.cpp \
              $(SRCS_DIR)/Server.cpp \
              $(SRCS_DIR)/Client.cpp \
              $(SRCS_DIR)/Channel.cpp \
              $(SRCS_DIR)/Utils.cpp \
              $(SRCS_DIR)/commands/Command.cpp \
              $(SRCS_DIR)/commands/Pass.cpp \
              $(SRCS_DIR)/commands/Nick.cpp \
              $(SRCS_DIR)/commands/User.cpp \
              $(SRCS_DIR)/commands/Ping.cpp \
              $(SRCS_DIR)/commands/Pong.cpp \
              $(SRCS_DIR)/commands/Quit.cpp \
              $(SRCS_DIR)/commands/Join.cpp \
              $(SRCS_DIR)/commands/Part.cpp \
              $(SRCS_DIR)/commands/Privmsg.cpp \
              $(SRCS_DIR)/commands/Notice.cpp \
              $(SRCS_DIR)/commands/Topic.cpp \
              $(SRCS_DIR)/commands/Mode.cpp \
              $(SRCS_DIR)/commands/Invite.cpp \
              $(SRCS_DIR)/commands/Kick.cpp

OBJS        = $(patsubst $(SRCS_DIR)/%.cpp, $(OBJS_DIR)/%.o, $(SRCS))

# Colors for terminal output
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[✓] Successfully built $(NAME)$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling:$(RESET) $<"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(YELLOW)[✓] Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)[✓] Cleaned $(NAME)$(RESET)"

re: fclean all

.PHONY: all clean fclean re
