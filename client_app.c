#include "header.h"

int	app(int socket, serv_config *s_conf)
{
	SOCKADDR_IN client_address = {0};
	SOCKET *client_socket = NULL;
	SOCKET new_socket;
	int address_size = sizeof(client_address);
	char buffer[1024];
	int retour;
	int i;
	
	client_socket = malloc(sizeof(s_conf->max_client));

	if (buffer == NULL)
	{
		printf("malloc(buffer)");
		exit(errno);
	}

	new_socket = accept(socket, (SOCKADDR *) &client_address, &address_size);

	if (new_socket == INVALID_SOCKET)
	{
		perror("accept()");
		closesocket(new_socket);
		exit(errno);
	}
	printf("New connection, socket: %d, ip: %s, port: %d\n", new_socket, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

	strcpy(buffer, "Message du serveur");
	retour = send(new_socket, &buffer, sizeof(buffer), 0);
	if (retour == SOCKET_ERROR)
	{
		perror("send()");
		exit(errno);
	}

	return *client_socket;
}
