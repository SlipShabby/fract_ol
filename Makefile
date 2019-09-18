# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajulanov <ajulanov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 19:43:34 by ajulanov          #+#    #+#              #
#    Updated: 2019/09/18 02:14:30 by ajulanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc -o

FLAGS = -Wall -Wextra -Werror -g 
FLAGSMLX = -framework OpenGL -framework AppKit

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
LIBFT_DIR = ./libft/
MLX = ./minilibx_macos/libmlx.a

SRC_FILES = main.c
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
LNK  = -L $(LIBFT_DIR)

GIT = "should make the Norm & test fr leaks"

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

.SILENT:

all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) $@ -c $<

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	printf "$(RESET)%s\n\$(RESET)" "Compiling..."
	@$(CC) $(NAME) $(OBJ) $(LNK) -lm $(LIBFT_DIR)/libft.a $(MLX) $(FLAGSMLX)
	@echo "\n$(NAME): $(GREEN)✔ object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME)✔ was created$(RESET)"

clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)✔ object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)✔ $(NAME) was deleted$(RESET)"
	@make -C $(LIBFT_DIR) fclean
	@echo "$(NAME): $(RED)✔ fcleaned$(RESET)"

re: fclean all

git:
	make fclean
	git add .
	git commit -m '$(GIT)'
	git push
	printf "$(GREEN) ✔  %s\n\$(GREEN)" "Git pushed $(NAME)"
