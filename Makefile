# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oseng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/28 11:49:03 by oseng             #+#    #+#              #
#    Updated: 2017/06/26 14:28:42 by oseng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GC = clang++

FLAG = -Wall -Wextra -Werror -Wno-c++11-extensions

SRCS = main.cpp factory.cpp calcul.cpp Exception.cpp


NAME = abstractvm

OBJ = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJ)
	@echo "by 👽    AbstractVM 🚀"

		@echo "\033[92mCompiling"
		@$(GC) $(FLAGS) -o $(NAME) $(OBJ)
		@echo "\033[37m->Done"

%.o: %.cpp
	 @$(GC)  $(FLAGS) -c $<

clean:
		@echo "\033[92mDeleting"
		@rm -f $(OBJ)
		@echo "\033[96mClean done"


fclean: clean
		@echo "\033[92mDeleting"
		@rm -f $(NAME)
		@echo "\033[96mFclean Done"

re: fclean all

.PHONY: all clean fclean re
