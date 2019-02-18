#include "sys_incl.h"
#include "ft.h"

int	app(SOCKET master_socket, t_serv_config *s_conf)
{
	SOCKADDR_IN client_address = {0};
	SOCKET new_socket;
	int address_size = sizeof(client_address);
	int *clients_socket = NULL;
	char buffer[1024] = {0};
	char msg[1000] = {0};
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
			get_error("select()", 1, -1);

		if (FD_ISSET(STDIN_FILENO, &readfs))
		{
			fgets(msg, sizeof(char) * 1000, stdin);
			strcpy(buffer, "$[server] ");
			strcat(buffer, msg);
			send_toall(clients_socket, 0, s_conf->max_client, buffer);
			cleanMsg(buffer, msg);
		}
		else if (FD_ISSET(master_socket, &readfs))
		{
			new_socket = accept(master_socket, (SOCKADDR *)&client_address, &address_size);

			if (new_socket == INVALID_SOCKET)
				get_error("accept()", 1, new_socket);

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
					strcpy(buffer, "$[server] Success connecting.\n");
					printf("%s", buffer);
					send_message(clients_socket[i], buffer);
					cleanMsg(buffer, msg);
					strcpy(buffer, "$[server] Someone connecting.\n");
					send_toall(clients_socket, clients_socket[i], s_conf->max_client, buffer);
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
						strcpy(buffer, "$[server] Someone disconnected.\n");
						send_toall(clients_socket, 0, s_conf->max_client, buffer);
						cleanMsg(buffer, msg);
						break;
					}
					else
					{
						printf("%s\n", buffer);
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
