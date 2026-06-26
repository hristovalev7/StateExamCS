# Задача 2 - Търсене в документи и папки

Задачата да се реши на езика C++.

## Описание

**Документ** наричаме символен низ с произволна дължина, който има име, също символен низ. Текстът в документа е съставен от редове, разделени със символа `'\n'`.

**Папка** наричаме контейнер, който може да съдържа както документи, така и други папки. Казваме, че `subfolder` е вложена папка във `folder`, ако `subfolder` е елемент на контейнера `folder` или е вложена в някоя папка, която е вложена във `folder`.

**Резултат от търсенето** на низа `str` в даден документ `doc` наричаме такава тройка `(name, N, line)`, където:

- `name` е името на документа `doc`
- `line` е съдържанието на някой ред в документа, съдържащ `str` като подниз
- `N` е поредния номер на `line` в документа

**Операции:**

- Резултатът от `doc.search(str)` е вектор с всички резултати от търсенето на `str` в `doc`
- При търсене в папка `folder`, `folder.search(str)` е вектор с всички резултати от търсенето на `str` в документите, съдържащи се във `folder` или в нейните вложени папки

---

## Условие

В следната програмата на езика за програмиране C++ липсват части.

Класът `Document` описва документ, а класът `Folder` описва папка. Класът `File` е абстрактен базов клас за `Document` и `Folder`, който дефинира операцията `search` за търсене на символен низ в йерархия от документи и папки.

**Да се попълнят липсващите части в програмата.**

При правилно заместване на празните места, програмата ще изведе следното на стандартния изход:

```
employees.txt, line 1: John Smith
employees.txt, line 2: Jane Smith
```

---

## Решение

```cpp
#include <vector>
#include <iostream>
#include <sstream>

struct SearchResult
{
    std::string fileName;
    unsigned line_number;
    std::string line;
};

class File
{
public:
    virtual std::vector<SearchResult> search(const std::string&) const = 0;
};

class Document: public File
{
    std::string name;
    std::string contents;
public:
    Document(const std::string& _name, const std::string& _contents)
        : name(_name), contents(_contents) {}

    std::vector<SearchResult> search(const std::string& s) const
    {
        std::istringstream doc(contents);
        std::string line;
        unsigned lineCount = 0;
        std::vector<SearchResult> result;

        while(std::getline(doc, line))
        {
            ++lineCount;
            if (line.find(s) != std::string::npos)
            {
                result.push_back({name, lineCount, line});
            }
        }
        return result;
    }
};

class Folder: public File
{
    std::vector<File*> files;
    std::string name;
public:
    Folder(const std::string& _name) : name(_name) {}

    void addFile(File* f)
    {
        files.push_back(f);
    }

    std::vector<SearchResult> search(const std::string& s) const
    {
        std::vector<SearchResult> result;
        for(const File* f : files)
        {
            std::vector<SearchResult> found = f->search(s);
            result.insert(result.end(), found.begin(), found.end());
        }
        return result;
    }
};

int main()
{
    Document d1("employees.txt", "John Smith\nMaryia Ivanova\n"),
             d2("inventory.txt", "Computers: 3\nPrinters: 1"),
             d3("employees.txt", "Ivan Petrov\nJane Smith"),
             d4("inventory.txt", "Computers: 5, 3D Printers: 1");

    Folder root("root"), acme("ACME Soft, Inc."), best("Best Soft, OOD");

    acme.addFile(&d1); acme.addFile(&d2);
    best.addFile(&d3); best.addFile(&d4);
    root.addFile(&acme); root.addFile(&best);

    std::vector<SearchResult> results = root.search("Smith");

    for(unsigned i = 0; i < results.size(); ++i)
    {
        std::cout << results[i].fileName
                  << ", line " << results[i].line_number << ": "
                  << results[i].line << std::endl;
    }
}
```

---

## Обяснение

### 1. Структура SearchResult

```cpp
struct SearchResult
{
    std::string fileName;
    unsigned line_number;
    std::string line;
};
```

Съдържа резултата от търсене: име на файл, номер на ред и самия ред.

### 2. Абстрактен базов клас File

```cpp
class File
{
public:
    virtual std::vector<SearchResult> search(const std::string&) const = 0;
};
```

