#ifndef __HEAP_H__
#define __HEAP_H__

#include "stdlib.h"

typedef struct heap {
    void** vector;
    int tope;
    size_t tamano;
}heap_t;




heap_t* crear_heap(size_t tamano);

int heap_insertar(void* elemento, heap_t* heap, int comparador(void*, void*));

void* heap_devolver_raiz(heap_t* heap);

int heap_borrar_raiz(heap_t* heap, int comparador(void*, void*));

#endif /* __HEAP_H__ */