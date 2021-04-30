#ifndef __GRAPH_ADJACENCY_LIST_H__
#define __GRAPH_ADJACENCY_LIST_H__

#include "list.h"
#include "hash.h"
#include <stdio.h>
#include <float.h>

struct link {
	float l_len;
	long l_oid;
	struct list_head l_list;
};

struct adjacency_list {
	int al_size;
	int al_curr;
	struct hash_table *al_ht;
	struct list_head *al_head;
	long *al_real_id;
	int *al_flags;
	float *al_lens;
	long *al_paths;
	float *al_x;
	float *al_y;
};

static inline struct adjacency_list *init_adjacency_list(int size)
{
	struct adjacency_list *al;
	int i;

	al = (struct adjacency_list *)malloc(sizeof(struct adjacency_list));
	al->al_head = (struct list_head *)malloc(sizeof(struct list_head) * size);
	al->al_size = size;
	al->al_curr = 0;
	al->al_ht = init_hash_table(size / 2);
	al->al_real_id = (long *)malloc(sizeof(long) * size);
	al->al_flags = (int *)malloc(sizeof(int) * size);
	al->al_lens = (float *)malloc(sizeof(float) * size);
	al->al_paths = (long *)malloc(sizeof(long) * size);
	al->al_x = (float *)malloc(sizeof(float) * size);
	al->al_y = (float *)malloc(sizeof(float) * size);

	for (i = 0; i < size; ++i)
		init_list_head(al->al_head + i);

	return al;
}

/*
static inline void adjacency_list_set_source(struct adjacency_list *al, long id)
{
	int i;
	long k0, k1;
	struct hash_entry *phe;	
	struct link *pl;
	
	for (i = 0; i < al->al_curr; ++i) {
		al->al_flags[i] = 0;
		al->al_lens[i] = FLT_MAX;
		al->al_paths[i] = -1;
	}

	phe = hash_table_search(al->al_ht, id);
	k0 = phe->h_map->m_inc; 

	al->al_flags[k0] = 1;
	al->al_lens[k0] = 0;
	list_for_each_entry(pl, al->al_head + k0, l_list) {
		al->al_lens[pl->l_oid] = pl->l_len;
		al->al_paths[pl->l_oid] = k0;
	}
}
*/

static inline void adjacency_list_shortest_path(struct adjacency_list *al, long id, long ide, const char *name_result)
{
	int i, v;
	float min_len;
	long k0, k1;
	struct hash_entry *phe;	
	struct link *pl;

	for (i = 0; i < al->al_curr; ++i) {
		al->al_flags[i] = 0;
		al->al_lens[i] = FLT_MAX;
		al->al_paths[i] = -1;
	}

	phe = hash_table_search(al->al_ht, id);
	k0 = phe->h_map->m_inc; 
	phe = hash_table_search(al->al_ht, ide);
	k1 = phe->h_map->m_inc;

	al->al_flags[k0] = 1;
	al->al_lens[k0] = 0;
	list_for_each_entry(pl, al->al_head + k0, l_list) {
		al->al_lens[pl->l_oid] = pl->l_len;
		al->al_paths[pl->l_oid] = k0;
	}

	while (1) {
		v = -1;
		min_len = FLT_MAX;
		for (i = 0; i < al->al_curr; ++i) 
			if (al->al_flags[i] != 1 && al->al_lens[i] < min_len) {
				v = i;
				min_len = al->al_lens[i];
			}
		if (v == -1)
			break;

		al->al_flags[v] = 1;
		list_for_each_entry(pl, al->al_head + v, l_list)
			if (pl->l_len + min_len < al->al_lens[pl->l_oid]) {
				al->al_lens[pl->l_oid] = pl->l_len + min_len;
				al->al_paths[pl->l_oid] = v;
			}
	}
    // no roads 
	if (al->al_lens[k1] == FLT_MAX) {
		printf("No roads between %ld and %ld.\n", id, ide); 
		return;
	}
    
	FILE *filp_result = NULL;
	if ((filp_result = fopen(name_result, "w")) == NULL) {
		printf("Open failed.\n");
		exit(-1);
	}
    // find roads
	float ll = al->al_lens[k1];
	printf("Find roads between %ld and %ld: \n\t", ide, id);
	printf("%ld ", ide);
	while (al->al_paths[k1] != -1) {
		// phe = hash_table_search_by_inc(al->al_ht, al->al_paths[k1]);
		// printf("%ld\t", phe->h_map->m_id);
		printf(" <--> %ld", al->al_real_id[al->al_paths[k1]]);
		fprintf(filp_result, "set arrow from %f,%f to %f,%f lt 3 lw 2\n", al->al_x[al->al_paths[k1]], al->al_y[al->al_paths[k1]], al->al_x[k1], al->al_y[k1]);
		k1 = al->al_paths[k1];
	}
	//store found data
	fclose(filp_result);
	printf("\n");
	printf("Length:\n\t%f\n", ll);
	return;
}
// add node to adjacency_list
static inline int adjacency_list_add_node(struct adjacency_list *al, long id, float x, float y)
{
	struct hash_entry *p_hash_entry;
	int ret;

	if ((p_hash_entry = hash_table_search(al->al_ht, id)))
		return p_hash_entry->h_map->m_inc;
	else {
		hash_table_insert(al->al_ht, id, al->al_curr);
		al->al_real_id[al->al_curr] = id;
		al->al_x[al->al_curr] = x;
		al->al_y[al->al_curr] = y;
		ret = al->al_curr;
		al->al_curr++;
		return ret;
	}
}




#endif // __GRAPH_ADJACENCY_LIST_H__
