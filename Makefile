##
## Makefile for myirc in /home/rootkid/rendu/psu/PSU_2016_myirc
## 
## Made by theo champion
## Login   <theo.champion@epitech.eu>
## 
## Started on  Wed May 24 15:39:32 2017 theo champion
## Last update Fri May 26 13:32:58 2017 theo champion
##

CC	= gcc

RM	= rm -f

SDIR	= ./src_server
CDIR	= ./src_client

CFLAGS	+= -W -Wall -Wextra -g3
CFLAGS	+= -I./include

SERVER	= server
CLIENT	= client

SSRCS	= $(SDIR)/main.c			\
          $(SDIR)/socket.c			\
          $(SDIR)/client_handler.c		\
	  $(SDIR)/user_manager.c		\
	  $(SDIR)/utils.c			\
	  $(SDIR)/connection_registration.c	\
	  $(SDIR)/chan_manager.c

CSRCS	= $(CDIR)/main.c			\

SOBJS	= $(SSRCS:.c=.o)
COBJS	= $(CSRCS:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) $(SOBJS) $(CFLAGS) -o $(SERVER)

$(CLIENT): $(COBJS)
	$(CC) $(COBJS) $(CFLAGS) -o $(CLIENT)

clean:
	$(RM) $(SOBJS) $(COBJS)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY:	all clean fclean re
