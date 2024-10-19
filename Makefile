NAME		=	webserv

DIR_SRCS	=	srcs/
DIR_OBJS	=	obj/
DIR_NET		=	network/

NETWORK		=	ASocket.cpp BindSocket.cpp ConnectSocket.cpp ListenSocket.cpp Server.cpp


SRCS		=	$(addprefix $(DIR_NET), $(NETWORK)) \
				main.cpp
PATH_SRCS	=	$(addprefix $(DIR_SRCS), $(SRCS))				

OBJS		=	$(addprefix $(DIR_OBJS), $(notdir $(SRCS:.cpp=.o)))

C		=	c++
CFLAGS	=	-Wall -Werror -Wextra -std=c++98

$(NAME)	:	$(OBJS)
			$(C) $(OBJS) -o $(NAME)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
			@mkdir -p $(DIR_OBJS)
			$(C) $(CFLAGS) -I $(DIR_SRCS) -I $(DIR_NET) -c $< -o $@


$(DIR_OBJS)%.o: $(DIR_SRCS)$(DIR_NET)%.cpp
			@mkdir -p $(DIR_OBJS)
			$(C) $(CFLAGS) -I $(DIR_SRCS) -I $(DIR_NET) -c $< -o $@

all		:	$(NAME)

clean	:
			rm -rf $(DIR_OBJS)

fclean	:	clean
			rm -f $(NAME) 

re		:	fclean all

.PHONY: all clean fclean re