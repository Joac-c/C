#include "heap.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

heap_t* crear_heap(size_t tamano){
    heap_t* heap = calloc(1, sizeof(heap_t));
    if(heap){
        heap->vector = calloc(tamano, sizeof(void*));
        heap->tamano = tamano;
        return heap;   
    }
    return NULL;
}

void cambiar(void**vector, int a, int b){
    void* aux = vector[a];
    vector[a] = vector[b];
    vector[b] = aux;
}

int posicion_padre(int direccion){
    return (direccion-1)/2;
}


int posicion_hijo_derecho(int direccion){
    return 2*direccion+1;
}

int posicion_hijo_izquierdo(int direccion){
    return 2*direccion+2;
}

//widqbwdiqwbdiquwdbiqwudbiqwdubiqwdubii
void subir(int direccion, heap_t* heap, int comparador(void*, void*)){
    if(!heap) return;
    if(direccion == 0) return;
    int padre = posicion_padre(direccion);
    if((comparador(heap->vector[direccion], heap->vector[padre])) == -1) cambiar(heap->vector, direccion, padre);
    else return;
    subir(padre, heap, comparador);
}

void bajar(int direccion, heap_t* heap, int comparador(void*, void*)){
    int derecha = posicion_hijo_derecho(direccion);
    int izquierda = posicion_hijo_izquierdo(direccion);
    if(izquierda >= heap->tope) return;
    if(derecha >= heap->tope || comparador(heap->vector[izquierda], heap->vector[derecha]) == -1 || comparador(heap->vector[izquierda], heap->vector[derecha]) == 0){
        cambiar(heap->vector, direccion, izquierda);
        bajar(izquierda, heap, comparador);
        return;
    }
    cambiar(heap->vector, direccion, derecha);
    bajar(derecha, heap, comparador);

}


int heap_insertar(void* elemento, heap_t* heap, int comparador(void*, void*)){
    //if(completo(heap->tope)) realloc(heap->vector, sizeof(void*)*heap->tope*2);
    if(!elemento || !heap) return 0;
    if(!heap->vector) return 0;
    if(heap->tamano == heap->tope) return 0;
    heap->vector[heap->tope] = elemento;
    subir(heap->tope, heap, comparador);
    heap->tope++;
    return 1;

}

void* heap_devolver_raiz(heap_t* heap){
    if(!heap || heap->tope == 0) return NULL;
    return heap->vector[0];
    return NULL;
}

int heap_borrar_raiz(heap_t* heap, int comparador(void*, void*)){
    if(!heap) return 0;
    if(heap->tope == 0) return 0;
    heap->vector[0] =  heap->vector[heap->tope -1];
    heap->tope--;
    bajar(0, heap, comparador);
    return 1;

}
