.SILENT:

OPTION= -lpthread

FLAGS= -Wextra -Werror

SRC=	srcs/server_app.c \
	srcs/server_listen.c \
	srcs/config_server.c \
	srcs/main.c \
	srcs/ft_files/ft_display.c \
	srcs/ft_files/ft_general.c \
	srcs/ft_files/ft_messages.c

all:
	gcc $(FLAGS) $(SRC) -o IRC_Server -I includes/ -g

clean:
	rm IRC_Server

re: clean all
