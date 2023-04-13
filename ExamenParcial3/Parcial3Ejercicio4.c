#include <stdio.h>
#include <pthread.h>

int buffer = 0;

void *productor(void *arg) {
    while(1) {
        if(buffer == 0) {
            int input;
            printf("Por favor, ingrese un numero: ");
            scanf("%d", &input);
            buffer = input;
        }
    }
}

void *consumidor(void *arg) {
    while(1) {
        if(buffer != 0) {
            if(buffer < 0) {
                printf("El numero ingresado es menor que 0. Se acaba el programa.\n");
                pthread_exit(NULL);
            } else {
                int result = buffer * buffer;
                printf("%d al cuadrado es igual a %d\n", buffer, result);
                buffer = 0;
            }
        }
    }
}

int main() {
    pthread_t hilo_productor, hilo_consumidor;
    int ret;

    // Hilo productor
    ret = pthread_create(&hilo_productor, NULL, productor, NULL);
    if(ret != 0) {
        printf("Error al crear el hilo productor\n");
        return 1;
    }

    // Hilo consumidor
    ret = pthread_create(&hilo_consumidor, NULL, consumidor, NULL);
    if(ret != 0) {
        printf("Error al crear el hilo consumidor\n");
        return 1;
    }

    // Esperar a que terminen
    pthread_join(hilo_productor, NULL);
    pthread_join(hilo_consumidor, NULL);
    
    
    return 0;
}
