# Задача 3

Задачата да се реши на езика **C++**.

---

## а) Функция `insertSum` за едносвързан списък

Елементите на едносвързан списък представяме чрез следната структура:

```cpp
struct node {
    int value;
    node* next;
};
```

Празния списък представяме като `nullptr`.

Да се реализира функция `insertSum`, която обработва подаден ѝ като аргумент списък, като между всеки два негови последователни елемента с нечетни стойности вмъква нов елемент със стойност – тяхната сума. Паметта за новите елементи да се заделя с `new`.

**Примерен вход:**

```
1 ⟶ 2 ⟶ 3 ⟶ 5 ⟶ 3 ⟶ 0 ⟶ 2
```

**Очакван резултат:**

```
1 ⟶ 2 ⟶ 3 ⟶ 8 ⟶ 5 ⟶ 8 ⟶ 3 ⟶ 0 ⟶ 2
```

### Решение:

```cpp
bool isOdd(int num) {
  return num % 2 == 1;
}

void insertSum(node* head) {
  if (head == nullptr) {
    cout << "List is empty";
    return;
  }

  node* iter = head;

  while (iter && iter->next) {  // it is not a single node
    bool currIsOdd = isOdd(iter->value);
    bool nextIsOdd = isOdd(iter->next->value);

    if (currIsOdd && nextIsOdd) {
      node* tmp = iter->next;

      try {
        iter->next = new node{iter->value + iter->next->value,
                              tmp};  // insert between them
      } catch (const std::bad_alloc&) {
        cerr << "Problem with allocating memory";
        return;
      }

      iter = tmp;
      continue;
    }

    iter = iter->next;
  }
}
```

---

## б) Програма за демонстрация на `insertSum`

Да се напише програма, която демонстрира работата на функцията `insertSum`. Тя трябва да прочете от стандартния вход елементите на свързан списък, върху които да приложи функцията, и след това да изведе на екрана получения резултат. Трябва да се подсигури коректна работа с паметта.

### Решение:

```cpp
void free(node* head) {
  while (head) {
    node* toDel = head;
    head = head->next;
    delete toDel;
  }
}

void print(node* head) {
  while (head) {
    cout << head->value << ' ';
    head = head->next;
  }
  cout << '\n';
}

node* createList(int itemCnt) {
  node* newNode = nullptr;

  if (itemCnt == 0) {
    return newNode;
  }

  try {
    int value;
    cin >> value;

    newNode = new node{value, createList(itemCnt - 1)};
  } catch (const bad_alloc&) {
    cerr << "Problem with allocating memory";
    return nullptr;
  }

  return newNode;
}

int main() {
  int cnt = 7;
  node* head = createList(cnt);

  print(head);
  insertSum(head);
  print(head);

  free(head);
  return 0;
}
```

---

## в) Анализ на грешки в функция за изтриване от BST

Следната функция трябва да премахва елемент по ключ от двоично дърво за търсене, но в нея са допуснати грешки. Да се посочат кои са грешките и за всяка от тях да се обясни максимално точно защо е грешка и как трябва да се коригира.

### Оригинален код с грешки:

```cpp
struct node
{
    int value;
    node* left, *right;
};

void remove(node*& root, int key)
{
    if (root->value < key)
        return remove(root->right, key);
    if (root->value > key)
        return remove(root->left, key);
    if (!root->left) root = root->right;
    else if (!root->right) root = root->left;
    else {
        node min = root->left;
        while (min->left){
            min = min->left;
        }
        root->value = min->value;
        min = min->right;
    }
}
```

### Грешки и корекции:

#### Грешка 1: Липсва проверка за празно дърво

**Ред:** Първият ред на функцията  
**Проблем:** Ако `root` е `nullptr`, достъпът до `root->value` води до undefined behavior.  
**Корекция:** Трябва да се добави проверка в началото:

```cpp
if (!root) return;
```

#### Грешка 2: Грешен тип на променливата `min`

**Ред:** `node min = root->left;`  
**Проблем:** `min` е обект от тип `node`, а не указател. Трябва да е `node*` или `node**`.  
**Корекция:**

```cpp
node** min = &root->right;  // Трябва да търсим в дясното поддърво
```

#### Грешка 3: Грешно поддърво за намиране на минимум

**Ред:** `node min = root->left;`  
**Проблем:** При премахване на възел с две деца, минималният елемент трябва да се търси в **дясното** поддърво, не в лявото.  
**Корекция:** `->right` вместо `->left`

#### Грешка 4: Нямаме достъп до родителя на минималния възел

**Проблем:** Променливата `min` трябва да е `node**`, за да можем да променим указателя в родителя.  
**Корекция:** Използваме `node**` и работим с `*min` и `(*min)->left`

#### Грешка 5: Липсва освобождаване на паметта

**Проблем:** След като премахнем възела, паметта не се освобождава с `delete`.  
**Корекция:** Трябва да запазим указател към възела, който ще се изтрие, и да го изтрием накрая.

### Коректен код:

```cpp
struct node
{
    int value;
    node* left, *right;
};

void remove(node*& root, int key)
{
    if (!root) return;                          // ДОБАВЕНО
    if (root->value < key)
        return remove(root->right, key);
    if (root->value > key)
        return remove(root->left, key);

    node* toDel = root;                         // ДОБАВЕНО

    if (!root->left) root = root->right;
    else if (!root->right) root = root->left;
    else {
        node** min = &root->right;              // ПОПРАВЕНО (node** и ->right)
        while ((*min)->left){                   // ПОПРАВЕНО
            min = &(*min)->left;                // ПОПРАВЕНО
        }
        root->value = (*min)->value;            // ПОПРАВЕНО
        toDel = *min;                           // ДОБАВЕНО
        *min = (*min)->right;                   // ПОПРАВЕНО
    }
    delete toDel;                               // ДОБАВЕНО
}
```

---

## Пълно решение

Вижте файла [task3.cpp](task3.cpp) за цялостната програма.
