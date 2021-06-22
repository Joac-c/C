
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
    print_test("recorte normal", !strcmp(cacho, "Ej"));
    free(cacho);
    cacho = substr("Hola mundo", 6);
    print_test("Recorte normal funciona", !strcmp(cacho, "Hola m"));
    free(cacho);
    cacho = substr("Algoritmos", 30);
    printf("%s\n", cacho);
    print_test("Recorte con n exedido", !strcmp(cacho, "Algoritmos"));
    printf("%s\n", cacho);
    free(cacho);
    cacho = substr("", 2);
    print_test("recorte con cadena vacia", cacho[0] == '\0');
    free(cacho);
    cacho = substr(ejemplo + 4, 2);
    printf("%s\n", cacho);
    print_test("recorte con puntero adelantado", !strcmp(cacho, "pl"));
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
    char* prueba[] = {"abc", "def", "ghi"};
    for(int i = 0; i < 3; i++) if(!strcmp(lista[i], prueba[i])) cont++;
   
    print_test("recorte con cadena vacia", cont == 3 );
    print_test("Null esta al final", lista[3] == NULL);
    liberar_lista(lista);
    lista = split("abc,,ghi", ',');
    prueba[1] = "";
    cont = 0;
    for(int i = 0; lista[i] != NULL; i++) if(!strcmp(lista[i], prueba[i])) cont++;
    for(int i = 0; i < 3; i++) printf("%s\n", prueba[i]);
    for(int i = 0; i < 3; i++) printf("%s\n", lista[i]);
    print_test("El elemento coincide", lista[1][0] == '\0');

    liberar_lista(lista);
    lista = split("abc,def,", ',');
    print_test("La coma del final se traduce en un espacio", lista[2][0] == '\0');
    liberar_lista(lista);

    lista = split("abc", '\0');
    prueba[0] = "abc";
    prueba[1] = NULL; 
    printf("\n%s\n", lista[1]);
    for(int i = 0; lista[i] != NULL; i++) if(!strcmp(lista[i], prueba[i])) cont++; 
    print_test("usar el fin de linea como divisor tiene efecto nulo",  cont == 1 );
    
    liberar_lista(lista);

    lista = split("", ',');
    print_test("Dividir una linea vacia devuelve una linea vacia", lista[0][0] == '\0' && lista[1] == NULL);
    printf("%s", lista[0]);
    liberar_lista(lista);

    lista = split("abc", ',');
    print_test("Dividir una linea con una sola palabra devuelve una lista con esa palabra", !strcmp(lista[0], "abc") && lista[1] == NULL);
    liberar_lista(lista);


    lista = split(",", ',');
    print_test("Dividir una linea con solo el divisor devuelve dos listas vacias",  lista[0][0] == '\0' && lista[1][0] == '\0' && lista[2] == NULL);
    liberar_lista(lista);
    


}

void prueba_join(){

    printf("\n\nPRUEBAS DE JOIN\n\n");
    char* linea;
    char** lista;
    lista = calloc(4, sizeof(char*));
    lista[0] = "abc";
    lista[1] = "def";
    lista[2] = "ghi";
    lista[3] = NULL;
    linea = join(lista, ',');
    print_test("prueba 2", !strcmp(linea, "abc,def,ghi"));
    free(linea);
    lista[1] = "";
    linea = join(lista, ',');
    print_test("prueba 2", !strcmp(linea, "abc,,ghi"));
    lista[1] = "def";
    lista[2] = "";
    free(linea);
    linea = join(lista, ',');
    print_test("prueba 2", !strcmp(linea, "abc,def,"));
    free(linea);
    free(lista);

    lista = calloc(2, sizeof(char*));
    lista[0] = "";
    lista[1] = NULL;
    
    linea = join(lista, ',');
    print_test("prueba 1", linea[0] == '\0');
    free(linea);    
    free(lista);

    lista = calloc(2, sizeof(char*));
    lista[0] = "abc";
    lista[1] = NULL;             
    linea = join(lista, ',');
    print_test("prueba 2", !strcmp(linea, "abc"));
    free(linea);
    free(lista);

    lista = calloc(3, sizeof(char*));
    lista[0] = "";
    lista[1] = "";
    lista[2] = NULL;         
    linea = join(lista, ',');
    print_test("prueba 3", !strcmp(linea, ","));
    free(linea);
    free(lista);
    
    lista = calloc(1, sizeof(char*));
    lista[0] = NULL;         
    linea = join(lista, ',');
    print_test("prueba 4", linea[0] == '\0');
    free(linea);
    free(lista);

    lista = calloc(3, sizeof(char*));
    lista[0] = "abc";
    lista[1] = "def";
    lista[2] = NULL;               
    linea = join(lista, '\0');
    print_test("prueba 5", !strcmp(linea, "abcdef"));

    free(linea);
    free(lista);
    
    printf("\n\nPrueba de VOLUMEN\n\n");

    char** list = calloc(3, sizeof(char*));
    list[1] = calloc(10000, sizeof(char));
    list[0] = calloc(10000, sizeof(char));
    list[2] = NULL;
    
    int i = 0;

    while(i <  9998){
        list[0][i] = 'b';
        list[1][i] = 'a';
        i++;
    }
    list[0][i] = '\0';
    list[1][i] = '\0';

    linea = join(list, 'c');
    free(list[0]);
    free(list[1]);
    free(list);
    free(linea);
    

}


void prueba_free();

void pruebas_strutil_estudiante() {
    prueba_substr();
    prueba_split();
    prueba_join();


    // ...
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    
    pruebas_strutil_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif