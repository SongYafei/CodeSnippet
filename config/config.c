#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"



config_t conf = {
	DEF_INPUT_PATH,
	DEF_OUTPUT_PATH,
	1
};


static
char * trim_left(char *str) {
	if(str == NULL)
		return NULL;
	char *p = str;
	while(*p == ' ' && *p != '\0') {
		++p;
	}
	return strcpy(str, p);
}

static
char * trim_right(char *str) {
	if(str == NULL)
		return NULL;

	int len = strlen(str);
	while(len) {
		if(*(str+len-1) == ' ') {
			*(str+len-1) = '\0';
		} else {
			break;
		}
		len--;
	}
	return str;
}

static
int get_kv(char *line, char **key, char **value) {
	trim_left(line);
	char *p = strchr(line, '=');
	if(p == NULL) {
		fprintf(stderr, "BAD FORMAT:%s\n", line);
		return -1;
	}
	*key = line;
	*value = p+1;
	*p = '\0';
	trim_right(*key);
	

	//remove the '\n' at the end of the line
	char *t = strrchr(*value, '\n');
	if(t != NULL)
		*t = '\0';
	t = strrchr(*value, '\r');
	if(t!= NULL)
		*t = '\0';
	trim_left(*value);
	trim_right(*value);
	return 0;
}


int read_config(config_t *conf) {
	FILE *fp = fopen(CONFIG_FILE_PATH, "r");
	if(fp == NULL) {
		fprintf(stderr, "Can not open config file\n");
		return -1;
	}

	char config_line[512];
	while(!feof(fp)) {
		memset(config_line, 0, sizeof(config_line));
		fgets(config_line, 512, fp);
		//printf("+++%s", config_line);
		trim_left(config_line);
		if(config_line[0] == '#' || config_line[0] == '\n'|| config_line[0] == '\r' || strcmp(config_line, "") == 0)
			continue;
		char *key = NULL;
		char *value = NULL;
		int ret = get_kv(config_line, &key, &value);
		// if(ret != -1)
		// 	printf("key:-%s-\nvalue:-%s-\n", key, value);
		if(ret != -1) {
			if(IS_EQUAL(key, "input")) {
				strcpy(conf->input_path, value);
			} else if(IS_EQUAL(key, "output")) {
				strcpy(conf->output_path, value);
			} else if (IS_EQUAL(key, "show_mid_steps")) {
				conf->show_mid_steps = atoi(value);
			}
		}
		
	}

	return 0;
}

// int main()
// {
// 	read_config(&conf);
// 	printf("input:%s--\n", conf.input_path);
// 	printf("output:%s--\n", conf.output_path);
// 	printf("show:%d--\n", conf.show_mid_steps);

// 	return 0;
// }