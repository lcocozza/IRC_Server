static void init(void)
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

static void end(void)
{
#ifdef _WIN32
    WSACleanup();
#endif
}

void	arg(int argc, char **argv)
{
	if (argc != 3)
	{
		printf(	"Invalide Argument.\n"
			"Usage: ./%s [ip] [port]\n", argv[0]);
		exit(0);
	}

}

int	init_connection(char **argv)
{
	int connection_status;
	SOCKET network_socket;
	SOCKADDR_IN server_address = {0};

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(6667);
	server_address.sin_family = AF_INET;

	connection_status = bind(network_socket, (SOCKADDR *) &server_address, sizeof(server_address));
	if (connection_status == SOCKET_ERROR)
	{	
		perror("bind()");
		exit(errno);
	}
	
	if(listen(network_socket, 5) == SOCKET_ERROR)
	{
		perror("listen()");
		exit(errno);
	}
	
	SOCKADDR_IN client_address = {0};
	SOCKET client_socket;
	int address_size = sizeof(client_address);

	client_socket = accept(network_socket, (SOCKADDR *) &client_address, &address_size);

	if (client_socket == INVALID_SOCKET)
	{
		perror("accept()");
		exit(errno);
	}

	closesocket(network_socket);
	closesocket(client_socket);
	
	return 0;
}
