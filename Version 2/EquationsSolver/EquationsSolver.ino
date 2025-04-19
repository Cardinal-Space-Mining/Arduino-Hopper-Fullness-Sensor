#include <Arduino.h>
#include <math.h>

#define EPS 1e-7        // Convergence threshold
#define MAX_ITER 1000   // Max iterations
#define DELTA 1e-5      // Step size for finite differences

void setup(){Serial.begin(9600);}

void loop(){
  FindValues(1.89, 1.42, 1.13);
  
  delay(5000);
  }
// Compute function values f1, f2, f3
void compute_functions(double v1, double v2, double v3, double a, double b, double c, double *f) {
    f[0] = v1 - 5.0 / (a * (1.0 / 10000.0 + 1.0 / b + 1.0 / c) + 1.0);
    f[1] = v2 - 5.0 / (b * (1.0 / 10000.0 + 1.0 / a + 1.0 / c) + 1.0);
    f[2] = v3 - 5.0 / (c * (1.0 / 10000.0 + 1.0 / a + 1.0 / b) + 1.0);

   /* 
   Serial.print("out: "); Serial.print(f[0],8);
   Serial.print(" "); Serial.print(f[1],8);
   Serial.print(" "); Serial.println(f[2],8);*/
}

// Approximate the Jacobian matrix numerically
void compute_jacobian(double v1, double v2, double v3, double a, double b, double c, double J[3][3]) {
    double f0[3], f1[3];

    // Original values
    compute_functions(v1,v2,v3, a, b, c, f0);

    // Perturb a
    compute_functions(v1,v2,v3, a + DELTA, b, c, f1);
    for (int i = 0; i < 3; i++)
        J[i][0] = (f1[i] - f0[i]) / DELTA;

    // Perturb b
    compute_functions(v1,v2,v3, a, b + DELTA, c, f1);
    for (int i = 0; i < 3; i++)
        J[i][1] = (f1[i] - f0[i]) / DELTA;

    // Perturb c
    compute_functions(v1,v2,v3, a, b, c + DELTA, f1);
    for (int i = 0; i < 3; i++)
        J[i][2] = (f1[i] - f0[i]) / DELTA;
    
    Serial.print("Da: "); Serial.print(J,8);
    Serial.print(", "); Serial.print(delta[1],8);
    Serial.print(", "); Serial.println(delta[2],8);

}

// Solve a 3x3 linear system using Gaussian elimination
void solve_linear_system(double A[3][3], double b[3], double x[3]) {
    double mat[3][4];

    // Copy A and b into augmented matrix
    for (int i = 0; i < 3; i++) {
        mat[i][0] = A[i][0];
        mat[i][1] = A[i][1];
        mat[i][2] = A[i][2];
        mat[i][3] = b[i];
    }

    // Gaussian elimination
    for (int i = 0; i < 3; i++) {
        // Normalize row i
        double pivot = mat[i][i];
        for (int j = i; j < 4; j++)
            mat[i][j] /= pivot;

        // Eliminate column i in other rows
        for (int k = 0; k < 3; k++) {
            if (k != i) {
                double factor = mat[k][i];
                for (int j = i; j < 4; j++)
                    mat[k][j] -= factor * mat[i][j];
            }
        }
    }

    // Extract solution
    for (int i = 0; i < 3; i++)
        x[i] = mat[i][3];
}

void FindValues(double v1, double v2, double v3) {
    // Initial guess
    double a = 1000, b = 1000, c = 1000;
    double f[3], J[3][3], delta[3];
    int iter = 0;

    while (iter++ < MAX_ITER) {
        compute_functions(v1,v2,v3, a, b, c, f);
        
        // Check for convergence
      if ((f[0] < EPS && f[0] > -EPS) &&(f[1] < EPS && f[1] > -EPS) &&(f[2] < EPS && f[2] > -EPS))
          break;

        compute_jacobian(v1,v2,v3, a, b, c, J);

        // Solve J * delta = -f
        double minus_f[3] = { -f[0], -f[1], -f[2] };
        solve_linear_system(J, minus_f, delta);

        a += delta[0];
        b += delta[1];
        c += delta[2];
    }

    // Print result
    //printf("Solution after %d iterations:\n", iter);
    Serial.print("R1: "); Serial.println(a);
    Serial.print("R2: "); Serial.println(b);
    Serial.print("R3: "); Serial.println(c);
}
