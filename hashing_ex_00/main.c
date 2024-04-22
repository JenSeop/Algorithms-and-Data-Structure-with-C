#include <stdio.h>
#include <stdint.h>

#define TABLE_SIZE 5381

typedef struct {
    uint32_t src_ip;
    uint32_t dest_ip;
    uint16_t src_port;
    uint16_t dest_port;
    uint8_t protocol;
} SessionTuple;

uint32_t hash_session(const SessionTuple* session) {
    uint32_t hash = 5381;

    hash = ((hash << 5) + hash) ^ (session->src_ip ^ session->dest_ip);
    hash = ((hash << 5) + hash) ^ session->src_port;
    hash = ((hash << 5) + hash) ^ session->dest_port;
    hash = ((hash << 5) + hash) ^ session->protocol;

    return hash % TABLE_SIZE;
}

int main() {
    SessionTuple session1 = {
        .src_ip = 3232235777,
        .dest_ip = 2886794753,
        .src_port = 1234,
        .dest_port = 80,
        .protocol = 6
    };

    SessionTuple session2 = {
        .src_ip = 2886794753,
        .dest_ip = 3232235777,
        .src_port = 1234,
        .dest_port = 80,
        .protocol = 6
    };

    printf("Hash for session 1: %u\n", hash_session(&session1));
    printf("Hash for session 2: %u\n", hash_session(&session2));

    return 0;
}