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
- [Day 3 (1 program)](#day-3)
  - [Chapter 7 The for Loop: Sums, Products, and the Loop Variable](#chapter-7-the-for-loop-sums-products-and-the-loop-variable)
- [Appendix: Mistake Checklist (Day 3)](#appendix-mistake-checklist-day-3)

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

> Folder prefix `ch_03`; 1 program written that day, covering Chapter 7: the `for` loop. The syntax itself is small, but the loop exercises that went with it managed to hit nearly every mistake a beginner can make, so this chapter runs longer than the first two days combined.

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

## Appendix: Mistake Checklist (Day 3)

> Pitfalls from days 1–2 are folded into the "Pitfalls" section of each chapter. This list only covers day 3 (`for` loops). Skim it before writing code.

1. **An extra semicolon after `for` / `if` / `while`**
   - `for (i = 1; i <= 3; i++);` → the body is an empty statement; the loop spins and the next statement just runs once. Very hard to spot.
   - `while (i <= 20;)` puts the semicolon **inside** the parentheses → compile error.

2. **Missing semicolon at the end of a statement, or writing a colon `:`**
   - Statements always end with `;`. A colon belongs only after `case` in a `switch`.
   - Inside `for (...)` the three clauses are separated by **semicolons**; **commas** only join several assignments within one clause.

3. **Loop variable not initialized**
   - `while (i <= 20)` needs `i = 1;` above it. `for` does this in clause 1; `while` does not.

4. **Forgetting the step → infinite loop**
   - `i` never changes, the condition never fails, the console floods. Press **Ctrl + C**.

5. **Not resetting the accumulator, or starting a product at 0**
   - Sums start at `sum = 0`, products at `acc = 1`.
   - Before reusing an accumulator for a second loop, write `sum = 0;` — with **no `int`**, since redeclaring gives error `C2374`.

6. **Closing the `printf` quote too early**
   - `printf("AVG2"=%.2f\n", ...)` is wrong: the specifiers `%.2f`, `\n` and the label **all** belong **inside** the quotes; variables go **outside**.
   - Order to type it: **empty pair of quotes → fill in text and specifiers → add the comma and variables outside → add the final semicolon**.

7. **Full-width (Chinese) punctuation sneaking into code**
   - `；` `，` `（）` `“”` `＝` are all rejected, and the error text is baffling (e.g. `expected ';' before '；'`).
   - Permanent fix: enable "use English punctuation in Chinese mode" in the IME, or lock the IME to English while coding.

8. **Indentation lies: it looks inside the loop but is not**
   - Without braces, `for` governs **only the single statement that follows it**.
   - No amount of indentation changes the result; **only braces do**. Always write `{}`.

9. **Assuming `i` after the loop is "the last value that entered"**
   - It is actually **the first value that fails the condition**, one step beyond (`i < 3` ends with `i = 3`, not 2).
   - With a step greater than 1, write out the sequence instead of using the "±1" shortcut.

10. **Integer division truncates**
    - `385 / 10` is **38**, not 38.5.
    - To keep the fraction you must convert **before** dividing: `(double)sum / 10`. Switching to `%f` afterwards does not help.

11. **Misreading compound assignment as "three numbers added"**
    - `sum += i` means `sum = sum + i` (adds to the **current** value), not "sum plus i".
    - Whenever two operators sit glued together, expand it to the long form first.

12. **Copying the previous program's range or variable**
    - Writing 1..100 when the exercise says 1..20; printing `i` when you meant `sum`.
    - After writing, re-check: the bound in the condition, the variable in the body, and which variable you print.
