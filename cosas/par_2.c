// 1, 4, 7

Parcial nro 2 de Joaquin Correa, Algoritmos 2

#include "stdbool.h"
#include "stdio.h"
/*
1. Implementar para un árbol binario una primitiva size_t ab_sin_nietos(const ab_t* ab) que devuelva la cantidad de
nodos en el árbol que no tienen nietos . Se le considera nieto de un nodo a un hijo de cualquiera de sus hijos. Es decir, un
nieto es un hijo del hijo. Indicar y justificar la complejidad de la primitiva implementada, y el tipo de recorrido utilizado. A
efectos del ejercicio, la estructura del árbol es:

typedef struct ab {
struct ab* izq;
struct ab* der;
void* dato;
} ab_t;

*/

typedef struct ab {
struct ab* izq;
struct ab* der;
void* dato;
} ab_t;

size_t ab_sin_nietos(const ab_t* ab){
    
    if(!ab->izq && !ab->der) return 1;
    if(!ab->der) if(ab_sin_nietos(ab->izq) == 1) return 2;
    if(!ab->izq) if(ab_sin_nietos(ab->der) == 1) return 2;
    int i = ab_sin_nietos(ab->izq) + ab_sin_nietos(ab->der);
    if(i == 2) return 3;
    else return i;
    
    
}

/*   COMPLEJIDAD

    La complejidad de este algoritmo es 0(n) ya que recorre todos los nodos una vez recursivamente y en cada llamado 
    realiza como maximo dos operaciones O(1) (Sumar y devolver valor). El tipo de recorrido es post orden (Primero baja y sube
    la rama izquierda, luego por la derecha y por ultimo devuelve (en este caso el numero de nietos) desde el nodo actual)
    
*/


/*

4. Implementar, para un Hash Cerrado, una primitiva que dado un Hash, un número k y una función bool
debe_duplicar_dato(const char* clave), y suponiendo que en el Hash todos los datos guardados son de tipo puntero a
entero, duplique el valor del dato guardado para las primeras k claves para las que la función debe_duplicar_dato devuelva
true. En caso de que el Hash tenga menos de k elementos, multiplicar por 2 el dato guardado de todas las claves para las
que debe_duplicar_dato devuelva true. Indicar y justificar la complejidad de la primitiva implementada. La firma de la
primitiva deberá ser: bool duplicar_selectivo(const hash_t* hash, int k, bool (*debe_duplicar_dato)(const
char* clave))
*/

#define OCUPADO 1;
#define BORRADO 2;
#define VACIO 0;

bool duplicar_selectivo(const hash_t* hash, int k, bool (*debe_duplicar_dato)(const char* clave)){

    int indice = 0;
    while(indice < k && indice < hash->tamaño){
        if(hash->tabla[indice].estado == OCUPADO){
            if(debe_duplicar_dato(hash->tabla[indice]->clave)){
                *(int*)(hash->tabla[indice]->elemento) = 2*(*(int*)hash->tabla[indice]->elemento);
                indice++;
            }
        }
    }


}

//  
// El algoritmo esta compuesto de un For que en el peor de los casos (k >= cantidad de elementos que cumplen la condicion) 
// realiza 3 operaciones (dos comparaciones y una multiplicacion) tantas veces
// Como espacios hay en el arreglo (tamaño del arreglo). El tamaño del arreglo depende linealmente de la cantidad de elementos almacenados (N)
// Por lo que (3(operaciones) * tamaño del arreglo) puede aproximarse a (cantidad de elementos = N).
// Por lo tanto la complejidad del algoritmo es O(N) 




/*
7. Realizar el seguimiento de ordenar por Radix Sort el siguiente arreglo de cadenas que representan versiones. Cada versión
tiene el formato a.b.c, donde cada valor a, b y c puede tener un valor entre 0 y 99. Considerar que se quiere que quede
ordenado primero por la primera componente (a), luego por la segunda (b) y finalmente por la tercera (c). Tener en cuenta
que, por ejemplo, 1.1.3 < 1.1.20, 2.20.8 < 3.0.0.

["10.4.2", "6.3.2", "10.1.4", "5.10.20", "3.2.1", "4.6.3", "2.1.5", "8.1.2", "6.3.1", "10.0.23"]
¿Cuál es el orden del algoritmo? ¿Es estable?
*/

// Primer ordenamiento (tercera cifra):
(pasos ordenados alfabeticamente. Solo aparecen los casilleros involucrados por una cuestion de espacio pero deberian ser del 0 al 99)
 
1) e) 3.2.1 i) 6.3.1

2) a) 10.4.2 b) 6.3.2 h) 8.1.2

3) f) 4.6.3

4) c) 10.1.4

5) g) 2.1.5

20) d) 5.10.20 

23) j) 10.0.23


// segundo ordenamiento (segunda cifra)

0) j) 10.0.23

1) g) 10.1.4 h) 2.1.5

2) a) 3.2.1 e) 8.1.2

3) b) 6.3.1 d) 6.3.2 

4) c) 10.4.2 

6) f) 4.6.3

10) i) 5.10.20

// Tercer ordenamiento(primera cifra)



2) c) 2.1.5

3) d) 3.2.1 

4) I) 4.6.3

5) J) 5.10.20

6) f) 6.3.1 g) 6.3.2 

8) e) 8.1.2

10) a) 10.0.23 b) 10.1.4 h)  10.4.2 


/*
Complejidad:


*/