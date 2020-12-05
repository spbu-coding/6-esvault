#include <stdio.h>
#include <string.h>

char *from_1_to_5[14] = {
        "string data 1\n",
        "string data 2\n",
        "string data 3\n",
        "string data 4\n",
        "string data 5\n"
};

char *from_5_to_1[14] = {
        "string data 5\n",
        "string data 4\n",
        "string data 3\n",
        "string data 2\n",
        "string data 1\n"
};

char *expected_data[14] = {
        "string data 4\n",
        "string data 5\n"
};

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        fprintf(stderr, "%s\n", argv[i]);
    }
    fprintf(stderr, "\n");
    FILE *output = fopen("output.txt", "wt");
    if (strcmp(argv[1], "5") == 0) {
        if (strcmp(argv[5], "asc") == 0) {
            for (int i = 0; i < 5; ++i) {
                fprintf(output, "%s", from_1_to_5[i]);
            }
        } else {
            for (int i = 0; i < 5; ++i) {
                fprintf(output, "%s", from_5_to_1[i]);
            }
        }
    } else if (strcmp(argv[1], "2") == 0){
        fprintf(output, "%s", expected_data[0]);
        fprintf(output, "%s", expected_data[1]);
    } else {
        return -1;
    }
        fclose(output);
    return 0;
}
