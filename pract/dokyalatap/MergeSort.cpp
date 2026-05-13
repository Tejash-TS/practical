#include <iostream>
#include <omp.h>
using namespace std;

// ---------- SEQUENTIAL ----------
void merge(int a[], int l, int m, int r) {
    int temp[1000], i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (a[i] < a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (i = l, j = 0; i <= r; i++, j++)
        a[i] = temp[j];
}

void sequentialMergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        sequentialMergeSort(a, l, m);
        sequentialMergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

// ---------- PARALLEL ----------
void parallelMergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(a, l, m);

            #pragma omp section
            parallelMergeSort(a, m + 1, r);
        }

        merge(a, l, m, r);
    }
}

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int *a = new int[n];
    int *b = new int[n]; // copy array

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i]; // copy for parallel
    }

    double start, stop;

    // -------- SEQUENTIAL TIME --------
    start = omp_get_wtime();
    sequentialMergeSort(a, 0, n - 1);
    stop = omp_get_wtime();
    double seqTime = stop - start;

    // -------- PARALLEL TIME --------
    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelMergeSort(b, 0, n - 1);
        }
    }

    stop = omp_get_wtime();
    double parTime = stop - start;

    // -------- OUTPUT --------
    cout << "\nSorted (Sequential): ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";

    cout << "\nSorted (Parallel): ";
    for (int i = 0; i < n; i++) cout << b[i] << " ";

    cout << "\n\nSequential Time: " << seqTime << " sec";
    cout << "\nParallel Time: " << parTime << " sec";

    cout << "\nSpeedup: " << (seqTime / parTime) << endl;

    return 0;
}