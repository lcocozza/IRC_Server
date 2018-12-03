#ifdef _WIN32

#include <winsock2.h>
#define CLRSRC "cls"

#elif __linux__

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define CLRSRC "clear"
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ft.c"
#include "config_server.c"

int	init_connection(void);
//void	init_config_file(void);
//int	config(serv_config *s_conf);
void	title(void);
int	app(int socket);
void	closeconnection(int socket);

void	title(void)
{
	printf(	"88888888888888b.  .d8888b.        .d8888b.\n"
  		"  888  888   Y88bd88P  Y88b      d88P  Y88b\n"
  		"  888  888    888888    888      Y88b.\n"
  		"  888  888   d88P888              'Y888b.   .d88b. 888d888888  888 .d88b. 888d888\n"
  		"  888  8888888P' 888                 'Y88b.d8P  Y8b888P'  888  888d8P  Y8b888P'\n"
  		"  888  888 T88b  888    888            '88888888888888    Y88  88P88888888888\n"
  		"  888  888  T88b Y88b  d88P      Y88b  d88PY8b.    888     Y8bd8P Y8b.    888\n"
		"8888888888   T88b 'Y8888P'88888888'Y8888P'  'Y8888 888      Y88P   'Y8888 888\n\n\n");
}

struct	serv_config {

	int config;
	int port;
	int user_max;
};

typedef struct serv_config serv_config;
