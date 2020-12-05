#include "arguments.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define error(...) (fprintf(stderr, __VA_ARGS__))

#define ERROR_EXIT_CODE -1

#define ALGORITHMS_COUNT 5
#define COMPARER_COUNT 2

const char *VALID_ALGORITHM_NAME[MAX_LENGTH_ALGORITHM_NAME] = {"bubble", "insertion", "merge", "quick", "radix"};
const char *VALID_COMPARER_NAME[MAX_LENGTH_COMPARER_NAME] = {"asc", "des"};

int is_numeric(const char *str) {
    for (size_t i = 0;; ++i) {
        if (str[i] == 0) {
            return 1;
        }
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
}

int check_algorithm_name(char *algorithm_name) {
    for (int i = 0; i < ALGORITHMS_COUNT; ++i) {
        if (strcmp(algorithm_name, VALID_ALGORITHM_NAME[i]) == 0) {
            return 0;
        }
    }
    return -1;
}

int check_comparer_name(char *comparer_name) {
    for (int i = 0; i < COMPARER_COUNT; ++i) {
        if (strcmp(comparer_name, VALID_COMPARER_NAME[i]) == 0) {
            return 0;
        }
    }
    return -1;
}

int set_parameters_values(int argc, char *argv[], arguments_t *arguments) {
    if (argc != 6) {
        error("Wrong count of parameters.\n");
        return ERROR_EXIT_CODE;
    }
    if (!is_numeric(argv[1])) {
        error("First parameter must be number\n");
        return ERROR_EXIT_CODE;
    }
    arguments->strings_count = (int)strtoll(argv[1], &argv[1], 10);
    if (arguments->strings_count < 0) {
        error("Count of string must be greater than 0\n");
        return ERROR_EXIT_CODE;
    }
    strncpy(arguments->input_filename, argv[2], MAX_LENGTH_FILE_NAME);
    strncpy(arguments->output_filename, argv[3], MAX_LENGTH_FILE_NAME);
    strncpy(arguments->algorithm_name, argv[4], MAX_LENGTH_ALGORITHM_NAME);
    strncpy(arguments->comparer_name, argv[5], MAX_LENGTH_COMPARER_NAME);
    if (check_algorithm_name(arguments->algorithm_name) != 0) {
        error("Wrong name of algorithm\n");
        return ERROR_EXIT_CODE;
    }
    if (check_comparer_name(arguments->comparer_name) != 0) {
        error("Wrong name of comparer\n");
        return ERROR_EXIT_CODE;
    }
    return 0;
}