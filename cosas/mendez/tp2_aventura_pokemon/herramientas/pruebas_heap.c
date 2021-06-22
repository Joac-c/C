#include "heap.h"
#include <stdio.h>
#include <stdbool.h>
#define TILDE "✓"
#define CRUZ "✗"
#define AMARILLO "\e[33m"
#define NORMAL "\e[0m"
#define ROJO "\e[31m"
#define AZUL "\e[34m"
#define ERROR -1
#define EXITO 0
#define TOPE 17
int exitosas = 0;
int fallidas = 0;
int verificaciones = 0;


int comparador(void* primero, void* segundo){
    if(!primero || !segundo) return -2;
    if(*(int*)primero == *(int*)segundo) return 0;
    if(*(int*)primero > *(int*)segundo) return 1;
    if(*(int*)primero < *(int*)segundo) return -1;
    return -2;
}

void verificar(bool afirmacion, const char* texto){
    if(afirmacion){
        printf(AZUL "\n" TILDE);
        exitosas++;
    }
    else{
        fallidas++;
        printf(ROJO "\n" CRUZ);
    }
    printf(NORMAL "%d -%s \n",verificaciones, texto);
    verificaciones++;
    fflush(stdout);

}

int** elementos_prueba(int** elementos){
    int indices[] = {8, 4, 12, 2, 6, 10, 14, 15, 1, 13, 9, 3, 11, 5, 7, 8, 6};
    for(int i = 0; i != TOPE; i++){
        elementos[i] = calloc(1, sizeof(int));
        *(elementos[i]) = indices[i];
    }
    return elementos;
}

int pruebas_insercion(){
    int** elementos = calloc(TOPE, sizeof(int*));
    elementos = elementos_prueba(elementos);
    heap_t* heap = crear_heap(TOPE);
    verificar((heap != NULL), "heap creado");
    verificar((heap_insertar(elementos[0], heap, comparador)) == 1, "incerto un elemento");
    verificar((heap_devolver_raiz(heap) == elementos[0]), "La raiz es correcta");
    verificar((heap_insertar(elementos[1], heap, comparador)) == 1, "incerto un elemento");
    verificar((heap_devolver_raiz(heap) == elementos[1]), "La raiz es correcta");
    verificar((heap_borrar_raiz(heap, comparador) == 1), "borro la raiz con exito");
    verificar((heap_devolver_raiz(heap) == elementos[0]), "La raiz es correcta");
    verificar((heap_borrar_raiz(heap, comparador) == 1), "borro la raiz con exito");
    verificar((heap_devolver_raiz(heap) == NULL), "La raiz es correcta");

    verificar((heap_insertar(elementos[0], heap, comparador)) == 1, "incerto un elemento");
    verificar((heap_devolver_raiz(heap) == elementos[0]), "La raiz es correcta");
    verificar((heap_insertar(elementos[1], heap, comparador)) == 1, "incerto un elemento");
    verificar((heap_devolver_raiz(heap) == elementos[1]), "La raiz es correcta");
    verificar((heap_borrar_raiz(heap, comparador) == 1), "borro la raiz con exito");
    verificar((heap_devolver_raiz(heap) == elementos[0]), "La raiz es correcta");
    verificar((heap_borrar_raiz(heap, comparador) == 1), "borro la raiz con exito");
    verificar((heap_devolver_raiz(heap) == NULL), "La raiz es correcta");
    int acciones = 0;
    bool seguimos = true;
    //El problema no son los elementos.
    int borden[] = {8, 4, 4, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    while ((acciones < TOPE) && (seguimos == true))
    {
        if(heap_insertar(elementos[acciones], heap, comparador) == 1){
            //printf("%d, ", *(int*)elementos[acciones]);
            verificar((borden[acciones] == *(int*)heap_devolver_raiz(heap)), "La raiz es correcta");
            printf("es %d", *(int*)heap_devolver_raiz(heap));
            acciones++;
        }
        else seguimos = false;
    
    }
    printf("\n");
    verificar((TOPE == acciones), "Realizo multiples inserciones exitosamente incluyendo repetidos");
    printf("Se insertaron %d elementos\n", acciones);
    printf("la raiz es %d\n", *(int*)heap_devolver_raiz(heap));
    verificar((1 == *(int*)heap_devolver_raiz(heap)), "La raiz es correcta");
    
    acciones = 0;
    seguimos = true;
    int orden[] = {1, 2, 3, 4, 5, 6, 6, 7, 8, 8, 9, 10, 11, 12, 13, 14, 15}; 
    while ((acciones < TOPE) && (seguimos == true))
    {
        verificar((orden[acciones] == *(int*)heap_devolver_raiz(heap)), "La raiz es correcta");
        printf("es %d", *(int*)heap_devolver_raiz(heap));
        verificar((heap_borrar_raiz(heap, comparador) == 1), "borro la raiz con exito");
        acciones++;
    }


    for(int i = 0; i != TOPE; i++){
        free(elementos[i]);
    }
    free(heap->vector);
    free(heap);
    free(elementos);
    return 1;

}


int main(int argc, char* argv[]){
    pruebas_insercion();
    
    return 0;
}