- Дефинира чисто виртуална функция `search`
- `= 0` прави метода **pure virtual** - класът е абстрактен и не може да се инстанцира
- Позволява полиморфизъм - да държим указатели към `File*`, които могат да сочат към `Document` или `Folder`

### 3. Клас Document

```cpp
class Document: public File
{
    std::string name;
    std::string contents;
public:
    Document(const std::string& _name, const std::string& _contents)
        : name(_name), contents(_contents) {}

    std::vector<SearchResult> search(const std::string& s) const
    {
        std::istringstream doc(contents);
        std::string line;
        unsigned lineCount = 0;
        std::vector<SearchResult> result;

        while(std::getline(doc, line))
        {
            ++lineCount;
            if (line.find(s) != std::string::npos)
            {
                result.push_back({name, lineCount, line});
            }
        }
        return result;
    }
};
```

**Обяснение на search:**

- **std::istringstream** - създава входен поток от низ, позволява четене ред по ред
- **std::getline(doc, line)** - чете следващия ред от `contents` в `line`
- **line.find(s)** - търси подниз `s` в `line`, връща позицията или `std::string::npos` ако не е намерен
- **++lineCount** - увеличава броя на редовете (започваме от 1)
- **result.push_back({name, lineCount, line})** - добавя резултат чрез aggregate initialization

### 4. Клас Folder

```cpp
class Folder: public File
{
    std::vector<File*> files;
    std::string name;
public:
    Folder(const std::string& _name) : name(_name) {}

    void addFile(File* f)
    {
        files.push_back(f);
    }

    std::vector<SearchResult> search(const std::string& s) const
    {
        std::vector<SearchResult> result;
        for(const File* f : files)
        {
            std::vector<SearchResult> found = f->search(s);
            result.insert(result.end(), found.begin(), found.end());
        }
        return result;
    }
};
```

**Обяснение на search:**

- **std::vector<File\*> files** - съдържа указатели към `File` (могат да са `Document` или `Folder`)
- **f->search(s)** - полиморфно извикване - ако `f` сочи към `Document`, извиква `Document::search`, ако сочи към `Folder`, извиква `Folder::search`
- **result.insert(result.end(), found.begin(), found.end())** - добавя всички елементи от `found` в края на `result`
- Рекурсивно търсене - ако `files` съдържа `Folder`, той също ще извика `search` върху своите файлове

### 5. Йерархия в main

```
root (Folder)
├── acme (Folder)
│   ├── d1: employees.txt - "John Smith\nMaryia Ivanova\n"
│   └── d2: inventory.txt - "Computers: 3\nPrinters: 1"
└── best (Folder)
    ├── d3: employees.txt - "Ivan Petrov\nJane Smith"
    └── d4: inventory.txt - "Computers: 5, 3D Printers: 1"
```

**Търсене на "Smith":**

1. `root.search("Smith")` търси във всички вложени файлове
2. Намира "Smith" в:
   - `d1` ред 1: "John Smith"
   - `d3` ред 2: "Jane Smith"

**Изход:**

```
employees.txt, line 1: John Smith
employees.txt, line 2: Jane Smith
```

---

## Ключови концепции

1. **Абстрактни класове** - клас с поне една pure virtual функция (= 0)
2. **Полиморфизъм** - извикване на правилната функция според типа на обекта по време на изпълнение
3. **Virtual функции** - позволяват override в наследниците
4. **Composite pattern** - `Folder` съдържа `File*`, които могат да са `Document` или `Folder` (рекурсивна структура)
5. **std::istringstream** - четене от низ като от файл
6. **std::string::find** - търсене на подниз, връща позиция или `npos`
7. **Range-based for loop** - `for(const File* f : files)` обхожда всички елементи
8. **Aggregate initialization** - `{name, lineCount, line}` създава `SearchResult` без explicit конструктор

---

## Алгоритмична сложност

- **Document::search:** O(n·m), където n е броят редове, m е дължината на реда (заради `find`)
- **Folder::search:** O(k·T), където k е броят файлове в папката, T е времето за търсене в един файл
- **Общо:** O(N·m), където N е общият брой редове във всички документи
