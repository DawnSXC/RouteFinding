#include "adjacency_list.h"
#include <stdio.h>
#include <regex.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 256
#define MAX_MATCH 16
#define MAX_ERROR 64
#define MAX_NUMBER_LINE 32
#define MAX_NODES 4096

void add_nodes(struct adjacency_list *al, FILE *filp)
{
	const char *node_pattern = "^<node.*id=(-{0,1}[1-9][0-9]*).*lat=(-{0,1}[0-9]+[.]{0,1}[0-9]+).*lon=(-{0,1}[0-9]+[.]{0,1}[0-9]+).*/node>";
	regex_t reg;
	int err_code;
	char preg[MAX_LINE];
	regmatch_t pmatch[MAX_MATCH];
	char err_string[MAX_ERROR];
	char numbers[MAX_NUMBER_LINE];
	long id;
	float x, y;

	fseek(filp, 0L, SEEK_SET);

	err_code = regcomp(&reg, node_pattern, REG_EXTENDED);
	if (err_code) {
		regerror(err_code, &reg, err_string, sizeof(err_string));
		printf("err: %s\n", err_string);
		exit(-1);
	}

	while (!feof(filp)) {
		fgets(preg, sizeof(preg), filp);
		// printf("%s", preg);
		
		err_code = regexec(&reg, preg, MAX_MATCH, pmatch, 0);
		if (err_code) {
			regerror(err_code, &reg, err_string,
				 sizeof(err_string));
			// printf("err: %s\n", err_string);
			continue;
		}

		memset(numbers, '\0', sizeof(numbers));
		memcpy(numbers, preg + pmatch[1].rm_so,
		       pmatch[1].rm_eo - pmatch[1].rm_so);
		// printf("%ld\t", atol(numbers));
		id = atol(numbers);

		memset(numbers, '\0', sizeof(numbers));
		memcpy(numbers, preg + pmatch[2].rm_so, pmatch[2].rm_eo - pmatch[2].rm_so);
		x = atof(numbers);
	
		memset(numbers, '\0', sizeof(numbers));
		memcpy(numbers, preg + pmatch[3].rm_so, pmatch[3].rm_eo - pmatch[3].rm_so);
		y = atof(numbers);
		
		adjacency_list_add_node(al, id, x, y);	
	}

	regfree(&reg);
}

void add_links(struct adjacency_list *al, FILE *filp)
{
	const char *link_pattern = 
	    "^<link.*node=(-{0,1}[1-9][0-9]*).*node=(-{0,1}[1-9][0-9]*).*length=([0-9]+[.]{0,1}[0-9]+).*/link>";
	regex_t reg;
	int err_code;
	char preg[MAX_LINE];
	regmatch_t pmatch[MAX_MATCH];
	char err_string[MAX_ERROR];
	char numbers[MAX_NUMBER_LINE];
	long id0, id1;
	float len;

	fseek(filp, 0L, SEEK_SET);

	err_code = regcomp(&reg, link_pattern, REG_EXTENDED);
	if (err_code) {
		regerror(err_code, &reg, err_string, sizeof(err_string));
		printf("err: %s\n", err_string);
		exit(-1);
	}

	while (!feof(filp)) {
		fgets(preg, sizeof(preg), filp);
		// printf("%s", preg);
		
		err_code = regexec(&reg, preg, MAX_MATCH, pmatch, 0);
		if (err_code) {
			regerror(err_code, &reg, err_string,
				 sizeof(err_string));
			// printf("err: %s\n", err_string);
			continue;
		}

		memset(numbers, '\0', sizeof(numbers));
		memcpy(numbers, preg + pmatch[1].rm_so,
		       pmatch[1].rm_eo - pmatch[1].rm_so);
		// printf("%ld\t", atol(numbers));
		id0 = atol(numbers);
	
		memset(numbers, '\0', sizeof(numbers));
		memcpy(numbers, preg + pmatch[2].rm_so,
		       pmatch[2].rm_eo - pmatch[2].rm_so);
		// printf("%ld\t", atol(numbers));
		id1 = atol(numbers);

		memset(numbers, '\0', sizeof(numbers));
		memcpy(numbers, preg + pmatch[3].rm_so,
		       pmatch[3].rm_eo - pmatch[3].rm_so);
		// printf("%f\n", atof(numbers));
		len = atof(numbers);

		adjacency_list_add_link(al, id0, id1, len);	
	}
	regfree(&reg);
}

int main(int argc, char **argv)
{
	FILE *filp = NULL;
	struct adjacency_list *al = init_adjacency_list(MAX_NODES);
	long s, e;

	if ((filp = fopen(argv[1], "r")) == NULL) {
		printf("Open failed.\n");
		exit(-1);
	}
	add_nodes(al, filp);
	add_links(al, filp);

	fclose(filp);
	// hash_table_search_by_inc(al->al_ht, 2100);

	printf("Enter start node id and end node id: ");
	scanf("%ld%ld", &s, &e);
	
	adjacency_list_shortest_path(al, s, e, "map_out_result");
	adjacency_list_disp(al, "map_out_node", "map_out_link");
	clear_adjacency_list(al);
	return 0;
}
