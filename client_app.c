#include "header.h"

int	app(int socket, serv_config *s_conf)
{
	SOCKADDR_IN client_address = {0};
	SOCKET *clients_socket = NULL;
	SOCKET new_socket;
	int address_size = sizeof(client_address);
	char buffer[1024];
	int retour;
	int i;

	fd_set readfs;

	clients_socket = malloc(sizeof(s_conf->max_client));
	for (i = 0; i < s_conf->max_client; i++)
		clients_socket[i] = 0;

	while (1)
	{
		FD_ZERO(&readfs);
		FD_SET(socket, &readfs);

		new_socket = accept(socket, (SOCKADDR *) &client_address, &address_size);

		if (new_socket == INVALID_SOCKET)
		{
			perror("accept()");
			closesocket(new_socket);
			exit(errno);
		}
		printf("New connection, socket: %d, ip: %s, port: %d\n", new_socket, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

		for (i = 0; i < s_conf->max_client; i++)
		{
			if (clients_socket[i] == 0)
			{
				clients_socket[i] == new_socket;
				strcpy(buffer, "Succesfull connection.\n");
				send(clients_socket[i], &buffer, sizeof(buffer), 0);
				break;
			}
			else if (clients_socket[s_conf->max_client - 1] != 0)
			{
				strcpy(buffer, "Connection error: no more client can be connected.\n");
				send(new_socket, &buffer, sizeof(buffer), 0);
			}
		}
	}

	return *clients_socket;
}

void	send_message(int *clients_socket)
{
	
}
