#include <Arduino.h>

#define EPS 1e-4            // Looser convergence for float precision
#define MAX_ITER 100        // Fewer iterations due to limited resources
#define DELTA 1e-2          // Slightly larger step size for stability

void computeFunctions(float v1, float v2, float v3, float a, float b, float c, float* f) {
    float r_internal = 1.0 / 10000.0;

    f[0] = v1 - 5.0 / (a * (r_internal + 1.0 / b + 1.0 / c) + 1.0);
    f[1] = v2 - 5.0 / (b * (r_internal + 1.0 / a + 1.0 / c) + 1.0);
    f[2] = v3 - 5.0 / (c * (r_internal + 1.0 / a + 1.0 / b) + 1.0);
}

void computeJacobian(float v1, float v2, float v3, float a, float b, float c, float J[3][3]) {
    float f0[3], f1[3];

    computeFunctions(v1, v2, v3, a, b, c, f0);

    computeFunctions(v1, v2, v3, a + DELTA, b, c, f1);
    for (int i = 0; i < 3; i++) J[i][0] = (f1[i] - f0[i]) / DELTA;

    computeFunctions(v1, v2, v3, a, b + DELTA, c, f1);
    for (int i = 0; i < 3; i++) J[i][1] = (f1[i] - f0[i]) / DELTA;

    computeFunctions(v1, v2, v3, a, b, c + DELTA, f1);
    for (int i = 0; i < 3; i++) J[i][2] = (f1[i] - f0[i]) / DELTA;
}

void solveLinearSystem(float A[3][3], float b[3], float x[3]) {
    float mat[3][4];

    // Augment the matrix
    for (int i = 0; i < 3; i++) {
        mat[i][0] = A[i][0];
        mat[i][1] = A[i][1];
        mat[i][2] = A[i][2];
        mat[i][3] = b[i];
    }

    // Gaussian Elimination
    for (int i = 0; i < 3; i++) {
        float pivot = mat[i][i];
        if (fabs(pivot) < 1e-6) pivot = 1e-6;
        for (int j = i; j < 4; j++) mat[i][j] /= pivot;

        for (int k = 0; k < 3; k++) {
            if (k != i) {
                float factor = mat[k][i];
                for (int j = i; j < 4; j++) mat[k][j] -= factor * mat[i][j];
            }
        }
    }

    // Back-substitution
    for (int i = 0; i < 3; i++) x[i] = mat[i][3];
}

void findValues(float v1, float v2, float v3, float* out) {
    float a = 1000.0, b = 1000.0, c = 1000.0;
    float f[3], J[3][3], delta[3];
    int iter = 0;

    while (iter++ < MAX_ITER) {
        computeFunctions(v1, v2, v3, a, b, c, f);
        if (fabs(f[0]) < EPS && fabs(f[1]) < EPS && fabs(f[2]) < EPS) break;

        computeJacobian(v1, v2, v3, a, b, c, J);

        float negF[3] = { -f[0], -f[1], -f[2] };
        solveLinearSystem(J, negF, delta);

        a += delta[0];
        b += delta[1];
        c += delta[2];

        // Prevent blow-up
        if (isnan(a) || isnan(b) || isnan(c)) break;
    }

    Serial.print("Iterations: "); Serial.println(iter);
    Serial.print("a = "); Serial.println(a, 4);
    Serial.print("b = "); Serial.println(b, 4);
    Serial.print("c = "); Serial.println(c, 4);

    out[0] = a;
    out[1] = b;
    out[2] = c;
}

void setup() {
    Serial.begin(9600);
    while (!Serial);  // Wait for Serial Monitor (optional)

    float result[3];
    findValues(1.89, 1.42, 1.13, result);

    Serial.println("Final Results:");
    Serial.print("a: "); Serial.println(result[0], 4);
    Serial.print("b: "); Serial.println(result[1], 4);
    Serial.print("c: "); Serial.println(result[2], 4);
}

void loop() {
  // Nothing to do here
}
