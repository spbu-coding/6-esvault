#include <stdio.h>
#include <stdlib.h>
#include "sortings.h"

#define MAX_FILENAME_LEN 100
#define VALID_ARGUMENTS_NUM 6

#define ERROR_CODE -1

#define error(...) (fprintf(stderr, __VA_ARGS__))

typedef void (*sort_func_t)(strings_array_t, array_size_t, comparator_func_t);

typedef struct {
    int strings_num;
    char input_filename[MAX_FILENAME_LEN];
    char output_filename[MAX_FILENAME_LEN];
    sort_func_t sortFunc;
    comparator_func_t cmp;
} arguments_t;

int is_numeric(const char *string) {
    for (int i = 0; ; i++) {
        if (string[i] == 0)
            return 1;
        if (string[i] < '0' || string[i] > '9')
            return 0;
    }
}

int asc_cmp(const char *str1, const char *str2) {
    return strcmp(str1, str2);
}

int des_cmp(const char *str1, const char *str2) {
    return -strcmp(str1, str2);
}

int set_arguments_value(int argc, char **argv, arguments_t *arguments) {
    if (argc != VALID_ARGUMENTS_NUM) {
        error("Wrong number of parameters\n");
        return ERROR_CODE;
    }
    if (!is_numeric(argv[1])) {
        error("First argument must be number\n");
        return ERROR_CODE;
    }
    arguments->strings_num = (int)strtoll(argv[1], NULL, 10);
    if (arguments->strings_num < 0) {
        error("Number of strings must be greater than 0\n");
        return ERROR_CODE;
    }
    strncpy(arguments->input_filename, argv[2], MAX_FILENAME_LEN);
    strncpy(arguments->output_filename, argv[3], MAX_FILENAME_LEN);
    if (strcmp(argv[4], "bubble") == 0) {
        arguments->sortFunc = bubble;
    } else if (strcmp(argv[4], "insertion") == 0) {
        arguments->sortFunc = insertion;
    } else if (strcmp(argv[4], "merge") == 0) {
        arguments->sortFunc = merge;
    } else if (strcmp(argv[4], "quick") == 0) {
        arguments->sortFunc = quick;
    } else if (strcmp(argv[4], "radix") == 0) {
        arguments->sortFunc = radix;
    } else {
        error("You should enter valid name of sort\n");
        return ERROR_CODE;
    }
    if (strcmp(argv[5], "asc") == 0) {
        arguments->cmp = asc_cmp;
    } else if (strcmp(argv[5], "des") == 0) {
        arguments->cmp = des_cmp;
    } else {
        error("You should enter valid name of comparator\n");
        return ERROR_CODE;
    }
    return 0;
}

void dealloc_strings(strings_array_t *array, array_size_t size) {
    for (array_size_t i = 0; i < size; ++i) {
        free((*array)[i]);
    }
    free(*array);
}

int alloc_strings(strings_array_t *array, int strings_num) {
    (*array) = malloc(sizeof(char *) * strings_num);
    if ((*array) == NULL) {
        error("Cannot allocate array\n");
        return ERROR_CODE;
    }
    for (int i = 0; i < strings_num; ++i) {
        (*array)[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);
        if ((*array)[i] == NULL) {
            error("Cannot allocate array[%d]\n", i);
            dealloc_strings(array, i);
        }
    }
    return 0;
}

int read_strings_from_file(const char *filename, strings_array_t strings, int strings_num) {
    FILE *input = fopen(filename, "rt");
    if (input == NULL) {
        error("Cannot open file %s", filename);
        return ERROR_CODE;
    }
    for (int i = 0; i < strings_num; ++i) {
        if (fgets(strings[i], MAX_INPUT_STRING_SIZE, input) == NULL) {
            error("Error of reading from %s", filename);
            return ERROR_CODE;
        }
    }
    char *last_string = strings[strings_num - 1];
    size_t last_string_len = strlen(last_string);
    if (last_string[last_string_len - 1] != '\n') {
        last_string[last_string_len] = '\n';
        last_string[last_string_len + 1] = '\0';
    }
    fclose(input);
    return 0;
}

int write_strings_to_file(const char *filename, strings_array_t strings, int strings_num) {
    FILE *output = fopen(filename, "wt");
    if (output == NULL) {
        error("Cannot open file %s", filename);
        return ERROR_CODE;
    }
    for (int i = 0; i < strings_num; ++i) {
        if (fputs(strings[i], output) == -1) {
            error("Error of writing to %s", filename);
            return ERROR_CODE;
        }
    }
    fclose(output);
    return 0;
}

int main(int argc, char *argv[]) {
    arguments_t arguments;
    int setting_result = set_arguments_value(argc, argv, &arguments);
    if (setting_result != 0) {
        return setting_result;
    }
    if (arguments.strings_num == 0) {
        char *n[1] = {"\n"};
        int writing_result = write_strings_to_file(arguments.output_filename, n, 1);
        if (writing_result != 0) {
            error("Cannot write \\n to file %s\n", arguments.output_filename);
            return ERROR_CODE;
        }
        return 0;
    }
    strings_array_t strings = NULL;
    int allocation_result = alloc_strings(&strings, arguments.strings_num);
    if (allocation_result != 0) {
        return allocation_result;
    }
    int reading_result = read_strings_from_file(arguments.input_filename, strings, arguments.strings_num);
    if (reading_result != 0) {
        return reading_result;
    }
    arguments.sortFunc(strings, arguments.strings_num, arguments.cmp);
    int writing_result = write_strings_to_file(arguments.output_filename, strings, arguments.strings_num);
    if (writing_result != 0) {
        return writing_result;
    }
    dealloc_strings(&strings, arguments.strings_num);
    return 0;
}