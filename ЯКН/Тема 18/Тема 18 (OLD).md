# Структури от данни — конспект за държавен изпит

## 1. Структури от данни — дефиниране на понятието

### 1.1 Тип данни (ТД)

**Тип данни** е инструмент за класификация на данните. Характеризира се с:

- **множество от стойности** (например `int` — всички цели числа в даден диапазон);
- **множество от операции** върху тези стойности (за `int`: `+`, `-`, `*`, `/`, `<`, ...).

Типът сам по себе си не казва нищо за това *как точно* е разположена информацията в паметта — той дава абстрактен интерфейс.

### 1.2 Структура от данни (СД)

**Структура от данни** е *схема за организация* на определен вид данни в паметта на компютъра — обикновено с цел ефективност на операциите.

Разликата с ТД:

- ТД отговаря на въпроса „какво?" (какви стойности, какви операции);
- СД отговаря на въпроса „как?" (как точно се подреждат байтовете, кои указатели сочат накъде).

Всеки съставен ТД може да се разглежда като СД. Пример: масивът `int a[10]` е СД, която представя 10 цели числа *последователно* в паметта.

### 1.3 Абстрактен тип данни (АТД)

**АТД** е *формален модел* на ТД или СД. Описва:

1. множеството от стойности;
2. имената и сигнатурите на операциите;
3. поведението и свойствата на операциите (обикновено чрез аксиоми).

АТД **не** налага конкретна организация на паметта и **не** налага конкретен език за реализация. Един АТД може да има няколко различни реализации (примерно стек със статичен масив, с разширяващ се масив или със свързан списък).

### 1.4 Логическо и физическо описание

Когато описваме една СД, разделяме описанието на две части:

**Логическо описание (АТД):**

- същност и предназначение;
- компоненти;
- операции;
- свойства на операциите.

**Физическо описание:**

- организация на паметта;
- представяне чрез един или повече ТД;
- реализация на операциите.

Тази дисциплина е важна: на изпит първо казваме *какво* представлява структурата (логически), и едва след това — *как* я реализираме (физически).

### 1.5 Класификация на СД

Според вида на компонентите:

- **хомогенни** — всички елементи са от един тип (масив, стек, опашка, списък, дърво в чистия си вид);
- **хетерогенни** — различни типове елементи (структура/`struct`, хетерогенен списък).

Според способността за промяна на размера:

- **статични** — фиксиран капацитет (статичен масив `int a[10]`);
- **динамични** — разширяват се (разширяващ се масив, свързан списък).

Според връзките между данните:

- **линейни** — всеки елемент има най-много един „следващ" (масив, списък, стек, опашка);
- **разклонени** — всеки елемент може да има няколко „наследници" (дърво);
- **мрежови** — произволни връзки между елементи (граф).

### 1.6 Интуиция

Когато избирате СД, питайте се:

1. *Колко често ще добавям/премахвам?* — ако много, искам O(1) за тези операции (списък/стек/опашка).
2. *Колко често ще търся?* — ако много, искам O(log n) или O(1) търсене (BST, хеш).
3. *Колко елементи ще има?* — ако броят е известен и фиксиран — статична реализация; ако расте — динамична.
4. *Достъп с произволен индекс ли искам, или само в началото/края?* — ако само в краищата, връзките са по-евтини от масивите.

---

## 2. Списък

### 2.1 АТД списък — логическо описание

**Списък** е *хомогенна линейна структура с последователен достъп до елементите*. Това означава: за да стигна до 5-ия елемент, обикновено трябва да мина през 1-ви, 2-ри, 3-ти и 4-ти (за разлика от масива, където директно индексирам).

Основни операции:

- `create()` — създаване на празен списък;
- `empty()` — проверка дали е празен;
- `insert(x, p)` — включване на елемент `x` на позиция `p`;
- `delete(p)` — изключване на елемента на позиция `p`;
- `get(p)` — достъп до елемента на позиция `p`.

**Позиция** (или *итератор*) — абстракция, която казва „кое място в списъка имам предвид сега". Тя е отделна от стойността на елемента.

### 2.2 Едносвързано представяне

Всеки елемент е „двойна кутия": *данна* + *указател към следващия*.

```
  [a1|·]──►[a2|·]──►[a3|·]──►[a4|·]──►NULL
   ▲                                   
  head
```

```cpp
template <typename T>
struct ListElement {
    T data;
    ListElement<T>* next;
};
```

**Защо точно така?** Защото елементите *не са* подредени последователно в паметта — всяко `new` връща произволен адрес. Затова всеки елемент трябва „да си носи адреса на следващия", иначе няма как да обхождаме.

**Какво трябва да помним за списъка като цяло?** Минимум — указател към първия елемент (`head`). По избор пазим и указател към последния (`tail`) — това ускорява вмъкване в края до O(1).

### 2.3 Двусвързано представяне

Всеки елемент носи и указател към *предишния*:

```
NULL◄──[·|a1|·]◄──►[·|a2|·]◄──►[·|a3|·]──►NULL
        ▲                       ▲
       head                    tail
```

```cpp
template <typename T>
struct DListElement {
    T data;
    DListElement<T>* next;
    DListElement<T>* prev;
};
```

### 2.4 Характеристики на реализациите

**Едносвързан списък:**

- ✅ По-малко памет на елемент (един указател);
- ✅ Прост код;
- ❌ Не може да се обхожда назад;
- ❌ Изтриване на елемент изисква да знаем *предишния* — иначе O(n) за намирането му;
- ❌ Изтриване „на текущата позиция" е неудобно без trick (затова обикновено правим `deleteAfter`).

**Двусвързан списък:**

- ✅ Обхождане в двете посоки;
- ✅ Изтриване на елемент при даден указател към него — O(1) (имаме `prev`);
- ✅ Удобни `insertBefore`, `deleteAt` за всеки итератор;
- ❌ Два пъти повече указатели → повече памет, по-сложна поддръжка (при всяка промяна обновяваме *две* връзки вместо една).

