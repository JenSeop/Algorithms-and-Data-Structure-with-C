#ifndef ___ChainHash
#define ___ChainHash

#include "Member.h"

// Bucket Node
typedef struct __node {
  Member  data;
  struct __node *next;
} Node;

// Hash Table
typedef struct {
  int size;
  Node **table;
} ChainHash;

// Initialize Hash Table
int Initialize(ChainHash *h, int size);

// Search
Node *Search(const ChainHash *h, const Member *x);

// Add Data
int Add(ChainHash *h, const Member *x);

// Delete Data
int Remove(ChainHash *h, const Member *x);

// Dump Hash Table
void Dump(const ChainHash *h);

// Delete All Data
void Clear(ChainHash *h);

// Exit Hash Table
void Terminate(ChainHash *h);

#endif