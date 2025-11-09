#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class QuickSortAnalyzer {
private:
    long long deter_comp;
    long long random_comp;

public:
    QuickSortAnalyzer() {
        deter_comp = 0;
        random_comp = 0;
    }

    // Deterministic quicksort partition - pivot = last element
    int partitionDeterministic(vector<int> &arr, int left, int right) {
        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
            deter_comp++;
        }
        swap(arr[i + 1], arr[right]);
        return i + 1;
    }

    void quickSortDeterministic(vector<int> &arr, int left, int right) {
        if (left < right) {
            int pivot = partitionDeterministic(arr, left, right);
            quickSortDeterministic(arr, left, pivot - 1);
            quickSortDeterministic(arr, pivot + 1, right);
        }
    }

    // Randomized quicksort partition - randomly selected pivot
    int partitionRandomized(vector<int> &arr, int left, int right) {
        int pivotIndex = left + rand() % (right - left + 1);
        swap(arr[pivotIndex], arr[right]); // move random pivot to end

        int pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
            random_comp++;
        }
        swap(arr[i + 1], arr[right]);
        return i + 1;
    }

    void quickSortRandomized(vector<int> &arr, int left, int right) {
        if (left < right) {
            int pivot = partitionRandomized(arr, left, right);
            quickSortRandomized(arr, left, pivot - 1);
            quickSortRandomized(arr, pivot + 1, right);
        }
    }

    long long getdeter_comp() {
        return deter_comp;
    }

    long long getrandom_comp() {
        return random_comp;
    }

    void resetCounts() {
        deter_comp = 0;
        random_comp = 0;
    }
};

int main() {
    srand(time(NULL));

    QuickSortAnalyzer qs;
    int choice;

    while (true) {
        cout << "\n---------- QUICK SORT ANALYSIS MENU ----------\n";
        cout << "1. Deterministic Quick Sort (last element pivot)\n";
        cout << "2. Randomized Quick Sort (random pivot)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        }

        int n;
        cout << "Enter number of elements: ";
        cin >> n;

        vector<int> arr(n);
        cout << "Enter elements: ";
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        qs.resetCounts(); // ensures fresh comparison count for each choice

        if (choice == 1) {
            qs.quickSortDeterministic(arr, 0, n - 1);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << "\nNumber of comparisons (deterministic quick sort): "
                 << qs.getdeter_comp() << "\n";

        } else if (choice == 2) {
            qs.quickSortRandomized(arr, 0, n - 1);
            cout << "Sorted array: ";
            for (int x : arr) cout << x << " ";
            cout << "\nNumber of comparisons (randomized quick sort): "
                 << qs.getrandom_comp() << "\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
