#include "header.h"

static void	init(void)
{
#ifdef _WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void	end(void)
{
#ifdef _WIN32
    WSACleanup();
#endif
}

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
	{	
		perror("bind()");
		closesocket(listen_socket);
		exit(errno);
	}
	
	listen_status = listen(listen_socket, 5);
	if (listen_status == SOCKET_ERROR)
	{
		perror("listen()");
		closesocket(listen_socket);
		exit(errno);
	}
	return listen_socket;
}

int	app(int socket)
{
	SOCKADDR_IN client_address = {0};
	SOCKET client_socket;
	int address_size = sizeof(client_address);
	char buffer[1024];
	int retour;
	
	if (buffer == NULL)
	{
		printf("malloc(buffer)");
		exit(errno);
	}

	client_socket = accept(socket, (SOCKADDR *) &client_address, &address_size);

	if (client_socket == INVALID_SOCKET)
	{
		perror("accept()");
		closesocket(client_socket);
		exit(errno);
	}
	
	strcpy(buffer, "NIQUE TA MERE");
	retour = send(client_socket, &buffer, sizeof(buffer), 0);
	if (retour == SOCKET_ERROR)
	{
		perror("send()");
		exit(errno);
	}

	return client_socket;
}

void	closeconnection(int socket)
{
	closesocket(socket);
}
