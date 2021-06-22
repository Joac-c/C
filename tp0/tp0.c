#include "tp0.h"
#include "stdlib.h"
#include "stdio.h"

#define MAXIMO 1
#define MINIMO -1


/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int auxiliar = *x;
    *x = *y;
    *y = auxiliar;
}



int maximo(int vector[], int n){
    //En la documentacion no se especifica que el int n recibido como argumento es el largo del vector
    if(n == 0) return -1;
    int k = 0; 
    for(int i = 0; i < n; i++){
        if(vector[i] > vector[k]) k = i;
        if(i == n - 1) return k;
    }
    return -1;
}



int comparar(int vector1[], int n1, int vector2[], int n2) {
    
    for(int i=0; i < n1; i++){
        // Casos limite: n1 o n2 son menores o iguales a cero. Algun vector es menor a otro 
        if(n2 <= i) return 1;
        if(vector1[i] > vector2[i]) return 1;
        if(vector2[i] > vector1[i]) return -1;
    }
    if(n1 < n2) return -1;
    return 0;
}



void seleccion(int vector[], int n){
    if(n == 0) return;
    int mayor = maximo(vector, n);
    
    swap(&vector[n -1], &vector[mayor]);
    seleccion(vector, n-1);
}

