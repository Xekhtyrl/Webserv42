NAME = webserv

DIR_SRCS	=	srcs/
DIR_OBJS	=	obj/
DIR_NET		=	network/
DIR_UTI		=	utils/
DIR_REQ		=	HTTPProtocol/
DIR_MET		=	HTTPMethod/
DIR_TEST	=	clientTest/

NETWORK		=	ASocket.cpp BindSocket.cpp ConnectSocket.cpp ListenSocket.cpp Server.cpp
UTILS		=	utils.cpp FileToVar.cpp VarToFile.cpp
METHOD		=	DELETE.cpp GET.cpp POST.cpp
PROTOCOL	=	HTTPReponse.cpp HTTPRequest.cpp HTTPRequestHandler.cpp

SRCS		=	$(addprefix $(DIR_NET), $(NETWORK))		\
				$(addprefix $(DIR_UTI), $(UTILS))		\
				$(addprefix $(DIR_REQ), $(PROTOCOL))	\
				$(addprefix $(DIR_MET), $(METHOD))		\
				main.cpp
PATH_SRCS	=	$(addprefix $(DIR_SRCS), $(SRCS))				

OBJS		=	$(addprefix $(DIR_OBJS), $(SRCS:.cpp=.o))

INCLUDE = -I . -I includes/ -I $(DIR_SRCS)$(DIR_MET) -I $(DIR_SRCS)$(DIR_NET) -I $(DIR_SRCS)$(DIR_REQ) -I $(DIR_SRCS)$(DIR_UTI)

C_GREEN = \033[0;32m

C_RED = \033[0;31m

C_BLUE = \033[0;34m

C_BPURP = \033[1;35m

C_END=\033[0m

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME):  $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(C_GREEN)$(NAME) compiled with $(C_BPURP)$(CFLAGS)$(C_END)"


$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(DIR_OBJS)
	@echo "$(C_RED)$(NAME) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	bash ~/Cleaner_42.sh
	@echo "$(C_RED)Update: Herobrine has been removed.$(C_END)"

re: fclean all

debug: CFLAGS += -fsanitize=address -g3
debug: re

add:
	@if [ -z "$(MSG)" ]; then \
		read -p "Enter commit message: " msg; \
		git add Makefile $(PATH_SRCS) webdata error/*.html includes .gitignore; \
		git commit -m "$$msg"; \
	else \
		git add Makefile $(PATH_SRCS) webdata error/*.html includes .gitignore; \
		git commit -m "$(MSG)"; \
	fi; \
	git push

.PHONY: all clean fclean re add debug
# NAME		=	webserv

# DIR_SRCS	=	srcs/
# DIR_OBJS	=	obj/
# DIR_NET		=	network/

# NETWORK		=	ASocket.cpp BindSocket.cpp ConnectSocket.cpp ListenSocket.cpp Server.cpp


# SRCS		=	$(addprefix $(DIR_NET), $(NETWORK)) \
# 				main.cpp
# PATH_SRCS	=	$(addprefix $(DIR_SRCS), $(SRCS))				

# OBJS		=	$(addprefix $(DIR_OBJS), $(notdir $(SRCS:.cpp=.o)))

# C		=	c++
# CFLAGS	=	-Wall -Werror -Wextra -std=c++98

# $(NAME)	:	$(OBJS)
# 			$(C) $(OBJS) -o $(NAME)

# $(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
# 			@mkdir -p $(DIR_OBJS)
# 			$(C) $(CFLAGS) -I $(DIR_SRCS) -I $(DIR_NET) -c $< -o $@


# $(DIR_OBJS)%.o: $(DIR_SRCS)$(DIR_NET)%.cpp
# 			@mkdir -p $(DIR_OBJS)
# 			$(C) $(CFLAGS) -I $(DIR_SRCS) -I $(DIR_NET) -c $< -o $@

# all		:	$(NAME)

# clean	:
# 			rm -rf $(DIR_OBJS)

# fclean	:	clean
# 			rm -f $(NAME) 

# re		:	fclean all
# >>>>>>> oli
