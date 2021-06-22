

void cambiar(char* mayor, char* pivote){
    char t = *mayor;
    *mayor = *pivote;
    *pivote = t
}


int partir(char* lista, int menor, int mayor){
    char* a = lista[menor];
    int k = menor;
    for(int i = menor + 1, mayor >= i, i++){
        if (lista[i] >= *(a))
        {
            cambiar(&lista[i], a);
            k = i;
        }

    return i;
}


void quicksort(char* lista, int menor, int mayor){
    // Recibe una lista y la ordena inp-lace usando el metodo quick sort
    //Necesito el dato de la longitud de la lista?
    // Necesito una parte que elija el pivote y separe el arreglo en 3(con arrays dinamicos)
    // Necesito otra parte pegue las partes segun el orden correspondiente
    int indice = partir(lista, menor, mayor);
    quicksort(lista, menor, i);
    quicksort(lista, i, mayor);


}