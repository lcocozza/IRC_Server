#include "header.h"

int	app(int master_socket, serv_config *s_conf)
{
	SOCKADDR_IN client_address = {0};
	SOCKET new_socket;
	int address_size = sizeof(client_address);
	char buffer[1024];
	char msg[1000];
	int *clients_socket = NULL;
	int statu = 0;
	int fdmax;
	int sd;
	int i;

	clients_socket = malloc(sizeof(int) * s_conf->max_client);

	fd_set readfs;

	for (i = 0; i < s_conf->max_client; i++)
		clients_socket[i] = 0;

	while (1)
	{
		FD_ZERO(&readfs);
		FD_SET(STDIN_FILENO, &readfs);
		FD_SET(master_socket, &readfs);

		fdmax = master_socket;

		for (i = 0; i < s_conf->max_client; i++)
		{
			sd = clients_socket[i];
			if (sd > 0)
				FD_SET(sd, &readfs);
			if (sd > fdmax)
				fdmax = sd;
		}

		if (select(fdmax + 1, &readfs, NULL, NULL, NULL) == -1)
		{
			perror("select()");
			exit(errno);
		}

		if (FD_ISSET(STDIN_FILENO, &readfs))
		{
			fgets(msg, sizeof(char) * 1000, stdin);
			strcpy(buffer, "[Server] ");
			strcat(buffer, msg);
			send_toall(clients_socket, 0, s_conf->max_client, buffer);
			cleanMsg(buffer, msg);
		}
		else if (FD_ISSET(master_socket, &readfs))
		{
			new_socket = accept(master_socket, (SOCKADDR *)&client_address, &address_size);

			if (new_socket == INVALID_SOCKET)
			{
				perror("accept()");
				closesocket(new_socket);
				exit(errno);
			}

			for (i = 0; i < s_conf->max_client; i++)
			{
				if (clients_socket[s_conf->max_client - 1] != 0)
				{
					strcpy(buffer, "Connection error: no more client can be connected.\n");
					send_message(new_socket, buffer);
					cleanMsg(buffer, msg);
					shutdown(new_socket, 2);
					closesocket(new_socket);
					break;
				}
				else if (clients_socket[i] == 0)
				{
					clients_socket[i] = new_socket;
					printf("New client connected with socket %d from %s:%d, in slot %d\n", clients_socket[i], inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), i);
					strcpy(buffer, "Success connecting.\n");
					send_message(clients_socket[i], buffer);
					cleanMsg(buffer, msg);
					break;
				}
			}
		}
		else
		{
			for (i = 0; i < s_conf->max_client; i++)
			{
				if (FD_ISSET(clients_socket[i], &readfs))
				{
					statu = receive_message(clients_socket[i], buffer);
					if (statu == 0)
					{
						printf("Socket %d Disconnect\n", clients_socket[i]);
						shutdown(clients_socket[i], 2);
						closesocket(clients_socket[i]);
						clients_socket[i] = 0;
						break;
					}
					else
					{
						send_toall(clients_socket, clients_socket[i], s_conf->max_client, buffer);
						cleanMsg(buffer, msg);
						break;
					}
				}
			}
		}
	}
	return *clients_socket;
}

void	send_toall(int *clients_socket, int actual_socket, int max, char *buffer)
{
	int i;

	for (i = 0; clients_socket[i] < max; i++)
	{
		if (clients_socket[i] != actual_socket && clients_socket[i] != 0)
			send_message(clients_socket[i], buffer);
	}
}

void	send_message(SOCKET socket, char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\n'; i++) ;
	buffer[i] = '\0';

	if (send(socket, buffer, strlen(buffer), 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
}

int	receive_message(SOCKET socket, char *buffer)
{
	int statu = 0;
	if ((statu = recv(socket, buffer, 1024, 0)) < 0)
		perror("recv()");
	return statu;
}

void cleanMsg(char *buffer, char *msg)
{
	/*int i;
	for (i = 0; buffer[i] != '\0'; i++)
		buffer[i] = 0;*/
	strcpy(buffer, "");
	strcpy(msg, "");
}
