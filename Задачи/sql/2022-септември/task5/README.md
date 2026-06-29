# Задача 4 - SQL

## 1) Цветни филми без най-дългия

Да се напише заявка, която извежда заглавията и дължините в минути на всички цветни филми без най-дългия цветен и без тези с неизвестна дължина. Ако има няколко филма с максимална дължина, нито един от тях не трябва да бъде изведен.

### Примерно решение:

```sql
USE movies;

SELECT title, length
FROM movie
WHERE incolor = 'Y'
  AND length IS NOT NULL
  AND length != (SELECT MAX(length)
                 FROM movie
                 WHERE incolor = 'Y');
```

---

## 2) Студиа без филми или с филми от една година

Да се посочи коя от следните заявки извежда имената на тези студиа, които нямат филми или са снимали филми само в една единствена година:

**А)**

```sql
SELECT name
FROM Studio
WHERE name NOT IN (SELECT studioname
                   FROM Movie)
   OR COUNT(DISTINCT year) = 1;
```

**Б)**

```sql
SELECT studioname
FROM (SELECT studioname, year
      FROM Movie
      GROUP BY studioname, year) Years
GROUP BY studioname
HAVING COUNT(*) <= 1;
```

**В)**

```sql
SELECT name
FROM Studio
LEFT JOIN Movie ON name = studioname
GROUP BY name
HAVING COUNT(DISTINCT year) <= 1;
```

**Г)**

```sql
SELECT name
FROM Studio
WHERE NOT EXISTS (SELECT * FROM Movie)
UNION
SELECT studioname
FROM Movie
GROUP BY studioname
HAVING COUNT(DISTINCT year) = 1;
```

### Примерно решение:

```
Отговор: В
```

**Обяснение:**

- **А)** Грешна - не може да се използва агрегатна функция `COUNT()` в `WHERE` без `GROUP BY`
- **Б)** Грешна - взима данни само от таблицата `Movie`, така че не може да върне студиа без филми (те не са в `Movie`)
- **В)** **Правилна** - `LEFT JOIN` включва всички студиа (дори без филми), а `HAVING COUNT(DISTINCT year) <= 1` филтрира тези с 0 или 1 различна година
- **Г)** Грешна - условието `WHERE NOT EXISTS (SELECT * FROM Movie)` връща всички студиа само ако изобщо няма филми в таблицата `Movie`, което е некоректно
