/*
 * Otacilio de Araujo Ramos Neto - 24/01/2017
 */

#define _POSIX_C_SOURCE 200809L

#ifndef __TIMEMEASUREMENT_H__
#define __TIMEMEASUREMENT_H__

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

typedef struct timespec timespec_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
  * Chame esta rotina antes do código que deseja medir o tempo de execução
  * @param tempo Apontador para uma estrutura que armazenará o tempo atual
  */
void timeEnter(timespec_t *tempo);

/**
  * Chame esta rotina após o código que deseja medir o tempo de execução
  * @param pspec Apontador para uma estrutura que foi passada para timeEnter
  * @param tempo Apontador para uma estrutura que retornará o tempo gasto
  *        tempo->tv_sec  Quantos segundos gastou
  *        tempo->tv_nsec Quantos nanossegundos gastou sem completar um segundo
  * O tempo total em nanossegundos pode ser calculado como tempo->tv_sec*1000000000+tempo->tv_nsec
  */
void getTimeElapsed(timespec_t *pspec, timespec_t *tempo);


void dormeTempo(timespec_t *tempoFps,timespec_t *tempo, uint64_t intervalo);
void printTimeElapsed(int frame, char *mensagem, timespec_t *tempo, int npontos);
void printTimeElapsed2(FILE *stream, int frame, const char *mensagem, timespec_t *tempo, int npontos);
void printTimeElapsed3(const char *mensagem, timespec_t *tempo);

#ifdef __cplusplus
}
#endif

#endif