
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nbody.h"

void printwa(void);

void printwa() {
  printf("Wrong number of arguments\nUsage: nbodysimul <datatype> <method> <maxt> <deltat> <output>\nwhere:\n  - <datatype>: 'random <n>' to generate a random galaxy of n bodies or 'file <filename>' to load a galaxy from a file.\n  - <method>: simulation methods either naive or bht\n  - <maxt>: the total duration, in real time, of the simulation\n  - <deltat>: the delta of time (use 0.1)\n  - <output>: none (to estimate computing times) or gif\n");
}

int main(int argc, char **argv) {
  if (argc != 7) {
    printwa();
    return -1;
  }

  NBody *nb;
    
  if (strcmp(argv[1],"random") == 0) {
    nb = nbodyGenerateRandom(atoi(argv[2]));
  } else if (strcmp(argv[1],"file")==0) {
    nb = nbodyLoadFromFile(argv[2]);
  } else {
    printwa();
    exit(-1);
  }
  
  double maxt = atof(argv[4]);
  double dt = atof(argv[5]);

  int bht = 0;
  if (strcmp(argv[3],"bht")==0)
    bht = 1;

  int plot = 0;
  if (strcmp(argv[6],"gif") == 0) {
    plot = 1;
    nbodyPrepareGIF(nb, "anim.gif", 500, 500);
    nbodyPlotGIF(nb,0);
  }

  clock_t begin = clock();

  for (double t=0.0; t<maxt; t += dt) {
    fprintf(stdout,".");
    fflush(stdout);
    if (bht)
      nbodySimulateBHT(nb, dt);
    else
      nbodySimulate(nb, dt);
    if (plot)
      nbodyPlotGIF(nb,0);
  }
  fprintf(stdout,"\n");
  fflush(stdout);

  clock_t end = clock();

  double time_spent = (double)(end-begin)/ (double)CLOCKS_PER_SEC;

  printf("Simulation time: %f seconds\n", time_spent);

  if (plot)
    nbodyCloseGIF(nb);

  nbodyFree(nb);

  return 0;
}
