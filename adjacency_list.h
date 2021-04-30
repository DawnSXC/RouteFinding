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






#endif // __GRAPH_ADJACENCY_LIST_H__
