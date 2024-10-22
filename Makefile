# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 17:39:37 by alexphil          #+#    #+#              #
#    Updated: 2024/10/22 17:40:23 by alexphil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target executable
TARGET      =	array.x

# C++ Compiler
CXX         =	c++

# Compiler flags
CXXFLAGS    =	-Wall -Wextra -Werror -pedantic -std=c++98 \
#				-Wno-unused-parameter -Wno-unused-variable

DXXFLAGS	=	-Wshadow -Wuninitialized -O0 -g3 \
#				-Wconversion

# Include directories
INCLUDES    =	-I.

# Source files
SRCS        =	main.cpp \
				

# Build directory
BUILD_DIR   =  .build

# Object files placed in the build directory
OBJS        =	$(SRCS:.cpp=.o)
OBJS       :=	$(addprefix $(BUILD_DIR)/, $(OBJS))

# Default rule
all: $(TARGET)
	@echo "$(GRN)[i] $(TARGET) $(DIM) $(CXXFLAGS) $(END)";
	@echo "$(GRN)"
	@echo " ▄▄▄       ██▓    ▓█████ ▒██   ██▒ ██▓███   ██░ ██  ██▓ ██▓    ";
	@echo "▒████▄    ▓██▒    ▓█   ▀ ▒ ██ ▓█ ░▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ";
	@echo "▒██  ▀█▄  ▒██░    ▒███   ░░ ███  ░▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ";
	@echo "░██▄▄▄▄██ ▒██░    ▒▓█  ▄ ░ ▓█ ██ ▒▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ";
	@echo " ▓█   ▓██▒░██████▒░▒████▒▒██▒ ▒██▒▒██▒ ░  ░░▓█▒░██▓░██░░██████▒";
	@echo " ▒▒   ▓▒█░░ ▒░▓  ░░░ ▒░ ░▒▒ ░ ░▓ ░▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░";
	@echo "  ▒   ▒▒ ░░ ░ ▒  ░ ░ ░  ░░░   ░▒ ░░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░";
	@echo "  ░   ▒     ░ ░      ░    ░    ░  ░░        ░  ░░ ░ ▒ ░  ░ ░   ";
	@echo "      ░  ░    ░  ░   ░  ░ ░    ░            ░  ░  ░ ░      ░  ░";
	@echo "$(END)"

# Link object files to create the executable
$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp Makefile
	@mkdir -p $(dir $@)
	@echo "$(YLW)[^] $(notdir $(@)) $(END)";
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@printf "$(UP)$(CUT)"

# Include dependency files
-include $(OBJS:.o=.d)

# Clean build folder and object files
clean:	
	@if [ -d $(BUILD_DIR) ]; then \
		echo "$(RED)[x] $(BUILD_DIR) $(END)"; \
		sleep 0.3; \
		rm -rf $(BUILD_DIR) *.dSYM *_shrubbery; \
		printf "$(UP)$(CUT)"; \
	fi
	

# Full clean including the executable
fclean: clean
	@if [ -f $(TARGET) ]; then \
		echo "$(RED)[x] $(TARGET) $(END)"; \
		sleep 0.3; \
		rm -f $(TARGET); \
		printf "$(UP)$(CUT)"; \
	fi

# Rebuild the project
re: fclean all

# Run the executable with latest changes
run: all
	@./$(TARGET) $(ARGS)

# Run the executable with debug flags through Valgrind
debug: CXXFLAGS += $(DXXFLAGS)
debug: re
	valgrind --leak-check=full --track-origins=yes ./$(TARGET) $(ARGS)
	
# Phony rules
.PHONY: all clean fclean re run debug

# Display Colors
RED		= 	\033[31m
GRN		= 	\033[38;5;85m
YLW		=	\033[33m
DIM		=	\033[2;37m
END		=	\033[0m
UP		=	\033[A
CUT		=	\033[K