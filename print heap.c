#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

static int pow2i(int a) {
    int r = 1;
    while (a--) {
        r *= 2;
    }
    return r;
}

static void display_tree(const int *arr, size_t arrlen) {
    assert(arrlen);

    int longest_digits = 0;
    int tree_depth = 0;

    int pos = 0;
    int depth = 0;
    for (size_t i = 0; i <arrlen; ++i) {
        if (arr[i] != -1) {
            const int len = snprintf(NULL, 0, "%d", arr[i]);
            if (longest_digits < len) {
                longest_digits = len;
            }
        }
        
        if (pos == 0) {
            tree_depth++;
            pos = pow2i(depth++);
        }
        pos--;      
    }

    //printf("%d %d\n", longest_digits, tree_depth);

    pos = 0;
    depth = 0;
    const int additional_offset = 3;
    int max_width = pow2i(tree_depth) * (longest_digits + additional_offset);
    for (size_t i = 0; i < arrlen; ++i) {
        const bool first = pos == 0;
        if (first) {
            pos = pow2i(depth);
            depth++;
        }
        const int count_elems = pow2i(depth);
        const int chunk = max_width / count_elems;
        const int width = chunk + (first ? -chunk/2 : 0);
        const int pre_spaces = width - longest_digits;

        printf("%*s", pre_spaces, "");
        if (arr[i] == -1) {
            printf("%*s", longest_digits, "-");
        } else {
            printf("%*d", longest_digits, arr[i]);
        }

        if (pos == 1) {
            printf("\n");
        }
        pos--;
    }

}

int main() {
    assert(pow2i(0) == 1);
    assert(pow2i(1) == 2);
    assert(pow2i(3) == 2*2*2);
    int arr1[] = {10,9,8,7,6,5,4,3,2,1,-1,-1,-1,-1,-1};
    display_tree(arr1, sizeof(arr1)/sizeof(*arr1));
    printf("\n");
}