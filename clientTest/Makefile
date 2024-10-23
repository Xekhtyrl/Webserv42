NAME	=	clientTest

SRCS	=	main.cpp Client.cpp ../srcs/network/ConnectSocket.cpp ../srcs/network/ASocket.cpp
OBJS	=	$(SRCS:.cpp=.o)
INCLUDES=	Client.hpp ../srcs/network/ConnectSocket.hpp ../srcs/network/ASocket.hpp

C		=	c++
CFLAGS	=	-Wall -Werror -Wextra -std=c++98

$(NAME)	:	$(OBJS)
			$(C) $(OBJS) -o $(NAME)

.cpp.o:
		$(C) $(CFLAGS) -I ./  -c $< -o $(<:.cpp=.o)

all		:	$(NAME)

clean	:
			rm -f $(OBJS)
fclean	:	clean
			rm -f $(NAME)
re		:	fclean all

.PHONY	:	all clean fclean re
