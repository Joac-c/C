#include "cola.h"
#include "testing.h"
#include "stdlib.h"
#include "stdio.h"

#define ITERACIONES 20
#define COLAS 20


static void prueba_crear_destruir(void) {
    printf("\nPruebas de crear y destruir cola\n\n");
    cola_t *cola = cola_crear();
    print_test("La cola se crea exitosamente", cola);
    print_test("La cola se crea vacia", cola_esta_vacia(cola) == true );
    cola_destruir(cola, NULL);
}

static void prueba_borde_recien_creada(void){
    printf("\nCasos borde con la cola recien creada \n\n");
    cola_t *cola = cola_crear();
    print_test("El primer elemento de una cola vacia es nulo", cola_ver_primero(cola) == NULL);
    print_test("Borrar un elemento de la cola vacia devuelve NULL", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
}


static void prueba_encolar_simple(void){
    printf("\n Pruebas basicas de encolar\n\n");
    int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

    cola_t *cola = cola_crear();
    print_test("Encolar devuelve true", cola_encolar(cola, &valores[0]) == true);
    print_test("El elemento encolado es el primero", cola_ver_primero(cola) == &valores[0]);
    print_test("Encolo otro elemento", cola_encolar(cola, &valores[1]) == true);
    print_test("El segundo elemento encolado es el primero", cola_ver_primero(cola) == &valores[0]);
    print_test("Encolo un tercer elemento", cola_encolar(cola, &valores[0]) == true);
    print_test("El tercer elemento encolado es el primero", cola_ver_primero(cola) == &valores[0]);
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
}

static void prueba_encolar_NULL(void){
    printf("\n Prueba de encolar NULL\n\n");

    cola_t *cola = cola_crear();
    print_test("El apilamiento del elemento NULL es válido", cola_encolar(cola, NULL) == true);
    cola_destruir(cola, NULL);
}

static void prueba_cola_desencolar_simple(void){
    printf("\nPruebas basicas de desencolar\n\n");
    cola_t *cola = cola_crear();
    int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

    cola_encolar(cola, &valores[0]);
    cola_encolar(cola, &valores[1]);
    cola_encolar(cola, &valores[2]);
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[0]);
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[1]);
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[2]);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
}

void prueba_encolar_cola_desencolar_simple_intercalado(){
    printf("\nPruebas basicas de encolar y cola_desencolar intercalados\n\n");
    int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

    cola_t *cola = cola_crear();
    print_test("Encolo un elemento", cola_encolar(cola, &valores[0]));
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[0]);
    print_test("Encolo un elemento", cola_encolar(cola, &valores[1]));
    print_test("Encolo un elemento", cola_encolar(cola, &valores[2]));
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[1]);
    print_test("Encolo un elemento", cola_encolar(cola, &valores[3]));
    print_test("Encolo un elemento", cola_encolar(cola, &valores[4]));
    print_test("Encolo un elemento", cola_encolar(cola, &valores[5]));
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[2]);
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[3]);
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[4]);
    print_test("cola_desencolar devuelve el primero correcto", cola_desencolar(cola) == &valores[5]);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);

}





void prueba_encolar_varios(){
    printf("\nprueba de encolar masivamente \n\n");
    int encolados = 0;
    int correctos = 0;
    bool seguimos = true;
    int* vector[ITERACIONES];

    cola_t *cola = cola_crear();
    while (encolados < ITERACIONES && seguimos == true)
    {   
        if(cola_encolar(cola, &vector[encolados]) == true) encolados++;
        if(cola_ver_primero(cola) == &vector[0]) correctos++;
        else seguimos = false;
    
    }
    print_test("Se acolan 1000 elementos exitosamente",  (ITERACIONES == encolados && correctos == ITERACIONES));
    printf("encolados totales = %d, primeros correctos totales = %d\n",  encolados, correctos);
    cola_destruir(cola, NULL);
}




void prueba_cola_desencolar_varios(){
    printf("\nprueba de cola_desencolar masivamente \n\n");
    int desencolados = 0;
    int correctos = 0;
    int* vector[ITERACIONES];
    void* actual;

    cola_t *cola = cola_crear();
    for(int i = 0; i < ITERACIONES; i++) cola_encolar(cola, &vector[i]);
    while (desencolados < ITERACIONES){   
        actual = cola_desencolar(cola);
        if(actual) desencolados++;
        if(actual == &vector[correctos]) correctos++;
    
    }
    print_test("Se cola_desencolaron 1000 elementos exitosamente",  (ITERACIONES == desencolados && correctos == ITERACIONES));
    printf("desencolados totales = %d, primeros correctos totales = %d\n",  desencolados, correctos);
    cola_destruir(cola, NULL);
}

