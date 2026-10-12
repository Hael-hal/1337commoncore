NAME = whatever
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror --std=c++98
HDR = whatever.hpp

SRCS = main.cpp 
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HDR)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re