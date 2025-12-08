#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* ---- Task 1: basic pointers ---- */
static void task1_pointer_increment(void) {
    int n = 7;
    int *ptr_to_n = &n;

    printf("Before: n = %d\n", n);
    *ptr_to_n += 1; /* increase by ONE */
    printf("After : n = %d\n\n", n);
}

/* ---- Task 2: loop over array with pointer */
static void task2_array_pointer_loop(void) {
    int vals[] = {10, 30, 2000};
    int *p = vals;

    printf("Array values + addresses:\n");
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); i++) {
        printf("vals[%zu] = %d at %p\n", i, *(p+i), (void*)(p+i));
    }
    printf("\n");
}

/* ---- Array compare ---- */
int compare_arrays(const int *a, const int *b, size_t len) {
    if (!a || !b) return 0;
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

void swap_bytes(void *x, void *y, size_t size) {
    if (!x || !y || size == 0) return;
    unsigned char tmp[size];
    memcpy(tmp, x, size);
    memcpy(x, y, size);
    memcpy(y, tmp, size);
}

/* 2D array printer using a flat pointer */
void print_array_2d(const int *arr, int width, int height) {
    if (!arr || width <= 0 || height <= 0) return;
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            printf("%d ", arr[r * width + c]);
        }
        printf("\n");
    }
}

int main(void) {
    task1_pointer_increment();
    task2_array_pointer_loop();

    /* compare_arrays demo */
    int a1[] = {1,2,3,4};
    int a2[] = {1,2,3,4};
    int a3[] = {1,2,3,5};
    printf("compare_arrays(a1,a2) = %d (expect 1)\n", compare_arrays(a1, a2, 4));
    printf("compare_arrays(a1,a3) = %d (expect 0)\n\n", compare_arrays(a1, a3, 4));

    /* swap demo */
    int x = 42, y = 99;
    printf("Before swap: x=%d y=%d\n", x, y);
    swap_bytes(&x, &y, sizeof(int));
    printf("After  swap: x=%d y=%d\n\n", x, y);

    /* 2D print demo */
    int arr2d[2][3] = {{1,2,3},{4,5,6}};
    print_array_2d(&arr2d[0][0], 3, 2);

    return 0;
}
