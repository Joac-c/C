//Parcialito nro 1 Joaquin Correa

//2, 4, 8


/*
Implementar una función int mas_cercano(int arreglo[], size_t largo, int n) que
reciba un arreglo desordenado de enteros, su largo y un entero N, y devuelva el elemento
del arreglo más cercano a N usando la técnica de división y conquista. ¿Cuál es el orden
del algoritmo? Justificar utilizando el Teorema del Maestro. Ejemplos:
mas_cercano([3, 4, 7, 2, 1], 5, 8) --> 7
mas_cercano([3, 4, 7, 2, 1], 5, 3) --> 3
mas_cercano([3, 4, 7, 2, 1], 5, 0) --> 1
*/


int mas_cercano(int arreglo[], size_t largo, int n){
    if(largo == 1) return arreglo[0];// Operacion de tiempo constante ---> X
    int a = mas_cercano(arreglo, largo/2, n); // LLamado recursivo de l
    a funcion, de tiempo variable (depende de largo)
    int b = mas_cercano(&arreglo[largo/2], largo/2, n); // LLamado recursivo de la funcion, de tiempo variable (depende de largo)
    if(n - a < n - b) return a;// Operacion de tiempo constante ---> Y
    return b;// Operacion de tiempo constante ---> Z
}

/*
    COMPLEJIDAD DEL ALGORITMO
    T(n) = A*T(N / B) + O(N**C)
    A = 2 Porque la funcion se llama a si misma dos veces en cada paso, una por cada mitad del arreglo;
    B = 2 Porque en cada llamado recursivo el problema se divide en dos (las dos mitades del arreglo recibido como parametro)
    O(n**C) = 1  Porque las otras operaciones de la funcion(X, Y, Z), realizadas en cada llamado, son de tiempo constante --> C = 0

    Como LogB(A) = 1 y 1 > C entonces la complejidad de la funcion es O(n**c * log(n)) == O(log(n))

*/




/*
Dadas dos pilas de enteros positivos (con posibles valores repetidos) cuyos elementos fueron
ingresados de menor a mayor, se pide implementar una función int* merge_pilas(pila*
pila_1, pila* pila_2) que devuelva un array ordenado de menor a mayor con todos los
valores de ambas pilas sin repeticiones. Detallar y justificar la complejidad del algoritmo
considerando que el tamaño de las pilas es N y M respectivamente.
*/

//Voy a utilizar una implementacion recursiva
int* _merge_pilas(pila* pila_1, pila* pila_2, size_t iters){
    if(pila_esta_vacia(pila_1) && pila_esta_vacia(pila_2)){ //Operacion de tiempo constante 
        int* arreglo = calloc(iters, sizeof(int)); //Operacion de tiempo constante 
        return arreglo; //Operacion de tiempo constante 
    }
    int valor; //Operacion de tiempo constante 
    if(pila_esta_vacia(pila_2) || (int*)pila_ver_tope(pila_1) <= (int*)pila_ver_tope(pila_2)) valor = pila_desapilar(pila_1); //operaciones de tiempo constante
    else valor = pila_desapilar(pila_1);     //Operacion de tiempo constante 
    iters++;    //Operacion de tiempo constante 
    int* arreglo = _merge_pilas(pila_1, pila_2, iters); //LLamado recursivo de la funcion, de tiempo variable (depende de N + M)
    arreglo[iters -1] = (int*)valor;//Operacion de tiempo constante 
    return arreglo;//Operacion de tiempo constante 
}

int* merge_pilas(pila_t* pila_1, pila_t* pila_2){
    return _merge_pilas(pila_1, pila_2, 0);//Operacion de tiempo constante = K

}

/*
    COMPLEJIDAD DEL ALGORITMO

    La complejidad del algoritmo es = O(n) ya que en cada llamado recursivo(hay uno solo por vez)
    se le resta un elemento a pila_1 o a pila_2 hasta que ambos tengan cero elementos
    y cada llamado tiene  operaciones de tiempo constante.

    (N + M) - X*1 = 0 --> X = (N + M) = cuantas veces se llama a la funcion
    ---> Como se recorre la totalidad de ambas pilas N + M puede considerarse N
    ---> La complejidad = O(X * Suma(ctes) + K) = O(N)   (*Suma(ctes) y +K son despreciables)

*/





/*
Implementar función lista_t* reemplazar(lista_t* lista, int elemento, int
reemplazo) que recibe una lista enlazada enteros, un elemento a reemplazar y un elemento
de reemplazo, y devuelve una lista enlazada nueva con el reemplazo realizado en cada
aparición del elemento. La lista original no debe ser modificada. Detallar y justificar la
complejidad del algoritmo. Ejemplos:
reemplazar([2, 13, 8, 4, 2, 7], 2, 4) --> [4, 13 8, 4, 4, 7]
reemplazar([2, 13, 8, 4, 2, 7], 22, 4) --> [2, 13, 8, 4, 2, 7]

*/

lista_t* reemplazar(lista_t* lista, int elemento, int reemplazo){
    lista_t* nueva = lista_crear();  // Operacion de tiempo constante ---> A
    lista_iter_t* iter = lista_iter_crear(lista);// Operacion de tiempo constante ---> B
    while(!lista_iter_al_final(iter)){ // Ciclo de tiempo variable (continua hasta que el iterador este en el final de la lista) --> EL cuerpo del while se repite N veces (una por cada elemento de la lista iterado)
        
        if((int*)lista_iter_ver_actual(iter) == elemento) lista_insertar_ultimo(nueva, reemplazo);// Operacion de tiempo constante ---> C
        else lista_insertar_ultimo(nueva, lista_iter_ver_actual(iter));// Operacion de tiempo constante ---> D
        lista_iter_avanzar(iter);// Operacion de tiempo constante ---> E
    }
    return nueva;// Operacion de tiempo constante ---> F

}


/*
    COMPLEJIDAD DEL ALGORITMO
    
    O(A + B + N * (C + D + E) + F) = O(N * K + Q)
    ---> Como k y Q son constantes, su efecto en la complejidad es despreciable 
    ---> La complejidad del algoritmo es O(N)
    

*/