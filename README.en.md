# C Programming Notes (English Edition)

> This notebook is written strictly against the three programs I have already finished. It covers only the syntax that actually appears in those programs, and does not introduce anything I have not yet studied.
> Companion Chinese edition: `README.zh.md` (same knowledge, with chapter numbering and section headings aligned one-to-one).

---

## Table of Contents

- [Chapter 1 Hello World — Anatomy of a C Program](#chapter-1-hello-world--anatomy-of-a-c-program)
- [Chapter 2 Circle Area and Circumference — Variables and printf Specifiers](#chapter-2-circle-area-and-circumference--variables-and-printf-specifiers)
- [Chapter 3 Comparing Two Numbers — Robust Input and a Custom Function](#chapter-3-comparing-two-numbers--robust-input-and-a-custom-function)
- [Chapter 4 Line-by-Line Syntax Reference](#chapter-4-line-by-line-syntax-reference)
- [Chapter 5 My Personal Mistake Checklist](#chapter-5-my-personal-mistake-checklist)

---

## Chapter 1 Hello World — Anatomy of a C Program

**Source file: `Hello world.c`**

```c
// Header file
#include <stdio.h>

// The main function. A program can have only one main function.
int main(void)   // Watch the spelling, and check whether the function exists
               // int means integer type, main is the main function, void means no parameters
{
    // Print to the screen; \n means new line
    printf("Day 1 of Learning C: Starting with Hello World\n");  // Remember the semicolon

    // By convention, returning 0 means the program ended normally
    return 0;
}
```

### 1.1 What this chapter teaches

| Code | Meaning |
| --- | --- |
| `#include <stdio.h>` | Header file. Pulls in the input/output tools; `printf` needs it to work |
| `int main(void)` | The main function. **A program can have only one main function**; execution starts here |
| `int` | Integer type |
| `main` | The fixed name of the main function |
| `void` | Means "no parameters" — nothing is received from outside |
| `printf("...");` | Print — output content to the screen |
| `\n` | Newline character; moves to the next line after printing |
| `return 0;` | By convention, returning 0 signals normal program termination |
| `// comment` | Single-line comment; for the programmer only, ignored by the computer |
| `/* ... */` | Multi-line comment (used in Chapter 3) for explanations spanning several lines |

### 1.2 Key reminders

- **Spelling `main`**: mistyping it as `mian` or `Main` causes a compile error.
- **Semicolon**: every statement must end with `;`. This is the easiest thing to forget.
- **Only one `main` per program**: if two `.c` files in one project each define a `main`, the linker reports "one or more multiply defined symbols found".

---

## Chapter 2 Circle Area and Circumference — Variables and printf Specifiers

**Source file: `Circle_calc.c`**

```c
#include <stdio.h>

int main(void)   // int = integer, main = main function, void = no parameters
{
    int r;        // int = integer; r is the radius
    float c, s;   // float = floating-point number; c is circumference, s is area

    r = 5;                      // radius is 5
    c = 2 * 3.14159 * r;        // circumference formula: 2πr
    s = 3.14159 * r * r;        // area formula: πr²

    printf("r=%d,c=%.2f,s=%.2f\n", r, c, s);
    // Print radius, circumference, area
    // %d is the integer placeholder
    // %.2f means a floating-point number shown to 2 decimal places
    return 0;
}
```

### 2.1 "Declare first, use later"

C requires that a variable be announced to the computer before it can be used.

```c
int r;      // Step 1: declare (tell the computer "I want a box for an integer, named r")
r = 5;      // Step 2: assign (put 5 into it)

float c, s; // One statement can declare several variables of the same type, separated by commas
c = 2 * 3.14159 * r;
s = 3.14159 * r * r;
```

Declaration and assignment can also be **combined into one step**, called *initialization*:

```c
int r = 5;              // declare and assign at the same time (initialize)
float c = 2 * 3.14159 * 5;
```

### 2.2 Two data types

| Type | Name | What it holds | Used for in this program |
| --- | --- | --- | --- |
| `int` | Integer type | Whole numbers (5, 12, -3) | Radius `r` |
| `float` | Single-precision floating-point | Numbers with a decimal point (3.14159) | Circumference `c`, area `s` |

> Note: `float` is one kind of "floating-point" type. So far only `int` and `float` have been studied.

### 2.3 Placeholders in printf

`printf` uses **placeholders** to say "what kind of data goes here":

```c
printf("r=%d,c=%.2f,s=%.2f\n", r, c, s);
```

**Rule: the number and order of placeholders must match the variables that follow, one by one.**

| Placeholder | Meaning | Corresponding variable |
| --- | --- | --- |
| `%d` | Integer placeholder, for an `int` | `r` (value 5) |
| `%.2f` | Floating-point, 2 decimal places | `c` (circumference) |
| `%.2f` | Floating-point, 2 decimal places | `s` (area) |

Output:

```
r=5,c=31.42,s=78.54
```

### 2.4 Why `%d` and `%.2f` must not be mixed

| Type | Correct placeholder | What happens if you use the wrong one |
| --- | --- | --- |
| `int` | `%d` | Using `%f` prints garbage |
| `float` | `%f` / `%.2f` | Using `%d` prints garbage |

**Remember: the placeholder must match the variable's type — this is a hard rule.**

---

## Chapter 3 Comparing Two Numbers — Robust Input and a Custom Function

**Source file: `compare_two_numbers.c`**

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

### 3.1 Overall structure

The program has three parts:

1. **Top**: `#define` and `#include` (tell the computer which tools to use)
2. **`Max` function**: written by us, placed before `main`, our own comparison tool
3. **`main` function**: the body of the program, which calls the tool above

### 3.2 What `#define _CRT_SECURE_NO_WARNINGS` is

This is a **Visual Studio-only switch** that must be placed **above every `#include`**.

**Purpose**: turn off Visual Studio's security warnings for `scanf`, `fgets`, and similar functions.

**Why it is needed**: VS considers those functions "unsafe" and issues warnings or even errors. Adding this line silences VS.

> Note: this is not part of standard C — it is a Visual Studio extension. Other compilers (such as gcc) do not need it.

### 3.3 What each header file provides

| Header | Tools it provides | Used for in this program |
| --- | --- | --- |
| `#include <stdio.h>` | `printf`, `fgets`, `sscanf` | Printing, reading a full line, reading data from a string |
| `#include <string.h>` | `strchr` | Finding a character inside a string |

**Include the header that corresponds to the tool you use.**

### 3.4 The custom function `Max`

```c
int Max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
```

| Part | Meaning |
| --- | --- |
| `int` | This function **returns an integer** |
| `Max` | The function name, chosen by us |
| `(int a, int b)` | Receives two integers, named `a` and `b` (`a`, `b` are parameters) |
| `return a;` | "Carry `a` back" to the caller |
| `return b;` | "Carry `b` back" to the caller |

**How to call it:**

```c
Max(x, y)        // pass in the values of x and y; the function returns the larger one
```

**The whole expression `Max(x, y)` evaluates to the returned value.** So it can be placed directly inside `printf`:

```c
printf("The larger value is: %d\n", Max(x, y));
//                                     ^ this is the "larger number"
```

### 3.5 The `ok` flag + `while (!ok)` loop

This is the core robustness idea of the program.

```c
int ok = 0;          // At the start: not successful yet (0 means "no")

while (!ok)          // !ok reads as "not successful yet?"
{
    ...
    if (sscanf(...) == 2)
    {
        ok = 1;      // Read successfully; set to 1 so the loop exits next time
    }
}
```

**The logic chain:**

| Step | Code | Meaning |
| --- | --- | --- |
| 1 | `int ok = 0;` | Set a flag, initially "not successful" |
| 2 | `while (!ok)` | Keep looping while not successful |
| 3 | Read input, check the format | See whether the user entered it correctly |
| 4 | `ok = 1;` | If correct, flip the flag so the loop ends |
| 5 | Loop exits | Continue to the code that follows |

**`!` means "logical NOT"**: `ok` is 0 (false), so `!ok` is 1 (true) and the loop continues.

### 3.6 What `char line[100]` is

```c
char line[100];   // character array, holds one full line of user input
```

- `char`: character type
- `line[100]`: a box that holds 100 characters (an array)
- Purpose: catch the whole line first, then process it at leisure

### 3.7 `fgets`: reading a full line

```c
fgets(line, sizeof(line), stdin);
```

| Argument | Meaning |
| --- | --- |
| `line` | Where to store what was read |
| `sizeof(line)` | Maximum number of characters to read (prevents overflow) |
| `stdin` | Read from the keyboard (`stdin` = "standard input") |

**Why read a full line**: if you use `scanf`, a wrong input can hang the program. Reading the whole line first and then checking it carefully avoids that.

### 3.8 `strchr`: finding a character in a string

```c
strchr(line, ',')     // look for the English comma ',' inside line
```

**What it returns is a "position" (an address).**

| Situation | Return value | Is `== NULL` true or false |
| --- | --- | --- |
| Comma found | A real position | false |
| Comma not found | `NULL` (meaning "none") | true |

So:

```c
if (strchr(line, ',') == NULL)   // was the comma not found?
{
    printf("Error: no English comma found.\n");
    continue;                    // "not found" -> report error -> jump back and retry
}
// Reaching here means the comma was found -> continue onward
```

**`continue` means: skip the rest of this iteration and go back to the start of the loop.**

### 3.9 `sscanf`: reading data from a string by a format

```c
sscanf(line, "%d,%d", &x, &y)
```

| Part | Meaning |
| --- | --- |
| `line` | Where to read from (here, a string, not the keyboard) |
| `"%d,%d"` | Read using the format "integer,integer" |
| `&x, &y` | Where to store the results (`&` means "address of") |
| Return value | **The number of items successfully read** |

So `== 2` means: **were both integers read?**

```c
if (sscanf(line, "%d,%d", &x, &y) == 2)
{
    ok = 1;      // Read 2 items: success
}
else
{
    printf("Error: invalid format.\n");   // Fewer than 2 items: wrong format
}
```

### 3.10 What `&` is

```c
&x    // "the address of the box x"
```

`sscanf` needs to **put something into the box**, so it needs "the address of the box", not what is inside it. That is why `&x` is required.

> For now, `&` only needs to be remembered as: **when `sscanf` reads into a variable, put `&` before the variable.**

---

## Chapter 4 Line-by-Line Syntax Reference

This chapter gathers the syntax that appears across the three programs, for quick lookup.

### 4.1 Preprocessor directives

```c
#define _CRT_SECURE_NO_WARNINGS     // Macro definition; must come before any #include
#include <stdio.h>                 // Include header stdio.h
#include <string.h>                // Include header string.h
```

### 4.2 Comments

```c
// Single-line comment: everything after // on this line is a comment

/*
 * Multi-line comment:
 * all of these lines are comments
 */
```

### 4.3 Functions

```c
return_type function_name(parameter_list)    // function header
{                                           // function body begins
    ...                                     // statements
    return value;                           // return (type must match the declaration)
}                                           // function body ends
```

The two functions in this program:

| Function | Return type | Parameters | Purpose |
| --- | --- | --- | --- |
| `main` | `int` | `void` (none) | Program entry point |
| `Max` | `int` | `int a, int b` | Returns the larger value |

### 4.4 Variable declaration and assignment

```c
type name;              // declaration: tell the computer this variable will be used
type name = value;      // initialization: declare and assign at the same time

name = value;           // assignment: put the value into the variable
```

Examples:

```c
int r;          // declare
r = 5;          // assign

int r = 5;      // declare + initialize (one step)

int x, y;       // declare two variables of the same type at once
float c, s;
```

### 4.5 Data types

| Keyword | Name | What it holds | Example |
| --- | --- | --- | --- |
| `int` | Integer type | Whole numbers | `5`, `12`, `-3` |
| `float` | Single-precision floating-point | Numbers with a decimal point | `3.14159`, `31.42` |
| `char` | Character type | A single character | `'A'`, `','` (see `line[100]`) |

### 4.6 Arithmetic operators

```c
c = 2 * 3.14159 * r;     // * multiplication
s = 3.14159 * r * r;     // multiplication; r * r is r squared
```

| Operator | Meaning |
| --- | --- |
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |
| `%` | Modulo (remainder; used in a Chapter 3 exercise: `n % 2 == 0` tests for even) |

### 4.7 Comparisons and logic

```c
if (a > b)       // if a is greater than b
if (sscanf(...) == 2)   // equality
if (strchr(...) == NULL)   // equal to NULL ("none")
while (!ok)      // ! is NOT: loop while ok is false
```

| Symbol | Meaning |
| --- | --- |
| `>` | Greater than |
| `<` | Less than |
| `==` | Equal to (**compare two values for equality**) |
| `=` | Assignment (**put the right value into the left side**) |
| `!=` | Not equal |
| `!` | Logical NOT (reverses true/false) |

> **The difference between `=` and `==` is the easiest trap**: `=` means "put in", `==` means "is it equal?".

### 4.8 `if ... else`

```c
if (condition)
    statement1;      // executed when the condition is true
else
    statement2;      // executed when the condition is false
```

Example:

```c
if (a > b)
    return a;     // a is bigger, return a
else
    return b;     // otherwise return b
```

### 4.9 `while` loop

```c
while (condition)
{
    ...            // repeat while the condition is true
}
```

```c
while (!ok)       // keep looping while the condition is true
{
    ...
    if (read correctly) ok = 1;   // flip the flag so the condition becomes false and the loop ends
}
```

### 4.10 `continue`

```c
continue;         // skip the rest of this iteration and go back to the loop start
```

**Note the difference between `continue` and `return`:**

| Statement | Effect |
| --- | --- |
| `continue;` | Skip to the next iteration; the loop keeps going |
| `return 0;` | End the whole function; the program exits |

### 4.11 `printf` and placeholder quick reference

```c
printf("format string", var1, var2, ...);
```

| Placeholder | Type | Note |
| --- | --- | --- |
| `%d` | `int` | Integer |
| `%f` | `float` | Floating-point (6 decimal places by default) |
| `%.2f` | `float` | Floating-point, 2 decimal places |
| `\n` | — | Newline |

### 4.12 `fgets` / `sscanf` / `strchr` quick reference

| Function | What it does | Key arguments | Return value |
| --- | --- | --- | --- |
| `fgets(line, sizeof(line), stdin)` | Read a full line from the keyboard | where to store, max chars, source | The string that was read |
| `sscanf(line, "%d,%d", &x, &y)` | Read data from a string by a format | source, format, destination | **Number of items read** |
| `strchr(line, ',')` | Find a character in a string | where to search, what to find | Position if found; `NULL` if not found |

---

## Chapter 5 My Personal Mistake Checklist

These are mistakes I have actually made. Scan this list before writing any code.

1. **Mixing up `=` and `==`**
   - `=` is assignment (put in); `==` is comparison (is it equal?).
   - Equality checks must use `==`.

2. **Missing the semicolon `;`**
   - Every statement needs a semicolon at the end.
   - The function body `{ }` itself does **not** need a semicolon after it.

3. **The `ok` flag is backwards**
   - `int ok = 0;` means "not successful yet" — must not be written as 1.
   - When reading succeeds you must write `ok = 1;`, not `ok = 0;`.

4. **Direction of `continue`**
   - `continue` means "jump back and retry", not "go on downward".
   - In `if (not found) { ... continue; }`, it is **when not found** that we continue; when found we go on downward.

5. **What `strchr == NULL` means**
   - `== NULL` means "**not** found", not "found".

6. **`sscanf` needs `&` when reading into variables**
   - Writing `sscanf(line, "%d,%d", x, y)` is wrong; it must be `&x, &y`.

7. **Placeholder and type do not match**
   - `int` uses `%d`, `float` uses `%f`. Mixing them prints garbage.

8. **The `.2` in `%.2f`**
   - It means "show 2 decimal places", not "divide by 2".

9. **`Max` must be written before `main`**
   - Otherwise calling it inside `main` reports "unidentified identifier".

10. **`#define _CRT_SECURE_NO_WARNINGS` must be at the very top**
    - Placing it after an `#include` has no effect.

11. **`char line[100]` uses square brackets `[ ]`**
    - Not `char line == 100`. `[ ]` means "open a box"; `==` means "compare".

12. **`sizeof(line)` means "check how big it is", not "set the size"**
    - The size is set by `[100]` in `char line[100]`.

---
