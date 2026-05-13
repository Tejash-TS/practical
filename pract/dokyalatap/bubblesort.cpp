#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

// Sequential Bubble Sort
void bubble_seq(int *a, int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

// Parallel Bubble Sort (Odd-Even Sort)
void bubble_parallel(int *a, int n) {
    for(int i = 0; i < n; i++) {
        int first = i % 2;

        #pragma omp parallel for shared(a, first)
        for(int j = first; j < n-1; j += 2) {
            if(a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int *a = new int[n];
    int *b = new int[n];

    cout << "Enter elements:\n";
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i]; // copy for parallel
    }

    // Sequential timing
    double start = omp_get_wtime();
    bubble_seq(a, n);
    double end = omp_get_wtime();
    double seq_time = end - start;

    // Parallel timing
    start = omp_get_wtime();
    bubble_parallel(b, n);
    end = omp_get_wtime();
    double par_time = end - start;

    // Output
    cout << "\nSorted array (Parallel):\n";
    for(int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }

    cout << "\n\nSequential Time: " << seq_time;
    cout << "\nParallel Time: " << par_time;
    cout << "\nSpeedup: " << seq_time / par_time << endl;

    return 0;
}