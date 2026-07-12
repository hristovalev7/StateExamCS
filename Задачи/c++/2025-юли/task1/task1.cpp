#include <iostream>
using namespace std;

// a)
bool hasRepeatingDigits(int number, bool digitCount[]) {
  if (number < 0) {
    return hasRepeatingDigits(-number, digitCount);
  }

  if (number < 10) {  // base case when we have a single digit
    return digitCount[number];
  }

  int digit = number % 10;

  if (digitCount[digit]) {
    return true;
  }

  digitCount[digit] = true;
  return hasRepeatingDigits(number / 10, digitCount);
}

bool hasRepeatingDigits(int number) {
  bool digitCount[10] = {false};

  return hasRepeatingDigits(number, digitCount);
}

// б)
int countRepeatingDigitsNumbers(int** matrix, int rows, int cols) {
  int count = 0;

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      if (hasRepeatingDigits(matrix[r][c])) {
        count++;
      }
    }
  }

  return count;
}

void collectMatching(int* repeatingDigitsNumbers,
                     int** matrix,
                     int rows,
                     int cols) {
  int idx = 0;

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      if (hasRepeatingDigits(matrix[r][c])) {
        repeatingDigitsNumbers[idx] = matrix[r][c];
        idx++;
      }
    }
  }
}

int* collect(int** matrix, int rows, int cols, int& resultSize) {
  if (!matrix || rows <= 0 || cols <= 0) {
    return nullptr;
  }

  resultSize = countRepeatingDigitsNumbers(matrix, rows, cols);

  if (resultSize == 0) {
    return nullptr;
  }

  int* repeatingDigitsNumbers = new int[resultSize];

  collectMatching(repeatingDigitsNumbers, matrix, rows, cols);

  return repeatingDigitsNumbers;
}

// в)
void freeMatrix(int** matrix, int rows) {
  for (size_t r = 0; r < rows; r++) {
    delete[] matrix[r];
  }
  delete[] matrix;
}

void readInput() {
  int rows, cols;
  cin >> rows >> cols;

  if (rows == 0 || cols == 0) {
    cout << "Invalid matrix!\n";
    return;
  }

  int** matrix = nullptr;
  size_t r = 0;
  try {
    matrix = new int*[rows];

    for (r = 0; r < rows; r++) {
      matrix[r] = new int[cols];
    }
  } catch (bad_alloc&) {
    for (int i = 0; i < r; i++)
      delete[] matrix[i];
    delete[] matrix;
    cout << "No memory!\n";
    return;
  }

  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      cin >> matrix[r][c];
    }
  }

  int resultSize = 0;
  int* repeatingDigitsNumbers = collect(matrix, rows, cols, resultSize);

  if (repeatingDigitsNumbers != nullptr) {
    for (size_t i = 0; i < resultSize; i++) {
      cout << repeatingDigitsNumbers[i] << ' ';
    }
  }

  delete[] repeatingDigitsNumbers;
  freeMatrix(matrix, rows);
}

int main() {
  readInput();

  return 0;
}