
#include "strutil.h"
#include "testing.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define ITERACIONES 100

void prueba_substr(){
    printf("\n\n Pruebas substr\n");
    //revisar el bug de mayusculas
    char* ejemplo = "Ejemplo";
    char* cacho = substr(ejemplo, 2);
    printf("%s\n", cacho);
    print_test("recorte normal", strcmp(cacho, "ej"));
    free(cacho);
    cacho = substr("Hola mundo", 6);
    print_test("Recorte normal funciona", strcmp(cacho, "hola m"));
    free(cacho);
    cacho = substr("Algoritmos", 30);
    printf("%s\n", cacho);
    print_test("Recorte con n exedido", strcmp(cacho, "algoritmos"));
    printf("%s\n", cacho);
    free(cacho);
    cacho = substr("", 2);
    print_test("recorte con cadena vacia", cacho[0] == '\0');
    free(cacho);
    cacho = substr(ejemplo + 4, 2);
    printf("%s\n", cacho);
    print_test("recorte con puntero adelantado", strcmp(cacho, "Pl"));
    free(cacho);
    

}


void liberar_lista(char** lista){
    int i = 0;
    while(lista[i] != NULL){
        free(lista[i]);
        i++;
    } 
    free(lista);
}


void prueba_split(){
    printf("\n\n Pruebas split\n");
    char** lista = split("abc,def,ghi", ',');
    int cont = 0;
    char* prueba[4] = {"Abc" , "Def", "Ghi"};
    for(int i = 0; i < 3; i++) if(strcmp(lista[i], prueba[i])) cont++;
   
    print_test("recorte con cadena vacia", cont == 3 );
    print_test("Null esta al final", lista[3] == NULL);
    liberar_lista(lista);
    lista = split("Abc,,Ghi", ',');
    prueba[1] = "";
    cont = 0;
    for(int i = 0; lista[i] != NULL; i++) if(strcmp(lista[i], prueba[i])) cont++;
    for(int i = 0; i < 3; i++) printf("%s\n", prueba[i]);
    for(int i = 0; i < 3; i++) printf("%s\n", lista[i]);
    print_test("El elemento coincide", lista[1][0] == '\0');
    liberar_lista(lista);
    lista = split("abc,def,", ',');
    //print_test("La coma del final se traduce en un espacio", lista[2][0] == '\0');
    liberar_lista(lista);
}

void prueba_join();

void prueba_free();

void pruebas_strutil_estudiante() {
    prueba_substr();
    prueba_split();


    // ...
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    
    pruebas_strutil_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif