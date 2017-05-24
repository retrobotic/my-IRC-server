##
## Makefile for myirc in /home/rootkid/rendu/psu/PSU_2016_myirc
## 
## Made by theo champion
## Login   <theo.champion@epitech.eu>
## 
## Started on  Wed May 24 15:39:32 2017 theo champion
## Last update Wed May 24 18:25:37 2017 theo champion
##

CC	= gcc

RM	= rm -f

SRCDIR	= ./src

CFLAGS	+= -W -Wall -Wextra -Werror -g3
CFLAGS	+= -I./include

NAME	= server

SRCS	= $(SRCDIR)/main.c		\
          $(SRCDIR)/socket.c		\
          $(SRCDIR)/client_handler.c	\
	  $(SRCDIR)/user_manager.c	\
	  $(SRCDIR)/chan_manager.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
