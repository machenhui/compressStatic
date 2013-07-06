#include <stdlib.h>
#include <stdio.h>
struct A {
	char a;
	int b;
	char c;
	char d;
};
struct B {
	char a;
	int b;
	char c;
	int d;
};

struct C {
	long d;
	char a;
	char c;

};

int main(int argc, char **argv) {
      struct B *b = malloc(sizeof(struct B));
      struct A *a = malloc(sizeof(struct A));
      struct C *c = malloc(sizeof(struct C));
      printf("a:%lu\t%p\n",sizeof(struct C),&c->a);
      printf("c:%lu\t%p\n",sizeof(struct C),&c->c);
      printf("d:%lu\t%p\n",sizeof(struct C),&c->d);
}
