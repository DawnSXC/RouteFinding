#ifndef __GRAPH_HASH_H__
#define __GRAPH_HASH_H__

#include "list.h"

struct map_table {
	long m_id;
	long m_inc;
};

struct hash_table {
	struct list_head *h_head;
	int h_size;
};

struct hash_entry {
	struct map_table *h_map;
	struct list_head h_list;
};

static inline struct hash_table *init_hash_table(int size)
{
	int i;
	struct hash_table *h;

	h = (struct hash_table *)malloc(sizeof(struct hash_table));
	h->h_head = (struct list_head *)malloc(sizeof(struct list_head) * size);
	h->h_size = size;
	for (i = 0; i < size; ++i)
		init_list_head(h->h_head + i);

	return h;
}

static inline int hash_func(struct hash_table *h, long k)
{
	k = k < 0 ? -k : k;
	return k % h->h_size;
}

static inline struct hash_entry *hash_table_search(struct hash_table *h, long id)
{
	long key = hash_func(h, id);

	struct hash_entry *p_hash_entry;
	list_for_each_entry(p_hash_entry, h->h_head + key, h_list)
		if (p_hash_entry->h_map->m_id == id)
			return p_hash_entry;
	return NULL;
}
		
		
#endif // __GRAPH_HASH_H__
