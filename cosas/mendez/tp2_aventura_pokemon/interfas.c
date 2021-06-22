#include <stdio.h>





int main(){
printf("\n\nMenú de inicio\n\n E: Ingresa el archivo del entrenador principal.\n A: Agrega un gimnasio al árbol de gimnasios.\n I: Comienza la partida.\n S: Simula la partida.");
printf("\n\nMenú de gimnasio\n\n E: Muestra al entrenador principal junto a sus Pokémon.\n G: Muestra la información del gimnasio actual.\n C: Permite cambiar los Pokémon de batalla.\n B: Realiza la próxima batalla planificada. * Si se derrotó al líder del gimnasio se deberá mostrar el Menú de victoria * Si se sufre una derrota frente a cualquier entrenador se deberá mostrar el Menú de derrota.");
printf("\n\nMenú de Batalla\n\n Datos de los pokemones vs \n\n N: Próximo combate.");
printf("\n\nMenú de victoria\n\n T: Toma un Pokémon del líder y lo incorpora en los Pokémon obtenidos del jugador. * Una vez realizada dicha operación, esta opción desaparece del menú.\n C: Permite cambiar los Pokémon de batalla. \n N: Próximo gimnasio. * Si no hay próximo gimnasio, se deberá notificar al usuario que se convirtió en Maestro Pokémon.");
printf("\n\nMenú de derrota\n\n C: Permite cambiar los Pokémon de batalla.\n R: Reintenta el gimnasio.\n F: Finaliza la partida.");

}