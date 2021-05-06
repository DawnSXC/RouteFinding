#include "hash.h"
#include "adjacency_list.h"
#include <stdio.h>

int main()
{
	int i, j;
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

	clear_hash_table(pht);


	struct adjacency_list *al = init_adjacency_list(20);
	for (i = 1; i < 15; ++i)
		adjacency_list_add_node(al, i);

	for (i = 1; i < 15; ++i)
		for (j = 1; j < 15; ++j)
			if (i < j)
				adjacency_list_add_link(al, i, j, 1);

	adjacency_list_disp(al);
	clear_adjacency_list(al);
}
