#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <pthread.h>

using namespace std;

int n = 1000; // Matrix size
double **A, **B, **C;
int num_threads;

struct ThreadArg
{
int id;
};

void *multiply(void *arg)
{
ThreadArg *thread_arg = (ThreadArg *)arg;
int i, j, k;
int start_row, end_row;
// Calculate the start and end rows for the current thread
int rows_per_thread = n / num_threads;
start_row = thread_arg->id * rows_per_thread;
end_row = start_row + rows_per_thread;

// Calculate matrix multiplication for the assigned rows
for (i = start_row; i < end_row; i++)
{
    for (j = 0; j < n; j++)
    {
        C[i][j] = 0;
        for (k = 0; k < n; k++)
        {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}

pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
if (argc < 2)
{
cerr << "Usage: " << argv[0] << " num_threads" << endl;
exit(1);
}
num_threads = atoi(argv[1]);
pthread_t threads[num_threads];
ThreadArg thread_args[num_threads];

// Initialize matrices A and B with random values
A = new double *[n];
B = new double *[n];
C = new double *[n];
for (int i = 0; i < n; i++)
{
    A[i] = new double[n];
    B[i] = new double[n];
    C[i] = new double[n];
    for (int j = 0; j < n; j++)
    {
        A[i][j] = (double)rand() / RAND_MAX;
        B[i][j] = (double)rand() / RAND_MAX;
        C[i][j] = 0;
    }
}

// Start timer
auto start_time = chrono::high_resolution_clock::now();

// Create threads and assign work
for (int i = 0; i < num_threads; i++)
{
    thread_args[i].id = i;
    pthread_create(&threads[i], NULL, multiply, (void *)&thread_args[i]);
}

// Wait for all threads to finish
for (int i = 0; i < num_threads; i++)
{
    pthread_join(threads[i], NULL);
}

// Stop timer
auto end_time = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

// Write output to file
ofstream outfile("output.txt");
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < n; j++)
    {
        outfile << C[i][j] << " ";
    }
    outfile << endl;
}

// Print execution time
cout << "Execution time: " << duration.count() << " milliseconds" << endl;

return 0;
}
