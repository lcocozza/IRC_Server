#ifdef _WIN32

#include <winsock2.h>
#define CLRSRC "cls"
#define ATTENDRE(temps) Sleep(temps*1000)

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
#define ATTENDRE(temps) sleep(temps)

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
#include <pthread.h>
#include <stdint.h>

typedef struct serv_config serv_config;
struct	serv_config {

	int config;
	int port;
	int backlog;
	int max_client;
};

int	init_connection(void);
void	init_config_file(void);
int	config(serv_config *s_conf);
void	title(void);
int	app(SOCKET socket, serv_config *s_conf);
int	receive_message(SOCKET socket, char *buffer);
void	send_message(SOCKET socket, char *buffer);
void	closeconnection(SOCKET socket);
void	viderBuffer();
