# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 11:57:58 by apriego-          #+#    #+#              #
#    Updated: 2023/08/27 20:10:04 by fbosch           ###   ########.fr        #
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
INCLUDE	=	-I./inc #-I./readline
RM		=	rm -fr

#==================FILES===================#

NAME		=	minishell
COMP		=	./libft/libft.a
SRC			=	tokenizer.c tokenizer_utils.c tokenizer_lists.c parser.c
HEADER		=	./inc/minishell.h
LIBFT_ROOT	:=	libft/
RDLINE_ROOT	:=	readline/
DIR_OBJ		:=	temp/
INC_ROOT	:=	inc/
OBJ		=	$(addprefix $(DIR_OBJ),$(SRC:.c=.o))

#==================RULES===================#

LIB_A		:=	$(LIBFT_ROOT)libft.a

LIB_ADD_DIR	:=	-L$(LIBFT_ROOT)

#<-------------------------------->HEADERS<---------------------------------->#
HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(LIBFT_ROOT))

all : temp librarys $(NAME)

librarys :
	@$(MAKE) -C $(LIBFT_ROOT) --no-print-directory

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_ADD_DIR) $(LIB_A) -o $@
	@echo "${GREEN}Minishell Compiled${NC}"

rdline :
	@echo "${YELLOW}Compiling Readline...${NC}"
	@cd ./readline/ &> /dev/null && ./configure &> /dev/null
	@make -C ./readline/ &> /dev/null
	@echo "${GREEN}Readline Compiled${NC}"


$(DIR_OBJ)%.o: %.c
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< -o $@
	@echo "${YELLOW}Compiling obj $@...${NC}"

temp	:
	@mkdir -p $(DIR_OBJ)

clean	:
	@$(MAKE) -C libft clean --no-print-directory
	@$(RM) $(DIR_OBJ)
	@printf "${RED}Objs deleted\n${NC}"

fclean	: clean
	@$(MAKE) -C libft cleaname --no-print-directory
	@$(MAKE) -C readline clean --no-print-directory
	@$(RM) $(NAME)
	@printf "${RED}Minishell deleted\n${NC}"

norm	:
	@printf "${PURPLE}SEARCHING FOR A PRINTF IN THE PROJECT: "
	@printf "%i \n${NC}" $(shell grep "	printf" *.c | wc -l)
	@printf "${YELLOW}Norminette...\n${NC}"
	@printf "${RED}"
	@norminette *.c inc/*.h > test && printf "$(GREEN)\t[OK]\n" || grep Error test
	@printf "${NC}"
	@rm test

re		: fclean all

.PHONY : all clean fclean re librarys rdline
