#include "hash.h"
#include "adjacency_list.h"
#include <stdio.h>

int main()
{
	int i, j;
	int false = 0;

	struct hash_table *pht = init_hash_table(5);
	printf("init_hash_table OK\n");

	for (i = -10; i < 20; ++i)
		hash_table_insert(pht, i, 100 +i);
	printf("hash_table_insert OK\n");

	for (i = -20; i < 25; ++i) {
		if (hash_table_search(pht, i))
			printf("%d find\n", i);
		else
			printf("%d not find\n", i);
	}

	for (i = -20; i < 25; ++i) {
		if ((i < -10 || i >=20) && hash_table_search(pht, i)) {
			false = 1;
			break;
		}
		else if ((i >= -10 && i < 20) && !hash_table_search(pht,i)) {
			false = 1;
			break;
		}
	}
	if (!false)
		printf("hash_table_insert AND hash_table_search CHECK OK\n");
	else
		printf("hash_table_insert AND hash_table_search CHECK FAILED\n");

	clear_hash_table(pht);


	struct adjacency_list *al = init_adjacency_list(20);
	for (i = 1; i < 15; ++i)
		adjacency_list_add_node(al, i, i, i);

	printf("Shortest path for empty graph:\n");
	adjacency_list_shortest_path(al, 1, 3, "test_empty_shortest_path");

	printf("Shortest path for non-empty graph\n");
	adjacency_list_add_link(al, 1, 3, 1);
	adjacency_list_add_link(al, 3, 6, 1);
	adjacency_list_add_link(al, 1, 6, 3);

	adjacency_list_shortest_path(al, 1, 6, "test_short_path");	

	adjacency_list_disp(al, "test_node", "test_link");
	clear_adjacency_list(al);
}
