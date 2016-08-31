#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hashmap hashmap;
typedef struct hashmap_node hashmap_node;

/* Hash map
 * ===================
 *
 */

/*
 * Returns an initialized hashmap.
 * data_cmp Function pointer to function for data comparison
 */
hashmap * hashmap_init(int (*data_cmp)(void * d1, void * d2), void (*data_free)(void * data));
void hashmap_free(hashmap * map);
hashmap_node * hashmap_node_init(void * data);
void hashmap_node_free(hashmap_node * map_node, void (*data_free)(void * data));
void * hashmap_node_get_data(hashmap_node * node);
size_t hashmap_insert(hashmap * map, hashmap_node * node, uint32_t hash);
size_t hashmap_remove(hashmap * map, hashmap_node * node, uint32_t hash);
hashmap_node * hashmap_find(hashmap * map, uint32_t hash, void * data);

size_t hashmap_count(hashmap * map);

void hashmap_foreach_init(hashmap *map);
hashmap_node * hashmap_foreach_next(hashmap *map, hashmap_node *node);

uint32_t get_hash_pointer(const void *p, uint32_t basis);
uint32_t get_hash_string(const char *c, uint32_t basis);

#define HASHMAP_FOR_EACH(HASHMAP, HASHMAP_NODE)                         \
  hashmap_foreach_init(HASHMAP);                                        \
  while ((HASHMAP_NODE = hashmap_foreach_next(HASHMAP, HASHMAP_NODE)))

#ifdef __cplusplus
}
#endif
