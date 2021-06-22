#include "evento_pesca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CANT_DATOS 4
#define FORMATO_LECTURA "%99[^;];%i;%i;%49[^\n]\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%s\n"







int cargar_pokemones(FILE* archivo, arrecife_t* arrecife){

    if (archivo == NULL || arrecife == NULL){
        return 0;
    }

    /*inicializo una variable en el stack con la estructura pokemon_t. Sirve para construir cada pokemon del arrecife*/
    pokemon_t* poke = malloc(sizeof(pokemon_t));
    if(poke == NULL){
        return 0;
    }

    /*Leo en la primera linea del archivo cada variable e inicializo con ellas los valores de poke*/
    int exitosos = fscanf(archivo, FORMATO_LECTURA, (*poke).especie, &((*poke).velocidad), &((*poke).peso), (*poke).color);
    if(exitosos != CANT_DATOS){
        free(poke);
        return 0;
    }
    int numero = 1; //Contador de pokemones

    while(exitosos == CANT_DATOS){

        //Copio en el vector la (*poke)structura     
        (*arrecife).pokemon[(*arrecife).cantidad_pokemon] = (*poke); 
        (*arrecife).cantidad_pokemon = numero;
    
        /*Transifiero a la (*poke)estructura la siguiente linea del archivo*/
        exitosos = fscanf(archivo, FORMATO_LECTURA, (*poke).especie, &((*poke).velocidad), &((*poke).peso), (*poke).color); 
        if(exitosos == CANT_DATOS){
            /*Agrando el vector lo que haga falta para que entren los siguientes pokemones*/
            numero++;
            pokemon_t* aux = realloc((*arrecife).pokemon, ((unsigned)numero)*sizeof(pokemon_t));
            if(aux == NULL){
                free(poke);
                return 0;
        }
        (*arrecife).pokemon = aux;
        }
    }
    free(poke);
    return 1;
}





arrecife_t* crear_arrecife(const char* ruta_archivo){

    /*Abro el archivo y asigno la memoria dinamica para el arrecife*/

    FILE* archivo = fopen(ruta_archivo, "r");  //Archivo
    if(archivo == NULL){
        return NULL;
    }

    arrecife_t* arrecife = malloc(sizeof(arrecife_t));  //Memoria arrecife 
    if(arrecife == NULL){
        fclose(archivo);
        return NULL;
    }
    (*arrecife).cantidad_pokemon = 0;
    (*arrecife).pokemon = malloc(sizeof(pokemon_t));  //memoria pokemones
    if((*arrecife).pokemon == NULL){
        free(arrecife);
        fclose(archivo);
        return NULL;
    }
        
    /*cargo los pokemones*/
    if(cargar_pokemones(archivo, arrecife) == 0){
        free((*arrecife).pokemon);
        free(arrecife);
        fclose(archivo);
        return NULL;
    }
   
    /*Aca me fijo si arrecife tiene cosas y lo devuelvo*/

    if((*arrecife).pokemon == NULL){
        free(arrecife);
        fclose(archivo);
        return NULL;
    }
    
    fclose(archivo);
    return arrecife;
}



acuario_t* crear_acuario (){
    acuario_t* acuario = malloc(sizeof(acuario_t));
    if (acuario == NULL)
    {
        return NULL;
    }
    
    (*acuario).pokemon = NULL;
    (*acuario).cantidad_pokemon = 0;
    return acuario;
}



typedef struct arreglo_con_indices{
        int* indices; 
        int total;
    }trasladables_t;

trasladables_t analizar_arrecife(arrecife_t* arrecife, bool (* seleccionar_pokemon )(pokemon_t *)){

    /*Recorre el arrecife y guarda en una estructura (trasladables_t)
     los indicess de los pokemones que cumplen los requisitos de seleccionar_pokemon y su cantidad. 
     Devuelve esa estructura(trasladables_t)*/
    
    trasladables_t trasladables; 
    trasladables.indices = malloc(sizeof(int));
    trasladables.total = 0;
    
    for(int i = 0; i < (*arrecife).cantidad_pokemon; i++){
        pokemon_t* prueba = &((*arrecife).pokemon[i]);
        if(seleccionar_pokemon(prueba) == true){
            trasladables.total++;
            int* aux; 
            aux = realloc(trasladables.indices, (unsigned)trasladables.total*sizeof(int));
            if (aux == NULL)
            {
                break;
            }
            trasladables.indices = aux;
            
            trasladables.indices[trasladables.total-1] = i;
        }

    }
    return trasladables;

}

