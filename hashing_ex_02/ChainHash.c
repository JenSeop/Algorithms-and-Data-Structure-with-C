#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "ChainHash.h"

// Hash Function
static int hash(int key, int size)
{
  return key % size;
}

// Set Member Data in Node
static void SetNode(Node *n, const Member *x, const Node *next)
{
  n->data = *x;   // data
  n->next = next; // next data
}

// Initialize Hash Table
int Initialize(ChainHash *h, int size)
{
  if((h->table = calloc(size, sizeof(Node *))) == NULL)
  {
    h->size = 0;
    return 0;
  }

  h->size = 0;
  for(int idx = 0; idx < size; idx++) // Set all bucket NULL
    h->table[idx] = NULL;
    return 1;
}

// Search Hash Table
Node *Search(const ChainHash *h, const Member *x)
{
  int key = hash(x->no, h->size); // Target Hash
  Node *p = h->table[key];        // Node State->Now

  while(p != NULL)
  {
    if(p->data.no == x->no) // Search Success
      return p;
    p = p->next;            // Move Next Node
  }
  return NULL;  // Search Fail
}

// Add Data
int Add(ChainHash *h, const Member *x)
{
  int key = hash(x->no, h->size); // Add Data Hash
  Node *p = h->table[key];        // Node State->Now
  Node *temp;

  while(p != NULL)
  {
    if(p->data.no == x->no) // Exist key
      return 1; // Add fail
    p = p->next;  // Move next node
  }

  if((temp = calloc(1, sizeof(Node))) == NULL)
    return 2;
  SetNode(temp, x, h->table[key]);  // Set data in Add node
  h->table[key] = temp;
  return 0; // Add success
}

// Delete Data
int Remove(ChainHash *h, const Member *x)
{
  int key = hash(x->no, h->size); // Delete Data Hash
  Node *p = h->table[key];  // Node State->Now
  Node **pp = &h->table[key]; // Node State->Now Pointer

  while(p != NULL)
  {
    if(p->data.no == x->no) // Search
    {
      *pp = p->next;
      free(p);  // Free
      return 0; // Delete Success
    }

    pp = &p->next;
    p = p->next;  // Set Next Node
  }
  
  return 1; // Delete Fail (Not Exist)
}

// Dump Hash Table
void Dump(const ChainHash *h)
{
  for (int idx = 0; idx < h->size; idx++)
  {
    Node *p = h->table[idx];
    printf("%02d  ", idx);
    while(p != NULL)
    {
      printf("-> %d (%s)  ", p->data.no, p->data.name);
      p = p->next;
    }
    putchar('\n');
  }
}

// Delete All Data
void Clear(ChainHash *h)
{
  for(int idx = 0; idx < h->size; idx++)
  {
    Node *p = h->table[idx]; // Node State->Now
    while(p != NULL)
    {
      Node *next = p->next;
      free(p);  // Node State->Now Free
      p = next; // Set Next Node
    }
    h->table[idx] = NULL;
  }
}

// Exit Hash Table
void Terminate(ChainHash *h)
{
  Clear(h);         // Delete All Data
  free(h->table);   // Hash Table Array Free
  h->size = 0;      // Reset Hash Table Size
}