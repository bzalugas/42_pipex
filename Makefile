#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 15:07:33 by bazaluga          #+#    #+#              #
#    Updated: 2024/06/30 15:38:01 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	    :=	pipex

NAMETMP	    :=	obj/tmp_pipex

NAMEB	    :=	obj_bonus/tmp_pipex

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

OBJ	    :=  $(addprefix $(OBJDIR)/, $(OBJ))

OBJB	    :=  $(addprefix $(OBJBDIR)/, $(OBJB))

CC	    :=  cc

CFLAGS	    :=  -Wall -Wextra -Werror

########### COLORS ##########

RED	:=  "\033[1;31m"
GREEN	:=  "\033[1;32m"
RESET	:=  "\033[0m"

all:		$(NAME)

bonus:		$(NAMEB)

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

$(NAMETMP):	$(OBJ) $(LIBFT)
		@rm -f $(NAMEB)
		@echo $(GREEN)"LINKING mandatory objects to create $(NAME)"
		$(CC) $(OBJ) $(CFLAGS) -L$(LIBFTDIR) -lft -o $(NAMETMP)
		@cp $(NAMETMP) $(NAME)
		@printf $(RESET)

$(NAME):	$(NAMETMP)

$(NAMEB):	$(OBJB) $(LIBFT)
		@rm -f $(NAMETMP)
		@echo $(GREEN)"LINKING bonus objects to create $(NAME)"
		$(CC) $(OBJB) $(CFLAGS) -L$(LIBFTDIR) -lft -o $(NAMEB)
		@cp $(NAMEB) $(NAME)
		@printf $(RESET)

libft:		$(LIBFT)
		@make -sC $(LIBFTDIR)

clean:
		@echo $(RED)"CLEANING OBJS"
		rm -rf $(OBJDIR)
		rm -rf $(OBJBDIR)
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