### 2.5 Сложност на операциите

За **едносвързан списък** (с `head` и `tail`):

| Операция | Време | Памет |
|---|---|---|
| `insertFirst` (в началото) | O(1) | O(1) |
| `insertLast` (в края, с tail) | O(1) | O(1) |
| `insertAfter(it)` | O(1) | O(1) |
| `insertBefore(it)` | O(n) | O(1) |
| `deleteFirst` | O(1) | O(1) |
| `deleteAfter(it)` | O(1) | O(1) |
| `deleteAt(it)` | O(n) | O(1) |
| `deleteLast` (с tail, но трябва нов tail) | O(n) | O(1) |
| `find(x)` | O(n) | O(1) |
| `get(i)` (i-ти по ред) | O(n) | O(1) |

За **двусвързан списък** всичко гореспоменато става O(1) с изключение на `find` и `get(i)`, които остават O(n) (защото си търсим елемент с обхождане).

**Интуиция за O(n) при едносвързан:** ако трябва да „погледна назад", единственият начин е да тръгна от `head` и да обходя до намирането на елемента — това е n стъпки.

### 2.6 Дефиниция на клас за едносвързан списък

```cpp
template <typename T>
class LinkedList {
public:
    // Възел — публичен struct, защото итераторът ще го ползва.
    // В по-„чист" вариант би бил private с friend клас за итератора.
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

private:
    Node* head;   // първия възел или nullptr ако списъкът е празен
    Node* tail;   // последния възел или nullptr; пази O(1) push_back
    size_t count; // брой елементи (улеснява empty(), size())

    // Помощни функции за управление на паметта
    void copyFrom(const LinkedList<T>& other);
    void free();

public:
    // — Голяма четворка —
    LinkedList();                                  // конструктор по подразбиране
    LinkedList(const LinkedList<T>& other);        // копиращ конструктор
    LinkedList<T>& operator=(const LinkedList<T>& other);  // оператор за присвояване
    ~LinkedList();                                 // деструктор

    // — Заявки —
    bool empty() const;
    size_t size() const;

    // — Модификации —
    void push_front(const T& x);   // O(1)
    void push_back(const T& x);    // O(1) с tail
    void pop_front();              // O(1)
    void pop_back();               // O(n) — трябва ни предишния на tail

    // Намиране на елемент. Връща указател към възела или nullptr.
    // O(n).
    Node* find(const T& x) const;

    // Изключване на елемент по стойност. Връща true ако е намерен.
    bool remove(const T& x);

    // Достъп за тест и обхождане
    const T& front() const;        // първи елемент; ако списъкът е празен — UB/изключение
    const T& back()  const;        // последен елемент
    Node* getHead() const { return head; }
};
```

#### Реализация на ключовите операции

```cpp
// Конструктор
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

// Деструктор — освобождава паметта на всички възли
template <typename T>
LinkedList<T>::~LinkedList() {
    free();
}

template <typename T>
void LinkedList<T>::free() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;  // първо запазваме следващия,
        delete current;              // защото след delete current->next е невалиден
        current = next;
    }
    head = tail = nullptr;
    count = 0;
}

// Копиращ конструктор — задължителен, иначе би имало „плитко копие"
// (две инстанции с един и същ head, освобождаване → двойно delete)
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
    : head(nullptr), tail(nullptr), count(0) {
    copyFrom(other);
}

template <typename T>
void LinkedList<T>::copyFrom(const LinkedList<T>& other) {
    Node* cur = other.head;
    while (cur != nullptr) {
        push_back(cur->data);   // ползваме готовата си операция
        cur = cur->next;
    }
}

// Оператор за присвояване — стандартния patterns с "self-assignment" защита
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {       // защита от l = l
        free();
        copyFrom(other);
    }
    return *this;
}

// push_front: O(1) — слагаме нов възел и пренасочваме head
template <typename T>
void LinkedList<T>::push_front(const T& x) {
    Node* p = new Node(x, head);   // p->next = head
    head = p;
    if (tail == nullptr) tail = p; // ако списъкът е бил празен
    ++count;
}

// push_back: O(1) благодарение на tail
template <typename T>
void LinkedList<T>::push_back(const T& x) {
    Node* p = new Node(x, nullptr);
    if (tail == nullptr) {
        // списъкът е празен
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
    ++count;
}

// pop_front: O(1)
template <typename T>
void LinkedList<T>::pop_front() {
    if (head == nullptr) return;   // или хвърляне на изключение
    Node* old = head;
    head = head->next;
    if (head == nullptr) tail = nullptr;  // последният елемент изчезна
    delete old;
    --count;
}

// pop_back: O(n) — нямаме prev указател, трябва да обходим
template <typename T>
void LinkedList<T>::pop_back() {
    if (head == nullptr) return;
    if (head == tail) {            // единствен елемент
        delete head;
        head = tail = nullptr;
        count = 0;
        return;
    }
    // Намираме предпредпоследния (този, чийто next е tail)
    Node* prev = head;
    while (prev->next != tail) prev = prev->next;
    delete tail;
    tail = prev;
    tail->next = nullptr;
    --count;
}

// find: O(n)
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::find(const T& x) const {
    Node* cur = head;
    while (cur != nullptr && !(cur->data == x)) {
        cur = cur->next;
    }
    return cur;   // или указател към намерения, или nullptr
}

// remove: O(n) — трябва да намерим *предишния* на изтривания
template <typename T>
bool LinkedList<T>::remove(const T& x) {
    if (head == nullptr) return false;
    if (head->data == x) {
        pop_front();
        return true;
    }
    Node* prev = head;
    while (prev->next != nullptr && !(prev->next->data == x)) {
        prev = prev->next;
    }
    if (prev->next == nullptr) return false;  // не е намерен
    Node* victim = prev->next;
    prev->next = victim->next;
    if (victim == tail) tail = prev;          // махнахме последния
    delete victim;
    --count;
    return true;
}
```

#### Интуиция за всяка операция

