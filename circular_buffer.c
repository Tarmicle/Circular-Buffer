//
// Created by Enrico on 06.12.16.
//


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "circular_buffer.h"
typedef struct circular_buffer {
    void *buffer;       // data buffer
    void *buffer_end;
    size_t capacity;    // maximum number of items in the buffer
    size_t cursor;      // number of items in the buffer
    size_t sz;          // size of each item in the buffer
    void *head;         // pointer to head
    void *tail;         // pointer to tail
    int error_code;
};

circular_buffer *cb_init(size_t capacity, size_t sz) {
    circular_buffer *cb;
    cb = malloc(sizeof(struct circular_buffer));

    cb->buffer = malloc(capacity * sz);
    if (cb->buffer == NULL) {
        //printf("Error: circular buffer == NULL");
    }
    cb->buffer_end = cb->buffer + capacity * sz;
    cb->capacity = capacity;
    cb->cursor = 0;
    cb->sz = sz;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;
    return cb;
}

void cb_free(circular_buffer *cb) {
    free(cb->buffer);
}

int cb_push(const void *item, circular_buffer *cb) {
    //Se il cursore è uguale alla capictà (overflow)
    if (cb->cursor == cb->capacity) {
        //printf("Errore! Raggiunta capacità massima buffer\n");
        return 0;
    }

    //memcopy(destination, source, size)
    memcpy(cb->head, item, cb->sz);
    //Aggiorno il pointer a head e lo posiziono al prossimo elemento
    cb->head = cb->head + cb->sz;
    if (cb->head == cb->buffer_end)
        cb->head = cb->buffer;
    cb->cursor++;
    return 1;
}

int cb_pop(void *item, circular_buffer *cb) {
    if (cb->cursor == 0) {
        cb->error_code=10;
        return 0;
    }
    memcpy(item, cb->tail, cb->sz);
    cb->tail = cb->tail + cb->sz;
    if (cb->tail == cb->buffer_end)
        cb->tail = cb->buffer;
    cb->cursor--;
    return 1;
}

int cb_errorcode(circular_buffer *cb){
    return cb->error_code;
}