void prueba_encolar_cola_desencolar_intercalado(){
    printf("\n Pruebas de encolar y cola_desencolar intercaladamente \n\n");
    int* vector[ITERACIONES];
    int encolados = 0;
    int desencolados = 0;
    cola_t *cola = cola_crear();

    for(int i = 0; i < ITERACIONES; i++){
        if(cola_encolar(cola, &vector[i])) encolados++;
        if(i%2 != 0) if(cola_desencolar(cola)) desencolados++;
    }
    print_test("Se encolaron y cola_desencolaron intercaladamente muchos elementos exitosamente",  (ITERACIONES == encolados && desencolados == ITERACIONES/2));
    cola_destruir(cola, NULL);
}


void prueba_cola_vaciada(){
    printf("\n Pruebas con la cola vaciada tras estar llena \n\n");
    cola_t *cola = cola_crear();
    int* vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) cola_encolar(cola, &vector[i]);
    for(int i = 0; i < ITERACIONES; i++) cola_desencolar(cola);
    print_test("La cola vaciada esta efectivamente vacia", cola_esta_vacia(cola) == true);
    print_test("cola_desencolar con la cola vaciada devuelve NULL", cola_desencolar(cola) == NULL);
    print_test("Ver_primero con la cola vaciada devuelve NULL", cola_ver_primero(cola) == NULL);
    cola_destruir(cola, NULL);
}


void destructor(void* elemento){
    free((int*)elemento);
}

void destructor_comp(void* cola){
    cola_destruir((cola_t*)cola, destructor);
}
typedef struct vector{
    size_t tamano;
    int** elems;
} vector_t;

void destructor_vec_punt(void* vector){
    vector_t* vec = (vector_t*)vector;
    for(size_t i = 0; i < vec->tamano; i++) free(vec->elems[i]);
    free(vec->elems);
    free(vec); 
}

void pruebas_cola_destruir(){
    printf("\n Pruebas de cola_destruir (Si fallan lo muestra valgrind)\n\n");
    
    printf("Prueba destruir con destructor NULL\n");
    cola_t *cola = cola_crear();
    int* vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) cola_encolar(cola, &vector[ITERACIONES]);
    cola_destruir(cola, NULL);
    
    printf("Prueba destruir con destructor liberando elementos con free\n");
    cola = cola_crear();
    for(int i = 0; i < ITERACIONES; i++) cola_encolar(cola, calloc(1, sizeof(int)));
    cola_destruir(cola, destructor);
    
    printf("Prueba destruir una cola de colas\n");
    cola = cola_crear();
    cola_t* subcola;
    for(int i = 0; i < COLAS; i++){
        subcola = cola_crear();
        for(int q = 0; q < ITERACIONES; q++) cola_encolar(subcola, calloc(1, sizeof(int)));
        cola_encolar(cola, subcola);
    } 
    cola_destruir(cola, destructor_comp);
    
     printf("Prueba destruir liberando una cola con vectores dinamicos de punteros dinamicos\n");
    cola = cola_crear();
    vector_t* vec;
    for(int i = 0; i < COLAS; i++){
        vec = calloc(1, sizeof(vector_t));
        for(int q = 0; q < ITERACIONES; q++){
            vec->tamano++;
            vec->elems = realloc(vec->elems, sizeof(int*)*vec->tamano);
            vec->elems[q] = calloc(1, sizeof(int));  
        } 
        cola_encolar(cola, vec);
    }
    cola_destruir(cola, destructor_vec_punt);

}


void pruebas_cola_estudiante() {

    // ...
    prueba_crear_destruir();
    prueba_borde_recien_creada();
    prueba_encolar_simple();
    prueba_encolar_NULL();
    prueba_cola_desencolar_simple();
    prueba_encolar_cola_desencolar_simple_intercalado();
    prueba_encolar_varios();
    prueba_cola_desencolar_varios();
    prueba_encolar_cola_desencolar_intercalado();
    prueba_cola_vaciada();
    pruebas_cola_destruir();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}


#endif
