#include "IRC_Server.h"

int	main(int argc, char **argv)
{
	serv_config s_conf = {0};
	int socket = init_connection();
	
	app(socket);
	//config(&s_conf);
	//system(CLRSRC);
	//title();

	return 0;
}
