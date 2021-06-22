#include "pila.h"
#include "testing.h"
#include "stdlib.h"
#include "stdio.h"

#define ITERACIONES 100000


static int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

static void prueba_crear_destruir(void) {
    printf("\nPruebas de crear y destruir pila\n\n");
    pila_t *pila = pila_crear();
    print_test("La pila se crea exitosamente", pila);
    print_test("La pila se crea vacia", pila_esta_vacia(pila) == true );
    pila_destruir(pila);
}

static void prueba_borde_recien_creada(void){
    printf("\nCasos borde con la pila recien creada \n\n");
    pila_t *pila = pila_crear();
    print_test("El tope de una pila vacia es nulo", pila_ver_tope(pila) == NULL);
    print_test("Borrar un elemento de la pila vacia devuelve NULL", pila_desapilar(pila) == NULL);
    pila_destruir(pila);
}


static void prueba_apilar_simple(void){
    printf("\nPruebas basicas de apilar\n\n");
    pila_t *pila = pila_crear();
    print_test("Apilar devuelve true", pila_apilar(pila, &valores[0]) == true);
    print_test("El elemento apilado es el tope", pila_ver_tope(pila) == &valores[0]);
    print_test("Apilo otro elemento", pila_apilar(pila, &valores[1]) == true);
    print_test("El segundo elemento apilado es el tope", pila_ver_tope(pila) == &valores[1]);
    print_test("Apilo un tercer elemento", pila_apilar(pila, &valores[2]) == true);
    print_test("El tercer elemento apilado es el tope", pila_ver_tope(pila) == &valores[2]);
    print_test("Se puede apilar NULL",  pila_apilar(pila, NULL) == true);
    print_test("El tope es NULL", pila_ver_tope(pila) == NULL);
    print_test("La pila no esta vacia", !pila_esta_vacia(pila));
    pila_destruir(pila);
}

static void prueba_desapilar_simple(void){
    printf("\nPruebas basicas de desapilar\n\n");
    pila_t *pila = pila_crear();
    pila_apilar(pila, &valores[0]);
    pila_apilar(pila, &valores[1]);
    pila_apilar(pila, &valores[2]);
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[2]);
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[1]);
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[0]);
    print_test("La pila esta vacia", pila_esta_vacia(pila));
    pila_destruir(pila);
}

void prueba_apilar_desapilar_simple_intercalado(){
    printf("\nPruebas basicas de apilar y desapilar intercalados\n\n");
    pila_t *pila = pila_crear();
    print_test("apilo un elemento", pila_apilar(pila, &valores[0]));
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[0]);
    print_test("apilo un elemento", pila_apilar(pila, &valores[1]));
    print_test("apilo un elemento", pila_apilar(pila, &valores[2]));
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[2]);
    print_test("apilo un elemento", pila_apilar(pila, &valores[3]));
    print_test("apilo un elemento", pila_apilar(pila, &valores[4]));
    print_test("apilo un elemento", pila_apilar(pila, &valores[5]));
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[5]);
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[4]);
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[3]);
    print_test("Desapilar devuelve el tope correcto", pila_desapilar(pila) == &valores[1]);
    print_test("La pila esta vacia", pila_esta_vacia(pila));
    pila_destruir(pila);

}





void prueba_apilar_varios(){
    printf("\nprueba de apilar masivamente \n\n");
    int apilados = 0;
    int correctos = 0;
    bool seguimos = true;
    int* vector[ITERACIONES];

    pila_t *pila = pila_crear();
    while (apilados < ITERACIONES && seguimos == true)
    {   
        if(pila_apilar(pila, &vector[apilados]) == true) apilados++;
        if(pila_ver_tope(pila) == &vector[apilados - 1]) correctos++;
        else seguimos = false;
    
    }
    print_test("Se apilan 1000 elementos exitosamente",  (ITERACIONES == apilados && correctos == ITERACIONES));
    printf("apilados totales = %d, topes correctos totales = %d\n",  apilados, correctos);
    pila_destruir(pila);
}




void prueba_desapilar_varios(){
    printf("\nprueba de desapilar masivamente \n\n");
    int desapilados = 0;
    int correctos = 0;
    int* vector[ITERACIONES];
    void* actual;

    pila_t *pila = pila_crear();
    for(int i = 0; i < ITERACIONES; i++) pila_apilar(pila, &vector[i]);
    while (desapilados < ITERACIONES){   
        actual = pila_desapilar(pila);
        if(actual) desapilados++;
        if(actual == &vector[ITERACIONES - desapilados]) correctos++;
    
    }
    print_test("Se desapilaron 1000 elementos exitosamente",  (ITERACIONES == desapilados && correctos == ITERACIONES));
    printf("desapilados totales = %d, topes correctos totales = %d\n",  desapilados, correctos);
    pila_destruir(pila);
}

void prueba_apilar_desapilar_intercalado(){
    printf("\n Pruebas de apilar y desapilar intercaladamente \n\n");
    int* vector[ITERACIONES];
    int apilados = 0;
    int desapilados = 0;
    pila_t *pila = pila_crear();

    for(int i = 0; i < ITERACIONES; i++){
        if(pila_apilar(pila, &vector[i])) apilados++;
        if(i%2 != 0) if(pila_desapilar(pila)) desapilados++;
    }
    print_test("Se apilaron y desapilaron intercaladamente muchos elementos exitosamente",  (ITERACIONES == apilados && desapilados == ITERACIONES/2));
    pila_destruir(pila);
}


void prueba_lista_vaciada(){
    printf("\n Pruebas con la lista vaciada tras estar llena \n\n");
    pila_t *pila = pila_crear();
    int* vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) pila_apilar(pila, &vector[i]);
    for(int i = 0; i < ITERACIONES; i++) pila_desapilar(pila);
    print_test("La pila vaciada esta efectivamente vacia", pila_esta_vacia(pila) == true);
    print_test("Desapilar con la pila vaciada devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("Ver_tope con la lista vaciada devuelve NULL", pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
}


void pruebas_pila_estudiante() {
    // ...
    prueba_crear_destruir();
    prueba_borde_recien_creada();
    prueba_apilar_simple();
    prueba_desapilar_simple();
    prueba_apilar_desapilar_simple_intercalado();
    prueba_apilar_varios();
    prueba_desapilar_varios();
    prueba_apilar_desapilar_intercalado();
    prueba_lista_vaciada();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
