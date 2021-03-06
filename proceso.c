#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>


void alarmHandler(int signal);
void quitHandler(int signal);

int alarmFlag = 1;

int main(int argc, char **argv){

  int p, n_iti = 1;
  signal(SIGALRM, alarmHandler);
  signal(SIGQUIT, quitHandler);

  if(argc != 2 || strspn(argv[1], "0123456789") != strlen(argv[1])) {
    fprintf(stderr, "Argumentos erroneos, solo se permite 1 y debe ser integer\n");
    exit(-1);
  }

  p = atoi(argv[1]);
  if (p <= 0) {
      fprintf(stderr, "El argumento debe ser mayor que 0\n");
      exit(-1);
  }

  char points[p];
  for(int i = 0; i < p; i++) {
      points[i] = '*';
  }

  while (1) {
      if (alarmFlag == 0) continue;

      alarmFlag = 0;
      fprintf(stderr, "[%i] Proceso %i [%s] iter %i \n", getpid(), p, points, n_iti);
      n_iti++;
      alarm(1);
  }
}

void alarmHandler(int signal) {
    alarmFlag = 1;
}

void quitHandler(int signal) {

}

