
#include "header.h"

int	app(int master_socket, serv_config *s_conf)
{
	SOCKADDR_IN client_address = {0};
	SOCKET new_socket;
	int address_size = sizeof(client_address);
	char buffer[1024];
	int *clients_socket = NULL;
	int statu = 0;
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
		FD_SET(clients_socket[0], &readfs);
		
		if (select(master_socket + 1, &readfs, NULL, NULL, NULL) == -1)
		{
			perror("select()");
			exit(errno);
		}
		
		if (FD_ISSET(STDIN_FILENO, &readfs))
		{
			fgets(buffer, sizeof(char) * 1024, stdin);
			send_message(clients_socket[0], buffer);
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
					break;
				}
			}
		}
		else
		{
			if (FD_ISSET(clients_socket[0], &readfs))
			{
				statu = receive_message(clients_socket[0], buffer);
				if (statu == -1)
				{
					printf("Disconnect\n");
				}
				else
				{
					printf("%s", buffer);
					viderBuffer();
				}
			}
		}
	}

	return *clients_socket;
}

void	send_message(SOCKET socket, char *buffer)
{
	if (send(socket, buffer, strlen(buffer), 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
	viderBuffer();
}

int	receive_message(SOCKET socket, char *buffer)
{
	int statu = 0;
	if (statu = recv(socket, buffer, 1024, 0) < 0)
		perror("recv()");
	return statu;
}

void viderBuffer()
{
    /*int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }*/
}
