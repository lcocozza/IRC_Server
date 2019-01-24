#include "sys_incl.h"
#include "ft.h"

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

	for (i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) ;
	buffer[i] = '\0';

	if (send(socket, buffer, strlen(buffer), 0) < 0)
		get_error("send()", 1, -1);
}

int	receive_message(SOCKET socket, char *buffer)
{
	int statu = 0;
	if ((statu = recv(socket, buffer, 1024, 0)) < 0)
		get_error("recv()", -1, -1);
	return statu;
}

void cleanMsg(char *buffer, char *msg)
{
	memset(buffer, 0, strlen(buffer));
	memset(msg, 0, strlen(msg));
	free(buffer);
	free(msg);
}

