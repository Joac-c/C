#include <stdbool.h>
#include <stdlib.h>

typedef struct campos
{
    char*** campo1;
    char*** campo2;
}campo_t;
 


campo_t* crear_memoria(){
    char fuera_stack = 1;
    char* fuera_din = malloc(sizeof(char));
    campo_t* base = malloc(sizeof(campo_t));
    base->campo2 = malloc(sizeof(int) * 5);
    for(int i = 0; i != 5; i++){
        base->campo2[i] = malloc(sizeof(int) * (size_t)(i+1));
        for(int k = 0; i >= k; k++ ){
            if (k % 2 == 0)
            {
                base->campo2[i][k] = &(*fuera_din);
            }
            else
            {
                base->campo2[i][k] = &fuera_stack;
            }
            
            
        } 

    }
    return base;
}
void destruir_memoria(campo_t* base){
    free(((*base).campo1)[1][1]);
    free((*base).campo1);
    free(base);    
}


int main(){
    campo_t* resultado = crear_memoria();
    destruir_memoria(resultado);
    return 0;
}



mergesort seria:

A*T(n/B) + f(n)
siendo
 B = 2 Porque el arreglo recibido siempre se divide en dos mitades en cada llamada recursiva hasta que reciba un unico elemento o cero
 A = 2 Porque el algoritmo realiza dos llamadas recursivas, una por cada mitad del arreglo
 F(n) = O(1) + O(n) = O(n) Porque dividir el arreglo es una operacion de complejidad constante
 y unir los arreglos manteniendo el orden interno es una operacion de tiempo lineal donde N es
 el tamaño de ambas mitades sumadas.

 Por lo tanto la ecuacion de recurrencia seria:
 F(n) = 2*T(n/2) + f(n)
 como N es igual a Nelevadp a log base b de a entonces
 T(n) = BigO(NlogN)


 Con quicksort:
 Depende el Caso:
 B ideal = 2 Porque todos los pivotes elegidos tienen exactamente la misma cantidad
 de elementos mayores que menores. Esto implicaria que en cada llamada recursiva
 el arreglo recibido se divida a la mitad. B peor = 1 Porque todos los pivotes elegidos
 tienen todos los elementos del arreglo mayores o todos menores. Esto implicaria que en cada llamada
 recursiva el arreglo recibido solo se reduzca en un elemento.

F(n) = O(N). La funcion en cuestion seria recorrer el arreglo recibido
para comparar(O(1)) cada elemento con el pivote y determinar si es mayor o menor.

 


int calcular_altura(nodo_abb_t* nodo){
    if(nodo.i == NULL && nodo.d == NULL){
        return 1;
    }
    int a = calcular_altura(nodo.i);
    int b = calcular_altura(nodo.b);
    return(1 + max(a, b));
}

//Buscar que es el factor de equilibrio

int contar_hojas(nodo_abb_t* nodo){
    if(nodo.i == NULL && nodo.d == NULL){
        return 1;
    }
    int a = contar_hojas(nodo.i);
    int b = contar_hojas(nodo.b);
    return(a + b;
}




void uno_y_uno(pila_t pila){
    if(pila_cantidad(pila) != 0){
        printf(pila_tope(pila));
        pila_desapilar(pila);
        uno_y_uno(pila);
    }
    pila_destruir(pila);
}

void mostrar_pila_ordenada(pila_t* pila, int (*comparar)(void*, void*)){

}