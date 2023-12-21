#include <stdio.h>

int ticketNumber=0, turnNumber=1;

int atomicIncrement (int *var);
void init();
void lock();
void unlock();

int atomicIncrement (int *var) {
  int tmp = *var;
  *var = tmp + 1;
  return (tmp);
}

void init(){
    ticketNumber++;
}

void unlock(){
    atomicIncrement(&turnNumber);
}

void lock(){
    while(ticketNumber != turnNumber);
}