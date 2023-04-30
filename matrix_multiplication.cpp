#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

int main()
{
    int n = 1000; // Matrix size
    int i, j, k;
    double sum = 0;

    // Generate random matrices A and B
    double **A = new double *[n];
    double **B = new double *[n];
    double **C = new double *[n];

    for (i = 0; i < n; i++)
    {
        A[i] = new double[n];
        B[i] = new double[n];
        C[i] = new double[n];

        for (j = 0; j < n; j++)
        {
            A[i][j] = (double)rand() / RAND_MAX;
            B[i][j] = (double)rand() / RAND_MAX;
            C[i][j] = 0;
        }
    }

    auto start_time = chrono::high_resolution_clock::now(); // Start Timer

    // Matrix multiplication
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now(); // End Timer

    // Output Result to file
    ofstream outfile;
    outfile.open("output.txt");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            outfile << C[i][j] << " ";
        }
        outfile << endl;
    }

    outfile.close();

    // Execution time
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    // Free memory
    for (i = 0; i < n; i++)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
