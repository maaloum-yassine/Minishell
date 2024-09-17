# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 20:13:51 by ymaaloum          #+#    #+#              #
#    Updated: 2024/09/17 07:02:56 by ymaaloum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =	main.c \
		signal.c \
		minishell_utlis/minishell_utlis1.c \
		minishell_utlis/minishell_utlis2.c \
		minishell_utlis/minishell_utlis3.c \
		minishell_utlis/minishell_utlis4.c \
		check_syntax/check_syntax1.c \
		check_syntax/check_syntax2.c \
		divide_cmd.c \
		handle_env.c \
		expand/expand_utils.c \
		expand/expand_utils1.c \
		expand/expand_utils2.c \
		expand/expand_utils3.c \
		expand/expand_utils4.c \
		expand/update_struct1.c \
		expand/update_struct2.c \
		expand/update_struct3.c \
		expand/update_struct4.c \
		expand/handl_quote1.c \
		expand/handl_quote2.c \
		builtins/check_builtins.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/pwd.c \
		builtins/unset.c \
		builtins/cd.c \
		builtins/export.c \
		builtins/exit.c \
		builtins/export_utlis1.c \
		builtins/export_utlis2.c \
		handl_redirection/handl_redirection1.c \
		handl_redirection/handl_redirection2.c \
		handl_redirection/handl_redirection3.c \
		handl_redirection/handl_redirection4.c \
		execution/ft_exec_cmd.c \
		execution/ft_path_command.c \
		execution/ft_redirection.c \
		execution/ft_utils1_exec.c \
		execution/ft_utils2_exec.c \
		execution/ft_utils1_redirecrtion.c \
		execution/ft_utils2_redirection.c \
		execution/ft_utils3_redirection.c \
		execution/ft_utils3_exec.c \


NAME = minishell
REDLINE= $(shell brew --prefix readline)
RDLIB = -lreadline -L $(REDLINE)/lib
RDINCLUD = -I $(REDLINE)/include
OBJ = $(SRC:.c=.o)

%.o: %.c
		$(CC) $(CFLAGS) -c  $< -o $@ $(RDINCLUD)

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RDLIB)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
