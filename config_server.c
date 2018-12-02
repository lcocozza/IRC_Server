void	init_config_file(void)
{
	FILE* config = NULL;

	config = fopen("config/config.txt", "w+");

	fprintf(config, "#config\n"
			"0\n\n"
			"#port\n"
			"6667\n\n"
			"#user_max\n"
			"5\n");

	fclose(config);
}

int	config(void)
{
	FILE* config = NULL;
	
	config = fopen("config/config.txt", "r");
	if (config == NULL)
	{
		init_config_file();
		config = fopen("config/config.txt", "r");
	}

	fclose(config);

	return 0;
}