- **push_front** е тривиален: правим нов възел, чийто `next` сочи към досегашния `head`, и преместваме `head`.
- **push_back** е лесен, *защото пазим `tail`*. Ако не го пазехме, щеше да е O(n) обхождане.
- **pop_back** е O(n) дори и да имаме `tail` — `tail` дава достъп до последния елемент, но за да го изтрия, трябва да направя предпоследния новия `tail`, а до него мога да стигна само през обхождане.
- **find** е O(n), защото нямаме индекс — единственият начин да проверим всеки елемент е да го посетим.

---

## 3. Стек

### 3.1 АТД стек — логическо описание

**Стек** е *хомогенна линейна структура с организация „последен влязъл — пръв излязъл"* (Last-In-First-Out, LIFO). Аналогия: купчина чинии — слагаш и взимаш само отгоре.

Операции:

- `create()` — създаване на празен стек;
- `empty()` — проверка за празнота;
- `push(x)` — включване на елемент;
- `pop()` — изключване на последния включен елемент;
- `peek()` (или `top()`) — поглеждане на последния включен елемент *без* изключване.

Свойства (аксиоми):

- `create().empty() = true`
- `s.push(x).empty() = false`
- `create().peek()`, `create().pop()` — грешка
- `s.push(x).peek() = x`
- `s.push(x).pop() = s` (push и pop са обратни)

### 3.2 Реализации — характеристики

#### Статична реализация (масив с фиксиран капацитет)

```
[a0][a1][a2][a3][..][..][..]
                 ▲
                top
```

Държим масив с фиксиран размер `N` и индекс `top`, който сочи първото *свободно* място (или последното заето — по конвенция).

- ✅ Изключително бърз — `push`/`pop`/`peek` са O(1) (просто пишем/четем в индекс);
- ✅ Минимални допълнителни разходи;
- ❌ Фиксиран капацитет — ако `top == N`, `push` се проваля (overflow);
- ❌ Хабим памет, ако стекът обикновено е малък, а сме заделили голям масив.

#### Динамична реализация (разширяващ се масив)

Същото като статичния, но когато се напълни, заделяме нов *по-голям* масив (обикновено двойно повече), копираме старите елементи и освобождаваме стария.

