#include <printf.h>
#include <stdlib.h>
#include "circular_buffer.h"

int cb_get_int(circular_buffer *const *cb1, int *i);

char cb_get_char(circular_buffer *const *cb1, char *c) {
    if (cb_pop(c, cb1)) printf("%c\n", *c);
    else if (cb_errorcode(cb1) == 10) printf("Ultimo elemento raggiunto.\n");
    else printf("Errore sconosciuto");
    return *c;
}

int main() {
    int n_elements = 200;
    circular_buffer *cb[n_elements];
    cb[0] = cb_init(10, sizeof(char));
    cb[1] = cb_init(10, sizeof(int));
    int i = 10;
    cb_push(&i, cb[0]);
    i = 50;
    cb_push(&i, cb[0]);
    char c = 'a';
    cb_push(&c, cb[1]);
    //Assegno un nuovo valore per vedere se il pop funziona
    i = 20;

    cb_get_int(cb[0], &i);
    cb_get_int(cb[0], &i);
    cb_get_int(cb[0], &i);
    cb_get_char(cb[1], &c);
    cb_get_char(cb[1], &c);
    return 0;
}

int cb_get_int(circular_buffer *const *cb1, int *i) {
    if (cb_pop(i, cb1)) printf("%d\n", (*i));
    else if (cb_errorcode(cb1) == 10) printf("Ultimo elemento raggiunto.\n");
    return (*i);
}

