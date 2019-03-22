#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

const int N = 2e8;
const double eps = 1e-5;

void vectorSumSequential(double* a, double* b, double* c, int N) {
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }
}

int main (int argc, char* argv[])
{
    cout.precision(4);

    int size, rank;

    double *a;
    double *b;
    double *c;
    double *ap;
    double *bp;
    double *cp;

    double startTime, finishTime, duration;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n1 = N / size;
    if (N % size) {
        ++n1;
    }

    ap = new double[n1];
    bp = new double[n1];
    cp = new double[n1];

    if (rank == 0) {
        a = new double[N];
        b = new double[N];
        c = new double[N];
        for (int i = 0; i < N; ++i) {
            a[i] = rand() / 31.5;
            b[i] = rand() / 1024.0;
        }

//        startTime = MPI_Wtime();
//        vectorSumSequential(a, b, c, N);
//        finishTime = MPI_Wtime();
//        duration = finishTime - startTime;
//
//        cout << N << ',' << 1 << ',' << fixed << duration << endl;
//        cerr << fixed << "N = " << N << ", processes = " << 1 << ", time = " << fixed << duration << endl;
        startTime = MPI_Wtime();
    }

    MPI_Scatter(a, n1, MPI_DOUBLE, ap, n1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, n1, MPI_DOUBLE, bp, n1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < n1; ++i) {
        cp[i] = ap[i] + bp[i];
    }

    MPI_Gather(cp, n1, MPI_DOUBLE, c, n1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        finishTime = MPI_Wtime();
        duration = finishTime - startTime;
        cout << N << ',' << size << ',' << fixed << duration << endl;
//        cerr << fixed << "N = " << N << ", processes = " << size << ", time = " << fixed << duration << endl;
        bool isCorrect = true;
        for (int i = 0; i < N; ++i) {
            if (fabs(c[i] - (a[i] + b[i])) >= eps) {
                isCorrect = false;
                cerr << "WRONG!\n";
                break;
            }
        }
        if (isCorrect) {
            cerr << "OK\n";
        }
    }

    MPI_Finalize();
    return 0;
}