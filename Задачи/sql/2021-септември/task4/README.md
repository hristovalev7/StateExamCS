# Задача 4 - SQL (Movies Database)

## Структура на базата данни

**Studio** - информация за филмови студиа:

- `name` — име (PRIMARY KEY)
- `address` — адрес

**Movie** - информация за филми:

- `title` — заглавие (PRIMARY KEY)
- `year` — година (PRIMARY KEY)
- `length` — дължина в минути
- `incolor` — 'Y' за цветен, 'N' за чернобял
- `studioname` — име на студио (FOREIGN KEY към Studio.name)

**MovieStar** - информация за филмови звезди:

- `name` — име (PRIMARY KEY)
- `address` — адрес
- `gender` — пол ('F' за жена, 'M' за мъж)
- `birthdate` — рождена дата

**StarsIn** - участие на звезди във филми:

- `movietitle` — заглавие на филм (PRIMARY KEY, FOREIGN KEY)
- `movieyear` — година (PRIMARY KEY, FOREIGN KEY)
- `starname` — име на звезда (PRIMARY KEY, FOREIGN KEY към MovieStar.name)

---

## Задача 4.1 - Студиа с цветен филм И филм с неизвестна дължина

Посочете заявката, която извежда имената на всички студиа, които имат **поне един цветен филм** И **едновременно с това поне един филм с неизвестна дължина**:

**а)**

```sql
SELECT studioName
FROM Movie
WHERE inColor != 'Y'
AND studioName = (SELECT studioName
                  FROM Movie
                  WHERE length IS NULL);
```

**б)**

```sql
SELECT studioName
FROM Movie
WHERE inColor = 'Y'
AND length = NULL;
```

**в)**

```sql
SELECT studioName
FROM Movie
WHERE inColor = 'Y'
INTERSECT
SELECT studioName
FROM Movie
WHERE length IS NULL;
```

**г)**

```sql
SELECT name
FROM Studio
LEFT JOIN Movie
ON name = studioName
WHERE inColor = 'Y'
OR length = NULL;
```

### Примерно решение:

```
Отговор: в)
```

**Обяснение:**

- **а) Грешна** - използва `inColor != 'Y'` (търси НЕ цветни филми вместо цветни). Също така подзаявката може да върне множество редове, което ще даде грешка при използване на `=`.

- **б) Грешна** - използва `length = NULL` вместо `length IS NULL` (в SQL трябва `IS NULL`). Също търси филми, които едновременно са цветни И с неизвестна дължина (един филм), а задачата иска студиа с поне един цветен И поне един с неизвестна дължина (може да са различни филми).

- **в) Правилна** - `INTERSECT` връща пресечението на двете множества:
  - Първата заявка: студиа с поне един цветен филм
  - Втората заявка: студиа с поне един филм с неизвестна дължина
  - Резултатът: студиа, които са в ДВЕТЕ множества

- **г) Грешна** - използва `OR` вместо `AND`. Ще върне студиа, които имат поне един цветен филм ИЛИ поне един с неизвестна дължина (не задължително и двете).

---

## Задача 4.2 - Брой черно-бели филми за всяка актриса

Посочете заявката, която за всяка актриса извежда името и броя на черно-белите филми, в които е участвала. Ако за дадена актриса няма информация в какви филми е участвала или е играла само в цветни филми, срещу нейното име да се изведе числото 0.

**а)**

```sql
SELECT name, COUNT(DISTINCT title)
FROM Movie
RIGHT JOIN StarsIn
ON title = movieTitle
AND year = movieYear
RIGHT JOIN MovieStar
ON starName = name
WHERE gender = 'F'
GROUP BY name
HAVING inColor = 'N';
```

**б)**

```sql
SELECT name, COUNT(title)
FROM MovieStar
LEFT JOIN StarsIn ON name = starName
LEFT JOIN Movie
ON movieTitle = title
AND movieYear = year
AND inColor = 'N'
WHERE gender = 'F'
GROUP BY name;
```

**в)**

```sql
SELECT name, COUNT(title)
FROM MovieStar
LEFT JOIN StarsIn ON name = starName
LEFT JOIN Movie
ON movieTitle = title
AND movieYear = year
HAVING inColor = 'N'
AND gender = 'F'
GROUP BY name;
```

**г)**

```sql
SELECT starName, COUNT(*)
FROM StarsIn
LEFT JOIN Movie
ON title = movieTitle
AND year = movieYear
WHERE inColor = 'N' AND gender = 'F'
GROUP BY name;
```

### Примерно решение:

```
Отговор: б)
```

**Обяснение:**

- **а) Грешна** - `HAVING inColor = 'N'` е некоректно. `HAVING` не може да филтрира по не-агрегирани колони по този начин (трябва да е в `WHERE` или в `ON` клаузата на JOIN).

- **б) Правилна** - перфектното решение:
  - Започва от `MovieStar` → включва ВСИЧКИ актриси
  - `LEFT JOIN StarsIn` → включва актриси без филми
  - `LEFT JOIN Movie ... AND inColor = 'N'` → условието `inColor = 'N'` в `ON` клаузата прави така, че да се свързват само черно-бели филми
  - `WHERE gender = 'F'` → филтрира само актрисите
  - `COUNT(title)` → брои само не-NULL стойности (т.е. само черно-белите филми, за останалите връща 0)

- **в) Грешна** - `HAVING inColor = 'N' AND gender = 'F'` е грешно. `HAVING` е след `GROUP BY`, но `inColor` и `gender` не са агрегирани. Също липсва `WHERE`, което е проблем.

- **г) Грешна** - множество проблеми:
  - Започва от `StarsIn` → няма да включи актриси без филми
  - `WHERE ... gender = 'F'` → но `gender` не е в таблиците `StarsIn` или `Movie`
  - `GROUP BY name` → използва `name` вместо `starName` (и `name` не е в SELECT)
  - `COUNT(*)` → ще брои редове вместо филми, и няма да връща 0 за актриси без черно-бели филми

**Ключова разлика:** Поставянето на `inColor = 'N'` в `ON` клаузата на `LEFT JOIN` (вариант б) вместо в `WHERE` е критично, защото:

- В `ON` клаузата: филтрира само преди свързването → актрисите без черно-бели филми се включват с NULL и COUNT връща 0
- В `WHERE` клаузата: филтрира след свързването → актрисите без черно-бели филми се изключват напълно
