# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 11:57:58 by apriego-          #+#    #+#              #
#    Updated: 2023/08/17 11:17:45 by apriego-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==================COLORS==================#

GREEN	=	\033[38;5;154m
RED		=	\033[38;5;197m
PURPLE	=	\033[38;5;171m
BLUE	=	\033[38;5;14m
NC		=	\033[0m
YELLOW	=	\033[38;5;190m

#=================COMMANDS=================#

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I./inc
RM		=	rm -fr

#==================FILES===================#

NAME	=	minishell
COMP	=	./libft/libft.a
SRC		=	minishell.c
HEADER	=	./inc/minishell.h
DIR_OBJ =	temp/
OBJ		=	$(addprefix $(DIR_OBJ),$(SRC:.c=.o))

#==================RULES===================#

all		:	makelib $(NAME)

$(NAME)	: temp $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(COMP) -o $(NAME)
	@printf "${GREEN}Compiled minishell${NC}"

$(DIR_OBJ)%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
	@printf "${YELLOW}Compiling obj $@...${NC}                  	\r"

makelib	:
	@$(MAKE) -C libft --no-print-directory
temp	:
	@mkdir -p $(DIR_OBJ)

clean	:
	@$(MAKE) -C libft clean --no-print-directory
	@$(RM) $(OBJ) $(DIR_OBJ)
	@printf "${RED}Objs deleted\n${NC}"

fclean	: clean
	@$(MAKE) -C libft cleaname --no-print-directory
	@$(RM) $(NAME)
	@printf "${RED}Minishell deleted\n${NC}"

norm	:
	@printf "${PURPLE}SEARCHING FOR A PRINTF IN THE PROJECT: "
	@printf "%i \n${NC}" $(shell grep "	printf" *.c | wc -l)
	@printf "${YELLOW}Norminette...  ${NC}"
	@printf "${RED}"
	@norminette > test && printf "$(GREEN)OK\n" || grep Error test
	@printf "${NC}"
	@rm test
