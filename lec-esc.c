#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_L  3
#define MAX_E  2


int dato = 0;

void *lector(void *arg) {
    int id = *((int *)arg);
    while (1) {
       
        // Leer datos
        printf("Lector %d leyendo: %d\n", id, dato);
        usleep(rand() % 1000000); // Retraso aleatorio de hasta 1 segundo (en microsegundos)
    }
}

void *escritor(void *arg) {
    int id = *((int *)arg);
     int aux;
    while (1) {
        
        // Escribir datos
        dato ++;
        printf("Escritor %d escribiendo: %d\n", id, dato);

        usleep(rand() % 2000000); // Retraso aleatorio de hasta 2 segundos (en microsegundos)
    }
}

int main() {
    

    // MAX_L lectores y MAX_E escritores
    pthread_t lectores[MAX_L], escritores[MAX_E]; 
    int i;
    int id_l[MAX_L],id_e[MAX_E];
    pthread_attr_t atrib;

    // Inicializar la semilla del generador de números aleatorios
    srand(time(NULL)); 

    // Inicializar la estructura pthread_attr
    pthread_attr_init( &atrib);

   

    // Crear lectores

    for(i = 0; i< MAX_L;i++){
        id_l[MAX_L]=i;
    pthread_create(&lectores[i],&atrib, lector, (void*) &id_l[i]);
    }

    // Crear escritores

    for(i = 0; i< MAX_E;i++){
    id_e[MAX_E]=i;
    pthread_create(&escritores[i],&atrib, escritor, (void*) &id_e[i]);
    }

    // Esperar a que los hilos terminen
    for(i = 0; i< MAX_L;i++){
    pthread_join(lectores[i], NULL);
    }
    for(i = 0; i< MAX_E;i++){
    pthread_join(escritores[i], NULL);
    }
    printf("Acaba el main\n");
    return 0;
}
