#include "pila.h"

#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;  //Array de punteros genericos(tamaño sin especificar)
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t *pila_crear(void){
    pila_t* pila = calloc(1, sizeof(pila_t));
    pila->datos = calloc(2, sizeof(void*));
    pila->capacidad = 2;
    return pila;
    
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
    if(!pila) return;
    if(pila->datos) free(pila->datos);
    free(pila);
}

// Devuelve verdadero si la pila no tiene elementos apilados, false en caso contrario.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){
    if(!pila || pila->cantidad == 0) return true;
    return false;
}


void expandir(pila_t* pila){
    if(pila && pila->datos){
        void** datos = realloc(pila->datos, pila->capacidad*2*sizeof(void*));
        if(datos){
            pila->datos = datos;
        }
        pila->capacidad = pila->capacidad*2;
    }
}


void reducir(pila_t* pila){
    if(pila && pila->datos){
        void** puntero = realloc(pila->datos, pila->capacidad/2*sizeof(void*));
        if(puntero){
            pila->datos = puntero;
            pila->capacidad = pila->capacidad/2;
        }
    }
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void *valor){
    if(!pila) return false;
    if(pila->cantidad*2 == pila->capacidad ){
        expandir(pila);
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void *pila_ver_tope(const pila_t *pila){
    if(!pila || pila->cantidad == 0) return NULL;
    return pila->datos[pila->cantidad -1];

}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void *pila_desapilar(pila_t *pila){
    if(!pila || pila->cantidad == 0) return NULL;
    void* valor = pila_ver_tope(pila);
    pila->datos[pila->cantidad -1] = NULL;
    pila->cantidad--;
    if(pila->cantidad == pila->capacidad/4 && pila && pila->capacidad >= 4){
        reducir(pila);
    }
    return valor;

}


// ...
