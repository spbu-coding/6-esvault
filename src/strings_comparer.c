#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        fprintf(stderr, "%s\n", argv[i]);
    }
    fprintf(stderr, "\n");
    return 0;
}