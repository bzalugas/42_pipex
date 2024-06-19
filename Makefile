#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 15:07:33 by bazaluga          #+#    #+#              #
#    Updated: 2024/06/19 13:18:49 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	    :=	pipex

SRCDIR	    :=	src

OBJDIR	    :=	obj

INCDIR	    :=	include

LIBFTDIR    :=	$(INCDIR)/libft

LIBFT	    :=	$(LIBFTDIR)/libft.a

SRC	    :=	error.c pipex.c

OBJ	    :=  $(SRC:.c=.o)

SRC	    :=  $(addprefix $(SRCDIR)/, $(SRC))

OBJ	    :=  $(addprefix $(OBJDIR)/, $(OBJ))

CC	    :=  cc

CFLAGS	    :=  -Wall -Wextra -Werror

########### COLORS ##########

RED	:=  "\033[1;31m"
GREEN	:=  "\033[1;32m"
RESET	:=  "\033[0m"

all:		$(NAME)

$(OBJDIR):
		mkdir -p $(OBJDIR)


$(OBJDIR)/%.o:	$(SRCDIR)/%.c Makefile | $(OBJDIR)
		@printf $(GREEN)
		$(CC) $(CFLAGS) -MMD -c $< -o $@
		@printf $(RESET)

$(MLX):
		@echo $(GREEN)"\n\tCOMPILING MLX"$(RESET)
		@make -sC $(MLXDIR)
		@echo $(GREEN)"\n\tMLX COMPILED\n"$(RESET)

$(LIBFT):
		@echo $(GREEN)"\n\tCOMPILING LIBFT"$(RESET)
		@make -sC $(LIBFTDIR)
		@echo $(GREEN)"\n\tLIBFT COMPILED"$(RESET)

$(NAME):	$(OBJ) $(MLX) $(LIBFT)
		@echo $(GREEN)"LINKING objects to create $(NAME)"
		$(CC) $(OBJ) $(CFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)
		@printf $(RESET)

bonus:		$(NAME)

libft:		$(LIBFT)
		@make -sC $(LIBFTDIR)

clean:
		@echo $(RED)"CLEANING OBJS"
		rm -f $(OBJ)
		rm -f $(OBJ:.o=.d)
		rm -rf $(OBJDIR)
		@make -sC $(LIBFTDIR) clean
		@echo $(RESET)

fclean:		clean
		@echo $(RED)"CLEANING ALL"
		rm -f $(NAME)
		rm -rf *.dSYM
		@make -sC $(LIBFTDIR) fclean
		@echo $(RESET)

re:		fclean
		@make all

-include	$(OBJ:.o=.d)

.PHONY:		all clean fclean re bonus libft
