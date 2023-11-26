#include <stdio.h>
#include <unistd.h>

void A();
void B();
void C();
void D();

int main(int argc, char *argv[]) {
    // A();
    // B();
    // C();
    D();
    return 0;
}


void A() {
  int i;
  for (i=1; i<=2; i++) {
    if (!fork())
      printf ("%d\n", i);
  }
  printf ("%d\n", i);
}

void B(){
    int i;
    for(i=3; i>1; i--) {
        if (fork ())
            printf ("%d\n", i);
        }
    printf ("%d\n", i);
}   

void C(){
    int i;
    for (i=0; i<2; i++) {
        if (fork ())
            fork ();
        }
    printf ("%d\n", i);
}

void D(){
    int i;
    for (i=2; i>=1; i--) {
        if (!fork ())
            printf ("%d\n", -i);
        else
            printf ("%d\n", i);
    }
}