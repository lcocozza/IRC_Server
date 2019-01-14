#include "header.h"

SOCKET *clients_socket = NULL;

int	main(int argc, char **argv)
{
	serv_config s_conf = {0};
	SOCKET socket;
	
	s_conf.max_client = 10;
	clients_socket = malloc(sizeof(s_conf.max_client));

	config(&s_conf);
	title();
	socket = init_connection();
	socket = app(socket, &s_conf);
	closeconnection(socket);

	return 0;
}
