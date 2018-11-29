#include "IRC_Client.h"

int	main(int argc, char **argv)
{
	int network_socket;

	arg(argc, argv);
	init_connection(argv);

	return 0;
}
