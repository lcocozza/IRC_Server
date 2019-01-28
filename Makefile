.SILENT:

FLAGS= -Wextra -Werror

SRC=	srcs/main.c \
	srcs/ft_files/ft_serveur.c\
	srcs/ft_files/ft_config.c \
	srcs/ft_files/ft_display.c \
	srcs/ft_files/ft_general.c \
	srcs/ft_files/ft_messages.c \
	srcs/ft_files/ft_network.c

all:
	gcc $(FLAGS) $(SRC) -o IRC_Server -I includes/ -g

clean:
	rm IRC_Server

re: clean all
