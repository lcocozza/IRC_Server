#ifndef FT_H
#define FT_H

typedef struct s_serv_config t_serv_config;
struct	s_serv_config {

	int config;
	int port;
	int backlog;
	int max_client;
};


/* ft_general.c */

void	get_error(char *str, int quit, SOCKET socket);


/* ft_messages.c */

int	receive_message(SOCKET socket, char *buffer);
void	send_message(SOCKET socket, char *buffer);
void	cleanMsg(char *buffer, char *msg);
void	send_toall(int *clients_socket, int socket, int max, char *buffer);


/* ft_display.c */

void	title(void);


/* ft_network.c */

int	init_connection(t_serv_config *s_conf);


/* ft_config.c */

void	init_config_file(void);
int	config(t_serv_config *s_conf);


/* ft_serveur.c */

int	app(SOCKET master_socket, t_serv_config *s_conf);


#endif
