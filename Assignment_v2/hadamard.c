#include "hadamard.h"

/**
 * @brief   Generate Hadamard matrix of order n
 * @param  n: Order of the Hadamard matrix. Must be powers of 2.
 * @param  h: 2D array to store the Hadamard matrix
 * @author  Karn Watcharasupat
 */
void hadamard(Int16 n, Int16 *h) {
	Int16 i, j, x;
    h[0] = 1;

    for (x = 1; x < n; x += x) {
        for (i = 0; i < x; i++) {
            for (j = 0; j < x; j++) {
                h[(i + x) * n + j] = h[i * n + j];
                h[i * n + (j + x)] = h[i * n + j];
                h[(i + x) * n + (j + x)] = -h[i * n + j];
            }
        }
    }
}
