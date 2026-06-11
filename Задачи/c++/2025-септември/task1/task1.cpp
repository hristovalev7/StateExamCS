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
    } catch (bad_alloc&) {
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

// Б)
bool contains(int* arr, size_t size, int value) {
  if (arr == nullptr || size == 0) {
    return false;
  }

  size_t mid = size / 2;

  if (arr[mid] == value) {
    return true;
  } else if (value < arr[mid]) {  // left
    return contains(arr, mid, value);
  } else {  // right
    return contains(arr + mid + 1, size - mid - 1, value);
  }
}

// В)
bool equal(double a, double b, double epsilon = 1e-10) {
  if (isnan(a) && isnan(b)) {
    return true;
  } else if (isinf(a) && isinf(b)) {
    return a == b;
  } else {
    return abs(a - b) < epsilon;
  }
}

bool less(double a, double b) {
  return !equal(a, b) && a < b;
}

int main() {
  int* arr = new int[5]{1, 2, 3, 4, 5};

  delete[] arr;
  return 0;
}
