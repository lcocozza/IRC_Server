#include "sys_incl.h"
#include "ft.h"

int	init_connection(t_serv_config *s_conf)
{
	int bind_status;
	int listen_status;
	SOCKET listen_socket;
	SOCKADDR_IN local_address = {0};

	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);
	local_address.sin_port = htons(s_conf->port);
	local_address.sin_family = AF_INET;

	bind_status = bind(listen_socket, (SOCKADDR *) &local_address, sizeof(local_address));
	if (bind_status == SOCKET_ERROR)
		get_error("bind()", 1, listen_socket);
	
	listen_status = listen(listen_socket, 5);
	if (listen_status == SOCKET_ERROR)
		get_error("listen()", 1, listen_socket);

	return listen_socket;
}
