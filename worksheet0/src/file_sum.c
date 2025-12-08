#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("foo.txt", "r");
    if (!fp) {
        perror("fopen(foo.txt)");
        return 1;
    }

    long long sum = 0;
    int x;
    while (fscanf(fp, "%d", &x) == 1) {
        sum += x;
    }

    if (ferror(fp)) {
        fprintf(stderr, "Read error: %s\n", strerror(errno));
        fclose(fp);
        return 1;
    }

    fclose(fp);
    printf("Sum: %lld\n", sum);
    return 0;
}
