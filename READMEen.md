# C Programming Notes

> **Notes**
>
> **1. File naming rule**: folders are named `ch_01_Helloworld`, where the two digits after `ch` are the **learning day** — `ch_01` = studied on day 1, `ch_02` = day 2, and so on. Several programs from the same day sit side by side, with no order between them.
> **Why days**: these notes do not follow a textbook's chapter system (see point 2), so the order in which topics appear would clash with chapter numbers. Numbering by day avoids that.
>
> **2. Learning path**: these notes are ordered by **whatever came up while studying** — I learn bit by bit and write down what I meet — **not** by a textbook syllabus, so the sequence differs from a standard course (for example, `fgets` + `sscanf` show up before arrays or pointers). Only syntax that actually appears in my programs is recorded; nothing is introduced before I study it.
>
> **3. Environment**: Visual Studio, so every `.c` file starts with `#define _CRT_SECURE_NO_WARNINGS` (a VS-only switch; gcc does not need it).
>
> **4. Companion edition**: `README.md` (same knowledge, chapters aligned one-to-one).

---

## Table of Contents

- [Day 1 (4 programs)](#day-1)
  - [Chapter 1 Hello World: Anatomy of a C Program](#chapter-1-hello-world-anatomy-of-a-c-program)
  - [Chapter 2 Circle Area and Circumference: Variables and printf Placeholders](#chapter-2-circle-area-and-circumference-variables-and-printf-placeholders)
  - [Chapter 3 double and scanf: More Precision and Reading Input](#chapter-3-double-and-scanf-more-precision-and-reading-input)
  - [Chapter 4 Comparing Two Numbers: Robust Input and a Custom Function](#chapter-4-comparing-two-numbers-robust-input-and-a-custom-function)
- [Day 2 (2 programs)](#day-2)
  - [Chapter 5 Operator Precedence and Associativity](#chapter-5-operator-precedence-and-associativity)
  - [Chapter 6 Increment/Decrement and Compound Assignment](#chapter-6-incrementdecrement-and-compound-assignment)
- [Appendix: Mistake Checklist (Day 2)](#appendix-mistake-checklist-day-2)

---

## Day 1

> Folder prefix `ch_01`; 4 programs written that day, covering Chapters 1–4: program structure, variables and output, then keyboard input and custom functions.

### Chapter 1 Hello World: Anatomy of a C Program

**Source file: `Helloworld.c` (`ch_01_Helloworld`)**

```c
// Turn off Visual Studio's security warnings for scanf etc.
#define _CRT_SECURE_NO_WARNINGS
// Header file
#include <stdio.h>

// The main function. A program can have only one main function.

int main(void)   // Watch the spelling, and check whether the function exists

// int means integer type, main is the main function, void means no parameters

{

	// Print to the screen; \n means new line

	printf("Day 1 of Learning C: Starting with Hello World\n");   // Remember the semicolon

	// By convention, returning 0 means the program ended normally

	return 0;

}
```

Output:

```
Day 1 of Learning C: Starting with Hello World
```

#### 1.1 Syntax covered

| Code | Meaning |
| --- | --- |
| `#define _CRT_SECURE_NO_WARNINGS` | Silences VS's security warnings for `scanf` / `fgets`. **Must come before every `#include`** |
| `#include <stdio.h>` | Pulls in the input/output tools; `printf` needs it to work |
| `int main(void)` | The main function — **a program can have only one**, and execution starts here |
| `int` / `main` / `void` | Integer type / fixed name of the main function / no parameters |
| `printf("...");` | Print to the screen |
| `\n` | Newline |
| `return 0;` | By convention, 0 signals normal termination |
| `//` and `/* */` | Single-line comment / multi-line comment (used in Chapter 4) |

#### 1.2 Pitfalls

- Spelling `main` as `mian` or `Main` fails to compile.
- Every statement ends with `;`; the function body's `{ }` gets **no** `;`.
- Two `.c` files each defining `main` in one project → linker error "one or more multiply defined symbols found".

---

### Chapter 2 Circle Area and Circumference: Variables and printf Placeholders

**Source file: `Circle_calc.c` (`ch_01_Circle_calc`)**

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)   // int = integer, main = main function, void = no parameters
{
	int r;        // int = integer; r is the radius
	float c, s;   // float = floating-point; c is circumference, s is area

	r = 5;                      // radius is 5
	c = 2 * 3.14159 * r;        // circumference: 2πr
	s = 3.14159 * r * r;        // area: πr²

	printf("r=%d,c=%.2f,s=%.2f\n", r, c, s);
	// %d = integer placeholder, %.2f = floating-point with 2 decimals
	return 0;
}
```

Output:

```
r=5,c=31.42,s=78.54
```

#### 2.1 Declare first, use later

```c
int r;      // declare: "I want a box for an integer, named r"
r = 5;      // assign: put 5 into it

float c, s; // one statement declares several variables of the same type, comma-separated

int r = 5;  // declare + assign in one step = initialization
```

#### 2.2 Data types

| Type | Name | What it holds |
| --- | --- | --- |
| `int` | Integer | Whole numbers (5, 12, -3) |
| `float` | Single-precision floating-point | Numbers with a decimal point (~6–7 significant digits) |
| `double` | Double-precision floating-point | Numbers with a decimal point (~15–16 significant digits), see Chapter 3 |

#### 2.3 printf placeholders

```c
printf("r=%d,c=%.2f,s=%.2f\n", r, c, s);
```

**The number and order of placeholders must match the variables that follow, one by one.**

| Placeholder | Type | Meaning |
| --- | --- | --- |
| `%d` | `int` | Integer |
| `%f` | `float` / `double` | Floating-point, 6 decimals by default |
| `%.2f` | `float` / `double` | Floating-point, 2 decimal places |
| `%%` | — | A literal `%` character |
| `\n` | — | Newline |

#### 2.4 Pitfalls

- The placeholder must match the type: `int` → `%d`, `float` → `%f`. Mixing them prints garbage.
- The `.2` in `%.2f` means "2 decimal places", not "divide by 2".
- C has no exponent operator; πr² is written `3.14159 * r * r`.

---

### Chapter 3 double and scanf: More Precision and Reading Input

**Source file: `Circle_calc_double.c` (`ch_01_Circle_calc_double`)**

Same problem as Chapter 2 with three changes: `float` → `double`, hard-coded radius → read from the keyboard, `%.2f` → `%.2lf`.

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    // Change 1: float becomes double (double precision, holds more digits)
    double r;          // radius
    double c, s;       // circumference c, area s

    // Change 2: reading a double with scanf requires %lf (l is a lowercase L)
    printf("Please enter the radius: ");
    scanf("%lf", &r);  // &r takes the address, same idea as sscanf in Chapter 4

    c = 2 * 3.14159 * r;      // circumference = 2πr
    s = 3.14159 * r * r;      // area = πr²

    // Change 3: printf uses %.2lf for double (%.2f also works)
    printf("r=%.2lf, c=%.2lf, s=%.2lf\n", r, c, s);

    return 0;
}
```

Output after typing `5`:

```
Please enter the radius: r=5.00, c=31.42, s=78.54
```

#### 3.1 scanf and printf use different placeholders

| Situation | `float` | `double` |
| --- | --- | --- |
| `printf` (output) | `%f` / `%.2f` | `%f` / `%.2f` (`%lf` also fine) |
| `scanf` (input) | `%f` | **must be `%lf`** |

> Mnemonic: **on input the two types differ (`%f` vs `%lf`); on output they do not.**

```c
scanf("%lf", &r);   // "format" + "address" — both are required
```

#### 3.2 Pitfalls

- The variable after `scanf` needs `&`: `scanf("%lf", r)` is wrong.
- Do **not** put `\n` in `scanf`'s format string — the program waits for an extra Enter and looks stuck.
- This program does not validate input (letters break it). See Chapter 4 for the robust way.

---

### Chapter 4 Comparing Two Numbers: Robust Input and a Custom Function

**Source file: `compare_two_numbers.c` (`ch_01_compare_two_numbers`)**

```c
/*
 * File: compare_two_numbers.c
 * Purpose: read two integers from the keyboard (separated by an English comma);
 *          if the format is wrong or no English comma is used, prompt and re-enter;
 *          finally print the larger of the two numbers.
 */

#define _CRT_SECURE_NO_WARNINGS        // Disable Visual Studio security warnings for scanf etc.
#include <stdio.h>                    // Provides printf / fgets / sscanf
#include <string.h>                   // Provides strchr, for finding a character

 /* Custom function: returns the larger of two integers */
int Max(int a, int b)
{
    if (a > b)                        // if a is greater than b
        return a;                     // return a
    else                              // otherwise
        return b;                     // return b
}

int main()
{
    int x, y;                         // Two integers entered by the user
    char line[100];                   // Character array, holds one full line of input
    int ok = 0;                       // Flag: have two integers been read successfully? (0=no, 1=yes)

    printf("Please enter two integers separated by an English comma\n");

    /* Keep looping as long as we haven't read two numbers successfully */
    while (!ok)
    {
        printf("> ");                 // Prompt: the user enters input here

        /* fgets: read one full line from the keyboard (stdin) into line
         * sizeof(line) caps how many characters are read, preventing overflow */
        fgets(line, sizeof(line), stdin);

        /* strchr: search line for the English comma ','
         * returning NULL means the comma was not found */
        if (strchr(line, ',') == NULL)
        {
            printf("Error: no English comma ',' found. Please try again!\n");
            continue;                 // Skip the rest of this iteration, go back to the loop start
        }

        /* sscanf: parse two integers from the string line using "%d,%d"
         * the return value is the number of items successfully read; we expect 2 */
        if (sscanf(line, "%d,%d", &x, &y) == 2)
        {
            ok = 1;                   // Two items read successfully; set flag to 1 and exit the loop
        }
        else
        {
            printf("Error: invalid format. Enter two numbers separated by an English comma (e.g. 12,13)!\n");
        }
    }

    printf("The larger value is: %d\n", Max(x, y));   // Call Max and print the result
    return 0;                         // Program ends normally
}
```

#### 4.1 Structure

1. Top: `#define` and `#include` (tell the computer which tools to use)
2. `Max`: our own comparison tool, written **before** `main`
3. `main`: the program body, which calls the tool above

#### 4.2 Tools used

| Code | From | What it does |
| --- | --- | --- |
| `fgets(line, sizeof(line), stdin)` | `stdio.h` | Reads a **whole line** from the keyboard into `line`, at most `sizeof(line)` characters |
| `strchr(line, ',')` | `string.h` | Finds a character in a string; returns the position, or `NULL` if not found |
| `sscanf(line, "%d,%d", &x, &y)` | `stdio.h` | Reads data from a string by format; **returns the number of items read** |
| `&x` | — | Address-of: to put something into the box, the function needs to know where the box is |

**Include the header that corresponds to the tool you use.**

> Why read a whole line: with `scanf`, bad input can hang the program. Read first, then check.

#### 4.3 The custom function Max

```c
int Max(int a, int b)    // int = returns an integer, Max = name, (int a, int b) = two parameters
{
    if (a > b) return a;
    else       return b;
}
```

**The whole expression `Max(x, y)` evaluates to the returned value**, so it can go straight into `printf`:

```c
printf("The larger value is: %d\n", Max(x, y));
//                                     ^ this is the "larger number"
```

#### 4.4 The `ok` flag + `while (!ok)`

```c
int ok = 0;      // 0 = not successful yet
while (!ok)      // ! is logical NOT: ok is 0 (false), so !ok is 1 (true) and the loop continues
{
    ...
    if (sscanf(...) == 2) ok = 1;   // flip the flag on success so the loop ends
}
```

| Situation | `strchr` returns | Is `== NULL` true? |
| --- | --- | --- |
| Comma found | a real position | false |
| Comma not found | `NULL` ("none") | true |

#### 4.5 Pitfalls

- `Max` must be written before `main`, otherwise: "undefined identifier".
- `ok` must start at 0 and only become 1 after a good read — do not flip it.
- `strchr(...) == NULL` means "**not** found".
- `sscanf` needs `&` on the variables it writes into.
- `char line[100]` uses square brackets `[ ]`, not `char line == 100`; the size is fixed by `[100]`, while `sizeof(line)` just asks how big it is.
- `continue` skips the rest of this iteration and goes back to the loop start; `return 0` ends the whole function.

---

## Day 2

> Folder prefix `ch_02`; 2 programs written that day, covering Chapters 5–6: operator precedence, then increment/decrement and compound assignment.

### Chapter 5 Operator Precedence and Associativity

**Source file: `operator_precedence.c` (`ch_02_operator_precedence`)**

> In one sentence: **precedence decides who is evaluated first; associativity decides whether same-level operators go left-to-right or right-to-left.**

#### 5.1 Precedence table (high → low)

| Level | Operators | Associativity |
| --- | --- | --- |
| 1 (highest) | `()` | — |
| 2 | `++` `--` `!` `-` (unary minus) `sizeof` | right to left |
| 3 | `*` `/` `%` | left to right |
| 4 | `+` `-` | left to right |
| 5 | `<` `<=` `>` `>=` | left to right |
| 6 | `==` `!=` | left to right |
| 7 | `&&` | left to right |
| 8 | `\|\|` | left to right |
| 9 (lowest) | `=` `+=` `-=` `*=` `/=` `%=` | right to left |

**When in doubt, add parentheses — they always win.**

#### 5.2 Verified rule by rule

| Rule | Code | Result |
| --- | --- | --- |
| Parentheses first | `2 + 3 * 4` / `(2 + 3) * 4` | 14 / 20 |
| Unary right after | `int i = 5; i++ * 2` | 10, then `i` becomes 6 |
| `!` is NOT | `!0` / `!1` | 1 / 0 |
| `* / %` before `+ -` | `10 - 6 / 2` | 7 |
| Same level: left to right | `10 % 3 * 2` | 2 |
| Comparison before `==` | `3 + 2 == 5` | 1 (true) |
| `&&` before `\|\|` | `0 \|\| (1 && 0)` | 0 |
| Assignment last | `u = v = 5` (right to left) | `u=5, v=5` |
| Associativity left to right | `10 - 3 - 2` / `2 * 3 / 2` | 5 / 3 |

> `5 > 3 == 1` and `0 || 1 && 0` give the right answer without parentheses, but they read badly and trigger compiler warnings — **parenthesize in real code**.

#### 5.3 Actual output

```
=== 1. parentheses ===
2 + 3 * 4 = 14
(2 + 3) * 4 = 20

=== 2. unary operators ===
i++ * 2 = 10, i = 6
!0 = 1, !1 = 0

=== 3. * / % before + - ===
10 - 6 / 2 = 7
10 % 3 * 2 = 2

=== 4. comparison before == and != ===
3 + 2 == 5 -> 1
(5 > 3) == 1 -> 1

=== 5. && before || ===
0 || (1 && 0) = 0

=== 6. assignment is last ===
u = v = 5  -> u=5, v=5
w = 2 + 3  -> w=5

=== 7. associativity ===
10 - 3 - 2 = 5
2 * 3 / 2 = 3

=== traps ===
a == 5 -> 0 (0 means false)
```

#### 5.4 Three traps

```c
if (a = 5)        // wrong: = assigns 5 to a, then tests whether a is true
if (a == 5)       // right: == compares

if (a & b == 0)   // wrong: this is a & (b == 0), since == binds tighter than &
if ((a & b) == 0) // right

i++ + ++i         // wrong: using and modifying the same variable in one expression — undefined
```

> Associativity only fixes how operators group. It does **not** fix the evaluation order of operands containing function calls or increments. Never rely on the order of operations that have side effects.

---

### Chapter 6 Increment/Decrement and Compound Assignment

**Source file: `increment_and_compound.c` (`ch_02_increment_and_compound`)**

> How to study it: work out the results on paper first, then compile, run, and compare.

#### 6.1 Compound assignment: operator on the left, one `=`

| Short form | Full form |
| --- | --- |
| `sum += i;` | `sum = sum + i;` |
| `sum -= i;` | `sum = sum - i;` |
| `sum *= i;` | `sum = sum * i;` |
| `sum /= i;` | `sum = sum / i;` |
| `sum %= i;` | `sum = sum % i;` |

Trace of this program (`sum` starts at 0):

| Statement | `sum` afterwards |
| --- | --- |
| `int sum = 0;` | 0 |
| `sum += 3;` | 3 |
| `sum *= 2;` | 6 |
| `sum -= 1;` | 5 |
| `sum /= 2;` | **2** (integer division truncates — not 2.5) |
| `sum %= 2;` | 0 |

#### 6.2 `++` `--`: identical on their own line

```c
int a = 5; a++;   // a = 6
int b = 5; ++b;   // b = 6, identical to a++
int c = 5; c--;   // c = 4
```

> Prefix and postfix are identical **only** when they stand alone. Inside a larger expression they differ completely.

#### 6.3 Prefix vs postfix (the important part)

| Form | Rule | Meaning |
| --- | --- | --- |
| `i++` | **use, then add** | Use the current value, then add 1 |
| `++i` | **add, then use** | Add 1 first, then use the new value |

```c
int i = 5; int x = i++;   // x = 5, i = 6
int j = 5; int y = ++j;   // y = 6, j = 6
int m = 5; int p = m--;   // p = 5, m = 4
int n = 5; int q = --n;   // q = 4, n = 4
```

#### 6.4 Actual output

```
=== Part 1: compound assignment ===
sum = 0

=== Part 2: ++ and -- (standalone) ===
a = 6, b = 6, c = 4

=== Part 3: i++ vs ++i ===
x = 5, i = 6
y = 6, j = 6

=== Part 4: m-- vs --m ===
p = 5, m = 4
q = 4, n = 4
```

#### 6.5 Pitfalls

- Never use and modify the same variable in one expression (`i++ + ++i`): undefined.
- `++` / `--` only work on **variables**: `5++` and `(a+b)++` are errors.
- Compound assignment has one `=`: `sum += 3` is right, `sum =+ 3` is wrong (it means `sum = +3`).

---

## Appendix: Mistake Checklist (Day 2)

> Day-1 pitfalls have been folded into each chapter's "Pitfalls". This list covers only the new ones from day 2 (precedence, increment/decrement, compound assignment). Skim it before every coding session.

1. **Mixing up `i++` and `++i`**
   - `i++` is use-then-add (`int x = i++;` gives `x` the old value); `++i` is add-then-use.
   - They are identical only when written alone as `i++;`.

2. **Using and modifying the same variable in one expression**
   - `i++ + ++i`, `a = i++ + i` — undefined result. Never write these in real code.

3. **Writing compound assignment as `=+` / `=-`**
   - The correct forms are `+=`, `-=` — the operator goes **before** the `=`.
   - `sum =+ 3` is read as `sum = +3`. It compiles, changes the meaning, and is painful to debug.

4. **Integer division truncates**
   - `5 / 2` is **2**, not 2.5. To keep the fraction, write `5.0 / 2`.

5. **`%` works on integers only**
   - You cannot take the remainder of a `float` or `double`.

6. **To print a `%` with `printf`, write `%%`**
   - A lone `%` is treated as a placeholder: the compiler warns and the output is garbage.

7. **Mixing up `=` and `==`**
   - `=` assigns, `==` compares. Comparisons always need `==`.

8. **Mixing bitwise operators with comparisons without parentheses**
   - `a & b == 0` means `a & (b == 0)`. Write `((a & b) == 0)`.

9. **Skipping parentheses when precedence is unclear**
   - `5 > 3 == 1` and `0 || 1 && 0` are correct but read badly and warn. **When unsure, parenthesize.**

10. **Forgetting `%lf` when `scanf` reads a `double`**
    - `scanf("%f", &r)` with `double r` reads the wrong thing; it must be `scanf("%lf", &r)`.
    - The reverse is fine: in `printf`, a `double` accepts either `%f` or `%lf`.

11. **Putting an extra `\n` in `scanf`'s format string**
    - `scanf("%lf\n", &r)` waits for one more input and looks like the program is stuck.

12. **Forgetting `&` on the variable after `scanf`**
    - `scanf("%lf", r)` is wrong; it must be `&r` (same reason as `&x` in `sscanf`, Chapter 4).
