# Задача 5 - База данни Movies

## Описание на базата данни

Дадена е базата от данни **Movies**, в която се съхранява информация за филми, филмови студиа, които ги произвеждат, както и актьорите, които участват в тях.

### Таблица Studio

Съдържа информация за филмови студиа:

- `name` — име, **първичен ключ**
- `address` — адрес

### Таблица Movie

Съдържа информация за филми. Атрибутите `title` и `year` заедно формират **първичния ключ**.

- `title` — заглавие
- `year` — година, в която е заснет филмът
- `length` — дължина в минути
- `incolor` — `'Y'` за цветен филм и `'N'` за черно-бял
- `studioname` — име на студио, **външен ключ към Studio.name**

### Таблица MovieStar

Съдържа информация за филмови звезди:

- `name` — име, **първичен ключ**
- `address` — адрес
- `gender` — пол, `'M'` за мъж (актьор) и `'F'` за жена (актриса)
- `birthdate` — рождена дата

### Таблица StarsIn

Съдържа информация за участието на филмовите звезди във филмите. Трите атрибута заедно формират **първичния ключ**. Атрибутите `movietitle` и `movieyear` образуват **външен ключ към Movie**.

- `movietitle` — заглавие на филма
- `movieyear` — година на заснемане на филма
- `starname` — име на филмовата звезда, **външен ключ към MovieStar.name**

---

## Задача 1

### Условие

Да се напише заявка, която извежда **без повторение** имената на всички актриси, които са играли във филми **както през 20-и век** (до 2000 г. включително), **така и през 21-и век** (от 2001 г. насам).

### Решение

```sql
SELECT STARNAME
FROM STARSIN
JOIN MOVIESTAR ON STARSIN.STARNAME = MOVIESTAR.NAME
WHERE GENDER = 'F' AND MOVIEYEAR <= 2000
INTERSECT
SELECT STARNAME
FROM STARSIN
JOIN MOVIESTAR ON STARSIN.STARNAME = MOVIESTAR.NAME
WHERE GENDER = 'F' AND MOVIEYEAR > 2000;
```

**Обяснение:**

- Използваме **INTERSECT** за да намерим сечението на два множества
- **Първата заявка** избира имената на всички актриси (`GENDER = 'F'`), които са играли във филми до 2000 г. включително
- **Втората заявка** избира имената на всички актриси, които са играли във филми след 2000 г.
- **INTERSECT** връща само онези актриси, които се появяват и в двете множества - т.е. тези, които са играли и в двата века
- JOIN с MOVIESTAR е необходим, за да филтрираме само актрисите (чрез проверка на `GENDER`)
- **INTERSECT автоматично премахва дублиращи се редове**, така че не е нужно DISTINCT

---

## Задача 2

### Условие

Да се посочи коя от следните заявки извежда **без повторение** имената на всички студиа, на които **сумарната дължина на всички техни черно-бели филми е по-голяма от дължината на най-дългия филм на това студио** (без значение дали е цветен):

**А)**

```sql
SELECT name
FROM Studio
LEFT JOIN Movie
ON name = studioname
AND incolor = 'N'
GROUP BY name
HAVING SUM(length) > MAX(length);
```

**Б)**

```sql
SELECT DISTINCT name
FROM Studio
RIGHT JOIN Movie
ON name = studioname
AND incolor = 'N'
WHERE SUM(length) > MAX(length);
```

**В)**

```sql
SELECT name
FROM Studio
WHERE (SELECT SUM(length)
       FROM Movie
       WHERE incolor = 'N'
       AND studioname = Studio.name)
      > (SELECT MAX(length)
         FROM Movie
         WHERE studioname = Studio.name);
```

**Г)**

```sql
SELECT DISTINCT studioname
FROM Movie m
WHERE (SELECT SUM(length)
       FROM Movie
       WHERE incolor = 'N'
       AND studioname = m.studioname)
      > (SELECT MAX(length)
         FROM Movie);
```

### Решение

**Правилният отговор е В).**

**Анализ на вариантите:**

**А) Грешен** ❌

```sql
SELECT name
FROM Studio
LEFT JOIN Movie ON name = studioname AND incolor = 'N'
GROUP BY name
HAVING SUM(length) > MAX(length);
```

- LEFT JOIN с условие `incolor = 'N'` означава, че само черно-белите филми ще бъдат присъединени
- MAX(length) ще взима максималната дължина **само измежду черно-белите филми** на студиото
- Но искаме MAX(length) от **всички филми** на студиото (цветни и черно-бели)
- **Грешка:** MAX(length) е от погрешно множество филми

**Б) Грешен** ❌

```sql
SELECT DISTINCT name
FROM Studio
RIGHT JOIN Movie ON name = studioname AND incolor = 'N'
WHERE SUM(length) > MAX(length);
```

- **Синтактична грешка:** SUM() и MAX() не могат да се използват директно в WHERE клаузата
- Агрегатните функции трябва да са в HAVING клаузата, не в WHERE
- WHERE се изпълнява **преди** GROUP BY, а SUM/MAX изискват групиране
- **Грешка:** Невалиден SQL синтаксис

**В) Верен** ✅

```sql
SELECT name
FROM Studio
WHERE (SELECT SUM(length)
       FROM Movie
       WHERE incolor = 'N' AND studioname = Studio.name)
      > (SELECT MAX(length)
         FROM Movie
         WHERE studioname = Studio.name);
```

- **Първата подзаявка:** Изчислява сумата от дължините на **всички черно-бели филми** на текущото студио
- **Втората подзаявка:** Намира максималната дължина измежду **всички филми** (черно-бели и цветни) на текущото студио
- Сравнява дали сумата на черно-белите филми е по-голяма от най-дългия филм
- Връща само студиата, които отговарят на условието
- **Коректен:** Правилна логика и синтаксис

**Г) Грешен** ❌

```sql
SELECT DISTINCT studioname
FROM Movie m
WHERE (SELECT SUM(length)
       FROM Movie
       WHERE incolor = 'N' AND studioname = m.studioname)
      > (SELECT MAX(length)
         FROM Movie);
```

- Първата подзаявка е правилна - сумата на черно-белите филми на студиото
- **Втората подзаявка е грешна:** `SELECT MAX(length) FROM Movie` без WHERE
- Това взима MAX(length) от **всички филми в цялата база данни**, не само за текущото студио
- Искаме да сравняваме с най-дългия филм **на конкретното студио**, не на всички студиа
- **Грешка:** Сравнява с грешна стойност (глобален максимум вместо локален)

---

## Ключови концепции

1. **INTERSECT** - връща сечението на два SELECT заявки (редове, които се появяват и в двете)
2. **LEFT JOIN** - връща всички редове от лявата таблица, дори ако няма съвпадение в дясната
3. **RIGHT JOIN** - връща всички редове от дясната таблица, дори ако няма съвпадение в лявата
4. **WHERE vs HAVING:**
   - WHERE филтрира редове **преди** групиране
   - HAVING филтрира групи **след** групиране
   - Агрегатни функции (SUM, MAX, COUNT) могат да се използват само в HAVING или подзаявки
5. **Подзаявки (Subqueries)** - заявка вътре в друга заявка, често се използва за сравнение със стойности, които изискват отделно изчисление
6. **Корелирани подзаявки** - подзаявка, която референцира колони от външната заявка (напр. `Studio.name`, `m.studioname`)
