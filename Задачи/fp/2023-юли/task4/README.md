# Задача 4 - Избори за съвет на старейшините

Задачата да се реши на един от езиците Scheme или Haskell.

## Описание

Обществото на информатиците провежда избори за съвет на старейшините.

- **Кандидатура** е наредена двойка от низове: името на кандидата и неговата специалност
- **Кандидатската листа** е списък от кандидатури
- Може да се гласува за произволен брой кандидати
- **Бюлетини** представляват предикати, които приемат кандидатура и връщат истина или лъжа, в зависимост дали се гласува за съответната кандидатура или не

**Примерна кандидатска листа:**

```haskell
cl = [("Kernighan","C"),("Ritchie","C"),("Stroustrup","C++"),("Steele","Scheme"),
      ("Sussman","Scheme"),("Church","Lambda"),("Curry","Lambda")]
```

---

## а) Функция votes - броене на гласове

### Условие

`votes` да връща броя на гласовете от бюлетините `ballots` за кандидата с име `cand`.

### Решение

```haskell
votes cand ballots = length $ filter (\ballot -> ballot cand) ballots
```

---

## б) Функция election - резултати от избори

### Условие

`election` да връща списък от наредени двойки от името на кандидата и броя от гласовете за него от бюлетините `ballots` в реда, в който кандидатите се срещат в листата `cl`.

### Решение

```haskell
election ballots cl = map (\cand@(name, _) -> (name, votes cand ballots)) cl
```

---

## в) Функция sortResults - сортиране на резултати

### Условие

`sortResults` да сортира резултатите, върнати от функцията `election`, в низходящ ред по броя на гласовете, като кандидатите с равен брой гласове запазват реда си от листата.

### Решение

```haskell
sortResults [] = []
sortResults ((name, votes):results) = more ++ equal ++ less
                      where more = sortResults $ filter (\(_,v) -> v > votes) results
                            equal = (name, votes) : filter (\(_,v) -> v == votes) results
                            less = sortResults $ filter (\(_,v) -> v < votes) results
```

---

## г) Функция selectCouncil - избиране на съвет

### Условие

`selectCouncil` да връща списък от имена от избраните не повече от `max` кандидати, които имат повече от половината гласове, в реда, върнат от `sortResults`.

### Решение

```haskell
selectCouncil max ballots cl = take max (map (\(n,v) -> n) (filter (\(_, v) -> v > length ballots `div` 2) results))
                                where results = sortResults (election ballots cl)
```
