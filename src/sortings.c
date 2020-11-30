#include "sortings.h"
#include <stdlib.h>

void swap(char **str1, char **str2) {
    char *tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

array_size_t get_max_length(strings_array_t strings, size_t strings_count) {
    size_t max = strlen(strings[0]);
    for (size_t i = 0; i < strings_count; ++i) {
        size_t tmp_size = strlen(strings[i]);
        if (tmp_size > max) {
            max = tmp_size;
        }
    }
    return max;
}

void count_sort(strings_array_t array, size_t size, size_t k, comparator_func_t cmp) {
    strings_array_t b = malloc(sizeof(char *) * size);
    int *c = malloc(sizeof(int) * 257);
    for (int i = 0; i < 257; ++i) {
        c[i] = 0;
    }
    for (size_t i = 0; i < size; ++i) {
        int tmp = k < strlen(array[i]) ? (int)(unsigned char)array[i][k] + 1 : 0;
        c[tmp]++;
    }
    if (cmp("a", "b") < 0) {
        for (int i = 1; i < 257; ++i) {
            c[i] += c[i - 1];
        }
    } else {
        for (int i = 257 - 2; i >=0; --i) {
            c[i] += c[i + 1];
        }
    }
    for (size_t i = size - 1; i >= 0; --i) {
        b[c[k < strlen(array[i]) ? (int)(unsigned char)array[i][k] + 1 : 0] - 1] = array[i];
        c[k < strlen(array[i]) ? (int)(unsigned char)array[i][k] + 1 : 0]--;
    }
    for (size_t i = 0; i < size; ++i) {
        array[i] = b[i];
    }
    free(b);
    free(c);
}

void bubble(strings_array_t array, array_size_t size, comparator_func_t cmp) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i; j < size; ++j) {
            if (cmp(array[j], array[i]) < 0) {
                swap(&array[i], &array[j]);
            }
        }
    }
}

void insertion(strings_array_t array, array_size_t size, comparator_func_t cmp) {
    for (array_size_t i = 1; i < size; i++) {
        char *tmp = array[i];
        for (array_size_t j = i - 1; j >= 0; j--) {
            if (cmp(array[j], tmp) < 0) {
                break;
            }
            array[j + 1] = array[j];
            array[j] = tmp;
        }
    }
}

void merge(strings_array_t a, array_size_t n, comparator_func_t cmp) {
    array_size_t step = 1;
    strings_array_t  temp = malloc(n * sizeof(char *));
    for (array_size_t i = 0; i < n; ++i) {
        temp[i] = malloc(sizeof(char) * n);
    }
    while (step < n) {
        array_size_t index = 0;
        array_size_t l = 0;
        array_size_t m = l + step;
        array_size_t r = l + step * 2;
        do {
            m = m < n ? m : n;
            r = r < n ? r : n;
            array_size_t i1 = l, i2 = m;
            for (; i1 < m && i2 < r; ) {
                if (cmp(a[i1], a[i2]) < 0) {
                    temp[index++] = a[i1++];
                } else {
                    temp[index++] = a[i2++];
                }
            }
            while (i1 < m) {
                temp[index++] = a[i1++];
            }
            while (i2 < r) {
                temp[index++] = a[i2++];
            }
            l += step * 2;
            m += step * 2;
            r += step * 2;
        } while (l < n);
        for (array_size_t i = 0; i < n; i++) {
            a[i] = temp[i];
        }
        step *= 2;
    }
    for (array_size_t i = 0; i < n; ++i) {
        free(temp[i]);
    }
    free(temp);
}

void quick(strings_array_t array, array_size_t size, comparator_func_t cmp) {
    long long i = 0;
    long long j = (long long)size - 1;
    char *mid = array[size / 2];
    do {
        while (cmp(array[i], mid) < 0) {
            i++;
        }
        while (cmp(array[j], mid) > 0) {
            j--;
        }
        if (i <= j) {
            swap(&array[i], &array[j]);
            i++; j--;
        }
    } while(i <= j);
    if (j > 0) {
        quick(array, j + 1, cmp);
    }
    if (i < (long long)size) {
        quick(&array[i], size - i, cmp);
    }
}

void radix(strings_array_t array, array_size_t size, comparator_func_t cmp) {
    size_t max = get_max_length(array, size);
    for (size_t digit = max; digit > 0; digit--) {
        count_sort(array, size, digit - 1, cmp);
    }
}