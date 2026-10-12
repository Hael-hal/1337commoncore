CC = c++ 

CFLAGS = -Wall -Werror -Wextra -std=c++98

NAME = Serializer

SRCS = main.cpp Serializer.cpp

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f  $(OBJS)

fclean : clean
	rm -f  $(NAME)

re : fclean all


.PHONY : re clean fclean all

