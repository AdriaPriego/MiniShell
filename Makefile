# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 11:57:58 by apriego-          #+#    #+#              #
#    Updated: 2023/08/31 16:34:14 by fbosch           ###   ########.fr        #
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
INCLUDE	=	-I./inc -I./readline
RM		=	rm -fr

#==================FILES===================#

NAME		=	minishell
COMP		=	./libft/libft.a

FILES_ENTRY	=	entry.c signals.c
FILES_BUILT	=	built_ins.c built_ins2.c
FILES_GEN	=	main.c utils.c
FILES_LEXER	=	tokenizer.c tokenizer_utils.c tokenizer_lists.c
EXPAN_GEN	=	expansor.c
HEADER		=	./inc/minishell.h
LIBFT_ROOT	:=	libft/
RDLINE_ROOT	:=	readline/
DIR_OBJ		:=	temp/
INC_ROOT	:=	inc/
SRC_DIR		=	src/
ENTRY_DIR	=	entry/
BUILT_DIR	=	built-ins/
LEXER_DIR	=	lexer/
PARSER_DIR	=	parser/
EXPAN_DIR	=	expansor/
EXEC_DIR	=	executor/

SRC_EXPAN	=	$(addprefix $(SRC_DIR),$(addprefix $(EXPAN_DIR),$(FILES_EXPAN)))
SRC_ENTRY	=	$(addprefix $(SRC_DIR),$(addprefix $(ENTRY_DIR),$(FILES_ENTRY)))
SRC_BUILT	=	$(addprefix $(SRC_DIR),$(addprefix $(BUILT_DIR),$(FILES_BUILT)))
SRC_LEXER	=	$(addprefix $(SRC_DIR),$(addprefix $(LEXER_DIR),$(FILES_LEXER)))
SRC_GEN		=	$(addprefix $(SRC_DIR), $(FILES_GEN))

OBJ_EXPAN	=	$(addprefix $(DIR_OBJ),$(SRC_EXPAN:.c=.o))
OBJ_ENTRY	=	$(addprefix $(DIR_OBJ),$(SRC_ENTRY:.c=.o))
OBJ_BUILT	=	$(addprefix $(DIR_OBJ),$(SRC_BUILT:.c=.o))
OBJ_LEXER	=	$(addprefix $(DIR_OBJ),$(SRC_LEXER:.c=.o))
OBJ			=	$(addprefix $(DIR_OBJ),$(SRC_GEN:.c=.o))

LIB_A		:=	$(RDLINE_ROOT)libreadline.a $(RDLINE_ROOT)libhistory.a \
				$(LIBFT_ROOT)libft.a

LIB_ADD_DIR	:=	-L$(RDLINE_ROOT) -L$(LIBFT_ROOT)

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

#=================HEADERS==================#
HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(LIBFT_ROOT))

#==================RULES===================#

all : temp librarys $(NAME)

librarys :
	@$(MAKE) -C $(LIBFT_ROOT) --no-print-directory
	@$(MAKE) rdline --no-print-directory

$(NAME) : $(OBJ) $(OBJ_BUILT) $(OBJ_ENTRY) $(OBJ_LEXER)
	@$(CC) $(CFLAGS) $(OBJ) $(OBJ_BUILT) $(OBJ_ENTRY) $(OBJ_LEXER) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@
	@echo "${GREEN}Minishell Compiled${NC}"

rdline :
	@echo "${YELLOW}Compiling Readline...${NC}"
	@cd ./readline/ &> /dev/null && ./configure &> /dev/null
	@make -C ./readline/ &> /dev/null
	@echo "${GREEN}Readline Compiled${NC}"


$(DIR_OBJ)%.o: %.c Makefile $(LIB_A) $(HEADER)
	@mkdir -p $(dir $@)
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
	@$(RM) $(NAME)
	@printf "${RED}Minishell deleted\n${NC}"
	@$(MAKE) -C readline clean --no-print-directory

norm	:
	@printf "${PURPLE}SEARCHING FOR A PRINTF IN THE PROJECT: "
	@printf "%i \n${NC}" $(shell grep "	printf" *.c | wc -l)
	@printf "${YELLOW}Norminette...\n${NC}"
	@printf "${RED}"
	@norminette src/*/*.c src/*.c inc/*.h > test && printf "$(GREEN)\t[OK]\n" || grep Error test
	@printf "${NC}"
	@rm test

re		: fclean all

.PHONY : all clean fclean re librarys rdline
