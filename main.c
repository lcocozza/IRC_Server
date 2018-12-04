#include "header.h"

int	main(int argc, char **argv)
{
	serv_config s_conf = {0};
	int socket;
	
	s_conf.max_client = 10;

	config(&s_conf);
	title();
	socket = init_connection();
	socket = app(socket, &s_conf);
	closeconnection(socket);

	return 0;
}
