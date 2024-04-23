#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUCKET_SIZE 10007 // 20011 10007
#define REV_ENDIAN(n) ((uint16_t)(((n) >> 8) | (n) << 8))

struct Bucket* hashTable = NULL; 

struct Tuples {
    uint32_t src_ip;
    uint32_t dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t protocol;
};

struct Node {
    int key;
    int val;
    struct Tuples tuple;
    struct Node* next;
};

struct Bucket{
    struct Node* head;
    int count;
};

struct Node* createNode(int key, int val, struct Tuples tuple){
    struct Node* newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->key = key;
    newNode->val = val;
    newNode->tuple = tuple;
    newNode->next = NULL;

    return newNode;
}

uint32_t hashSession(struct Tuples tuple){
    uint32_t hash = 5381;

    hash = ((hash << 5) + hash) ^ (tuple.src_ip ^ tuple.dst_ip);
    hash = ((hash << 5) + hash) ^ tuple.src_port;
    hash = ((hash << 5) + hash) ^ tuple.dst_port;
    hash = ((hash << 5) + hash) ^ tuple.protocol;
    
    return hash % BUCKET_SIZE;
}

uint32_t hashSession2(struct Tuples tuple){
    uint32_t hash = 5381;

    hash += tuple.src_ip ^ tuple.dst_ip | tuple.src_port ^ tuple.dst_port | tuple.protocol;

    return hash % BUCKET_SIZE;
}

uint32_t hashSession3(struct Tuples tuple){
    uint32_t hash = hashSession(tuple);
    uint32_t BitsUint32 = sizeof(uint32_t) * 24;
    uint32_t TwelveSisteen = (BitsUint32 * 12) / 16;
    uint32_t OneEighth = BitsUint32 / 8;
    uint32_t HighBits = 0XFFFFFFFF << (BitsUint32 - OneEighth);

    for (int idx = 0; idx < 5; idx++)
    {
        hash = (hash << OneEighth) + hash;
        if(hash & HighBits)
        {
            hash = ((hash ^ (hash >> TwelveSisteen)) & HighBits);
        }
    }
    return hash % BUCKET_SIZE;
}

void add(int key, int val, struct Tuples tuple){
    
    int hashIndex = hashSession(tuple);
    
    struct Node* newNode = createNode(key, val, tuple);
    
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode;
    }
    
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

void remove_key(int key, struct Tuples tuple){
    int hashIndex = hashSession(tuple);
    
    int flg = 0;
    
    struct Node* node;
    struct Node* before;
    
    node = hashTable[hashIndex].head;
    
    while (node)
    {
        if (node->key == key){
            
            if (node == hashTable[hashIndex].head){
                hashTable[hashIndex].head = node->next;
            }
            else{
                before->next = node->next;
            }
            
            hashTable[hashIndex].count--;
            free(node);
            flg = 1;
        }
        before = node;
        node = node->next;
    }
    
    if (flg)
        printf("\n [ %d ] deleted.\n", key);
    else
        printf("\n [ %d ] donst exist.\n", key);
}

void search(int key, struct Tuples tuple){
    int hashIndex = hashSession(tuple);
    struct Node* node = hashTable[hashIndex].head;
    int flg = 0;
    while (node)
    {
        if (node->key == key){
            flg = 1;
            break;
        }
        node = node->next;
    }
    if (flg)
        printf("\n key [ %d ], val [ %d ]\n", node->key, node->val);
    else
        printf("\n dont exist. \n");
}

void display(){
    
    struct Node* iterator;
    int col = 0;
    int non_col = 0;
    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        int flg = 0;
        iterator = hashTable[i].head;
        if(iterator)
        {
            printf("Bucket[%d] :\n", i);
            while (iterator)
            {
                if(flg)
                    col++;
                else
                    non_col++;
                printf("Session[%u] = { src_ip %d.%d.%d.%d, dst_ip %d.%d.%d.%d, src_port %u, dst_port %u, proto %u}  ->\n",
                    hashSession(iterator->tuple),

                    (iterator->tuple.src_ip>>24) & 0XFF,(iterator->tuple.src_ip>>16) & 0XFF,
                    (iterator->tuple.src_ip>>8) & 0XFF,(iterator->tuple.src_ip>>0) & 0XFF,

                    (iterator->tuple.dst_ip>>24) & 0XFF,(iterator->tuple.dst_ip>>16) & 0XFF,
                    (iterator->tuple.dst_ip>>8) & 0XFF,(iterator->tuple.dst_ip>>0) & 0XFF,

                    REV_ENDIAN(iterator->tuple.src_port),REV_ENDIAN(iterator->tuple.dst_port),
                    iterator->tuple.protocol
                );
                iterator = iterator->next;
                flg++;
            }
            printf("\n");
        }
    }
    printf("\n========= display complete ========= \n");
    printf("col = %d non_col = %d\n",col,non_col);
}

int main(){
    
    hashTable = (struct Bucket *)malloc(BUCKET_SIZE * sizeof(struct Bucket));
    
    for (int i=0; i < 39; i++){
        struct Tuples tuple = { 3232235777 + i, 2886794753 - i, 53764, 20480, 6 + (i/10)};
        add(i, 10*i, tuple);
    }

    display();
}