typedef struct serv_config serv_config;
struct	serv_config {

	int config;
	int port;
	int backlog;
	int max_client;
};

int	init_connection(void);
void	init_config_file(void);
int	config(serv_config *s_conf);
void	title(void);
int	app(SOCKET master_socket, serv_config *s_conf);
int	receive_message(SOCKET socket, char *buffer);
void	send_message(SOCKET socket, char *buffer);
void	closeconnection(SOCKET socket);
void	cleanMsg(char *buffer, char *msg);
void	send_toall(int *clients_socket, int socket, int max, char *buffer);
