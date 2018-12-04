#include "header.h"

void	init_config_file(void)
{
	FILE* config = NULL;

	config = fopen("config/config.txt", "w+");

	fprintf(config, "#config\n"
			"0\n\n"
			"#port\n"
			"6667\n\n"
			"#backlog\n"
			"5\n\n"
			"#max_client\n"
			"10\n\n");

	fclose(config);
}

int	config(serv_config *s_conf)
{
	char str[10];
	FILE* config = NULL;

	config = fopen("config/config.txt", "r+");
	if (config == NULL)
	{
		init_config_file();
		config = fopen("config/config.txt", "r+");
	}
	
	rewind(config);
	while (strcmp(str ,"#config\n") != 0)
		fgets(str, sizeof(str), config);
	
	s_conf->config = atoi(fgets(str, sizeof(str), config));
	if (s_conf->config == 1)
	{	
		printf("file configured\n");
		return 0;
	}
	printf("file not configured\n");

	fclose(config);

	return 0;
}