int mover_pokemones(arrecife_t* arrecife, acuario_t* acuario, trasladables_t trasladables, int cantidad_seleccion){
    
    /* 
    */


    //Asigno memoria para el acuario y el auxiliar
    pokemon_t* aux = realloc((*acuario).pokemon, sizeof(pokemon_t)*(size_t)trasladables.total + sizeof(pokemon_t)*(size_t)(*acuario).cantidad_pokemon);
    if(aux == NULL){
        printf("maliosal");
        return -1;
    }
    (*acuario).pokemon = aux;
    
    pokemon_t* se_quedan = malloc(sizeof(pokemon_t)*(size_t)((*arrecife).cantidad_pokemon - cantidad_seleccion));
    if(se_quedan == NULL){
        free((*acuario).pokemon);
        return -1;
    }

    int e = 0;
    int k = 0;

    //Traslado los pokemones
    
    for(int i=0; i<(*arrecife).cantidad_pokemon; i++){

        if( (e < trasladables.total)&&(i == trasladables.indices[e]) && (e != cantidad_seleccion)){
            (*acuario).pokemon[e +(*acuario).cantidad_pokemon] = (*arrecife).pokemon[i];
            e++;
        }
        else 
        {

            se_quedan[k] = (*arrecife).pokemon[i];
            k++;
        }
        
    }
        

    free((*arrecife).pokemon);
    free(trasladables.indices);
    (*arrecife).pokemon = se_quedan;
    (*arrecife).cantidad_pokemon = (*arrecife).cantidad_pokemon - cantidad_seleccion;
    (*acuario).cantidad_pokemon += cantidad_seleccion;
    return 0;
}
    


int trasladar_pokemon (arrecife_t* arrecife , acuario_t* acuario , bool (* seleccionar_pokemon )
(pokemon_t *), int cant_seleccion){

    if (seleccionar_pokemon == NULL || arrecife == NULL){
        return -1;
    }


    //1) Analizo el arrecife
    trasladables_t trasladables = analizar_arrecife(arrecife, seleccionar_pokemon);
    if(trasladables.indices == NULL){
        return -1;
    }


    //2) Muevo los pokemones
    if(cant_seleccion <= trasladables.total){
        return mover_pokemones(arrecife, acuario, trasladables, cant_seleccion);
        }
    else{
        free(trasladables.indices);
        return -1;
    }
}

    



void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
    printf("En el arrecife hay %d pokemones\n", arrecife->cantidad_pokemon);
    for(int i=0; i< (*arrecife).cantidad_pokemon; i++){
        mostrar_pokemon(&((*arrecife).pokemon[i]));
        printf("\n");
    }
    
}

void censar_acuario(acuario_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
    printf("En el acuario hay %d pokemones\n", arrecife->cantidad_pokemon);
    for(int i=0; i< (*arrecife).cantidad_pokemon; i++){
        mostrar_pokemon(&((*arrecife).pokemon[i]));
        printf("\n");
    }
    
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
    FILE* archivo = fopen(nombre_archivo, "w");
    for(int i=0; i< (*acuario).cantidad_pokemon; i++){
        fprintf(archivo, FORMATO_ESCRITURA, (*acuario).pokemon[i].especie, (*acuario).pokemon[i].velocidad,(*acuario).pokemon[i].peso,(*acuario).pokemon[i].color);
        if (archivo == NULL)
        {
            return -1;
        }
        
    }
    fclose(archivo);
    return 0;
}


void liberar_acuario(acuario_t* acuario){
    free((*acuario).pokemon);
    free(acuario);
}


void liberar_arrecife(arrecife_t* arrecife){
    free((*arrecife).pokemon);
    free(arrecife);
}




