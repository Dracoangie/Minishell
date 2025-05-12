# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angnavar <angnavar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 10:57:18 by angnavar          #+#    #+#              #
#    Updated: 2025/05/12 15:12:57 by angnavar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.out

# Source and object files
SRC = main.c src/Minishell.c src/Errors.c \
	src/Parse/Parse_input.c src/Parse/Parse_files.c src/Parse/Here_doc.c \
	src/Parse/Parse_quotes.c src/Parse/Parse_to_cmds.c \
	src/Exec/Cmds.c  src/Exec/Exec_cmds.c \
	src/Utils/Utils_0.c src/Utils/Utils_1.c \
	src/Free/Free_shell.c src/Free/Free_input.c \
	src/builtins/builtins.c src/builtins/builtins_utils.c src/builtins/Echo.c
OBJ_DIR = obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

# Library and include directories
INCLUDE_DIR := includes
LIBFT_DIR   := includes/libft
LIBFT       := $(LIBFT_DIR)/libft.a
LDLIBS = -lreadline

# Compiler and flags
CC = cc
RM = rm -f
RMDIR = rm -rf
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

# ===================================== BANNER =================================== #

define banner
@echo "\033[0;34m"
@echo '            _       _     _          _ _ '
@echo '           (_)     (_)   | |        | | |'
@echo '  _ __ ___  _ _ __  _ ___| |__   ___| | |'
@echo ' |  _   _ \| |  _ \| / __|  _ \ / _ \ | |'
@echo ' | | | | | | | | | | \__ \ | | |  __/ | |'
@echo ' |_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|'
@echo "\033[0m"
endef

# =============================== MAIN TARGET =================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(banner)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDLIBS) -o $(NAME)
	@echo "\033[0;32m▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄ Build completed. ▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄\033[0m"

# =========================== LIBFT COMPILATION ============================== #

$(LIBFT):
	@echo "📦 Checking libft..."
	@$(MAKE) -s -C $(LIBFT_DIR) --no-print-directory

# ============================= FILE COMPILATION =============================== #

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "\033[0;34m⚙️  Compiling $<...\033[0m"
	@$(CC) $(CFLAGS)  -c $< -o $@

# ================================ CLEANING ===================================== #

clean:
	@echo "\033[0;35m🧹 Cleaning object files...\033[0m"
	@$(MAKE) -s -C $(LIBFT_DIR) clean --no-print-directory
	@$(RMDIR) $(OBJ_DIR)

fclean: clean
	@echo "\033[0;35m🗑️  Removing executables...\033[0m"
	@$(MAKE) -s -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) $(NAME)
	@$(RM) $(NAME)_asan

re: fclean all

# ============================== EXECUTION RULE ================================= #

run: all
	@echo "\033[0;36m🚀 Running program...\033[0m"
	@./$(NAME)

# ====================== ADDRESSSANITIZER TARGETS ============================== #

$(NAME)_asan: $(LIBFT) $(OBJ)
	$(banner)
	@echo "\033[0;33m🧪 Linking with AddressSanitizer...\033[0m"
	@$(CC) $(CFLAGS) -g -fsanitize=address $(OBJ) $(LIBFT) $(LDLIBS) -o $(NAME)_asan
	@echo "\033[0;32m▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄ ASan build ready ▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄\033[0m"

asan: $(NAME)_asan

runasan: $(NAME)_asan
	@echo "\033[0;36m🚀 Running with ASan...\033[0m"
	@./$(NAME)_asan

.PHONY: all clean fclean re run asan runasan
