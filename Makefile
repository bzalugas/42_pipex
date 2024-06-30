#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 15:07:33 by bazaluga          #+#    #+#              #
#    Updated: 2024/06/30 14:29:40 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	    :=	pipex

SRCDIR	    :=	src

SRCBDIR	    :=	src_bonus

OBJDIR	    :=	obj

OBJBDIR	    :=	obj_bonus

INCDIR	    :=	include

LIBFTDIR    :=	$(INCDIR)/libft

LIBFT	    :=	$(LIBFTDIR)/libft.a

SRC	    :=	end_pipex.c handle_in_out.c handle_pipe.c run_cmds.c pipex.c utils.c

SRCB	    :=	end_pipex_bonus.c handle_in_out_bonus.c handle_pipe_bonus.c \
		run_cmds_bonus.c pipex_bonus.c utils_bonus.c

OBJ	    :=  $(SRC:.c=.o)

OBJB	    :=  $(SRCB:.c=.o)

SRC	    :=  $(addprefix $(SRCDIR)/, $(SRC))

SRCB	    :=  $(addprefix $(SRCBDIR)/, $(SRCB))

OBJ	    :=  $(addprefix $(OBJDIR)/, $(OBJB))

OBJB	    :=  $(addprefix $(OBJBDIR)/, $(OBJB))

CC	    :=  cc

CFLAGS	    :=  -Wall -Wextra -Werror

########### COLORS ##########

RED	:=  "\033[1;31m"
GREEN	:=  "\033[1;32m"
RESET	:=  "\033[0m"

all:		$(NAME)

$(OBJDIR):
		mkdir -p $(OBJDIR)

$(OBJBDIR):
		mkdir -p $(OBJBDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c Makefile | $(OBJDIR)
		@printf $(GREEN)
		$(CC) $(CFLAGS) -MMD -c $< -o $@
		@printf $(RESET)

$(OBJBDIR)/%.o:	$(SRCBDIR)/%.c Makefile | $(OBJBDIR)
		@printf $(GREEN)
		$(CC) $(CFLAGS) -MMD -c $< -o $@
		@printf $(RESET)

$(LIBFT):
		@echo $(GREEN)"\n\tCOMPILING LIBFT"$(RESET)
		@make -sC $(LIBFTDIR)
		@echo $(GREEN)"\n\tLIBFT COMPILED"$(RESET)

$(NAME):	$(OBJ) $(LIBFT)
		@echo $(GREEN)"LINKING mandatory objects to create $(NAME)"
		$(CC) $(OBJ) $(CFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)
		@printf $(RESET)

bonus:		$(OBJB) $(LIBFT)
		@echo $(GREEN)"LINKING bonus objects to create $(NAME)"
		$(CC) $(OBJB) $(CFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)
		@printf $(RESET)

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
		@make -s all

-include	$(OBJ:.o=.d)

.PHONY:		all clean fclean re bonus libft
