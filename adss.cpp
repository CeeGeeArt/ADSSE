#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<chrono>
#include<ctime>
using namespace std;
using namespace std::chrono;
using namespace std;

// SUPPLEMENTARY FUNCTIONS
void printArray(int array[], int arrSize, int newlineSize) {
    for (int i = 0; i < arrSize; i++) {
        cout << array[i] << " ";
        if ((i + 1) % newlineSize == 0 && i != 0) {
            cout << "\n";
        }
    }
    cout << "\n";
}
// RANDOMIZED SELECT
int Partition(int PArray[], int Pstart, int Pend) {
    int x = PArray[Pend];
    int i = Pstart - 1;
    for (int j = Pstart; j < Pend; j++) {
        if (PArray[j] <= x) {
            i = i + 1;
            int temp = PArray[i];
            PArray[i] = PArray[j];
            PArray[j] = temp;
        }
    }
    int temp = PArray[i + 1];
    PArray[i + 1] = PArray[Pend];
    PArray[Pend] = temp;
    return i + 1;
}

int RandomizedPartition(int RPArray[], int RPstart, int RPend) {
    int i = rand() % (RPend - RPstart + 1) + RPstart;
    int temp = RPArray[RPend];
    RPArray[RPend] = RPArray[i];
    RPArray[i] = temp;
    return Partition(RPArray, RPstart, RPend);
}

int RandomizedSelect(int Array[], int start, int end, int target) {
    if (start == end) {
        return Array[start];
    }
    int pivot = RandomizedPartition(Array, start, end);
    int k = pivot - start + 1;
    if (target == k) {
        return Array[pivot];
    }
    else if (target < k) {
        return RandomizedSelect(Array, start, pivot - 1, target);
    }
    else {
        return RandomizedSelect(Array, pivot + 1, end, target - k);
    }
}
// BUBBLE SORT BEGIN
void bubbleSort(int A[], int n) {
    bool swapped = true;
    while (swapped == true) {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (A[i - 1] > A[i]) {
                swap(A[i - 1], A[i]);
                swapped = true;
            }
        }
        n = n - 1;
    }
}
// GNOME SORT BEGIN
void gnomeSort(int a[], int dataSize) {
    int pos = 0;
    while (pos < dataSize) {
        if (pos == 0 || a[pos] >= a[pos - 1]) {
            pos = pos + 1;
        }
        else {
            swap(a[pos], a[pos - 1]);
            pos = pos - 1;
        }
    }
}
// MAIN
int main() {
    const int dataSize = 85000;
    int dataArray[dataSize];
    int dataArray2[dataSize];
    int dataArray3[dataSize];
    fstream dataSet("data.csv");
    if (dataSet.is_open()) {
        for (int i = 0; i < dataSize; i++) {
            string lineElement;
            getline(dataSet, lineElement, ',');
            dataArray[i] = stoi(lineElement);
            dataArray2[i] = stoi(lineElement);
            dataArray3[i] = stoi(lineElement);
        }
    }

    printArray(dataArray, dataSize, 85000);

    cout << "---" << endl;

    int inputStart = 0;
    int inputEnd = dataSize - 1;
    int inputTarget = 500;

    // RUNNING TIME FOR BUBBLE SORT
    steady_clock::time_point bubbleSortStart = steady_clock::now();
    bubbleSort(dataArray2, dataSize);
    cout << dataArray2[inputTarget - 1] << endl;
    steady_clock::time_point bubbleSortStop = steady_clock::now();
    auto bubbleSortDuration = bubbleSortStop - bubbleSortStart;
    cout << "--- Bubble Sort Running Time: " << duration <double, milli>(bubbleSortDuration).count() << " ms " << " ---" << endl << endl;

    // RUNNING TIMES
    // RUNNING TIME FOR RANDOM SELECT
    steady_clock::time_point randSelectStart = steady_clock::now();
    cout << RandomizedSelect(dataArray, inputStart, inputEnd, inputTarget) << endl;
    steady_clock::time_point randSelectStop = steady_clock::now();
    auto randSelectDuration = randSelectStop - randSelectStart;
    cout << "--- Randomized Select Running Time: " << duration <double, milli>(randSelectDuration).count() << " ms " << " ---" << endl << endl;

    //RUNNING TIME FOR GNOME SORT
    steady_clock::time_point gnomeSortStart = steady_clock::now();
    gnomeSort(dataArray3, dataSize);
    cout << dataArray3[inputTarget - 1] << endl;
    steady_clock::time_point gnomeSortStop = steady_clock::now();
    auto gnomeSortDuration = gnomeSortStop - gnomeSortStart;
    cout << "--- Gnome Sort Running Time: " << duration <double, milli>(gnomeSortDuration).count() << " ms " << " ---" << endl << endl;

    return 0;
}