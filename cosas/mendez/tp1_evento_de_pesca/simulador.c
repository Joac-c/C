#include "evento_pesca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define FORMATO_ESCRITURA "%s;%i;%i;%s\n"
#define CANT_SELEC 2


void mostrar_pokemon1(pokemon_t* pokemon){
    //Simplemente imprime los datos del pokemon en una linea separados por ;
    printf(FORMATO_ESCRITURA, (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
}


void mostrar_pokemon2(pokemon_t* pokemon){
    //Imprime los datos del pokemon antecedidos por el nombre de cada uno
    printf("especie %s    velocidad %i    peso %i    color %s", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
}

void mostrar_pokemon3(pokemon_t* pokemon){
    //Imprime la especie del pokemon y el rasgo mas caracteristico entre peso y velocidad
    printf("especie: %s\n", (*pokemon).especie);
    if(pokemon->peso < pokemon->velocidad ){
        printf("Es un pokemon veloz %i\n", (*pokemon).velocidad);
    }
    else{
        printf("Es un pokemon pesado %i\n", (*pokemon).peso);
    }

}

void mostrar_pokemon4(pokemon_t* pokemon){
    //Imprime la especie y su color. Porque el look es lo primero.
    printf("Hermoso %s de color %s\n", pokemon->especie, pokemon->color);

}
void mostrar_pokemon5(pokemon_t* pokemon){
    //Imprime todos los atributos del pokemon en lineas distintas. Serio y prolijo.
    printf("especie %s\n", (*pokemon).especie);
    printf("velocidad %i\n", (*pokemon).velocidad);
    printf("peso %i\n", (*pokemon).peso);
    printf("color %s\n", (*pokemon).color);
}


bool suma_nombre_par(pokemon_t* pokemon){
    //Devuelve true si la suma de los valores assci de los caracteres en el nombre del pokemon es par
    int i = 0;
    int valor_especie = 0;
    while((*pokemon).especie[i] != 0){
        valor_especie += (int)(*pokemon).especie[i];
        i++;
    }
    if(valor_especie%2 == 0){
        return true;
    }
    return false;
    
    
}


bool tiene_rojo(pokemon_t* pokemon){
    //devuelve true si el pokemon tiene algo de color rojo
    
    bool final = false;
    int guia = 0;

    while(!final){
        int iguales = 0;
        for(int i = 0; i != 4; i++){
            if(0 == (*pokemon).color[i + guia]){
                final = true;
                break;     
            } 
            if("rojo"[i] == (*pokemon).color[i + guia]){
                iguales++;
            }
            else{
                break;
            }
        }
        if(iguales == 4){
            return true;
        }
        guia++;
    }
    return false;

    
}



bool pokemon_lento(pokemon_t* pokemon){
    //Devuelve true si el pokemon es mas lento que 9
    if (9 < (*pokemon).velocidad ){
        return true;
    }
    return false;
    
    
    
}


bool nombre_bombastico(pokemon_t* pokemon){
    //Devuelve true si el pokemon tiene una especie con muchas vocales. En un evento quedan mas epicos esos nombres.
    char* vocales = "aeiouAEIOU";
    int cant_vocales = 0;
    for (int i = 0;  i < strlen((*pokemon).especie); i++){
        for(int e = 0; e != 10; e++){
            if((*pokemon).especie[i] == vocales[e]){
                cant_vocales++;
            }
        }

    }
    if(3 <cant_vocales ){
        return true;
    }
    return false;
    
    
    
}

bool rapido_para_su_tamano(pokemon_t* pokemon){
    //Devuelve true si el pokemon es rapido a pesar de tener un peso relativamente alto
    if ( 15 < (*pokemon).peso && 3 <=(*pokemon).velocidad / (*pokemon).peso){
        return true;
    }
    return false;
    
    
    
}


int main (int argc, char* argv[]) { 
    arrecife_t* arrecife  = crear_arrecife("arrecife.txt");
    censar_arrecife(arrecife, mostrar_pokemon1);
    
    acuario_t* acuario = crear_acuario();

    trasladar_pokemon(arrecife, acuario, tiene_rojo, CANT_SELEC);
    censar_arrecife(arrecife, mostrar_pokemon1);
    censar_acuario(acuario, mostrar_pokemon1); 
    
    trasladar_pokemon(arrecife, acuario, suma_nombre_par, CANT_SELEC);
    censar_arrecife(arrecife, mostrar_pokemon2);
    censar_acuario(acuario, mostrar_pokemon2);
    
    trasladar_pokemon(arrecife,acuario, pokemon_lento, CANT_SELEC);
    censar_arrecife(arrecife, mostrar_pokemon3);
    censar_acuario(acuario, mostrar_pokemon3);

    trasladar_pokemon(arrecife,acuario, nombre_bombastico, CANT_SELEC);
    censar_arrecife(arrecife, mostrar_pokemon4);
    censar_acuario(acuario, mostrar_pokemon4);

    trasladar_pokemon(arrecife,acuario, rapido_para_su_tamano, CANT_SELEC);
    censar_arrecife(arrecife, mostrar_pokemon5);
    censar_acuario(acuario, mostrar_pokemon5);
    guardar_datos_acuario(acuario, "acuarium.txt");
    liberar_acuario(acuario);
    liberar_arrecife(arrecife);
    
    
    printf("Ejecutaste el main"); 
    
    
    return 0;
}