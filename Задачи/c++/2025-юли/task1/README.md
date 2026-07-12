# Задача 1

Задачата да се реши на езика **C++**.

---

## а) Рекурсивна функция за проверка на повтарящи се цифри

Да се попълнят празните места в дадения долу фрагмент от програмен код така, че функцията `hasRepeatingDigits` да проверява рекурсивно дали в дадено цяло число има повтарящи се цифри.

```cpp
bool hasRepeatingDigits(int number, bool digitCount[])
{
    if (number < 0){
        return __________________________________;
    }
    if (number < 10) {
        return __________________________________;
    }
    int digit = number % 10;
    if (________________________) {
        return true;
    }
    ___________________________;
    return hasRepeatingDigits(_____________, ______________);
}
bool hasRepeatingDigits(int number)
{
    bool digitCount[10] = { false };
    return hasRepeatingDigits(number, digitCount);
}
```

### Решение:

```cpp
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
```

---

## б) Функция за събиране на елементи с повтарящи се цифри

Да се реализира функцията `collect` със следния прототип:

```cpp
int* collect(int** matrix, int rows, int cols, int& resultSize);
```

Функцията да връща като резултат едномерен масив, съдържащ онези елементи на целочислената матрица `matrix` с размерност `rows × cols`, в които има повтарящи се цифри. Едномерният масив трябва да бъде заделен динамично с `new`. Размерът му да бъде точно колкото са елементите с повтарящи се цифри и да се връща чрез параметъра `resultSize`. Може да се използва наготово функцията `hasRepeatingDigits`, както и да се реализират допълнителни помощни функции.

### Решение:

```cpp
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
```

---

## в) Главна програма

Да се реализира програма, която показва работата на функцията, като прочита от стандартния вход размерите на матрицата и елементите ѝ, извиква функцията `collect` и извежда на стандартния изход елементите на масива, който тя връща.

### Решение:

```cpp
#include <iostream>
using namespace std;

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
```

---

## Пълно решение

Вижте файла [task1.cpp](task1.cpp) за цялостната програма.
