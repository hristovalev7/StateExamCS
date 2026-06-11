#include <iostream>
using namespace std;

// A)
bool resize(int*& arr, size_t size, size_t new_size) {
    if (size == new_size) {
        return true;
    }

    int* new_arr = nullptr;
    if (new_size > 0) {
        try {
            new_arr = new int[new_size];
        }
        catch (bad_alloc&) {
            return false;
        }
    }
	
    size_t limit = min(size, new_size);

    for (size_t i = 0; i < limit; ++i) {
        new_arr[i] = arr[i];
	}

    delete[] arr;
    arr = new_arr;
    return true;
}

int main() {
    int* arr = new int[5] {1, 2, 3, 4, 5};
    resize(arr, 5, 0);
    cout << arr << endl;
   /* for (size_t i = 0; i < 5; ++i) {
        cout << arr[i] << endl;
    }*/

    delete[] arr;
    return 0;
}
