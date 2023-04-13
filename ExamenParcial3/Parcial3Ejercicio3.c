#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigusr1_handler(int sig) {
printf("Señal 1 recibida.\n");
}

void sigusr2_handler(int sig) {
printf("Señal 2 recibida.\n");
}

void alarm_handler(int sig) {
printf("Pasaron 2 segundos.\n");
exit(0);
}

int main() {
pid_t pidM, pidV, pidR, pidP, pidQ;

pidM = getpid();

pidQ = fork();

if (pidQ < 0) {
    perror("Error al crear proceso Q.");
    exit(1);
} else if (pidQ == 0) {
    // Proceso Q
    exit(0);
} else {
    pidV = fork();

    if (pidV < 0) {
        perror("Error al crear proceso V.");
        exit(1);
    } else if (pidV == 0) {
        // Proceso V
        sleep(4);
        kill(pidM, SIGUSR2);
        sleep(4);
        kill(pidM, SIGUSR1);
        exit(0);
    } else {
        pidR = fork();

        if (pidR < 0) {
            perror("Error al crear proceso R.");
            exit(1);
        } else if (pidR == 0) {
            // Proceso R
            signal(SIGALRM, alarm_handler);
            alarm(2); // Alarma 2 segundos
            while(1) {
                printf("Proceso R (PID=%d)\n", getpid());
                sleep(1);
            }
        } else {
            pidP = fork();

            if (pidP < 0) {
                perror("Error al crear proceso P.");
                exit(1);
            } else if (pidP == 0) {
                // Proceso P
                signal(SIGALRM, alarm_handler);
                alarm(2); // Alarma 2 segundos
                while(1) {
                    printf("Proceso P (PID=%d)\n", getpid());
                    sleep(1);
                }
            } else {
                // Proceso M
                signal(SIGUSR1, sigusr1_handler);
                signal(SIGUSR2, sigusr2_handler);

                int status;
                pid_t pid;

                // Proeso M
                pid = waitpid(pidQ, &status, 0);
                if (pid == -1) {
                    perror("Error al esperar por proceso Q.");
                }
                pid = waitpid(pidV, &status, 0);
                if (pid == -1) {
                    perror("Error al esperar por proceso V.");
                }

                // Esperar 2 segundos para que R y P impriman su ID
                sleep(2);

                // Terminar los procesos R y P
                kill(pidR, SIGKILL);
                kill(pidP, SIGKILL);

                exit(0);
            }
        }
    }
}

return 0;
}
