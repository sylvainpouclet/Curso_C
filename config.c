#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static const char *init_mode_str[] = {
	[CFG_DEFAULT] = "default",
	[CFG_GLIDER]  = "glider",
	[CFG_RANDOM]  = "random",
};

static const struct option long_options[] =
{
	{"help",         no_argument,       0, 'h'},
	{"size_x",       required_argument, 0, 'x'},
	{"size_y",       required_argument, 0, 'y'},
	{"init ",        required_argument, 0, 'i'},
	{"save_file",    required_argument, 0, 's'},
	{"restore_file", required_argument, 0, 'r'},
	{0, 0, 0, 0}
};

static bool check_config(const struct config *config);
static enum cfg_init_mode str2init_mode(const char *opt);
static bool load_config(struct config *config);


int config_parse_argv(struct config *config, int argc, char *argv[])
{
	int option_index = 0;
	int c;

	// Default values
	config->show_help    = false;	
	config->size_x       = 0;
	config->size_y       = 0;
	config->init_mode    = 0;
	config->cfg_file     = NULL;
	config->flag_save    = false;
	config->flag_restore = false;
	int i;
	for (i = 0; i < LINE_LEN; i++){
		config->save_file[i] = ' ';
		config->save_file[i] = ' ';
	}

	while ((c = getopt_long(argc, argv, "hx:y:i:s:r:", long_options,
				&option_index)) != -1) {
		switch (c) {
		case 'h':
			config->show_help = true;
			break;
		case 'x':
			config->size_x = strtol(optarg, NULL, 0);
			break;
		case 'y':
			config->size_y = strtol(optarg, NULL, 0);
			break;
		case 'i':
			config->init_mode = str2init_mode(optarg);
			break;
		case 's':
			strcpy(config->save_file, optarg);
			config->flag_save = true;
			break;
		case 'r':
			strcpy(config->restore_file, optarg);
			config->flag_restore = true;
			break;

		default:
			printf("Error entrada\n");
			exit(EXIT_FAILURE);
		}
	}

	// Check for config file name
	if (optind != argc) {
		if (optind == argc - 1) {
			config->cfg_file = argv[optind];
			if (!load_config(config))
				return false;
		} else {
			return false;
		}
	}

	return check_config(config);
}

static bool check_config(const struct config *config)
{
	bool correct = true;

	if (config->show_help)
		return true;
	correct &= config->size_x > 0;
	correct &= config->size_y > 0;
	correct &= (config->init_mode > CFG_NOT_DEF && config->init_mode < _CFG_MAX_);

	return correct;
}

static enum cfg_init_mode str2init_mode(const char *opt)
{
	int i;
	for (i = 0; i < CFG_N_INIT_MODES; i++)
		if (!strcmp(opt, init_mode_str[i]))
			break;

	return i == CFG_N_INIT_MODES ? CFG_NOT_DEF : i;
}

void config_print_usage(const char *arg0)
{
	printf("Usage: %s\n"
		"\t[-h|--help]\n"
		"\t[-x|--size_x <num>]\n"
		"\t[-y|--size_y <num>]\n"
		"\t[-i|--init <init_mode>]\n"
		"\t[-s|--save <game file>]\n"
		"\t[-r|--read <game file>]\n"
		"\t[file]\n"
		, arg0);

	// Print all initialization modes
	printf("\ninitialization modes: \n");
	int i;
	for (i = 0; i < CFG_N_INIT_MODES; i++)
		printf("\t%s\n",init_mode_str[i]);
	printf("\ninitialization with a config file:\n ./game_of_life file\n");
}

void config_print(const struct config *config)
{
	printf("config {\n");
	printf("\tshow help = %s\n", config->show_help ? "TRUE" : "FALSE");
	printf("\tsize_x    = %d\n", config->size_x);
	printf("\tsize_y    = %d\n", config->size_y);
	printf("\tinit_mode = %d(%s)\n",
		config->init_mode, init_mode_str[config->init_mode]);
	printf("\tsave_file   = %s\n", config->save_file);
	printf("\trestore_file   = %s\n", config->restore_file);
	printf("}\n");
}

static bool load_config(struct config *config)
{
	FILE *file = fopen(config->cfg_file, "r");
	if (!file){
		perror("Error opening config file");
		return false;
	}
	
	char line[LINE_LEN];
	
	// Size x
	fgets(line, LINE_LEN, file);
	if (ferror(file)) {
		perror("Error reading config file");
		return false;
	}
	config->size_x = strtol(line, NULL, 0);

	// Size y
	fgets(line, LINE_LEN, file);
	if (ferror(file)) {
		perror("Error reading config file");
		return false;
	}
	config->size_y = strtol(line, NULL, 0);

	// init mode
	fgets(line, LINE_LEN, file);
	if (ferror(file)) {
		perror("Error reading config file");
		return false;
	}

	// Eliminacion del caracter de salto de linea
	char *ptr_scan = NULL;
	ptr_scan = strchr(line, '\n');
	if (ptr_scan != NULL) 
		*ptr_scan = '\0'; 

	config->init_mode = str2init_mode((const char *)line);

	// save to file
	fgets(config->save_file, LINE_LEN, file);
	if (ferror(file)) {
		perror("Error reading config file");
		return false;
	}
	// Eliminacion del caracter de salto de linea
	ptr_scan = strchr(config->save_file, '\n');
	if (ptr_scan != NULL) 
		*ptr_scan = '\0';

	config->flag_save = true;

	// restore from file
	fgets(config->restore_file, LINE_LEN, file);
	if (ferror(file)) {
		perror("Error reading config file");
		return false;
	}

	// Eliminacion del caracter de salto de linea
	ptr_scan = strchr(config->restore_file, '\n');
	if (ptr_scan != NULL) 
		*ptr_scan = '\0';

	config->flag_restore = true;

	fclose (file);

	return true;
}


