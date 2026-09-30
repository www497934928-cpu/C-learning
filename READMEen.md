# C Programming Notes

> **Notes**
>
> **1. File naming rule**: folders are named `ch_01_Helloworld`, where the two digits after `ch` are the **learning day** — `ch_01` = studied on day 1, `ch_02` = day 2, and so on. Several programs from the same day sit side by side, with no order between them.
> **Why days**: these notes do not follow a textbook's chapter system (see point 2), so the order in which topics appear would clash with chapter numbers. Numbering by day avoids that.
>
> **2. Learning path**: these notes are ordered by **whatever came up while studying** — I learn bit by bit and write down what I meet — **not** by a textbook syllabus, so the sequence differs from a standard course (for example, `fgets` + `sscanf` show up before arrays or pointers). Only syntax that actually appears in my programs is recorded; nothing is introduced before I study it.
>
> **3. Environment**: Visual Studio 2026 Community (18.10.2), so every `.c` file starts with `#define _CRT_SECURE_NO_WARNINGS` (a VS-only switch; gcc does not need it) — see [P.3](#p3-scanf-gets-blocked-by-a-warning).
>
> **4. Companion edition**: `README.md` (same knowledge, chapters aligned one-to-one).

---

## Table of Contents

- [Preface: environment stuff](#preface-environment-stuff)
  - [P.1 What to tick when installing VS](#p1-what-to-tick-when-installing-vs)
  - [P.2 A repository is not the same as a VS project](#p2-a-repository-is-not-the-same-as-a-vs-project)
  - [P.3 scanf gets blocked by a warning](#p3-scanf-gets-blocked-by-a-warning)
  - [P.4 Chinese comments break the build](#p4-chinese-comments-break-the-build)
  - [P.5 The property sheet is installed but /utf-8 is missing](#p5-the-property-sheet-is-installed-but-utf-8-is-missing)
  - [P.6 VS things that confused me at first](#p6-vs-things-that-confused-me-at-first)
- [Day 1 (4 programs)](#day-1)
  - [Chapter 1 Hello World: Anatomy of a C Program](#chapter-1-hello-world-anatomy-of-a-c-program)
  - [Chapter 2 Circle Area and Circumference: Variables and printf Placeholders](#chapter-2-circle-area-and-circumference-variables-and-printf-placeholders)
  - [Chapter 3 double and scanf: More Precision and Reading Input](#chapter-3-double-and-scanf-more-precision-and-reading-input)
  - [Chapter 4 Comparing Two Numbers: Robust Input and a Custom Function](#chapter-4-comparing-two-numbers-robust-input-and-a-custom-function)
- [Day 2 (2 programs)](#day-2)
  - [Chapter 5 Operator Precedence and Associativity](#chapter-5-operator-precedence-and-associativity)
  - [Chapter 6 Increment/Decrement and Compound Assignment](#chapter-6-incrementdecrement-and-compound-assignment)
- [Day 3 (4 programs)](#day-3)
  - [Chapter 7 The for Loop: Sums, Products, and the Loop Variable](#chapter-7-the-for-loop-sums-products-and-the-loop-variable)
  - [Chapter 8 break and continue](#chapter-8-break-and-continue)
  - [Chapter 9 The Three Shapes of if, Nested Loops, and Breaking Out](#chapter-9-the-three-shapes-of-if-nested-loops-and-breaking-out)
  - [Chapter 10 Guess the Number: Random Numbers and Robust Input](#chapter-10-guess-the-number-random-numbers-and-robust-input)

---

## Preface: environment stuff

> This part is about the things that went wrong **before** I wrote any real C. None of it is syntax, and any one item can eat a whole day.
> The order matters: install → create the repo → write code → add Chinese comments → check that it actually took effect. Skip a step and the next section's weird symptom shows up.

### P.1 What to tick when installing VS

(This machine is Visual Studio 2026 Community, version 18.10.2 — Help → About. The `v145` below is the 2026 toolset number; on VS 2022 it is `v143`. Everything else is the same.)

The downloaded `VisualStudioSetup.exe` is only a few MB. Double-clicking it opens a small window full of options, and there is no hint about what to pick or how big this is going to be. What I got stuck on was the "Installation details" pane on the right: a long list of SDKs and build tools that looked like something I had to tick one by one.

I did not.

That exe is just a bootstrapper, not Visual Studio. The real content is in the list of **Workloads** it shows after going online, and for C you need exactly one: **"Desktop development with C++"**.

It says C++ because MSVC compiles both C and C++ and Microsoft bundles them into one workload — there is no separate "C language" entry anywhere in the list.

**So what about that long list on the right?**

Once the workload is ticked, the pane **lists and pre-ticks** a batch of components by itself. It is not a to-do list; it is the set of things already chosen for you. Microsoft splits it into three tiers:

| Tier | Contains | Should you touch it? |
| --- | --- | --- |
| Required | MSBuild, C++ core features, C++ core desktop features, Windows Universal C Runtime | cannot be unticked |
| Recommended | **MSVC v145 build tools**, **Windows 11 SDK**, C++ CMake tools, AddressSanitizer, vcpkg | you can — **but do not** |
| Optional | C++ ATL / MFC, C++/CLI support, MSVC v140 / v142 legacy toolsets | not needed for learning; safe to skip |

So the precise version is: you do not have to tick them by hand, but you must not untick them.

Leave the SDK alone in particular. It supplies the Windows API headers and libraries that VS needs at the moment it creates a project; without it the build just fails.

And skip the "Individual components" tab on a first install. That tab is for adding things later — a missing SDK version, a legacy toolset. Opening it early is an easy way to mess up the defaults.

**Small things worth doing**

- **Install location** can be moved to another drive. The C: default plus the SDK runs well over 10 GB.
- **Language pack**: a Chinese pack gives a Chinese UI, but the **error messages come out in Chinese too**, which is painful to search for. English UI is easier, or at least get used to reading the error codes (`C4996`, `C4819`, …).
- **Restart once** after installing, before opening VS.

How to tell it worked: build something and read the command line in the Output window. `/Fd"...\vc145.pdb"` means the v145 toolset is being used (VS 2022 shows `vc143`).

---

### P.2 A repository is not the same as a VS project

What VS calls a "project" was not what I wanted as a "repository". A repository is a folder; a VS project is a `.vcxproj` file. I had no idea which to create first or how to make them line up.

Three separate concepts:

| Name | What it is | Who creates it |
| --- | --- | --- |
| Repository | a folder containing `.git` | `git init` |
| Solution | `.sln`, groups several projects | Visual Studio |
| Project | `.vcxproj`, sources + build settings | Visual Studio |

What my folder looks like now:

```
F:\Github_C_learning\
├─ .git\
├─ ch_01_Helloworld\
├─ ch_02_increment_and_compound\
├─ ch_03_loop_sum_for\
├─ ch_03_if_else_nested\
├─ ch_03_guess_number\
└─ Directory.Build.props
```

Create the folder and run `git init` there first, then make projects inside it.

**Three choices when creating a project**

- Template: **"Empty Project"**. The "Console App" template brings code and headers you do not need.
- **"Place solution and project in the same directory": leave it unchecked.** It adds a nesting level and makes paths messy.
- Create `.c` files by hand, **not `.cpp`**. VS picks the compiler from the extension: `.c` compiles as C, `.cpp` as C++, and the two languages differ — the "universal header" business later on is entirely a C++ thing.

**One `main` per project**

Two `.c` files each defining `main` in one project give the linker error "one or more multiply defined symbols found". To keep many small programs in one repository, give each program its own subfolder and its own project.

**The most misleading part**

What "Solution Explorer" shows is VS's **virtual** tree, not the real disk layout. To see the actual files, click **"Show All Files"** in the toolbar.

---

### P.3 scanf gets blocked by a warning

The first time I used `scanf`, this came straight back:

```
error C4996: 'scanf': This function or variable may be unsafe.
             Consider using scanf_s instead.
```

Microsoft decided `scanf` is unsafe because it does not check the buffer length, and suggests its own `scanf_s`. But `scanf_s` is not standard C — it does not compile with gcc or Clang, so it is not an option when learning standard C.

The fix is one line at the **top** of the `.c` file:

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
```

It has to go **before** the `#include`. `#define` is a preprocessor directive applied top to bottom; written after `#include`, the header has already been processed and the switch misses its chance entirely.

If you would rather not repeat it in every file, add `_CRT_SECURE_NO_WARNINGS` under Project Properties → **C/C++ → Preprocessor → Preprocessor Definitions**, once per project. I keep both: the project setting and the line in each file, so things still work after moving to another machine.

That is where "every `.c` file starts with `#define _CRT_SECURE_NO_WARNINGS`" comes from.

---

### P.4 Chinese comments break the build

No code changed — I only added Chinese comments — and these two appeared:

```
warning C4819: The file contains a character that cannot be represented in the current code page (950).
error   C1075: end of file found before the balancing '{'
```

(Sometimes it is C2143 or C2059 instead, which looks even more random.)

The cause: the file is saved as **UTF-8 without BOM**, while VS decodes it with the system ANSI code page. On Chinese Windows that is **950 (Big5, Traditional)** or 936 (GBK, Simplified). Read UTF-8 bytes with Big5 rules and the byte pairing goes wrong.

Traditional Chinese setups are especially exposed. Big5 is a double-byte encoding whose **trail byte range is `0x40–0x7E`**, and that range covers almost every printable ASCII character — letters, `{`, `}`, `[`, `]`, `|`, `~`, `@`, `#`, `$`.

So this can happen:

```c
printf("結果");    // 漢字註釋
{
```

If the second byte of one of those characters lands on `0x7B` (the ASCII code of `{`), VS reads it as **an opening brace**; conversely the real `{` after the comment can be **swallowed** as the trail byte of some character. Braces stop balancing, hence `C1075` — it reads like a missing brace, but not one brace is actually wrong.

**Fix: add `/utf-8` to the compiler**

That tells it to treat both the source and execution character sets as UTF-8. Three places to put it, each sturdier than the one above:

| Where | How | Scope |
| --- | --- | --- |
| single project | Project Properties → **C/C++ → Command Line → Additional Options**, add `/utf-8` | that project |
| user level | write it into `%LOCALAPPDATA%\Microsoft\MSBuild\v4.0\Microsoft.Cpp.x64.user.props` (and the Win32 one) | **all** VS projects on this machine |
| repository level (recommended) | drop a `Directory.Build.props` at the repository root | **every** project under this repository |

Contents of `Directory.Build.props`:

```xml
<?xml version="1.0" encoding="utf-8"?>
<Project>
  <ItemDefinitionGroup>
    <ClCompile>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
    </ClCompile>
  </ItemDefinitionGroup>
</Project>
```

How to check: Project Properties → **C/C++ → Command Line → Additional Options**. Seeing `/utf-8` means it worked — in *italics*, which means it is inherited from a property sheet above rather than set in this project.

---

### P.5 The property sheet is installed but /utf-8 is missing

The one-click installer printed `DONE!`, and the diagnostic script confirmed the props file was there and really contained `utf-8`. Still, "Additional Options" in the project was empty and Chinese comments kept breaking the build.

The reason: **the project was created before the property sheet was installed**, and VS had already cached its settings at startup. Property sheets only apply to projects **reloaded after a restart**; clicking "Rebuild" by itself does nothing.

The order that works:

```
install property sheet -> close VS completely -> reopen VS -> open the project -> rebuild
```

**Why I ended up preferring `Directory.Build.props`**

| | User property sheet | `Directory.Build.props` |
| --- | --- | --- |
| Depends on the `%LOCALAPPDATA%` path | yes | no |
| Depends on the VS version (v4.0 / v17 …) | yes | no |
| Caching problems | **yes** | none — read on every build |
| Still works after cloning on another machine | no | **yes**, the file lives in the repo |

In the end I kept both layers: the user property sheet covers the machine, `Directory.Build.props` covers this learning repository. Either one alone is enough.

---

### P.6 VS things that confused me at first

- **Build / Rebuild / Clean**: Build compiles only what changed; Rebuild does everything. After changing compiler options, use **Rebuild**.
- **Debug / Release**: use Debug while learning — debug info, no optimization, and uninitialized variables get filled with `0xCCCCCCCC`. Release optimizes, and some bugs only appear there.
- **x64 / x86**: the target platform; it has to match the installed Windows SDK. x64 is fine for a beginner.
- **F5 flashes the window away**: F5 is "Start Debugging", and the console closes when the program ends. Use **Ctrl+F5** ("Start Without Debugging"), or put `getchar();` before `return 0;`.
- **Error List shows one line**: the full error text is in the **Output** window below; Error List is only a summary.
- **Line numbers lie**: for a missing brace or an encoding problem the compiler often notices only at **end of file**, so the reported line is the last one — search backwards.
- **Exclude From Project vs Delete**: exclude only removes it from the build, the file stays on disk; delete really deletes.
- **Only one `main` per project**: see [P.2](#p2-a-repository-is-not-the-same-as-a-vs-project).

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

if (a & b == 0)   // wrong: it means a & (b == 0), because == binds tighter than &
if ((a & b) == 0) // right

i++ + ++i         // wrong: using and modifying the same variable in one expression; result undefined
```

> Associativity only fixes the grouping direction; it does **not** guarantee the evaluation order of function calls or increments inside the operands. Never rely on the order of side effects.

---

### Chapter 6 Increment/Decrement and Compound Assignment

**Source file: `increment_and_compound.c` (`ch_02_increment_and_compound`)**

> How to study: work it out on paper first, then compile and run to check.

#### 6.1 Compound assignment: operator on the left, a single `=`

| Short form | Equivalent |
| --- | --- |
| `sum += i;` | `sum = sum + i;` |
| `sum -= i;` | `sum = sum - i;` |
| `sum *= i;` | `sum = sum * i;` |
| `sum /= i;` | `sum = sum / i;` |
| `sum %= i;` | `sum = sum % i;` |

The trace used in this program (`sum` starts at 0):

| Statement | `sum` afterwards |
| --- | --- |
| `int sum = 0;` | 0 |
| `sum += 3;` | 3 |
| `sum *= 2;` | 6 |
| `sum -= 1;` | 5 |
| `sum /= 2;` | **2** (integer division truncates; not 2.5) |
| `sum %= 2;` | 0 |

#### 6.2 `++` `--`: prefix vs postfix is irrelevant when standalone

```c
int a = 5; a++;   // a = 6
int b = 5; ++b;   // b = 6, exactly the same effect as a++
int c = 5; c--;   // c = 4
```

> The two forms only match when the operator stands alone on its line. Inside a larger expression they differ completely.

#### 6.3 Postfix `++` vs prefix `++` (key point)

| Form | Rule | Meaning |
| --- | --- | --- |
| `i++` | **use, then add** | take `i`'s current value first, add 1 afterwards |
| `++i` | **add, then use** | add 1 first, then use the new value |

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

- Never use and modify the same variable in one expression (`i++ + ++i`); the result is undefined.
- `++` / `--` work only on **variables**: `5++` and `(a+b)++` are both invalid.
- Compound assignment uses a single equals sign: `sum += 3` is right, `sum =+ 3` is wrong (it means `sum = +3`).

---

## Day 3

> Folder prefix `ch_03`; 4 programs written that day, covering Chapters 7–10: the `for` loop, `break` / `continue`, `if` and nested loops, then the first "complete little game". The syntax itself is small, but the exercises that went with it managed to hit nearly every mistake a beginner can make, so these four chapters run longer than the first two days combined.

### Chapter 7 The for Loop: Sums, Products, and the Loop Variable

**Source file: `loop_sum_for.c` (`ch_03_loop_sum_for`)**

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int i, sum = 0;

    /* 1 + 2 + ... + 100 */
    for (i = 1; i <= 100; i++)
    {
        sum += i;          // same as sum = sum + i
    }

    printf("sum = %d\n", sum);

    return 0;
}
```

Output:

```
sum = 5050
```

#### 7.1 The three clauses of `for`

```c
for (init; condition; step)
    body;
```

| Clause | Example | When it runs | How many times |
| --- | --- | --- | --- |
| init | `i = 1` | **before** the loop | **once** |
| condition | `i <= 100` | at the **start** of every round | n + 1 (the last check fails and exits) |
| step | `i++` | at the **end** of every round | n |
| body | `sum += i;` | when the condition holds | n |

"Init runs once" is the part that matters. Putting the accumulator reset there (`for (i = 1, sum = 0; ...)`) is **legal and worth doing** — it is exactly equivalent to a separate `sum = 0;` line, except the reset travels with the loop, so you cannot forget it when copying or reordering.

| Form | Result | Why |
| --- | --- | --- |
| `for (i = 1, sum = 0; i <= 50; i += 2)` | 625 | init clause, runs once |
| `for (i = 1; sum = 0, i <= 50; i += 2)` | 0 | landed in the condition; resets every round |
| `for (i = 1; i <= 50; i += 2, sum = 0)` | 0 | landed in the step; resets every round |

A comma is **not** a clause separator. `for (A; B; C)` has exactly **two semicolons**; commas only join several assignments *inside* one clause.

#### 7.2 Sums and products start from different values

| | Sum | Product |
| --- | --- | --- |
| Initial value | `sum = 0` | **`acc = 1`** |
| Operation | `sum += i` | `acc *= i` |
| Start index | anything | **must be ≥ 1** |
| Example | 1+2+…+20 = **210** | 5! = **120** |

Why products start at 1 rather than 0: 0 is the **absorbing element** of multiplication — `0 × anything = 0`, so the result would always be 0. In addition 0 is the safe choice (`0 + anything = that thing`).

The start index has to be ≥ 1 for the same reason: starting at 0 gives `acc = 1 × 0 = 0`, and every later multiplication stays 0.

```c
/* 5! = 1×2×3×4×5 */
int i, acc;
for (i = 1, acc = 1; i <= 5; i++)
    acc *= i;
printf("5! = %d\n", acc);      // 120
```

#### 7.3 What a `while` version has to add back

Everything `for` does for you, a `while` loop **must do by hand**:

| In `for` | Where it goes in `while` |
| --- | --- |
| clause 1, init `i = 1` | **before** the `while` |
| clause 2, condition `i <= 20` | **inside** the `while (...)` parentheses |
| clause 3, step `i++` | **last statement** of the body |

```c
/* for version */
for (i = 1; i <= 20; i++)
    sum += i;

/* while version: identical output, 210 */
i = 1;                  // clause 1 moved above the while
while (i <= 20)         // clause 2 stays in the parentheses
{
    sum += i;
    i++;                // clause 3 moved to the end of the body
}
```

Miss any one of the three and the loop is broken: no init → `i` holds garbage and the number of rounds is unknown; no step → an infinite loop (press **Ctrl + C**).

#### 7.4 What is `i` after the loop?

**When the loop ends, `i` = the first value that makes the condition false.**

Not "the last value that entered the loop" — **those two always differ by one step**, because the step runs before the next condition check.

| Loop | Full sequence of `i` | Last one in | `i` after the loop |
| --- | --- | --- | --- |
| `i = 0; i < 3; i++` | 0 1 2 \| 3 | 2 | **3** |
| `i = 1; i <= 5; i++` | 1…5 \| 6 | 5 | **6** |
| `i = 10; i >= 1; i -= 2` | 10 8 6 4 2 \| 0 | 2 | **0** |
| `i = 2; i <= 10; i += 3` | 2 5 8 \| 11 | 8 | **11** |

There is a shortcut when the step is 1:

- no equals sign (`<` `>`) → afterwards `i` is the number used in the condition
- with an equals sign (`<=` `>=`) → afterwards `i` is that number ± 1 (+1 going up, −1 going down)

**The shortcut breaks when the step is larger than 1.** In `for (i = 1; i <= 10; i += 4)` the values are `1 5 9 | 13`; the bound is 10, but `i` jumps from 9 straight to **13** — neither 10 nor 11. For those, **write the sequence out**.

The method that always works: **write out the full sequence of `i` → drop the values that fail the condition → compute with what is left.** If the sequence is wrong, no amount of arithmetic saves you.

The nasty part is that this mistake **does not crash or warn** — the value is just off by one. Once arrays arrive:

```c
int a[5] = {1,2,3,4,5};
for (i = 0; i < 5; i++)
    ...;
printf("%d", a[i]);    // you think a[4]=5, but this is a[5] — out of bounds!
```

#### 7.5 The step does not have to be 1

```c
for (i = 2; i <= 50; i += 2)   // sum of evens = 650
for (i = 1; i <= 50; i += 2)   // sum of odds  = 625
for (i = 10; i >= 1; i -= 2)   // backwards: 10+8+6+4+2 = 30
```

Thanks to the compound assignment from Chapter 6, `i += 2` is `i = i + 2`, and `i -= 3` is `i = i - 3`.

#### 7.6 Several variables in one `for`: use commas

Let `i` climb while `j` falls, meeting in the middle:

```c
int i, j;

for (i = 0, j = 9; i < j; i++, j--)    // two inits, two steps, both comma-separated
    printf("i=%d j=%d\n", i, j);
```

Output:

```
i=0 j=9
i=1 j=8
i=2 j=7
i=3 j=6
i=4 j=5
```

Still exactly **two semicolons**. A third one (`for (...; ...; ...;)`) fails to compile — the compiler goes looking for a fourth clause.

#### 7.7 The trap of omitting braces

**Indentation is formatting for *humans*; the compiler ignores it entirely. Only `{ }` decides what is inside the loop.**

```c
sum = 0;
for (i = 1; i <= 3; i++)
    sum += i;
    printf("%d ", sum);      // misleading indent: this line is OUTSIDE the loop
printf("\n");
```

With no braces after `for`, the body is **only the single statement that follows**. What really happens above:

- `sum += i;` runs 3 times → `sum = 1+2+3 = 6`
- `printf` runs once → prints `6`

**The output is `6`, not `1 3 6`.**

Four variants, measured (gcc emits `-Wmisleading-indentation`):

| Variant | Result |
| --- | --- |
| `sum += 10;` indented, looks like it is inside | `sum = 16` |
| `sum += 10;` not indented, obviously outside | `sum = 16` |
| everything on one line | `sum = 16` |
| **braces added**, both statements really inside | `sum = 36` |

The first three give identical results — indentation changes nothing, braces are the only thing that does.

**Always add braces, even for a single statement.** Then indentation and the real structure can never disagree, and a statement added later cannot silently fall outside the loop. Commercial style guides (Google, the Linux kernel) require it.

#### 7.8 Integer division and averages

```c
int sum = 385, n = 10;

printf("%d\n", sum / 10);            // 38    two ints, the fraction is dropped
printf("%.2f\n", (double)sum / 10);  // 38.50 convert before dividing
```

**Convert before the division**: integer division happens **at the moment of the `/`**, independently of the `printf` placeholder. Even `printf("%f", sum / 10)` prints 38 — switching to `%f` afterwards does not rescue it.

#### 7.9 Reference values from that day's exercises

```
sum = 5050                  // 1+2+...+100
sum (1..20)  = 210          // for version
while version = 210         // rewritten as while, output must match
i after loop = 5            // after for (i=0; i<5; i++)
sum of even  = 650          // 2+4+...+50
sum of odd   = 625          // 1+3+...+49
5! = 120                    // 1×2×3×4×5
sum of squares = 2870       // 1²+2²+...+20², written i * i
AVG1 = 38                   // 385/10, integer division (the wrong way)
AVG2 = 38.50                // (double)385/10
```

#### 7.10 Pitfalls

- An extra semicolon **after** the `for` / `if` / `while` parentheses → the body becomes an empty statement and the loop runs for nothing.
- An extra semicolon **inside** `while (i <= 20;)` → compile error; `while` takes a single condition.
- Forgetting the step in the body → infinite loop; press **Ctrl + C**.
- Putting `printf` inside the body → it prints once per round; for a final result put it **after** the closing brace.
- Starting a product at 0, or multiplying from 0 → the result is always 0.
- Reusing an accumulator without resetting → you get the sum of both results (650+625=1275): **no error, just wrong**.
- Copying the previous program's range (writing 100 when the exercise asks for 20).

---

### Chapter 8 break and continue

**Source file: `ch_03_break_continue.c` (`ch_03_break_continue`)**

Both say "if this condition holds, do not follow the normal plan", but they differ sharply in how far they go. I gave each one a comparison, which sticks better than the definitions:

| | Comparison | Rest of this round? | `i++`? | Later rounds? |
| --- | --- | --- | --- | --- |
| **`break`** | **walking out the door** | no | **no** | none at all |
| **`continue`** | **failing the security check** | no | **yes, as usual** | they run |

I had already met `continue` — it is the "no comma found, ask again" line in `compare_two_numbers.c` from Chapter 4. I just did not know its name then; this is where it gets claimed properly.

**Both almost always pair with an `if`**, because they need a reason for "when to jump".

#### 8.1 break: run as soon as the condition holds

```c
sum = 0;
for (i = 1; i <= 10; i++) {
    sum += i;
    if (sum > 15)       // > 15, not >= 15: sum == 15 does not trigger it
        break;
}
printf("sum = %d, i = %d\n", sum, i);        // 21 6
```

Round by round:

| Round | i | after `sum += i` | `sum > 15`? | did `i++` run? |
| --- | --- | --- | --- | --- |
| 1 | 1 | 1 | no | yes |
| 2 | 2 | 3 | no | yes |
| 3 | 3 | 6 | no | yes |
| 4 | 4 | 10 | no | yes |
| 5 | 5 | 15 | **no** (15 is not greater than 15) | yes |
| 6 | 6 | **21** | yes → break | **no** |

#### 8.2 Where does `i` end up after a break?

**`i` stops at the value of the round it jumps out of, because `i++` never gets the chance to run.**

That is a completely different route from the "normal ending" of yesterday:

| | How it ended | What `i` is |
| --- | --- | --- |
| normal ending | the condition turns false on its own | the first value that fails (one step past the bound) |
| **`break`** | forced exit while the condition still **holds** | **that round's value**; `i++` never ran |

```c
sum = 0;
for (i = 1; i <= 10; i++) {
    if (i == 4)
        break;
    sum += i;
}
printf("sum = %d, i = %d\n", sum, i);        // 6 4
```

`i` is **4**, not 5. Reaching for yesterday's "bound + 1" rule, the condition here is `i <= 10`, so it is easy to write 11 out of habit — and that is wildly wrong.

**`i++` lives in clause 3 of the `for`, and only runs when a round completes normally. `break` skips that clause entirely.**

#### 8.3 break before or after: different results

The most practical point of this chapter. Two snippets differing in position alone:

```c
/* A: break first */
for (i = 1; i <= 8; i++) {
    if (i == 5) break;      // leaves during the i==5 round
    sum += i * 2;
}
// sum = 20, i = 5

/* B: break last */
for (i = 1; i <= 8; i++) {
    sum += i * 2;           // adds first, then decides whether to leave
    if (i == 5) break;
}
// sum = 30, i = 5
```

**`sum` differs by 10 (that is `5 * 2`), while `i` is identical.**

> **Takeaway: where `break` sits does not change `i`; it only changes whether the statements of that round finished.**
> Before → that round's `i` never gets added. After → that round's `i` was already added.

#### 8.4 When break never fires, it is just an ordinary for

```c
sum = 0;
for (i = 1; i <= 5; i++) {
    sum += i;
    if (sum > 1000)     // never true; break never executes
        break;
}
printf("sum = %d, i = %d\n", sum, i);        // 15 6
```

With a condition that can never hold, `break` is dead weight, and **yesterday's rule applies straight**: `i = 5 + 1 = 6`.

#### 8.5 What break is actually for

The sections above all stop "once some value is reached", which looks like making trouble for yourself. The real use is **stop once found, instead of grinding to the end**:

```c
int target = 0;
for (i = 1; i <= 100; i++) {
    if (i % 7 == 0) {
        target = i;
        break;          // found it, leave; no need to test the rest
    }
}
printf("first number divisible by 7: %d, i = %d\n", target, i);   // 7 7
```

**Without `break`**: the loop runs on to `i = 101`, and `target` ends up holding the **last** match (98) — searching for "the first" silently becomes "the last". No error, just the wrong answer.

#### 8.6 continue: skip this round, carry on with the next

```c
sum = 0;
for (i = 1; i <= 6; i++) {
    if (i == 3)
        continue;       // during the i==3 round, sum += i does not run
    sum += i;
}
printf("sum = %d, i = %d\n", sum, i);        // 18 7
```

`1+2+4+5+6 = 18` (3 was skipped), and **`i` is 7, not 3** — with `continue`, `i++` runs as usual and the loop finishes normally.

In the security-check comparison: `i=3` gets turned back, **but it is not re-checked** — the turn passes to `i=4`. Otherwise it would loop forever.

#### 8.7 Where `continue` sits matters the same way

```c
sum = 0;
for (i = 1; i <= 6; i++) {
    sum += i;           // before the continue: runs every round
    if (i == 3)
        continue;
    sum += 100;         // after the continue: skipped in the i==3 round
}
printf("sum = %d, i = %d\n", sum, i);        // 521 7
```

Round by round:

```
i=1  add i -> 1    add 100 -> 101
i=2  add i -> 103  add 100 -> 203
i=3  add i -> 206  continue! skip +100   <- this round only added 3
i=4  add i -> 210  add 100 -> 310
i=5  add i -> 315  add 100 -> 415
i=6  add i -> 421  add 100 -> 521
```

#### 8.8 A `continue` at the end of the body does nothing

```c
sum = 0;
for (i = 1; i <= 4; i++) {
    sum += i;
    if (i == 2)
        continue;       // nothing follows it, so it skips thin air
}
printf("sum = %d, i = %d\n", sum, i);        // 10 5
```

**Identical to not writing `continue` at all.**

The check is simple: **look at what comes after the `continue`. If nothing, it is decoration.**

#### 8.9 Side by side, the difference is clearest

The same loop with one keyword swapped:

```c
for (i = 1; i <= 6; i++) {
    if (i == 3) break;      // walks out the door
    sum += i;
}
// sum = 3,  i = 3     1+2, i stops at 3

for (i = 1; i <= 6; i++) {
    if (i == 3) continue;   // failed the check
    sum += i;
}
// sum = 18, i = 7     1+2+4+5+6, i runs on to 7
```

`sum` differs by 15, `i` by 4 — **and all of it comes down to whether `i++` ran.**

#### 8.10 One trap left for later

`break` exits **only the loop it sits in**. With a single loop there is no ambiguity; once nested loops arrive (a loop inside a loop), `break` leaves just the innermost one and the outer loop carries on. That day is [Chapter 9, section 9.6](#96-break-exits-only-the-loop-it-sits-in); for now, remember "nearest".

#### 8.11 Actual output (all 13 sections, measured)

```
1) sum = 21, i = 6                      // stop once sum > 15
2) A: sum = 20, i = 5                   // break first
3) B: sum = 30, i = 5                   // break last
4) sum = 6, i = 4                       // i stops at the triggering round
5) sum = 15, i = 6                      // break never fires
6) sum = 80, i = 10                     // descending, i -= 2
7) first number divisible by 7: 7, i = 7
8) break    -> sum = 3,  i = 3
   continue -> sum = 18, i = 7
9) sum = 18, i = 7                      // continue, basic
10) sum = 37, i = 11                    // skip every multiple of 3
11) sum = 521, i = 7                    // continue last
12) sum = 13, i = 0                     // descending + continue
13) sum = 10, i = 5                     // continue as decoration
```

#### 8.12 Pitfalls

- Working out `i` after a `break` as "bound + 1" → `i` stops at the triggering round; `i++` never ran.
- Assuming the statement after `break` still runs → everything left in that round is skipped, `i++` included.
- Ignoring where `break` sits → before or after `sum += i` changes the result by a whole round's increment.
- Treating `continue` as `break` → with `continue`, `i++` runs and the loop finishes normally.
- Thinking `continue` re-checks the same `i` → it skips the rest of *this* round; the next round has a **new** `i`.
- Putting `continue` at the end of the body → nothing left to skip, so it does nothing.
- Getting the equality wrong in the `if` → `sum > 15` and `sum >= 15` differ by one round (at exactly 15, only the latter fires).

---

### Chapter 9 The Three Shapes of if, Nested Loops, and Breaking Out

**Source file: `if_else_nested.c` (`ch_03_if_else_nested`)**

The first of the two programs I wrote that day. I thought I already knew `if`; what actually stopped me was something else — which `if` an `else` belongs to, and where `break` lands once you put a loop inside a loop. It also pays off the debt from 8.10 in the previous chapter (`break` exits only one level).

#### 9.1 The three shapes

| Shape | Form | How many branches run |
| --- | --- | --- |
| bare `if` | `if (...) A;` | 0 or 1 |
| `if-else` | `if (...) A; else B;` | **exactly one, always** |
| `else-if` chain | `if ... else if ... else` | stops at the first match |

A bare `if` means "do it if the condition holds, otherwise forget it". There is a trap in these two lines:

```c
if (i > 5)
    printf("1) i > 5, printed\n");
printf("   always printed\n");       // runs unconditionally
```

The second line is indented exactly like the first, and it is **not inside the `if`**. Braces decide what belongs to the `if`, not indentation — I already got burned by this with `for` in Chapter 7, and here it comes again.

`if-else`: one of the two, always exactly one. Never both, never neither.

`else-if` chain: tried top to bottom, and **the first match leaves the whole chain** — the conditions below are never even tested. The `chain done` line at the end is the proof: what you leave is the `if` chain, not the program.

#### 9.2 Order the conditions strictest first

`score = 85` walking down:

| Order | Condition | for 85 | Outcome |
| --- | --- | --- | --- |
| 1 | `>= 90` | false | move down |
| 2 | `>= 80` | **true** | print B, look no further |
| 3 | `>= 70` | (never reached) | — |
| `else` | catch-all | (never reached) | — |

At first I thought the order did not matter, since all four conditions are there anyway. It does:

| Written as | 85 is graded | 90 is graded |
| --- | --- | --- |
| `>=90 → >=80 → >=70` | **B** (right) | A (right) |
| `>=60 → >=90 → >=80` | **pass (wrong)** | pass (wrong) |

A score of 90 gets caught by the first `>=60` and graded "pass". So: **highest threshold first**, and once it is written, run 90, 80 and 70 through it to see which branch catches each.

#### 9.3 Trap 1: else binds to the nearest if

The two blocks differ only in the sign of `j`:

```c
/* first: i=1, j=1 */
if (i > 0)
    if (j > 0)
        printf("both positive\n");
    else
        printf("???\n");           // not printed: j>0 holds, so this is unreachable

/* second: i=1, j=-1 */
if (i > 0)
    if (j > 0)
        printf("inner\n");
    else
        printf("inner else taken (i=%d j=%d)\n", i, j);   // this one does print!
```

The second one is what convinced me. **The outer `i > 0` holds**, so if that `else` really belonged to the outer `if` it could not possibly run. Seeing it print is how I realised the `else` belongs to the **inner `if (j > 0)`**.

> `else` always goes with the **nearest unmatched `if`**, and how you indent has nothing to do with it.

gcc names this one nicely: `-Wdangling-else`.

The cure is braces — with them the binding is nailed down:

```c
if (i > 0) {
    if (j > 0) {
        printf("both\n");
    }
}
else {                              /* now it really belongs to the outer if */
    printf("outer else\n");
}
```

This prints only `braces fix it`. Since `i > 0` holds, the outer `else` should not run — and printing nothing is exactly what "bound correctly" looks like.

#### 9.4 Trap 2: one equals sign

```c
i = 0;
if (i = 5)                          /* puts 5 into i, then tests i's truth value */
    printf("5) entered, i becomes %d\n", i);   /* prints: i becomes 5 */
```

That single `=` does **two damaging things**, and the second one is the sneakier of the pair:

1. The condition is an assignment whose value is 5, and **nonzero means true** → it is always taken, the `else` is unreachable.
2. `i` gets quietly changed to 5. That is the real trouble: everything later that reads `i` is now wrong, and you would never think to look at this line.

gcc's warning is `-Wparentheses`, roughly "did you mean `==`?".

A trick I picked up later: put the constant on the left, `if (5 == i)`. Slip and drop an equals sign and it becomes `5 = i`, which will not compile. `i = 5` is perfectly legal, so the compiler can only warn — and if you do not read warnings, it just goes through.

#### 9.5 Nested loops: the outer one takes a step, the inner one spins a circle

```c
for (i = 1; i <= 3; i++) {
    for (j = 1; j <= 2; j++) {      /* every outer step, the inner loop runs twice */
        printf("   i=%d j=%d\n", i, j);
    }
}
```

The saying: *the outer one is slow, the inner one fast, like the hour hand and the minute hand*. 3 × 2 = 6 runs in total.

I first worked that out as 5 (3+2) and only noticed when the output had six lines — it is **multiplied**, not added.

One more thing I got wrong: I expected the inner `j` to carry on from the 2 of the previous round. It does not. `j = 1` sits in clause 1 of the inner `for`, so it starts over on every outer step: 1, 2, 1, 2.

#### 9.6 break exits only one level (paying off 8.10)

```c
for (i = 1; i <= 3; i++) {
    for (j = 1; j <= 3; j++) {
        if (j == 2)
            break;                  /* exits for(j) only */
        printf("   i=%d j=%d\n", i, j);
    }
    /* back here; the outer loop continues with the next i */
}
```

Output:

```
i=1 j=1
i=2 j=1
i=3 j=1
```

The inner loop prints only `j=1` each time, but **the outer `i` still runs through 1, 2, 3**.

`break` is "nearest-first": it leaves the loop it is in and stops there; the outer loop knows nothing. I file it as "it jumps out of whichever loop is closest". `continue` is the same, it only minds its own level (see 9.8).

#### 9.7 Leaving several levels: raise a flag

```c
int flag = 0;                   /* 0 = keep going, 1 = stop */
int hit_i = 0, hit_j = 0;

for (i = 1; i <= 5 && !flag; i++) {      /* outer condition gains !flag */
    for (j = 1; j <= 5; j++) {
        if (i * j == 6) {
            flag = 1;           /* raise the flag */
            hit_i = i;
            hit_j = j;
            break;              /* leave the inner loop first */
        }
    }
}
```

Two steps:

1. **Inner loop**: on a hit, set `flag = 1`, then `break` out.
2. **Outer loop**: hang `&& !flag` on its condition. When the round ends and control comes back to the outer test, `!flag` is already false, so the outer loop quits.

Measured: `i*j==6 at i=2 j=3, flag=1` — hit at `i=2 j=3`, and the outer loop never runs 3, 4, 5.

This is the `ok` flag from `compare_two_numbers.c` (Chapter 4) under a different name; `found` in the next chapter is the same thing again. All of them say the same thing to the outer loop: done, pack up.

C has no keyword for leaving several loops at once (`goto` can, but nobody recommends it), so a flag is the way.

#### 9.8 continue inside nested loops

```c
sum = 0;
for (i = 1; i <= 3; i++) {
    for (j = 1; j <= 3; j++) {
        if (j == 2)
            continue;           /* skips this round, but j++ still runs */
        sum += i * j;
    }
}
printf("9) sum=%d i=%d j=%d\n", sum, i, j);   /* 24 4 4 */
```

| `i` | `j = 1` | `j = 2` | `j = 3` | subtotal |
| --- | --- | --- | --- | --- |
| 1 | +1 | skipped | +3 | 4 |
| 2 | +2 | skipped | +6 | 8 |
| 3 | +3 | skipped | +9 | 12 |
| | | | **total** | **24** |

Afterwards `i = 4` and `j = 4` — both ended **normally** (bound + 1), because `continue` does not skip `j++`. Chapter 8's rule survives being nested.

#### 9.9 Actual output

```
1) i > 5, printed
   always printed
2) 3 is odd
3) 85 -> B
   chain done
4) both positive
4) inner else taken (i=1 j=-1)
4) braces fix it
5) entered, i becomes 5
5) i == 5 false, i still 0
6) nested:
   i=1 j=1
   i=1 j=2
   i=2 j=1
   i=2 j=2
   i=3 j=1
   i=3 j=2
7) break inner only:
   i=1 j=1
   i=2 j=1
   i=3 j=1
8) i*j==6 at i=2 j=3, flag=1
9) sum=24 i=4 j=4
```

Compiling throws three warnings: two `-Wdangling-else` and one `-Wparentheses`. Those traps are left in the code on purpose — the warnings are the compiler poking me in the ribs.

#### 9.10 Pitfalls

- Assuming `else` follows indentation → it binds to the **nearest unmatched `if`**; braces are the only way to pin it down.
- Writing `=` where `==` was meant → the condition is always true, and the variable gets overwritten behind your back. That side effect is the hardest part to find.
- Expecting `break` to escape several levels → it leaves **the one loop it is in**; raise a flag to go further.
- Adding the run counts of nested loops (3+2) instead of **multiplying** them (3×2 = 6).
- Expecting the inner `j` to carry on → `j = 1` sits in clause 1 and re-initialises on every outer step.
- Ordering an `else-if` chain loose-to-strict → boundary values get stolen early (90 graded as "pass").
- Thinking a match in the `if` chain ends the program → only the chain is left; what follows still runs.
- Using the same variable for both levels (both `i`) → the inner loop wrecks the outer counter and everything goes wrong.

---

### Chapter 10 Guess the Number: Random Numbers and Robust Input

**Source file: `guess_number.c` (`ch_03_guess_number`)**

The second program of the day, and the longest one so far. It uses nearly everything from the first nine chapters: a `while` loop, a three-way `if`, a flag variable, `break`, `continue`, and the return value of `scanf`.

| Item | Rule |
| --- | --- |
| Range | 1–100 (the computer picks a number) |
| Tries | 7 |
| Feedback | too big / too small |
| Bad input | ask again — **the try is free** |

#### 10.1 Random numbers: srand seeds, rand draws

```c
#include <stdlib.h>             /* rand / srand */
#include <time.h>               /* time */

srand((unsigned)time(NULL));    /* seed: once, at the start */
secret = rand() % 100 + 1;      /* 1..100 */
```

The range comes out like this:

| Expression | Range |
| --- | --- |
| `rand()` | 0 .. `RAND_MAX` |
| `rand() % 100` | 0 .. 99 |
| `rand() % 100 + 1` | **1 .. 100** |

For `[min, max]` write `rand() % (max - min + 1) + min`. It is a remainder, so the number after `%` decides how many values there are.

The first version I wrote had `rand()` and no `srand`, and every run produced the same sequence — I was convinced I had broken something. So: **`srand` once, at the top of `main`.**

Inside the loop it is worse: within one second `time(NULL)` is the same value, so you reseed with the same number over and over and keep drawing the same thing.

> Include the header for whatever you use: `rand` / `srand` live in `stdlib.h`, `time` in `time.h`.

#### 10.2 Two conditions on one loop

```c
while (count < max_try && !found)
```

| Condition | Guards | When it turns false |
| --- | --- | --- |
| `count < max_try` | tries remaining | all 7 used → **lost** |
| `!found` | not guessed yet | guessed → **won** |

Both sides of `&&` must hold to go on; either one going false ends it. Afterwards `if (found)` sorts out which ending it was:

```c
if (found) printf("You won! ...\n");
else       printf("You lost! ...\n");
```

#### 10.3 The return value of scanf

```c
ret = scanf("%d", &guess);
```

I had been using this function for three days before I found out it returns anything. And **what it returns is how many items it read, not the number** — the number is in `guess`.

| `ret` | Meaning | What the program does |
| --- | --- | --- |
| `1` | one integer read | carry on, `count++` |
| `0` | input present, but not an integer | warn + flush + `continue` |
| `EOF` (that is, `-1`) | input ran out (`Ctrl+Z`, or the pipe went dry) | warn + `break` |

It goes into `ret` because three tests follow. Writing `if (scanf(...) == 1)` allows only one test, and every extra `scanf` you write really does consume more input — it is not a free "let me check".

#### 10.4 A bad guess costs nothing: look at where count++ sits

```c
if (ret != 1) {              /* input present, but not an integer */
    printf("  Not a number, try again (this try is FREE)\n");

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;                    /* empty body: read to end of line, clearing the junk */
    continue;
}

/* case three: ret == 1, input is valid, carry on */
count++;                     /* reaching here means the input was valid */
```

Three things are packed into that short block:

1. **`continue` skips everything left in the round** — `count++` included. So this round costs no try, and the next prompt still says `[1/7]`.
2. **The buffer has to be flushed.** Leave those letters there and the next `scanf` reads them again, decides "not a number" again, `continue`s again… I tried it once and the screen went berserk. `while ((ch = getchar()) != '\n' && ch != EOF);` has an empty body (that lone semicolon *is* the body) and reads up to the newline.
3. **`count++` comes after the check** — that is the real reason only valid input is counted.

Chapter 8 said a `continue` with nothing after it is decoration. Here `count++` and a whole three-way `if` come after it, so it is doing real work.

`ch` must be `int`, not `char`: `getchar` returns an `int` precisely so that `EOF` (usually `-1`) can be represented, and a `char` may never see it.

#### 10.5 The found flag

```c
else {                     /* neither smaller nor larger, so equal */
    printf("  *** BINGO! ***\n");
    found = 1;             /* raise the flag */
    break;
}
```

Both lines are there, and they cover different things:

- `break` leaves the loop on the spot, no more guessing.
- `found = 1` is for the `if` **outside** the loop, so it can tell "guessed it" from "ran out of tries".

I first thought `break` alone was enough. It is not — you get out either way, but the outside has no idea how you got out, so winning still prints `You lost!`.

#### 10.6 The three-way branch

```c
if (guess < secret)       printf("  Too small!\n");
else if (guess > secret)  printf("  Too big!\n");
else                      printf("  *** BINGO! ***\n");
```

The third one needs no `else if (guess == secret)` — neither smaller nor larger means equal. A bonus of writing it this way: exactly one of the three runs, so no case can slip through.

#### 10.7 Are 7 tries enough?

Guess the middle of the current range and the range halves:

| Try | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Candidates left | 50 | 25 | 12 | 6 | 3 | 1 | 0 |

`log₂100 ≈ 6.64` and `2⁷ = 128 > 100`, so **7 is enough** — this game is not luck, it is halving.

#### 10.8 Actual output

> `secret` changes every run; the four transcripts below all come from one session where the answer was 90.

**① Guessed it (6 tries)**

```
=== Guess the number (1-100), 7 tries ===
[1/7] Your guess:   Too small!
[2/7] Your guess:   Too small!
[3/7] Your guess:   Too small!
[4/7] Your guess:   Too big!
[5/7] Your guess:   Too big!
[6/7] Your guess:   *** BINGO! ***
You won! Answer = 90, used 6 tries.
```

**② Bad input is free (the `abc` round costs nothing)**

```
[1/7] Your guess:   Too small!
[2/7] Your guess:   Not a number, try again (this try is FREE)
[2/7] Your guess:   Too small!
```

**③ Letters glued to a number (`50abc`)**

```
[1/7] Your guess:   Too small!                                  <- scanf reads 50, returns 1
[2/7] Your guess:   Not a number, try again (this try is FREE)  <- the leftover abc, next round
[2/7] Your guess:   *** BINGO! ***
You won! Answer = 90, used 2 tries.
```

`scanf("%d")` stops after the `50` and leaves `abc` behind, so the complaint arrives **one round late**. I only worked that out after staring at `[2/7]` appearing twice.

**④ End of input / out of tries**

```
[1/7] Your guess:   Too small!
[2/7] Your guess:   Input closed. Game over.
You lost! Answer was 90. (used 1 tries)
```

```
[7/7] Your guess:   Too small!
You lost! Answer was 90. (used 7 tries)
```

#### 10.9 Pitfalls

- Missing `&` after the variable: `scanf("%d", guess)` is wrong.
- Using the return value as the number: `guess = scanf("%d", &guess)` puts 1 or 0 into `guess`.
- Forgetting `srand` → the same sequence every run, so the game is not random.
- Putting `srand` inside the loop → reseeding with the same value, the number stops changing.
- Not flushing on bad input → the same letters are read again and again, an infinite scrolling loop.
- Declaring the flushing `ch` as `char` → `EOF` may never be seen.
- Putting `count++` **before** the `continue` → bad input costs a try, contradicting "this try is FREE".
- Writing `break` but forgetting `found = 1` → you win and it prints `You lost!`.
- `rand() % 100` is 0..99; drop the `+1` and the range becomes 0..99, so `secret` could be 0.
- Writing the three-way test as two separate `if`s → it evaluates twice; an `else-if` chain stops at the match.
