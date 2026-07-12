# Задача 4 - Функционално програмиране (Haskell)

## Условие

Група приятели отиват на екскурзия и се редуват да плащат общите сметки. Когато се прибират, установяват, че всеки дължи на някого дребна сума пари.

**Представяне:**

- Всяко задължение се представя с кортеж: `(длъжник, сума, получател)`
- **Верига** - последователност от различни хора, в която всеки дължи на предишния една и съща сума
- **Кръг** - затворена верига (първият дължи на последния същата сума)

**Цел:**

- При верига: последният може да се издължи директно на първия
- При кръг: всички задължения се погасяват

---

## Примерно решение:

```haskell
-- а) Намира най-дълъг списък в списък от списъци
maxByLength ls = foldr (\xs acc -> if length xs > length acc then xs else acc) [] ls

-- б) Намира най-дълга верига, завършваща с chain, сума amount и краен получател final
maxChain chain@(last:rest) amount final dues
        | last == final = chain
        | otherwise = maxByLength [ maxChain (receiver:chain) amount final dues |
                                    (giver, due, receiver) <- dues,
                                    amount == due,
                                    giver == last,
                                    not (receiver `elem` rest) ]

-- в) Намира най-дълъг кръг при даден списък от задължения
maxCircle dues = maxByLength [ maxChain [receiver] due giver dues |
                              (giver, due, receiver) <- dues ]
```

---

## Обосновка:

### а) `maxByLength`

```haskell
maxByLength ls = foldr (\xs acc -> if length xs > length acc then xs else acc) [] ls
```

**Обяснение:**

- Използва `foldr` за обхождане на списъка от списъци `ls`
- На всяка стъпка сравнява текущия списък `xs` с акумулатора `acc`
- Връща по-дългия от двата
- Стартова стойност е празният списък `[]`

---

### б) `maxChain`

```haskell
maxChain chain@(last:rest) amount final dues
        | last == final = chain
        | otherwise = maxByLength [ maxChain (receiver:chain) amount final dues |
                                    (giver, due, receiver) <- dues,
                                    amount == due,
                                    receiver == last,
                                    not (receiver `elem` rest) ]
```

**Обяснение:**

**Параметри:**

- `chain@(last:rest)` - текущата верига (последният елемент е `last`)
- `amount` - търсената сума
- `final` - краен получател (целта е да достигнем този човек)
- `dues` - списък от всички задължения

**Логика:**

1. **Базов случай:** `last == final` - достигнали сме крайния получател, връщаме веригата
2. **Рекурсивен случай:** търсим всички възможни продължения:
   - `(giver, due, receiver) <- dues` - разглеждаме всички задължения
   - `amount == due` - сумата трябва да съвпада
   - `giver == last` - задължението трябва да започва от последния във веригата
   - `not (receiver `elem` rest)` - получателят не трябва вече да е във веригата (избягваме цикли)
   - Добавяме `receiver` в началото на веригата и търсим рекурсивно
3. От всички намерени продължения избираме най-дългото с `maxByLength`

**Важна забележка:** В кода се използва `` `elem` `` (с обратни кавички), не `'elem'` (с апострофи).

---

### в) `maxCircle`

```haskell
maxCircle dues = maxByLength [ maxChain [receiver] due giver dues |
                              (giver, due, receiver) <- dues ]
```

**Обяснение:**

- За всяко задължение `(giver, due, receiver)` стартираме нова верига
- Започваме с `[receiver]` като начална верига
- Търсим верига със сума `due` и краен получател `giver`
- Ако намерим такава верига, това означава че `receiver -> ... -> giver` формират верига, и тъй като имаме задължение `giver -> receiver`, затваряме кръга
- От всички намерени кръгове избираме най-дългия

---

## Пример:

```haskell
dues = [("Alice", 10, "Bob"),
        ("Bob", 10, "Charlie"),
        ("Charlie", 10, "Alice"),
        ("David", 5, "Eve")]

-- maxCircle dues ще намери: ["Alice", "Charlie", "Bob"]
-- Защото: Bob->Charlie (10), Charlie->Alice (10), Alice->Bob (10) формират кръг
```
