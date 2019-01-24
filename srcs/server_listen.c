#include "sys_incl.h"
#include "ft.h"

#ifdef _WIN32
static void	init(void)
{
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
}
#endif

#ifdef _WIN32
static void	end(void)
{
    WSACleanup();
}
#endif

int	init_connection(void)
{
	int bind_status;
	int listen_status;
	SOCKET listen_socket;
	SOCKADDR_IN local_address = {0};

	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);
	local_address.sin_port = htons(6667);
	local_address.sin_family = AF_INET;

	bind_status = bind(listen_socket, (SOCKADDR *) &local_address, sizeof(local_address));
	if (bind_status == SOCKET_ERROR)
		get_error("bind()", 1, listen_socket);
	
	listen_status = listen(listen_socket, 5);
	if (listen_status == SOCKET_ERROR)
		get_error("listen()", 1, listen_socket);

	return listen_socket;
}
