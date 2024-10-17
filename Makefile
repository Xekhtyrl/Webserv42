NAME = webserv

SRC =	HTTPReponse.cpp	\
		HTTPRequest.cpp		\
		utils.cpp			\
		test.cpp

INCLUDE = -I .

OBJ = $(SRC:.cpp=.o)

C_GREEN = \033[0;32m

C_RED = \033[0;31m

C_BLUE = \033[0;34m

C_BPURP = \033[1;35m

C_END=\033[0m

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(C_GREEN)$(NAME) compiled with $(C_BPURP)$(CFLAGS)$(C_END)"

%.o:	%.cpp
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "$(C_RED)$(NAME) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	bash ~/Cleaner_42.sh
	@echo "$(C_RED)Update: Herobrine has been removed.$(C_END)"

re: fclean all

debug: re
debug: CFLAGS += -fsanitize=address -g3

add:
	@if [ -z "$(MSG)" ]; then \
		read -p "Enter commit message: " msg; \
		git add Makefile $(SRC) *.hpp .gitignore; \
		git commit -m "$$msg"; \
	else \
		git add Makefile $(SRC) *.hpp .gitignore; \
		git commit -m "$(MSG)"; \
	fi; \
	git push

.PHONY: all clean fclean re