- ✅ Няма ограничение в капацитета (докато има памет);
- ✅ Амортизирана сложност на `push` остава O(1) (рядкото копиране се „размива");
- ❌ Понякога едно `push` отнема O(n) (когато стане преоразмеряване);
- ❌ Прелокациите хвърлят валидни досега указатели/итератори.

#### Свързана реализация

Веригата от двойни кутии, като при списък, но винаги се работи само в *върха*.

```
NULL ◄── [a0|·] ◄── [a1|·] ◄── [a2|·]
                                  ▲
                                 top
```

(Стрелките сочат „надолу", защото върхът е най-новият елемент.)

- ✅ Винаги O(1) push и pop, без амортизация;
- ✅ Капацитетът е ограничен само от паметта;
- ❌ Един допълнителен указател на елемент → по-голям обем памет;
- ❌ Всеки `push` прави `new`, всеки `pop` прави `delete` — на практика по-бавно от масивната реализация заради cache-miss и алокации.

### 3.3 Сложност на операциите

| Реализация | `push` | `pop` | `peek` | `empty` |
|---|---|---|---|---|
| Статичен масив | O(1) | O(1) | O(1) | O(1) |
| Разширяващ се масив | O(1) амортизирано (но O(n) в най-лош случай) | O(1) | O(1) | O(1) |
| Свързано | O(1) | O(1) | O(1) | O(1) |

Виждаме: с точност до амортизация, **всички реализации дават O(1) за всички операции**. Това е голямата сила на стека.

### 3.4 Дефиниция на клас за стек (свързана реализация)

```cpp
template <typename T>
class LinkedStack {
private:
    struct StackElement {
        T data;
        StackElement* next;
        StackElement(const T& d, StackElement* n) : data(d), next(n) {}
    };

    StackElement* topPtr;   // върхът на стека или nullptr ако е празен
    size_t count;

    void copyFrom(const LinkedStack<T>& other);
    void free();

public:
    LinkedStack();
    LinkedStack(const LinkedStack<T>& other);
    LinkedStack<T>& operator=(const LinkedStack<T>& other);
    ~LinkedStack();

    bool  empty() const;
    size_t size() const;

    void push(const T& x);     // O(1)
    void pop();                // O(1)
    const T& peek() const;     // O(1)
};
```

#### Реализация

```cpp
template <typename T>
LinkedStack<T>::LinkedStack() : topPtr(nullptr), count(0) {}

template <typename T>
LinkedStack<T>::~LinkedStack() { free(); }

template <typename T>
void LinkedStack<T>::free() {
    while (topPtr != nullptr) {
        StackElement* old = topPtr;
        topPtr = topPtr->next;
        delete old;
    }
    count = 0;
}

template <typename T>
bool LinkedStack<T>::empty() const {
    return topPtr == nullptr;
}

// push: О(1) — нов елемент сочи към досегашния връх и става нов връх
template <typename T>
void LinkedStack<T>::push(const T& x) {
    topPtr = new StackElement(x, topPtr);
    ++count;
}

// pop: O(1) — премахваме върха, новият връх е next
template <typename T>
void LinkedStack<T>::pop() {
    if (topPtr == nullptr) return;  // или throw
    StackElement* old = topPtr;
    topPtr = topPtr->next;
    delete old;
    --count;
}

template <typename T>
const T& LinkedStack<T>::peek() const {
    // Ако стекът е празен — UB; в реален код throw std::logic_error.
    return topPtr->data;
}

// Копиране — внимание! Ако наивно копираме отгоре-надолу, ще обърнем стека.
// Затова или го обхождаме два пъти, или ползваме рекурсия.
template <typename T>
void LinkedStack<T>::copyFrom(const LinkedStack<T>& other) {
    if (other.topPtr == nullptr) return;

    // Първо: копираме отгоре-надолу в обратен ред (т.е. получаваме обърнат стек).
    // Второ: преобръщаме го отново чрез обхождане.
    // Алтернативно (и по-чисто): рекурсия по дълбочина.
    // Тук показваме итеративния вариант с временен помощен стек.

    // Стъпка 1: натрупваме обърнат
    LinkedStack<T> reversed;
    StackElement* cur = other.topPtr;
    while (cur != nullptr) {
        reversed.push(cur->data);
        cur = cur->next;
    }
    // Стъпка 2: pop-ваме от обърнатия и push-ваме в нашия
    while (!reversed.empty()) {
        push(reversed.peek());
        reversed.pop();
    }
}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other)
    : topPtr(nullptr), count(0) {
    copyFrom(other);
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
```

#### Интуиция

Свързаната реализация на стек е почти най-простата СД от тази програма. Запомнете:

- върхът *винаги е head на списък*;
- `push` = добавяне в началото;
- `pop` = премахване от началото;
- *никога не пипаме „опашката"* — стекът е едностранен.

---

## 4. Опашка

### 4.1 АТД опашка — логическо описание

**Опашка** е *хомогенна линейна структура с организация „пръв влязъл — пръв излязъл"* (First-In-First-Out, FIFO). Аналогия: реална опашка на гише — който е дошъл по-рано, се обслужва по-рано.

Операции:

- `create()` — създаване;
- `empty()` — проверка за празнота;
- `enqueue(x)` (или `push(x)`) — включване в задния край;
- `dequeue()` (или `pop()`) — изключване от предния край;
- `front()` — поглеждане на първия (най-стария) елемент;
- (понякога) `back()` — поглеждане на последния.

### 4.2 Реализации — характеристики

#### Статична реализация (последователно, в масив)

Държим масив с фиксиран капацитет и два индекса — `front` и `back`. `front` сочи първия (най-стария) елемент, `back` — позицията *след* последния.

```
[ ][a0][a1][a2][a3][ ][ ][ ]
    ▲              ▲
   front          back
```

**Проблем:** при последователно `dequeue` → `enqueue` опашката „пълзи" надясно в масива и в един момент стига края — въпреки че има свободно място отляво.

**Решение:** третираме масива като *цикличен буфер* — щом `back` стигне края, „завърта" се в началото (`back = (back + 1) % N`). Така мястото в началото пак става използваемо.

- ✅ O(1) за `enqueue`/`dequeue` (просто увеличаваме индекс);
- ❌ Фиксиран капацитет.

#### Динамична реализация (разширяващ се цикличен буфер)

Като статичната, но при запълване — преоразмеряваме. Тънък момент: при копиране в новия буфер елементите трябва да се „изправят" (да започват от индекс 0), за да не се изгуби логиката.

- ✅ Неограничен капацитет;
- ✅ Амортизирано O(1) `enqueue`;
- ❌ Преоразмеряването е O(n).

#### Свързана реализация

Свързан списък, в който държим *и* `front`, *и* `back` указатели. `dequeue` маха от `front`, `enqueue` добавя след `back`.

```
[a0|·]──►[a1|·]──►[a2|·]──►NULL
 ▲                  ▲
front              back
```

- ✅ Винаги O(1) и за двете операции;
- ✅ Неограничен капацитет;
- ❌ Допълнителна памет за указатели; по-бавно в практиката заради алокации.

### 4.3 Сложност на операциите

| Реализация | `enqueue` | `dequeue` | `front` |
|---|---|---|---|
| Статичен цикличен масив | O(1) | O(1) | O(1) |
| Разширяващ се цикличен масив | O(1) амортизирано | O(1) | O(1) |
| Свързано (front + back) | O(1) | O(1) | O(1) |

### 4.4 Дефиниция на клас за опашка (свързана реализация)

```cpp
template <typename T>
class LinkedQueue {
private:
    struct QueueElement {
        T data;
        QueueElement* next;
        QueueElement(const T& d, QueueElement* n = nullptr) : data(d), next(n) {}
    };

    QueueElement* frontPtr;   // първият (най-старият) елемент
    QueueElement* backPtr;    // последният (най-новият) елемент
    size_t count;

    void copyFrom(const LinkedQueue<T>& other);
    void free();

public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<T>& other);
    LinkedQueue<T>& operator=(const LinkedQueue<T>& other);
    ~LinkedQueue();

    bool  empty() const;
    size_t size() const;

    void enqueue(const T& x);     // O(1)
    void dequeue();               // O(1)
    const T& front() const;       // O(1)
};
```

#### Реализация

```cpp
template <typename T>
LinkedQueue<T>::LinkedQueue()
    : frontPtr(nullptr), backPtr(nullptr), count(0) {}

template <typename T>
LinkedQueue<T>::~LinkedQueue() { free(); }

template <typename T>
void LinkedQueue<T>::free() {
    while (frontPtr != nullptr) {
        QueueElement* old = frontPtr;
        frontPtr = frontPtr->next;
        delete old;
    }
    backPtr = nullptr;
    count = 0;
}

template <typename T>
bool LinkedQueue<T>::empty() const {
    return frontPtr == nullptr;
}

// enqueue: добавяме в края — за това имаме backPtr.
template <typename T>
void LinkedQueue<T>::enqueue(const T& x) {
    QueueElement* p = new QueueElement(x, nullptr);
    if (backPtr == nullptr) {
        // опашката е била празна
        frontPtr = backPtr = p;
    } else {
        backPtr->next = p;
        backPtr = p;
    }
    ++count;
}

// dequeue: махаме от началото
template <typename T>
void LinkedQueue<T>::dequeue() {
    if (frontPtr == nullptr) return;   // или throw
    QueueElement* old = frontPtr;
    frontPtr = frontPtr->next;
    if (frontPtr == nullptr) backPtr = nullptr;  // изпразнихме се
    delete old;
    --count;
}

template <typename T>
const T& LinkedQueue<T>::front() const {
    return frontPtr->data;
}

template <typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue<T>& other) {
    // Тук е лесно — обхождаме other отпред-назад и enqueue-ваме.
    QueueElement* cur = other.frontPtr;
    while (cur != nullptr) {
        enqueue(cur->data);
        cur = cur->next;
    }
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
    : frontPtr(nullptr), backPtr(nullptr), count(0) {
    copyFrom(other);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
```

#### Интуиция

- За опашката *задължително* държим **два** указателя — иначе или `enqueue`, или `dequeue` става O(n);
- `dequeue` е аналогично на `pop_front` от списък;
- `enqueue` е аналогично на `push_back` от списък — затова и държим `backPtr`;
- Граничният случай е единствен елемент: тогава `frontPtr == backPtr`. При неговото dequeue *и двата* трябва да станат `nullptr`. Често допускана грешка е да забравим да нулираме `backPtr`.

#### Защо не само едно `tailPtr`?

При опашка `enqueue` слага в края (нужен е `back`), а `dequeue` маха от началото (нужен е `front`). Това са *двата различни края* — затова държим два указателя, за разлика от стека, при който и двете операции са на върха.

---

## 5. Дървовидни структури

### 5.1 Кореново дърво — дефиниция

**Кореново дърво** е йерархична структура от данни, в която на всеки елемент е съпоставено множество от подчинени елементи.

Формално (рекурсивна дефиниция):

> Кореново дърво е наредена двойка (или списък) **(X, T₁, T₂, …, Tₙ)**, където:
> - **X** е данна — *корен* на дървото;
> - **T₁, T₂, …, Tₙ** са коренови дървета — *поддървета*, n ≥ 0.

Често отъждествяваме кореновите дървета с корените им — наричаме ги **възли**. Възел без подчинени се нарича **листо**.

Терминология:

- *корен* — върховният възел;
- *родител* на възел X — възелът, чийто непосредствен подчинен е X;
- *деца* на X — непосредствените подчинени;
- *братя/сестри* — възли с общ родител;
- *листо* — възел без деца;
- *дълбочина (level)* на възел — разстоянието до корена;
- *височина (height)* на дърво — максималната дълбочина на листо.

Операции:

- `create(x)` — създаване на дърво с корен `x`;
- `addSubtree(t)` — добавяне на поддърво `t`;
- `root()` — достъп до корена;
- `subtrees()` — достъп до поддърветата.

### 5.2 Двоично кореново дърво

**Двоично дърво** е специален вид дърво, в което всеки възел има **най-много две деца**, при това *подредени* — *ляво* и *дясно*. Това подреждане е важно: ляво и дясно са различни (в общия случай).

Рекурсивна дефиниция:

> Двоично дърво е:
> - празното дърво (⊥), или
> - наредена тройка **(X, L, R)**, където X е данна (корен), L и R са двоични дървета (ляво и дясно поддърво).

> ⚠️ Двоичните дървета и общите коренови дървета *не са еквивалентни*. Например за тернарно дърво:  
> *(1, (2), (3), ⊥)* ≠ *(1, (2), ⊥, (3))* — въпреки че и в двата случая 1 има две деца 2 и 3, *позицията* е различна.

### 5.3 Начини за представяне в паметта

#### А) Свързано представяне (с указатели)

Най-естественият и често използван начин. За двоично дърво:

```cpp
template <typename T>
struct BinaryTreeNode {
    T data;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;
};
```

За дърво с произволен брой деца — различни варианти:

1. *Списък от деца във всеки възел* — всеки възел има указател към връзан списък от деца:

```cpp
template <typename T>
struct TreeNode {
    T data;
    LinkedList<TreeNode<T>*> children;
};
```

2. *Най-ляво дете + десен брат* (left-child / right-sibling) — превръщаме всяко дърво в *двоично*:

```cpp
template <typename T>
struct TreeNode {
    T data;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightSibling;
};
```

Възел има указатели към *първото* си дете и към своя *следващ брат*. Това е удобно, защото позволява еднакво представяне за всички ариести.

#### Б) Последователно представяне (в масив)

За двоично дърво — последователност от тройки *(корен, ляво, дясно)*:

| индекс | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| данна | a | a₀ | a₁ | a₀₀ | a₀₁ | a₁₁ |
| ляво  | 1 | 3 | -1 | 6 | -1 | -1 |
| дясно | 2 | 4 | 5 | -1 | 7 | 8 |

Където `-1` означава „няма това дете". Тоест данните се пазят в един масив, а структурата — в два масива от индекси.

**Специален случай:** *пълно* двоично дърво може да се представи в обикновен масив без индекси: коренът е на позиция 0, а децата на възел на позиция `i` са на позиции `2i + 1` и `2i + 2`. Този трик се ползва при пирамидите (binary heap).

За общо кореново дърво — последователност от тройки *(данна, най-ляво дете, десен брат)*.

#### Сравнение

| Свойство | Свързано | Последователно |
|---|---|---|
| Лесна модификация | ✅ | ❌ |
| Малко памет (без индекси) | ❌ | ✅ |
| Бърз произволен достъп | ❌ | ✅ |
| Подходящо за фиксирано дърво | ❌ | ✅ |
| Подходящо за често променящо се дърво | ✅ | ❌ |

### 5.4 Клас за двоично дърво

```cpp
template <typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& d, Node* l = nullptr, Node* r = nullptr)
            : data(d), left(l), right(r) {}
    };

private:
    Node* rootPtr;

    // Рекурсивни помощни функции
    static Node* copyTree(const Node* src);
    static void  freeTree(Node* n);
    static size_t sizeRec(const Node* n);
    static size_t heightRec(const Node* n);
    static void printPrefix(const Node* n);    // обхождане в префиксен ред
    static void printInfix(const Node* n);     // в инфиксен (за BST дава сортиран)
    static void printPostfix(const Node* n);   // в постфиксен

public:
    BinaryTree();                                       // създава празно дърво
    BinaryTree(const T& rootData,
               BinaryTree<T> left = BinaryTree<T>(),
               BinaryTree<T> right = BinaryTree<T>());  // създава (X, L, R)
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree<T>& operator=(const BinaryTree<T>& other);
    ~BinaryTree();

    bool   empty() const;
    size_t size() const;
    size_t height() const;
    const T& root() const;

    // Достъп до Node* — полезно за наследници (напр. BST)
    Node*  getRoot() const { return rootPtr; }

    // Обхождания
    void printPrefix() const  { printPrefix(rootPtr); }
    void printInfix()  const  { printInfix(rootPtr); }
    void printPostfix() const { printPostfix(rootPtr); }
};
```

#### Реализация

```cpp
template <typename T>
BinaryTree<T>::BinaryTree() : rootPtr(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree(const T& rootData,
                          BinaryTree<T> left,
                          BinaryTree<T> right) {
    // Прехвърляме ownership на поддърветата към новия корен:
    // взимаме им root указателите, занулявайки оригиналите,
    // за да не освободят паметта в своите деструктори.
    rootPtr = new Node(rootData, left.rootPtr, right.rootPtr);
    left.rootPtr = nullptr;
    right.rootPtr = nullptr;
}

template <typename T>
BinaryTree<T>::~BinaryTree() { freeTree(rootPtr); }

template <typename T>
void BinaryTree<T>::freeTree(Node* n) {
    if (n == nullptr) return;
    freeTree(n->left);     // първо освобождаваме поддърветата
    freeTree(n->right);    // (постфиксно обхождане)
    delete n;              // и накрая самия възел
}

// Дълбоко копиране — рекурсивно
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyTree(const Node* src) {
    if (src == nullptr) return nullptr;
    return new Node(src->data, copyTree(src->left), copyTree(src->right));
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
    : rootPtr(copyTree(other.rootPtr)) {}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
    if (this != &other) {
        freeTree(rootPtr);
        rootPtr = copyTree(other.rootPtr);
    }
    return *this;
}

template <typename T>
bool BinaryTree<T>::empty() const { return rootPtr == nullptr; }

template <typename T>
size_t BinaryTree<T>::sizeRec(const Node* n) {
    if (n == nullptr) return 0;
    return 1 + sizeRec(n->left) + sizeRec(n->right);
}

template <typename T>
size_t BinaryTree<T>::size() const { return sizeRec(rootPtr); }

template <typename T>
size_t BinaryTree<T>::heightRec(const Node* n) {
    if (n == nullptr) return 0;
    size_t hl = heightRec(n->left);
    size_t hr = heightRec(n->right);
    return 1 + (hl > hr ? hl : hr);
}

template <typename T>
size_t BinaryTree<T>::height() const { return heightRec(rootPtr); }

template <typename T>
const T& BinaryTree<T>::root() const { return rootPtr->data; }

// Префиксно обхождане: KLR (корен, ляво, дясно)
template <typename T>
void BinaryTree<T>::printPrefix(const Node* n) {
    if (n == nullptr) return;
    std::cout << n->data << ' ';
    printPrefix(n->left);
    printPrefix(n->right);
}

// Инфиксно обхождане: LKR — за BST дава елементите подредени!
template <typename T>
void BinaryTree<T>::printInfix(const Node* n) {
    if (n == nullptr) return;
    printInfix(n->left);
    std::cout << n->data << ' ';
    printInfix(n->right);
}

// Постфиксно обхождане: LRK — полезно за освобождаване
template <typename T>
void BinaryTree<T>::printPostfix(const Node* n) {
    if (n == nullptr) return;
    printPostfix(n->left);
    printPostfix(n->right);
    std::cout << n->data << ' ';
}
```

### 5.5 Обхождания — три основни схеми

За двоично дърво има три класически схеми за обхождане „в дълбочина":

1. **Префиксно (preorder, KLR):** *първо корен, после ляво, после дясно*.  
   Дава „естественото" четене отгоре-надолу.
2. **Инфиксно (inorder, LKR):** *първо ляво, после корен, после дясно*.  
   За BST дава елементите в *сортиран* ред.
3. **Постфиксно (postorder, LRK):** *първо ляво, после дясно, после корен*.  
   Удобно за освобождаване (`freeTree`), защото освобождаваме децата преди родителя.

Има и обхождане „в широчина" (BFS/level-order), което се реализира с *опашка* — добавяме корена, после неговите деца, после техните деца и т.н.

### 5.6 Интуиция

- Дървото е *рекурсивна* СД — почти всеки алгоритъм върху него е рекурсивен и следва структурата на дефиницията;
- Базовият случай при рекурсията е *празно дърво* (`nullptr`);
- Когато пишете нещо за дърво, питайте се: „какво искам да правя с корена и какво да правя с поддърветата?" — тази декомпозиция почти винаги работи.

---

## 6. Двоично кореново дърво за търсене (ДДТ / BST)

### 6.1 Дефиниция и логическо описание

**Двоично дърво за търсене** (Binary Search Tree, BST) е двоично дърво, в което елементите са подредени с *линейна наредба* и за всеки възел е изпълнено инвариант на BST:

> ⊥ е ДДТ.  
> *(X, L, R)* е ДДТ, ако:
> - *X* е по-голямо от всички елементи в *L*;
> - *X* е по-малко от всички елементи в *R*;
> - *L* и *R* също са ДДТ.

Тоест: във всеки възел всички елементи в *лявото* поддърво са *по-малки* от него, а всички в *дясното* — *по-големи*.

Пример:

```
         5
        / \
       3   8
      / \ / \
     2  4 6 10
    /     \
   1       7
```

Този инвариант води до много мощно свойство: **инфиксното обхождане на BST дава елементите подредени**.

Основни операции:

- `create()` — създаване на празно дърво;
- `insert(x)` — включване на елемент;
- `remove(x)` — изключване;
- `search(x)` / `contains(x)` — търсене;
- често — `find_min()`, `find_max()`.

Често елементите са двойки *(ключ, стойност)* и наредбата е по ключа.

### 6.2 Начини за представяне в паметта

Същите като при общото двоично дърво — основно **свързано представяне с указатели** (всеки възел сочи към ляво и дясно поддърво). Алтернативи (последователно представяне в масив) се ползват рядко, защото BST е *динамична* структура — много рядко я има в готов вид и често я променяме.

```cpp
template <typename T>
struct BSTNode {
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;
};
```

### 6.3 Сложност на операциите

Всички основни операции имат сложност **O(h)**, където *h* е височината на дървото:

- ако дървото е **добре балансирано** — h ≈ log n → **O(log n)**;
- ако дървото е **изродено** в списък (вмъкване в сортиран ред: 1, 2, 3, 4, …) — h = n → **O(n)**.

| Операция | Средно | Най-лошо |
|---|---|---|
| `search` | O(log n) | O(n) |
| `insert` | O(log n) | O(n) |
| `remove` | O(log n) | O(n) |

> ⚠️ Това е защо съществуват *самобалансиращи се* дървета — AVL, червено-черни, и подобни. Те поддържат височината O(log n) и така гарантират най-лоша O(log n). B-дърветата имат същата сложност, но са оптимизирани за блокова памет (диск).

### 6.4 Алгоритми на операциите — интуиция

#### Търсене на елемент X

Започваме от корена.

1. Ако възелът е `nullptr` — X не е намерен.
2. Ако `data == X` — намерен.
3. Ако `X < data` — търсим вляво (всички възможни кандидати са вляво).
4. Ако `X > data` — търсим вдясно.

На всяка стъпка отрязваме „половината" от дървото. Това дава O(h) сложност.

#### Включване на елемент X

Аналогично на търсенето — слизаме надолу, докато стигнем празно място (`nullptr`). Там създаваме нов възел и го връзваме. Новите възли *винаги* стават листа.

#### Изключване на елемент X

Това е най-сложната операция. Три случая според бройката деца на изтривания възел Y:

**Случай 1: Y е листо (няма деца)** — просто го изтриваме и нулираме родителския указател.

```
   ...                ...
    |                  |
    Y     →         (NULL)
```

**Случай 2: Y има точно едно дете** — изтриваме Y и „пришиваме" детето му на негово място (под родителя на Y).

```
   ...                ...
    |                  |
    Y         →        C
   / 
  C
```

**Случай 3: Y има две деца** — *най-сложно*. Не можем просто да го махнем — къде да отидат двете поддървета? Решение: намираме *най-малкия в дясното поддърво* (или най-големия в лявото) — нека е M. M е „следващият по подреденост" след Y. Заменяме *данната* на Y със стойността на M (което запазва инварианта на BST), и след това *изтриваме* M от мястото му в дървото. M по конструкция има най-много едно дете (не може да има ляво — иначе нямаше да е минимум), така че неговото изтриване попада в Случай 1 или 2.

```
       Y                    M
      / \                  / \
     L   R       →        L   R'
        / \                  / \
       M  ...               ... ...
       |
      (nullptr или
       десен наследник)
```

R' е R след изтриването на M.

#### Защо това работи?

- Замяната с *минимума на дясното поддърво* запазва инварианта: новата стойност M е по-голяма от всичко в L (защото М е в R и Y < всички в R, а сега новият корен е M, който е *най-малкият* в R, тоест L < M ≤ R\\{M}).
- M не нарушава нищо отдолу — той само сменя стойността си в корена и изчезва от поддървото R.

### 6.5 Клас за BST

```cpp
template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& d, Node* l = nullptr, Node* r = nullptr)
            : data(d), left(l), right(r) {}
    };

    Node* rootPtr;

    // — Рекурсивни помощни функции —
    static Node* copyTree(const Node* src);
    static void  freeTree(Node* n);

    // Включване — връща новия корен на (под)дървото
    static Node* insertRec(Node* n, const T& x);

    // Търсене
    static const Node* findRec(const Node* n, const T& x);

    // Изключване — връща новия корен на (под)дървото
    static Node* removeRec(Node* n, const T& x);

    // Намира и откача минимума, връща новия корен; *out получава
    // указател към откачения възел.
    static Node* extractMin(Node* n, Node*& out);

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& other);
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);
    ~BinarySearchTree();

    bool empty() const { return rootPtr == nullptr; }

    bool contains(const T& x) const;
    void insert(const T& x);
    bool remove(const T& x);

    // Обхождане в инфиксен ред (за тест) — за BST извежда подредено
    void printSorted() const;
};
```

#### Реализация

```cpp
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : rootPtr(nullptr) {}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() { freeTree(rootPtr); }

template <typename T>
void BinarySearchTree<T>::freeTree(Node* n) {
    if (n == nullptr) return;
    freeTree(n->left);
    freeTree(n->right);
    delete n;
}

template <typename T>
typename BinarySearchTree<T>::Node*
BinarySearchTree<T>::copyTree(const Node* src) {
    if (src == nullptr) return nullptr;
    return new Node(src->data, copyTree(src->left), copyTree(src->right));
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other)
    : rootPtr(copyTree(other.rootPtr)) {}

template <typename T>
BinarySearchTree<T>&
BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other) {
    if (this != &other) {
        freeTree(rootPtr);
        rootPtr = copyTree(other.rootPtr);
    }
    return *this;
}

// — Търсене —
template <typename T>
const typename BinarySearchTree<T>::Node*
BinarySearchTree<T>::findRec(const Node* n, const T& x) {
    if (n == nullptr) return nullptr;          // не намерен
    if (x == n->data) return n;                // намерен
    if (x < n->data) return findRec(n->left, x);
    return findRec(n->right, x);
}

template <typename T>
bool BinarySearchTree<T>::contains(const T& x) const {
    return findRec(rootPtr, x) != nullptr;
}

// — Включване —
// Връща корена на (под)дървото след включването.
template <typename T>
typename BinarySearchTree<T>::Node*
BinarySearchTree<T>::insertRec(Node* n, const T& x) {
    if (n == nullptr) {
        // Стигнахме празно място — създаваме нов листен възел.
        return new Node(x);
    }
    if (x < n->data) {
        n->left = insertRec(n->left, x);       // включваме вляво
    } else if (n->data < x) {
        n->right = insertRec(n->right, x);     // включваме вдясно
    }
    // Ако x == n->data — не правим нищо (дубликатите се игнорират;
    // според конкретната задача може и да се позволяват).
    return n;
}

template <typename T>
void BinarySearchTree<T>::insert(const T& x) {
    rootPtr = insertRec(rootPtr, x);
}

// — Помощна функция: откачане на минимума —
// От дървото с корен n изважда най-левия възел и го връща в out.
// Връща новия корен на дървото.
template <typename T>
typename BinarySearchTree<T>::Node*
BinarySearchTree<T>::extractMin(Node* n, Node*& out) {
    if (n == nullptr) { out = nullptr; return nullptr; }
    if (n->left == nullptr) {
        // n е минимумът — откачаме го, неговото дясно поддърво
        // заема мястото му в родителя.
        out = n;
        Node* right = n->right;
        n->right = nullptr;           // откачваме връзката
        return right;
    }
    n->left = extractMin(n->left, out);
    return n;
}

// — Изключване —
template <typename T>
typename BinarySearchTree<T>::Node*
BinarySearchTree<T>::removeRec(Node* n, const T& x) {
    if (n == nullptr) return nullptr; // не е намерен — нищо не правим

    if (x < n->data) {
        n->left = removeRec(n->left, x);
        return n;
    }
    if (n->data < x) {
        n->right = removeRec(n->right, x);
        return n;
    }

    // Тук x == n->data — трябва да изтрием n
    if (n->left == nullptr && n->right == nullptr) {
        // Случай 1: листо
        delete n;
        return nullptr;
    }
    if (n->left == nullptr) {
        // Случай 2а: само дясно дете
        Node* right = n->right;
        delete n;
        return right;
    }
    if (n->right == nullptr) {
        // Случай 2б: само ляво дете
        Node* left = n->left;
        delete n;
        return left;
    }

    // Случай 3: две деца — заменяме с минимума на дясното поддърво
    Node* minNode = nullptr;
    n->right = extractMin(n->right, minNode);
    // Копираме данните, изтриваме откачения възел
    n->data = minNode->data;
    delete minNode;
    return n;
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& x) {
    // Връщаме true, ако елементът е бил наличен — за простота
    // тук пропускаме проверката и винаги връщаме true; в реален
    // код би се проверило с contains() първо или би се вмъкнал
    // out-flag в removeRec.
    if (!contains(x)) return false;
    rootPtr = removeRec(rootPtr, x);
    return true;
}

// — Обхождане —
template <typename T>
static void printInfixRec(const typename BinarySearchTree<T>::Node* n) {
    // (декларацията на Node е private, затова в реален код
    // ще оставим printSorted да е метод и да вика частна функция)
}
```

> Бележка: тъй като `Node` е `private`, помощна функция вън от класа не може да го достъпва. В реален код `printSorted` е метод на класа и вика частна рекурсивна функция вътре.

#### Пример как се ползва

```cpp
int main() {
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(8);
    bst.insert(1);
    bst.insert(4);
    bst.insert(7);

    bst.contains(4);   // true
    bst.contains(10);  // false

    bst.remove(5);     // премахва корена; реорганизира с минимума отдясно (7)

    return 0;
}
```

### 6.6 Интуиция

- BST е *бинарно търсене, кодирано в структурата на дървото*. Всеки възел е „половината" на масив, която следваме при двоично търсене.
- За да остане ефективно, дървото трябва да е *балансирано*. Сортирано вмъкване → изродено дърво → O(n). Това е голяма уловка на изпит.
- Изключването с *две* деца винаги се решава чрез **най-малкия в дясно** (или най-големия в ляво) — има буквално двойка опции, които работят, защото и двете запазват инварианта.
- Всички операции естествено се пишат *рекурсивно* — следваме структурата на дефиницията. Итеративни варианти съществуват, но рекурсивните са по-кратки и по-четивни.

---

## Обобщителна таблица

| СД | Логика | Бърза операция | Бавна операция | Типична реализация |
|---|---|---|---|---|
| **Списък** | последователен достъп | вмъкване/премахване при известна позиция (O(1) за двусвързан) | произволен достъп — O(n) | свързано |
| **Стек** | LIFO | push, pop, peek — всичко O(1) | няма произволен достъп | масив или свързано |
| **Опашка** | FIFO | enqueue, dequeue — O(1) | няма произволен достъп | свързано с front+back, или цикличен буфер |
| **Дърво** | йерархия | зависи от обхождането | произволен достъп — O(h) | свързано с указатели |
| **BST** | подредена йерархия | search/insert/remove — O(log n) средно | при изродено — O(n) | свързано; AVL/RB за гаранция |

---

## Чести грешки и съвети за изпит

1. **`delete` на NULL е безопасен** — но винаги пишете `if (p != nullptr)` за яснота при показване на код.
2. **При свързани структури — пазете показалеца преди да го изгубите.** `Node* next = cur->next; delete cur; cur = next;` — *никога* `delete cur; cur = cur->next;`.
3. **Опашка и стек нямат обща реализация** — на изпит **не** казвайте „имам клас Container и стекът и опашката го наследяват" освен ако наистина не сте го направили (като при хетерогенен списък).
4. **Голяма четворка задължително.** Деструктор, копиращ конструктор и оператор за присвояване — иначе паметта изтича или се освобождава двойно. Опционално: move-конструктор и move-оператор (C++11).
5. **BST не е магически — той е O(n) в най-лошия случай.** Споменете това.
6. **Сложността на операцията „включване в края на свързан списък" зависи от това дали имаме `tail` указател.** O(1) с tail, O(n) без.
7. **Опашка винаги има *два* указателя** (front и back), стекът — *един* (top). Това следва директно от логиката на операциите.
8. **Дървовидните алгоритми са естествено рекурсивни.** Базов случай — празно дърво. Рекурсивна стъпка — корен + поддървета.

