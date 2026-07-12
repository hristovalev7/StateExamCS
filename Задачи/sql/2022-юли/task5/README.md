# Задача 5 - SQL (Movies Database)

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
- `gender` — пол ('M' или 'F')
- `birthdate` — рождена дата

**StarsIn** - участие на звезди във филми:

- `movietitle` — заглавие на филм (PRIMARY KEY, FOREIGN KEY)
- `movieyear` — година (PRIMARY KEY, FOREIGN KEY)
- `starname` — име на звезда (PRIMARY KEY, FOREIGN KEY към MovieStar.name)

---

## 1) Филми от студиото на "The Usual Suspects"

Да се попълнят празните места в следната заявка така, че тя да извежда името на студиото на филма 'The Usual Suspects' и заглавията на всички филми на същото студио:

### Примерно решение:

```sql
SELECT s.name, m.title
FROM movie m JOIN studio s ON m.studioname = s.name
WHERE s.name = (SELECT studioname
                FROM movie
                WHERE title = 'The Usual Suspects' AND year = 1995);
```

**Обяснение:**

- `m` - алиас за таблицата movie
- `= s.name` - условие за JOIN (свързваме movie.studioname със studio.name)
- `=` или `IN` - оператор за сравнение (тук използваме `=`, защото очакваме един резултат)
- `studioname` - връщаме името на студиото от подзаявката
- `movie` - таблицата, от която извличаме студиото на "The Usual Suspects"

---

## 2) Звезди без информация за филми

Да се посочи коя от следните заявки извежда имената на филмовите звезди, за които няма информация в кои филми са играли:

**А)**

```sql
SELECT DISTINCT starname
FROM starsin
GROUP BY starname
HAVING COUNT(*) = 0;
```

**Б)**

```sql
SELECT ms.name, si.movietitle
FROM moviestar ms
LEFT JOIN starsin si
ON ms.name = si.starname
WHERE si.movietitle IS NULL;
```

**В)**

```sql
SELECT name
FROM starsin
JOIN moviestar ON starname = name
GROUP BY name
HAVING COUNT(name) = 0;
```

**Г)**

```sql
SELECT name
FROM moviestar
WHERE NOT EXISTS (SELECT starname
                  FROM starsin);
```

### Примерно решение:

```
Отговор: Б
```

**Обяснение:**

- **А) Грешна** - използва `starsin` като базова таблица, което означава, че взима само звезди, които ИМАТ записи в `starsin`. `COUNT(*) = 0` никога няма да е изпълнено за групирани редове.

- **Б) Правилна** - използва `LEFT JOIN`, което включва ВСИЧКИ звезди от `moviestar`, дори тези без съответствие в `starsin`. Условието `WHERE si.movietitle IS NULL` филтрира само звездите без филми. _(Забележка: заявката връща и `si.movietitle`, но той винаги е NULL)_

- **В) Грешна** - използва `JOIN` (inner join), което изключва звездите, които нямат записи в `starsin`. `HAVING COUNT(name) = 0` никога няма да е изпълнено.

- **Г) Грешна** - `NOT EXISTS (SELECT starname FROM starsin)` проверява дали таблицата `starsin` е празна като цяло, не за конкретната звезда. Връща всички звезди само ако няма НИКАКВИ записи в `starsin`.

**Правилна алтернатива:**

```sql
SELECT name
FROM moviestar
WHERE name NOT IN (SELECT starname FROM starsin);
```

или

```sql
SELECT name
FROM moviestar ms
WHERE NOT EXISTS (SELECT 1
                  FROM starsin si
                  WHERE si.starname = ms.name);
```
