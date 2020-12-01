#include <stdio.h>
#include <stdlib.h>
#include "sortings.h"
#include "arguments.h"

#define ERROR_EXIT_CODE -1

#define error(...) (fprintf(stderr, __VA_ARGS__))

int des_cmp(const char *str1, const char *str2) {
    return -strcmp(str1, str2);
}

void sort(arguments_t arguments, strings_array_t strings) {
    if (strcmp(arguments.comparer_name, "asc") == 0) {
        if (strcmp(arguments.algorithm_name, "bubble") == 0) {
            bubble(strings, arguments.strings_count, strcmp);
        } else if (strcmp(arguments.algorithm_name, "insertion") == 0) {
            insertion(strings, arguments.strings_count, strcmp);
        } else if (strcmp(arguments.algorithm_name, "merge") == 0) {
            merge(strings, arguments.strings_count, strcmp);
        } else if (strcmp(arguments.algorithm_name, "quick") == 0) {
            quick(strings, arguments.strings_count, strcmp);
        } else {
            radix(strings, arguments.strings_count, strcmp);
        }
    } else {
        if (strcmp(arguments.algorithm_name, "bubble") == 0) {
            bubble(strings, arguments.strings_count, des_cmp);
        } else if (strcmp(arguments.algorithm_name, "insertion") == 0) {
            insertion(strings, arguments.strings_count, des_cmp);
        } else if (strcmp(arguments.algorithm_name, "merge") == 0) {
            merge(strings, arguments.strings_count, des_cmp);
        } else if (strcmp(arguments.algorithm_name, "quick") == 0) {
            quick(strings, arguments.strings_count, des_cmp);
        } else {
            radix(strings, arguments.strings_count, des_cmp);
        }
    }
}

//int alloc_strings(strings_array_t *array, long long strings_count) {
//    (*array) = malloc(sizeof(char *) * strings_count);
//    if ((*array) == NULL) {
//        error("Cannot allocate array\n");
//        return ERROR_EXIT_CODE;
//    }
//    for (long long i = 0; i < strings_count; ++i) {
//        (*array)[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);
//        if ((*array)[i] == NULL) {
//            for (long long j = 0; j < i; ++j) {
//                free((*array)[j]);
//            }
//            error("Cannot allocate array\n");
//            return ERROR_EXIT_CODE;
//        }
//    }
//    return 0;
//}

void dealloc_strings(strings_array_t *array, array_size_t size) {
    for (array_size_t i = 0; i < size; ++i) {
        free((*array)[i]);
    }
    free(*array);
}

int read_strings_from_file(const char *filename, strings_array_t strings, long long strings_count) {
    error("main.c 69\n");
    FILE *input = fopen(filename, "rt");
    if (input == NULL) {
        error("Cannot open file %s", filename);
        return ERROR_EXIT_CODE;
    }
    error("main.c 75\n");
    for (int i = 0; i < strings_count; ++i) {
        if (fgets(strings[i], MAX_INPUT_STRING_SIZE, input) == NULL) {
            error("Error of reading from %s", filename);
            return ERROR_EXIT_CODE;
        }
        error("%s\n", strings[i]);
    }
    error("main.c 82\n");
    char *last_string = strings[strings_count - 1];
    error("%s --- %zu\n", last_string, strlen(last_string));
    error("main.c 84\n");
    size_t last_string_len = strlen(last_string);
    error("main.c 84\n");
    if (last_string[last_string_len - 1] != '\n') {
        error("main.c 84\n");
        last_string[last_string_len] = '\n';
        error("main.c 84\n");
        last_string[last_string_len + 1] = '\0';
    }
    error("main.c 89\n");
    fclose(input);
    return 0;
}

int write_string_to_file(const char *filename, strings_array_t strings, long long strings_count) {
    FILE *output = fopen(filename, "wt");
    if (output == NULL) {
        error("Cannot open file %s", filename);
        return ERROR_EXIT_CODE;
    }
    for (int i = 0; i < strings_count; ++i) {
        if (fputs(strings[i], output) == -1) {
            error("Error of writing to %s", filename);
            return ERROR_EXIT_CODE;
        }
    }
    fclose(output);
    return 0;
}

int main(int argc,  char *argv[]) {
    arguments_t arguments;
    error("main.c 108\n");
    int result = set_parameters_values(argc, argv, &arguments);
    if (result != 0) {
        return result;
    }
    error("main.c 109\n");
    strings_array_t strings = NULL;
    strings = malloc(sizeof(char *) * arguments.strings_count);
    if (strings == NULL) {
        error("Cannot allocate array\n");
        return ERROR_EXIT_CODE;
    }
    for (long long i = 0; i < arguments.strings_count; ++i) {
        strings[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);
        if (strings[i] == NULL) {
            for (long long j = 0; j < i; ++j) {
                free(strings[j]);
            }
            error("Cannot allocate array\n");
            return ERROR_EXIT_CODE;
        }
    }
    error("main.c 111\n");
    int reading_result = read_strings_from_file(arguments.input_filename, strings, arguments.strings_count);
    if (reading_result != 0) {
        return reading_result;
    }
    error("main.c 112\n");
    sort(arguments, strings);
    error("main.c 113\n");
    int writing_result = write_string_to_file(arguments.output_filename, strings, arguments.strings_count);
    if (writing_result != 0) {
        return writing_result;
    }
    error("main.c 114\n");
    dealloc_strings(&strings, arguments.strings_count);
    return 0;
}
