#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

#include "coumap/cmap.h"
#include "coumap/util.h"
#include "coumap/hash.h"

typedef struct hashmap {
  struct cmap cmap;
  struct cmap_position cmap_position;
  int (*data_cmp)(void * d1, void * d2);
  void (*data_free)(void * data);
} hashmap;

typedef struct hashmap_node {
  struct cmap_node cmap_node;
  void * data;
} hashmap_node;

hashmap * hashmap_init(int (*data_cmp)(void * d1, void * d2), void (*data_free)(void * data)) {
  hashmap * map = (hashmap *)malloc(sizeof(hashmap));
  cmap_init(&(map->cmap));
  map->data_cmp = data_cmp;
  map->data_free = data_free;
  return map;
}

void hashmap_free(hashmap * map) {
  hashmap_node *node;
  HASHMAP_FOR_EACH(map, node) {
    hashmap_node_free(node, map->data_free);
  }
  free(map);
}

hashmap_node * hashmap_node_init(void * data) {
  hashmap_node * map_node = (hashmap_node *)malloc(sizeof(hashmap_node));
  map_node->data = data;
  return map_node;
}

void hashmap_node_free(hashmap_node * node, void (*data_free)(void * data)) {
  data_free(node->data);
}

size_t hashmap_insert(hashmap * map, hashmap_node * node, uint32_t hash) {
  return cmap_insert(&(map->cmap), &(node->cmap_node), hash);
}

size_t hashmap_remove(hashmap * map, hashmap_node * node, uint32_t hash) {
  return cmap_remove(&(map->cmap), &(node->cmap_node), hash);
}

hashmap_node * hashmap_find(hashmap * map, uint32_t hash, void * data) {
  hashmap_node * hashmap_node;
  const struct cmap_node * cmap_node;

  CMAP_FOR_EACH_WITH_HASH(hashmap_node, cmap_node, hash, &(map->cmap)) {
    if (map->data_cmp(hashmap_node->data, data) == 0) {
      return hashmap_node;
    }
  }
  return NULL;
}

size_t hashmap_count(hashmap * map) {
  return cmap_count(&(map->cmap));
}

void * hashmap_node_get_data(hashmap_node * node) {
  return node->data;
}

void hashmap_foreach_init(hashmap *map) {
  map->cmap_position.bucket = 0;
  map->cmap_position.entry = 0;
  map->cmap_position.offset = 0;
}

hashmap_node * hashmap_foreach_next(hashmap *map, hashmap_node *node) {
  struct cmap_node *cmap_node;
  cmap_node = cmap_next_position(&(map->cmap), &(map->cmap_position));
  return OBJECT_CONTAINING(cmap_node, node, cmap_node);
}

uint32_t get_hash_pointer(const void *p, uint32_t basis) {
  return hash_pointer(p, basis);
}

uint32_t get_hash_string(const char *c, uint32_t basis) {
  return hash_string(c, basis);
}
