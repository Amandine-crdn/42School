SRCS	= main.cpp  Brain.cpp AAnimal.cpp Dog.cpp Cat.cpp 

OBJS	= $(SRCS:.cpp=.o)

NAME	= Abstract

CLANG	= c++

FLAGS	= -Wall -Wextra -Werror -std=c++98


all:	$(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.cpp
	$(CLANG) $(FLAGS) -c $<  -o $(<:.cpp=.o)

.PHONY:	 all, clean, fclean, re