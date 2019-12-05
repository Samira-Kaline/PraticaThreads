/*
 * Otacilio de Araujo Ramos Neto - 24/01/2017
 */

#include "timeMeasurement.h"

void timeEnter(timespec_t *tempo)
{
    #ifndef WIN32
    clock_gettime(CLOCK_MONOTONIC, tempo);
    #endif
}

void getTimeElapsed(timespec_t *pspec,timespec_t *tempo)
{
    #ifndef WIN32
    struct timespec spec;

    clock_gettime(CLOCK_MONOTONIC, &spec);

    tempo->tv_sec  = (((((uint64_t)spec.tv_sec) - ((uint64_t)pspec->tv_sec))*((uint64_t)1000000000) - ((uint64_t)pspec->tv_nsec) + ((uint64_t)spec.tv_nsec)) / ((uint64_t)1000000000));
    tempo->tv_nsec = (((((uint64_t)spec.tv_sec) - ((uint64_t)pspec->tv_sec))*((uint64_t)1000000000) - ((uint64_t)pspec->tv_nsec) + ((uint64_t)spec.tv_nsec)) % ((uint64_t)1000000000));
    #endif
}

void printTimeElapsed(int frame, char *mensagem, timespec_t *tempo, int npontos)
{
    #ifndef WIN32
    printf("%d; %s; %"PRIdMAX"; %09ld; %d\n", frame, mensagem, (intmax_t)tempo->tv_sec, tempo->tv_nsec, npontos);
    #endif
}

void printTimeElapsed2(FILE *stream, int frame, const char *mensagem, timespec_t *tempo, int npontos)
{
    #ifndef WIN32
    fprintf(stream, "%s; %d; %"PRIdMAX"; %09ld; %d\n", mensagem, frame, (intmax_t)tempo->tv_sec, tempo->tv_nsec, npontos);
    #endif
}

void printTimeElapsed3(const char *mensagem, timespec_t *tempo)
{
    #ifndef WIN32
    fprintf(stderr, "%s; %"PRIdMAX"; %09ld\n", mensagem, (intmax_t)tempo->tv_sec, tempo->tv_nsec);
    #endif
}

void dormeTempo(timespec_t *tempoFps,timespec_t *tempo, uint64_t intervalo)
{
    #ifndef WIN32
    uint64_t tempoEmprestimo=0;
    // Ve quanto tempo passou
    getTimeElapsed(tempoFps, tempo);
    // Calcula quanto precisa dormir

    // Esse caso não foi bem testado devido ao tv_sec>0 ser difícil de acontecer.
	// Seria bom depois testar para valer para ver se está correto.
    if(tempo->tv_sec>0){
        tempo->tv_nsec += 1000000000*tempo->tv_sec - tempoFps->tv_nsec;
    }

    if(intervalo >= (tempo->tv_nsec+tempoEmprestimo)){
        // Se sobrou tempo entao dorme o restante
        tempo->tv_sec = 0;
        tempo->tv_nsec = intervalo - tempo->tv_nsec - tempoEmprestimo;
        tempoEmprestimo = 0;
        nanosleep(tempo, NULL);
    }else{
        tempoEmprestimo = - (intervalo - (tempo->tv_nsec+tempoEmprestimo));
    }
    #endif // WIN32
}