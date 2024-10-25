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
# =======
# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2024/10/22 17:39:37 by alexphil          #+#    #+#              #
# #    Updated: 2024/10/24 18:25:42 by alexphil         ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# # Target executable
# TARGET      =	conf

# # C++ Compiler
# CXX         =	c++

# # Compiler flags
# CXXFLAGS    =	-Wall -Wextra -Werror -pedantic -std=c++98 \
# #				-Wno-unused-parameter -Wno-unused-variable

# DXXFLAGS	=	-Wshadow -Wuninitialized -O0 -g3 \
# #				-Wconversion

# # Include directories
# INCLUDES    =	-I.

# # Source files
# SRCS        =	main.cpp \
				

# # Build directory
# BUILD_DIR   =  .build

# # Object files placed in the build directory
# OBJS        =	$(SRCS:.cpp=.o)
# OBJS       :=	$(addprefix $(BUILD_DIR)/, $(OBJS))

# # Default rule
# all: $(TARGET)
# 	@echo "$(GRN)[i] $(TARGET) $(DIM) $(CXXFLAGS) $(END)";
# 	@echo "$(GRN)"
# 	@echo " ▄▄▄       ██▓    ▓█████ ▒██   ██▒ ██▓███   ██░ ██  ██▓ ██▓    ";
# 	@echo "▒████▄    ▓██▒    ▓█   ▀ ▒ ██ ▓█ ░▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ";
# 	@echo "▒██  ▀█▄  ▒██░    ▒███   ░░ ███  ░▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ";
# 	@echo "░██▄▄▄▄██ ▒██░    ▒▓█  ▄ ░ ▓█ ██ ▒▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ";
# 	@echo " ▓█   ▓██▒░██████▒░▒████▒▒██▒ ▒██▒▒██▒ ░  ░░▓█▒░██▓░██░░██████▒";
# 	@echo " ▒▒   ▓▒█░░ ▒░▓  ░░░ ▒░ ░▒▒ ░ ░▓ ░▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░";
# 	@echo "  ▒   ▒▒ ░░ ░ ▒  ░ ░ ░  ░░░   ░▒ ░░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░";
# 	@echo "  ░   ▒     ░ ░      ░    ░    ░  ░░        ░  ░░ ░ ▒ ░  ░ ░   ";
# 	@echo "      ░  ░    ░  ░   ░  ░ ░    ░            ░  ░  ░ ░      ░  ░";
# 	@echo "$(END)"

# # Link object files to create the executable
# $(TARGET): $(OBJS)
# 	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# # Compile source files into object files
# $(BUILD_DIR)/%.o: %.cpp Makefile
# 	@mkdir -p $(dir $@)
# 	@echo "$(YLW)[^] $(notdir $(@)) $(END)";
# 	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
# 	@printf "$(UP)$(CUT)"

# # Include dependency files
# -include $(OBJS:.o=.d)

# # Clean build folder and object files
# clean:	
# 	@if [ -d $(BUILD_DIR) ]; then \
# 		echo "$(RED)[x] $(BUILD_DIR) $(END)"; \
# 		sleep 0.3; \
# 		rm -rf $(BUILD_DIR) *.dSYM *_shrubbery; \
# 		printf "$(UP)$(CUT)"; \
# 	fi
	

# # Full clean including the executable
# fclean: clean
# 	@if [ -f $(TARGET) ]; then \
# 		echo "$(RED)[x] $(TARGET) $(END)"; \
# 		sleep 0.3; \
# 		rm -f $(TARGET); \
# 		printf "$(UP)$(CUT)"; \
# 	fi

# # Rebuild the project
# re: fclean all

# # Run the executable with latest changes
# run: all
# 	@./$(TARGET) $(ARGS)

# # Run the executable with debug flags through Valgrind
# debug: CXXFLAGS += $(DXXFLAGS)
# debug: re
# 	valgrind --leak-check=full --track-origins=yes ./$(TARGET) $(ARGS)
	
# # Phony rules
# .PHONY: all clean fclean re run debug

# # Display Colors
# RED		= 	\033[31m
# GRN		= 	\033[38;5;85m
# YLW		=	\033[33m
# DIM		=	\033[2;37m
# END		=	\033[0m
# UP		=	\033[A
# CUT		=	\033[K
# >>>>>>> alexphil
