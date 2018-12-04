#include "header.h"

int	main(int argc, char **argv)
{
	serv_config s_conf = {0};
	int socket;
	
	config(&s_conf);
	title();
	socket = init_connection();
	socket = app(socket);
	closeconnection(socket);

	return 0;
}
