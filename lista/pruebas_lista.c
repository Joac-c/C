#include "lista.h"
#include "testing.h"
#include "stdlib.h"
#include "stdio.h"

#define ITERACIONES 100





static void prueba_crear_destruir(void) {
    printf("\nPruebas de crear y destruir lista\n\n");
    lista_t *lista = lista_crear();
    print_test("La lista se crea exitosamente", lista);
    print_test("La lista se crea vacia", lista_esta_vacia(lista) == true );
    lista_destruir(lista, NULL);
}

static void prueba_borde_recien_creada(void){
    printf("\nCasos borde con la lista recien creada \n\n");
    lista_t *lista = lista_crear();
    print_test("El tope de una lista vacia es nulo", lista_ver_primero(lista) == NULL);
    print_test("Borrar un elemento de la lista vacia devuelve NULL", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista, NULL);
}


static void prueba_insertar_simple(void){
    int vector[ITERACIONES];
    printf("\n Pruebas basicas de insertar\n\n");
    lista_t *lista = lista_crear();
    print_test("insertar devuelve true", lista_insertar_ultimo(lista, &vector[0]) == true);
    print_test("El elemento enlistado es el tope", lista_ver_primero(lista) == &vector[0]);
    print_test("Encolo otro elemento", lista_insertar_ultimo(lista, &vector[1]) == true);
    print_test("El segundo elemento enlistado es el tope", lista_ver_primero(lista) == &vector[0]);
    print_test("Encolo un tercer elemento", lista_insertar_ultimo(lista, &vector[0]) == true);
    print_test("El tercer elemento enlistado es el tope", lista_ver_primero(lista) == &vector[0]);
    print_test("Se puede insertar NULL",  lista_insertar_ultimo(lista, NULL) == true);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
}

static void prueba_lista_borrar_primero_simple(void){
    int vector[ITERACIONES];
    printf("\nPruebas basicas de bolista_borrar_primero\n\n");
    lista_t *lista = lista_crear();
    lista_insertar_ultimo(lista, &vector[0]);
    lista_insertar_ultimo(lista, &vector[1]);
    lista_insertar_ultimo(lista, &vector[2]);
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[0]);
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[1]);
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[2]);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
}

void prueba_insertar_lista_borrar_primero_simple_intercalado(){
    int vector[ITERACIONES];
    printf("\nPruebas basicas de insertar y lista_borrar_primero intercalados\n\n");
    lista_t *lista = lista_crear();
    print_test("Encolo un elemento", lista_insertar_ultimo(lista, &vector[0]));
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[0]);
    print_test("Encolo un elemento", lista_insertar_ultimo(lista, &vector[1]));
    print_test("Encolo un elemento", lista_insertar_ultimo(lista, &vector[2]));
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[1]);
    print_test("Encolo un elemento", lista_insertar_ultimo(lista, &vector[3]));
    print_test("Encolo un elemento", lista_insertar_ultimo(lista, &vector[4]));
    print_test("Encolo un elemento", lista_insertar_ultimo(lista, &vector[5]));
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[2]);
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[3]);
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[4]);
    print_test("lista_borrar_primero devuelve el tope correcto", lista_borrar_primero(lista) == &vector[5]);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);

}





void prueba_insertar_varios(){
    printf("\nprueba de insertar masivamente \n\n");
    int enlistados = 0;
    int correctos = 0;
    bool seguimos = true;
    int vector[ITERACIONES];

    lista_t *lista = lista_crear();
    while (enlistados < ITERACIONES && seguimos == true)
    {   
        if(lista_insertar_ultimo(lista, &vector[enlistados]) == true) enlistados++;
        if(lista_ver_primero(lista) == &vector[0]) correctos++;
        else seguimos = false;
    
    }
    print_test("Se alistan 1000 elementos exitosamente",  (ITERACIONES == enlistados && correctos == ITERACIONES));
    printf("enlistados totales = %d, topes correctos totales = %d\n",  enlistados, correctos);
    lista_destruir(lista, NULL);
}




