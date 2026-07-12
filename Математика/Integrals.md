## Таблични интеграли + свойства

### Степенни и основни
| Функция | Интеграл | Кратко описание / Условие |
| --- | --- | --- |
| $1$ | $\displaystyle\int 1\,dx = x + C$ | Интеграл на единица е самото $x$. |
| $x^n$ | $\displaystyle\int x^n\,dx = \dfrac{x^{n+1}}{n+1} + C$ | Качваш степента с 1 и делиш на новата степен. Само за $n \neq -1$. |
| $\dfrac{1}{x}$ | $\displaystyle\int \dfrac{1}{x}\,dx = \ln\lvert x\rvert + C$ | Специалният случай $n = -1$. Модул, защото $x$ може да е отрицателно. |
| $\dfrac{1}{\sqrt{x}}$ | $\displaystyle\int \dfrac{1}{\sqrt{x}}\,dx = 2\sqrt{x} + C$ | Случай на степенното правило с $n = -\tfrac{1}{2}$. За $x > 0$. |

### Показателни функции
| Функция | Интеграл | Кратко описание / Условие |
| --- | --- | --- |
| $e^x$ | $\displaystyle\int e^x\,dx = e^x + C$ | Експонентата си остава същата. |
| $a^x$ | $\displaystyle\int a^x\,dx = \dfrac{a^x}{\ln a} + C$ | За $a > 0,\ a \neq 1$. При $a = e$ дава $e^x$. |

### Тригонометрични функции
| Функция | Интеграл | Кратко описание / Условие |
| --- | --- | --- |
| $\sin x$ | $\displaystyle\int \sin x\,dx = -\cos x + C$ | Обратно на производната — тук се появява минус. |
| $\cos x$ | $\displaystyle\int \cos x\,dx = \sin x + C$ | Косинус става синус, без минус. |
| $\dfrac{1}{\cos^2 x}$ | $\displaystyle\int \dfrac{1}{\cos^2 x}\,dx = \mathrm{tg}\,x + C$ | Обратно на производната на тангенса. |
| $\dfrac{1}{\sin^2 x}$ | $\displaystyle\int \dfrac{1}{\sin^2 x}\,dx = -\mathrm{ctg}\,x + C$ | Обратно на производната на котангенса. |

### Водещи до обратни тригонометрични
| Функция | Интеграл | Кратко описание / Условие |
| --- | --- | --- |
| $\dfrac{1}{\sqrt{1-x^2}}$ | $\displaystyle\int \dfrac{1}{\sqrt{1-x^2}}\,dx = \arcsin x + C$ | За $-1 < x < 1$. Може и като $-\arccos x + C$. |
| $\dfrac{1}{1+x^2}$ | $\displaystyle\int \dfrac{1}{1+x^2}\,dx = \mathrm{arctg}\,x + C$ | Може и като $-\mathrm{arcctg}\,x + C$. |
| $\dfrac{1}{a^2+x^2}$ | $\displaystyle\int \dfrac{1}{a^2+x^2}\,dx = \dfrac{1}{a}\mathrm{arctg}\,\dfrac{x}{a} + C$ | Обобщение с параметър $a \neq 0$. |
| $\dfrac{1}{\sqrt{a^2-x^2}}$ | $\displaystyle\int \dfrac{1}{\sqrt{a^2-x^2}}\,dx = \arcsin\dfrac{x}{a} + C$ | Обобщение с параметър $a > 0$, за $\lvert x\rvert < a$. |

### Свойства на неопределен интеграл
| Свойство | Формула | Кратко описание / Условие |
| --- | --- | --- |
| **Константа** | $\displaystyle\int c\cdot f(x)\,dx = c\int f(x)\,dx$ | Числовата константа се изнася пред интеграла. |
| **Събиране** | $\displaystyle\int \big(f(x)+g(x)\big)\,dx = \int f(x)\,dx + \int g(x)\,dx$ | Интеграл на сбор = сбор от интегралите. |
| **Изваждане** | $\displaystyle\int \big(f(x)-g(x)\big)\,dx = \int f(x)\,dx - \int g(x)\,dx$ | Същото като събирането, но с минус. |
| **По части** | $\displaystyle\int u\,dv = uv - \int v\,du$ | При произведение. Избираш $u$ (лесно за диференциране) и $dv$ (лесно за интегриране). |
| **Под диференциала** | $\displaystyle\int f\big(\varphi(x)\big)\varphi'(x)\,dx = \int f(u)\,du,\quad u = \varphi(x)$ | Внасяш част от израза под знака $d(\ )$. |

### Свойства на определен интеграл
| Свойство | Формула | Кратко описание / Условие |
| --- | --- | --- |
| **Нютон–Лайбниц** | $\displaystyle\int_a^b f(x)\,dx = F(b) - F(a)$ | Основната формула. $F$ е примитивна на $f$, т.е. $F' = f$. |
| **Размяна на границите** | $\displaystyle\int_a^b f(x)\,dx = -\int_b^a f(x)\,dx$ | Смяната на местата на границите сменя знака. |
| **Съвпадащи граници** | $\displaystyle\int_a^a f(x)\,dx = 0$ | Интеграл върху нулев интервал е нула. |
| **Адитивност по интервала** | $\displaystyle\int_a^b f\,dx = \int_a^c f\,dx + \int_c^b f\,dx$ | Разбиване на интервала през междинна точка $c$. |
| **Константа** | $\displaystyle\int_a^b c\cdot f(x)\,dx = c\int_a^b f(x)\,dx$ | Константата се изнася пред интеграла. |
| **Събиране / Изваждане** | $\displaystyle\int_a^b \big(f \pm g\big)\,dx = \int_a^b f\,dx \pm \int_a^b g\,dx$ | Линейност — границите остават същите. |
| **По части** | $\displaystyle\int_a^b u\,dv = \big[uv\big]_a^b - \int_a^b v\,du$ | Като при неопределения, но с граници: $\big[uv\big]_a^b = u(b)v(b) - u(a)v(a)$. |
| **Смяна на променливата** | $\displaystyle\int_a^b f\big(\varphi(x)\big)\varphi'(x)\,dx = \int_{\varphi(a)}^{\varphi(b)} f(u)\,du$ | При субституция $u = \varphi(x)$ границите също се преобразуват. |
| **Монотонност** | Ако $f(x) \le g(x)$, то $\displaystyle\int_a^b f\,dx \le \int_a^b g\,dx$ | Валидно за $a \le b$. |
| **Оценка с модул** | $\displaystyle\left\lvert \int_a^b f\,dx \right\rvert \le \int_a^b \lvert f\rvert\,dx$ | Валидно за $a \le b$. |
