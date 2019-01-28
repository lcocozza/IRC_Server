#include "sys_incl.h"
#include "ft.h"

int	main(int argc, char **argv)
{
	t_serv_config s_conf = {0};
	SOCKET socket;
	
	s_conf.max_client = 10;
	s_conf.port = 6667;

	config(&s_conf);
	title();
	socket = init_connection(&s_conf);
	socket = app(socket, &s_conf);
	closesocket(socket);

	return 0;
}