void prueba_lista_borrar_primero_varios(){
    printf("\nprueba de lista_borrar_primero masivamente \n\n");
    int desenlistados = 0;
    int correctos = 0;
    int vector[ITERACIONES];
    void* actual;

    lista_t *lista = lista_crear();
    for(int i = 0; i < ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    while (desenlistados < ITERACIONES){   
        actual = lista_borrar_primero(lista);
        if(actual) desenlistados++;
        if(actual == &vector[correctos]) correctos++;
    
    }
    print_test("Se lista_borrar_primeroon 1000 elementos exitosamente",  (ITERACIONES == desenlistados && correctos == ITERACIONES));
    printf("desenlistados totales = %d, topes correctos totales = %d\n",  desenlistados, correctos);
    lista_destruir(lista, NULL);
}

void prueba_insertar_lista_borrar_primero_intercalado(){
    printf("\n Pruebas de insertar y lista_borrar_primero intercaladamente \n\n");
    int vector[ITERACIONES];
    int enlistados = 0;
    int desenlistados = 0;
    lista_t *lista = lista_crear();

    for(int i = 0; i < ITERACIONES; i++){
        if(lista_insertar_ultimo(lista, &vector[i])) enlistados++;
        if(i%2 != 0) if(lista_borrar_primero(lista)) desenlistados++;
    }
    print_test("Se insertaron y lista_borrar_primeroon intercaladamente muchos elementos exitosamente",  (ITERACIONES == enlistados && desenlistados == ITERACIONES/2));
    lista_destruir(lista, NULL);
}


void prueba_lista_vaciada(){
    printf("\n Pruebas con la lista vaciada tras estar llena \n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    for(int i = 0; i < ITERACIONES; i++) lista_borrar_primero(lista);
    print_test("La lista vaciada esta efectivamente vacia", lista_esta_vacia(lista) == true);
    print_test("lista_borrar_primero con la lista vaciada devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ver_tope con la lista vaciada devuelve NULL", lista_ver_primero(lista) == NULL);
    lista_destruir(lista, NULL);
}




void prueba_iter_inicio_lista_vacia(void){
    lista_t *lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    int vector[ITERACIONES];
    print_test("El iterador se crea exitosamente con una lista vaica", iter);
    print_test("El iterador esta al final de la lista vacia", lista_iter_al_final(iter));
    print_test("El elemento actual del iterador es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Iter_avanzar devuelve false", lista_iter_avanzar(iter) == false);
    print_test("Iter_borrar devuelve NULL", lista_iter_borrar(iter) == NULL);
    print_test("Insertar un elemento en la posicion actual del iterador devuelve true", lista_iter_insertar(iter, &vector[0]) == true);
    print_test("Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio", lista_ver_primero(lista) == &vector[0]);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

void prueba_iter_inicio_lista_ocupada(void){
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i <= 3; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("El iterador se crea exitosamente con una lista con elementos", iter);
    print_test("El elemento actual del iterador es el primero de la lista", lista_iter_ver_actual(iter) == &vector[0]);
    print_test("Iter_avanzar devuelve true", lista_iter_avanzar(iter) == true);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}


void prueba_iter_avanzar_simple(){
    printf("\nPruebas de avanzar con el iterador\n\n");
    int vector[ITERACIONES];
    lista_t *lista = lista_crear();
    for(int i = 0; i != 3; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("Iter_avanzar devuelve true", lista_iter_avanzar(iter) == true);
    print_test("iter_ver_actual devuelve el elemento correcto", lista_iter_ver_actual(iter) == &vector[1]);
    print_test("Iter_avanzar devuelve true", lista_iter_avanzar(iter) == true);
    print_test("iter_ver_actual devuelve el elemento correcto", lista_iter_ver_actual(iter) == &vector[2]);
    print_test("Iter_avanzar devuelve true", lista_iter_avanzar(iter) == true);
    print_test("El iterador esta al final de la lista", lista_iter_al_final(iter));
    print_test("Iter_avanzar devuelve false", lista_iter_avanzar(iter) == false);
    print_test("iter_ver_actual devuelve Null", lista_iter_ver_actual(iter) == NULL);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

}


void prueba_iterador_avanzar_varios(){
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    int acciones = 0;
    bool seguimos = true;
    int correctos = 0;
    while (acciones < ITERACIONES   && seguimos == true)
    {
        if(lista_iter_ver_actual(iter) == &vector[acciones]) correctos++;
        if(lista_iter_avanzar(iter) == true) acciones++;
        else seguimos = false;
    
    }
    print_test("Se avanzó hasta el final de la lista y devuelve true cada vez",  (ITERACIONES  == acciones));
    print_test("El actual del iterador corresponde cada vez corresponde al elemento correcto de la lista",  (ITERACIONES   == correctos));
    printf("Se avanzo %d veces y coincidieron %d elementos\n", acciones,  correctos);
    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
    
}
void prueba_iter_insertar_principio(void){
    printf("\nPruebas de insertar al final con el iterador\n\n");
    
    lista_t *lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    int vector[ITERACIONES];
    int acciones = 0;
    int correctos = 0;
    print_test("inserto un elemento exitosamente", lista_iter_insertar(iter, &vector[0]));
    print_test("Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.", lista_ver_primero(lista) == &vector[0]);
    for(int i = 1; i != ITERACIONES; i++) if(lista_iter_insertar(iter, &vector[i])) acciones++;
    for(int i = 0; i != ITERACIONES; i++) if(lista_iter_avanzar(iter)) if(lista_iter_ver_actual(iter) == &vector[ITERACIONES - i -2]) correctos++;
    
    print_test("Se insertaron varios elementos al principio con el iterador",  (ITERACIONES - 1  == acciones));
    print_test("El ultimo elemento en ser insertado efectivamente se inserta al principio.", lista_ver_primero(lista) == &vector[ITERACIONES - 1]);
    print_test("Avanzamos en cada elemento y el actual es correcto",  (ITERACIONES - 1   == correctos));
    printf("Se inserto %d veces y coincidieron %d elementos\n", acciones,  correctos);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

}

void prueba_iter_insertar_final(void){
    printf("\nPruebas de insertar al final con el iterador\n\n");
    int vector[ITERACIONES];
    lista_t *lista = lista_crear();
    for(int i = 0; i != ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    while(lista_iter_avanzar(iter));
    print_test("El iterador se encuentra al final", lista_iter_al_final(iter));
    print_test("Insertar un elemento cuando el iterador esta al final de la lista devuelve true", lista_iter_insertar(iter, &vector[ITERACIONES]));
    print_test("Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final", lista_ver_ultimo(lista) == &vector[ITERACIONES]) ;
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

}

void prueba_iter_insertar_intercalado(void){
    printf("\nPruebas de insertar al final con el iterador\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES/2; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    for(int i = 0; i < ITERACIONES/8; i++) lista_iter_avanzar(iter);
    print_test("Inserto un elemento en el medio de la lista", lista_iter_insertar(iter, &vector[ITERACIONES/2 + 1]));
    for(int i = ITERACIONES/8; i < ITERACIONES/4 ; i++) lista_iter_avanzar(iter);
    print_test("Inserto un otro elemento mas adelante", lista_iter_insertar(iter, &vector[ITERACIONES/2 + 2]));
    for(int i = ITERACIONES/4; i < ITERACIONES/3 ; i++) lista_iter_avanzar(iter);
    print_test("Inserto un tercer elemento mas adelante", lista_iter_insertar(iter, &vector[ITERACIONES/2 + 3]));
    lista_iter_destruir(iter);
    iter = lista_iter_crear(lista);
    for(int i = 0; i < ITERACIONES/8; i++) lista_iter_avanzar(iter);
    print_test("El primer elemento esta en la ubicacion correcta", lista_iter_ver_actual(iter) == &vector[ITERACIONES/2 + 1]);
    for(int i = ITERACIONES/8; i < ITERACIONES/4 ; i++) lista_iter_avanzar(iter);
    print_test("El segundo elemento esta en la ubicacion correcta", lista_iter_ver_actual(iter) == &vector[ITERACIONES/2 + 2]);
    for(int i = ITERACIONES/4; i < ITERACIONES/3 ; i++) lista_iter_avanzar(iter);
    print_test("El tercer elemento esta en la ubicacion correcta", lista_iter_ver_actual(iter) == &vector[ITERACIONES/2 + 3]);
    print_test("La cantidad de elementos es correcta", lista_largo(lista) == ITERACIONES/2 + 3);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

}


void prueba_iter_borrar_principio(void){
    printf("\nPruebas de borrar al principio con el iterador\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i != ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    //for(int i = 0; i != ITERACIONES; i++) lista_iter_insertar(iter, &vector[ITERACIONES - i]);
    int acciones = 0;
    int correctos = 0;
    print_test("Borro exitosamente un elemento de una lista con el iterador recien creado", lista_iter_borrar(iter) == &vector[0]);
    print_test("Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista.", lista_ver_primero(lista) == &vector[1]);
    for(int i = 1; i != ITERACIONES/2; i++) if(lista_iter_borrar(iter) == &vector[i]) acciones++;
    print_test("Tras borrar varios elementos al principio la cantidad es correcta", lista_largo(lista) == ITERACIONES - ITERACIONES/2);
    if(lista_iter_ver_actual(iter) == &vector[ITERACIONES/2]) correctos++;
    for(int i = ITERACIONES/2; i != ITERACIONES; i++) if(lista_iter_avanzar(iter)) if(lista_iter_ver_actual(iter) == &vector[i + 1]) correctos++;
    print_test("Se borraron varios elementos al principio con el iterador",  (ITERACIONES/2 - 1  == acciones));
    print_test("Avanzamos en cada elemento y el actual es correcto",  (ITERACIONES - ITERACIONES/2   == correctos));
    printf("Se borro %d veces y coincidieron %d elementos\n", acciones,  correctos);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

}


void prueba_borrar_al_final(void){
    printf("\nPruebas de borrar al final con el iterador\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i != ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    for(int i = 0; i != ITERACIONES - 1; i++) lista_iter_avanzar(iter);
    print_test("LLevo el iterador hasta el final y borro el ultimo elemento", lista_iter_borrar(iter));
    print_test("Remover el último elemento con el iterador cambia el último de la lista.", lista_ver_ultimo(lista) == &vector[ITERACIONES - 2]);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

}
void prueba_iter_borrar_hasta_final(void){
    printf("\nPruebas de borrar hasta el final con el iterador\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i != ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    int acciones = 0;
    for(int i = 0; i != ITERACIONES; i++) if(lista_iter_borrar(iter) == &vector[i]) acciones++;
    printf("Se borro %d veces \n", acciones);
    print_test("Tras borrar varios elementos al principio la cantidad es correcta", lista_largo(lista) == 0);
    print_test("Se borraron todos los elementos",  (ITERACIONES   == acciones));
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("El actual del iterador es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("El iterador esta al final", lista_iter_al_final(iter));
    print_test("Insertar devuelve true", lista_iter_insertar(iter, &vector[0]));
    print_test("Insertar devuelve true", lista_iter_insertar(iter, &vector[1]));
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

}


void prueba_borrar_medio(){
    printf("\nPruebas de borrar en el medio\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i != ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    lista_iter_t* iter = lista_iter_crear(lista);
    for(int i = 0; i < ITERACIONES/4; i++) lista_iter_avanzar(iter);
    print_test("Borro un elemento en el medio exitosamente", lista_iter_borrar(iter));
    lista_iter_destruir(iter);
    iter = lista_iter_crear(lista);
    bool encontrado = false; 
    for(int i = 0; i < ITERACIONES; i++)  if(lista_iter_avanzar(iter)) if(lista_iter_ver_actual(iter) == &vector[ITERACIONES/4]) encontrado = true;
    print_test("El elemento borrado no se encuentra en la lista", !encontrado);
    lista_iter_destruir(iter);
    iter = lista_iter_crear(lista);
    for(int i = 0; i < ITERACIONES/2; i++) lista_iter_avanzar(iter);
    print_test("Borro otro elemento en el medio exitosamente", lista_iter_borrar(iter));
    for(int i = 0; i < ITERACIONES/2 + ITERACIONES/4; i++) lista_iter_avanzar(iter);
    print_test("Borro otro elemento mas adelante", lista_iter_borrar(iter));
    lista_iter_destruir(iter);
    iter = lista_iter_crear(lista);
    encontrado = false;
    for(int i = 0; i < ITERACIONES; i++) if(lista_iter_avanzar(iter)) if(lista_iter_ver_actual(iter) == &vector[ITERACIONES/2 + 1] || lista_iter_ver_actual(iter) == &vector[ITERACIONES/2 + ITERACIONES/4 + 2]) encontrado = true;
    print_test("Los elementos borrados no se encuentran en la lista", !encontrado);
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    




}

bool funcion_iter_imprimir_elemento(void* elem, void* suma){
    int* num = (int*)elem;
    *(int*)suma = *(int*)suma + 1;
    if(*num%20 == 0 || *num == ITERACIONES - 1) printf("%d \n", *num);
    else printf("%d, ", *num);
    return true;
}


void prueba_iterador_interno_lista_vacia(){
    printf("\nprueba_iterador_interno_lista_vacia\n\n");
    lista_t *lista = lista_crear();
    int suma = 0;
    lista_iterar(lista, funcion_iter_imprimir_elemento, &suma);
    print_test("Prueba exitosa", suma == 0);
    lista_destruir(lista, NULL);
}

void prueba_iterador_interno_sin_corte(){
    printf("\nprueba_iterador_interno_sin_corte\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) vector[i] = i;
    for(int i = 0; i < ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    int suma = 0;
    lista_iterar(lista, funcion_iter_imprimir_elemento, &suma);
    print_test("El iterador interno sin corte llega hasta el final de la lista", suma == ITERACIONES);
    lista_destruir(lista, NULL);

}


bool funcion_iter_sumar(void* elem, void* suma){
    int* num = (int*)elem;
    *(int*) suma = *num + *(int*) suma;
    if(*(int*)suma > ITERACIONES/2){
        printf("La suma de elementos es %d, mayor a la mitad de los elementos en la lista \n", *(int*)suma);
        return false;
    }
    else return true;

}

void prueba_iterador_interno_con_corte(){
    printf("\nprueba_iterador_interno_con_corte\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) vector[i] = i;
    for(int i = 0; i < ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    int suma = 0;
    lista_iterar(lista, funcion_iter_sumar, &suma);
    print_test("El iterador interno con corte devuelve el valor esperado", suma > ITERACIONES/2);
    lista_destruir(lista, NULL);
}

void prueba_iterador_interno_con_corte_dos_veces(){
    printf("\nprueba_iterador_interno_dos_veces\n\n");
    lista_t *lista = lista_crear();
    int vector[ITERACIONES];
    for(int i = 0; i < ITERACIONES; i++) vector[i] = i;
    for(int i = 0; i < ITERACIONES; i++) lista_insertar_ultimo(lista, &vector[i]);
    int suma = 0;
    lista_iterar(lista, funcion_iter_sumar, &suma);
    print_test("El iterador interno con corte devuelve el valor esperado", suma > ITERACIONES/2);
    suma = 0;
    lista_iterar(lista, funcion_iter_sumar, &suma);
    print_test("El iterador interno con corte devuelve el valor esperado", suma > ITERACIONES/2);
    lista_destruir(lista, NULL);
    print_test("La lista es NULL despues de ser destruida", lista);
}


void pruebas_lista_estudiante() {
    prueba_crear_destruir();
    prueba_borde_recien_creada();
    prueba_insertar_simple();
    prueba_lista_borrar_primero_simple();
    prueba_insertar_lista_borrar_primero_intercalado();
    prueba_insertar_varios();
    prueba_lista_borrar_primero_varios();
    prueba_insertar_lista_borrar_primero_intercalado();
    prueba_lista_vaciada();
    prueba_iterador_interno_sin_corte();


    prueba_iter_inicio_lista_vacia();
    prueba_iter_inicio_lista_ocupada();
    prueba_iter_avanzar_simple();
    prueba_iterador_avanzar_varios();
    prueba_iter_insertar_principio();
    prueba_iter_insertar_final();
    prueba_iter_insertar_intercalado();
    prueba_iter_borrar_principio();
    prueba_iter_borrar_hasta_final();
    prueba_iterador_interno_lista_vacia();
    prueba_iterador_interno_sin_corte();
    prueba_iterador_interno_con_corte();
    prueba_iterador_interno_con_corte_dos_veces();


    // ...
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
