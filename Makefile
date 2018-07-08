# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 14:34:33 by knovytsk          #+#    #+#              #
#    Updated: 2018/01/24 14:34:35 by knovytsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRCS_PATH = srcs
OBJS_PATH = objs

SRCS = main.c get_map_data.c map_validation.c errors.c initialize.c image.c rendering.c\
		textures.c draw_scene.c hook.c menu_mode_events.c move_events.c view_events.c\
		exit.c moves.c draw_walls.c draw_sky_floor.c
OBJS = $(addprefix $(OBJS_PATH)/,$(SRCS:.c=.o))
INCLUDES = -I includes
LIBFT = -C libft

CC = gcc -Wall -Wextra -Werror
FLAGS = -lmlx -framework OpenGL -framework AppKit -Ofast -O3

all: $(NAME)

$(OBJS): | $(OBJS_PATH)

$(OBJS_PATH):
	@mkdir $(OBJS_PATH)

$(OBJS_PATH)/%.o: %.c
	@$(CC) -c $< $(INCLUDES) -o $@

$(NAME): $(OBJS)
	@echo "\033[33;1mCompilation of libft...\033[0m"
	@make $(LIBFT)
	@$(CC) -o $(NAME) $(OBJS) libft/libft.a $(FLAGS)
	@echo "\033[36;1mENJOY THE GAME\033[0m"

clean:
	@make clean -C libft
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf bin objs

fclean: clean
	@/bin/rm -f libft/libft.a
	@/bin/rm -f $(NAME)
	@echo "\033[32;1mCleaned\033[0m"

re: fclean all

vpath %.c $(SRCS_PATH)

.PHONY: clean fclean re all