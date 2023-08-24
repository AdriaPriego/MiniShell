# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apriego- <apriego-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 13:15:19 by apriego-          #+#    #+#              #
#    Updated: 2023/08/24 10:46:27 by apriego-         ###   ########.fr        #
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

LIB		=	ar rcs
CC		=	gcc
CCFLAGS	=	-Wall -Wextra -Werror
INCFLAG	=	-I../inc
RM		=	rm -fr

#==================FILES===================#

NAME			=	libft.a
INCLUDE 		=	../inc/libft.h
PRINTF			=	ft_printf/
PRINTFFD		=	ft_printf_fd/
GETLINE			=	get_next_line/
SRC				=	ft_memset.c ft_bzero.c ft_strlen.c ft_atoi.c ft_isdigit.c ft_isalpha.c\
					ft_isprint.c ft_isascii.c ft_isalnum.c ft_memchr.c ft_memcpy.c\
					ft_memcmp.c ft_memmove.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c\
					ft_strncmp.c ft_toupper.c ft_tolower.c ft_strnstr.c ft_strrchr.c ft_calloc.c\
					ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_substr.c\
					ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_itoa.c ft_split.c ft_striteri.c\
					ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
					ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\
					ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
					ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_test_int.c

FILESPRINTF		=	ft_hex.c ft_printf.c ft_printfnbr.c

SRCPRINTF		=	$(addprefix $(PRINTF),$(FILESPRINTF))

FILESPRINTFFD	=	ft_hex_fd.c ft_printf_fd.c ft_printfnbr_fd.c

SRCPRINTFFD		=	$(addprefix $(PRINTFFD),$(FILESPRINTFFD))

FILESGETLINE 	=	get_next_line_utils.c get_next_line.c

SRCGETLINE		=	$(addprefix $(GETLINE),$(FILESGETLINE))
DIR_OBJ			=	temp/
OBJ				=	$(addprefix $(DIR_OBJ),$(SRC:.c=.o))
OBJPRINT		=	$(addprefix $(DIR_OBJ),$(SRCPRINTF:.c=.o))
OBJPRINTFD		=	$(addprefix $(DIR_OBJ),$(SRCPRINTFFD:.c=.o))
OBJGETLINE		=	$(addprefix $(DIR_OBJ),$(SRCGETLINE:.c=.o))

#==================RULES===================#

all: temp $(NAME)

temp:
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJ) $(OBJPRINT) $(OBJGETLINE) $(OBJPRINTFD)
	@$(LIB) $(NAME) $(OBJ) $(OBJPRINT) $(OBJGETLINE) $(OBJPRINTFD)
	@printf "${GREEN}Compiled libft\n${NC}"

$(DIR_OBJ)%.o: %.c $(INCLUDE)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) $(INCFLAG) -c -o $@ $<
	@printf "${YELLOW}Compiling obj $@...${NC}\n"

clean:
	@$(RM) $(DIR_OBJ)
	@echo "${RED}DELETING ALL LIBFT OBJ${NC}"

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED}DELETING ALL LIBFT${NC}"

cleaname:
	@$(RM) $(NAME)
	@echo "${RED}DELETING ALL LIBFT${NC}"

re: fclean all

.PHONY: all clean fclean re 