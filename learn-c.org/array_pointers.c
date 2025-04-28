#include <stdio.h>

int main(void)
{
    /* 1. A plain array of 5 ints  ───────────────────────────────── */
    int a[5] = { 1, 2, 3, 4, 5 };          /* 5 contiguous ints      */

    /* 2. An array of 5 *pointers* to int ─────────────────────────── */
    int x = 10, y = 20, z = 30;
    int *ap[5] = { &x, &y, &z, NULL, NULL };   /* 5 separate pointers */

    /* 3. A real 2-D array: 3 × 5 ints  ──────────────────────────── */
    int m[3][5] = {                        /* = 15 ints in one block */
        {  1,  2,  3,  4,  5 },
        { 10, 20, 30, 40, 50 },
        {100,200,300,400,500 }
    };

    /* 4. “Array of 2-element arrays” (array of tuples) ───────────── */
    int pairs[4][2] = {                   /* 4 tuples (x,y)          */
        { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 }
    };

    /* 5a. Pointer to one 5-element array (row pointer) ───────────── */
    int (*row)[5] = &m[1];                /* points at 2nd row       */

    /* 5b. Array of 2 pointers, each to a 5-element array ─────────── */
    int (*rows[2])[5] = { &m[0], &m[2] }; /* rows[0]→row0, rows[1]→row2 */

    /* ------------- demo output ----------------------------------- */
    puts("1) int a[5]");
    for (int i = 0; i < 5; ++i)
        printf("  a[%d]=%2d  @%p\n", i, a[i], (void*)&a[i]);

    puts("\n2) int *ap[5]");
    for (int i = 0; i < 5; ++i)
        printf("  ap[%d]=%p → %d\n", i, (void*)ap[i], ap[i]?*ap[i]:-1);

    puts("\n3) int m[3][5]");
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 5; ++c)
            printf("  m[%d][%d]=%3d @%p\n", r,c,m[r][c],(void*)&m[r][c]);

    puts("\n4) int pairs[4][2]");
    for (int i = 0; i < 4; ++i)
        printf("  (%d,%d) @%p\n", pairs[i][0], pairs[i][1], (void*)pairs[i]);

    puts("\n5a) int (*row)[5] = &m[1]");
    for (int i = 0; i < 5; ++i)
        printf("  row[0][%d]=%3d\n", i, (*row)[i]);

    puts("\n5b) int (*rows[2])[5]");
    for (int k = 0; k < 2; ++k)
        printf("  rows[%d] points to m[%d][0] @%p  first val = %d\n",
               k, (rows[k]==&m[0]?0:2), (void*)rows[k], (*rows[k])[0]);

    return 0;
}