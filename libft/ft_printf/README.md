*This project has been created as part of the 42 curriculum by peda-cos.*

# ft_printf

## Description

`ft_printf` is a C reimplementation of the standard `printf(3)` library function, compiled and delivered as the static library **`libftprintf.a`**. The function scans a format string, interprets every `%` conversion specifier, pulls the corresponding variadic argument, formats it, and writes the result directly to stdout via `write(2)`. The return value mirrors the standard: total bytes written on success, `-1` on error.

### Supported conversion specifiers

| Specifier | Output |
|-----------|--------|
| `%c` | Single character |
| `%s` | Null-terminated string |
| `%p` | Pointer address in hexadecimal (`0x…`) |
| `%d` / `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned hexadecimal (lowercase) |
| `%X` | Unsigned hexadecimal (uppercase) |
| `%%` | Literal `%` character |

### Bonus flags (flag / field-width / precision)

The bonus build (`make bonus`) extends each specifier with full formatting support:

| Flag / modifier | Effect |
|-----------------|--------|
| `-` | Left-align the output within the field width |
| `0` | Pad numbers with `'0'` instead of spaces (ignored when `-` is active or an explicit precision is set) |
| `.prec` | Maximum characters for strings; minimum digits for integers; implied precision for `%p` |
| `#` | Prefix non-zero `%x`/`%X`/`%p` values with `0x` or `0X` |
| `+` | Force a sign character (`+` or `-`) on numeric output |
| ` ` (space) | Prefix positive numbers with a space instead of `+` (overridden by `+`) |
| `<width>` | Minimum field width as a decimal integer before the specifier |

---

## Instructions

### Compilation

Build the **standard** library (mandatory part):

```bash
make
```

Build the **bonus** library (full flag / width / precision support):

```bash
make bonus
```

Both targets produce `libftprintf.a` in the project directory. Other useful targets:

```bash
make clean    # remove object files
make fclean   # remove object files and libftprintf.a
make re       # fclean then all
```

### Installation (linking)

Copy (or keep) `libftprintf.a` and `ft_printf.h` in the desired location, then link your program with:

```bash
cc main.c -L. -lftprintf -o my_program
```

- `-L.` — search the current directory for the library archive  
- `-lftprintf` — link against `libftprintf.a`

### Usage example

```c
#include "ft_printf.h"

int main(void)
{
    int n;

    n = ft_printf("Hello, %s! Answer is %d (0x%08x)\n", "world", 42, 42);
    ft_printf("Bytes written: %d\n", n);
    return (0);
}
```

Compile and run:

```bash
cc main.c -L. -lftprintf -o demo
./demo
# Hello, world! Answer is 42 (0x0000002a)
# Bytes written: 43
```

---

## Resources

### Standard references

- **`<stdarg.h>` manual** — `man stdarg` / POSIX `<stdarg.h>` specification; describes `va_list`, `va_start`, `va_arg`, `va_end` macros used to iterate variadic arguments.
- **`write(2)` manpage** — `man 2 write`; the only output syscall used; explains return value semantics including `-1` on error and `errno`.
- **`man 3 printf`** — the canonical specification for conversion specifiers, flags, field-width, and precision rules that this project reimplements.
- **42 subject** — `en.subject.pdf` provided by the school; defines the exact specifiers required, bonus flags, norminette constraints, and the expected library name `libftprintf.a`.

### AI usage

AI assistance (Claude) was used for the following tasks during this project:

- **Conceptual clarification** — explaining how `va_arg` interacts with argument promotion rules (e.g., why `char` and `short` must be pulled as `int`), and the precise semantics of precision vs. width for `%s` and `%p`.
- **README drafting** — structuring and writing this document.
- **Algorithm brainstorming** — discussing trade-offs between a function-pointer dispatch table and a flat `if/else` chain (see §Algorithm below).

AI was **not** used for:

- Writing any `.c` or `.h` source files — all implementation code was written by hand.
- Debugging or fixing norminette errors.
- Understanding the 42 subject requirements (read directly from the PDF).

---

## Algorithm and Data Structures

### 1. Four-stage pipeline

Every `%` specifier travels through a fixed four-stage pipeline inside `ft_printf`:

```
format string
    │
    ▼
parse_format()   — read flags, width, precision, specifier char → populate t_fmt
    │
    ▼
dispatch()       — route t_fmt.spec to the correct convert_*() function
    │
    ▼
convert_*()      — pull va_arg, apply formatting, call write(2) helpers
    │
    ▼
write(2)         — bytes land on stdout; return value bubbles up to ft_printf
```

Non-`%` characters bypass the entire pipeline and are written directly with a single `write(1, ptr, 1)` call.

**Why a pipeline instead of a monolithic function?**  
Each stage has a single, testable responsibility. `parse_format` never touches the `va_list`; `convert_*` never touches the raw format string. This separation makes it straightforward to extend (e.g., adding a new flag means touching only `parse_format` and the relevant converter) and keeps every function well within the 25-line norminette limit.

---

### 2. The `t_fmt` context struct

```c
typedef struct s_fmt
{
    char  spec;        /* 'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%' */
    int   width;       /* minimum field width; 0 = not specified      */
    int   prec;        /* precision; -1 = not specified               */
    int   flag_minus;  /* '-' left-align                              */
    int   flag_zero;   /* '0' zero-pad                                */
    int   flag_hash;   /* '#' alternate form (0x / 0X prefix)         */
    int   flag_plus;   /* '+' force sign                              */
    int   flag_space;  /* ' ' space for positive numbers              */
}   t_fmt;
```

`t_fmt` is stack-allocated inside `ft_printf` and re-initialised by `init_fmt()` at the start of each `%` specifier. Converters receive a pointer to it and treat it as read-only input.

**Why a struct instead of global state?**  
Global variables would make `ft_printf` non-reentrant and non-thread-safe. A `t_fmt` on the stack is reset automatically each specifier; there is no risk of flag leakage between consecutive conversions.

**Why a struct instead of passing every field as a separate parameter?**  
With seven fields, passing them individually would produce function signatures with eight or more parameters — violating the norminette four-parameter limit and making every call site unreadable. Grouping them into one struct keeps each function signature to `(t_fmt *fmt, va_list *ap)`, exactly two parameters.

---

### 3. Flat `if/else` dispatch over `fmt->spec`

`dispatch()` is a flat `if/else if` chain:

```c
if (fmt->spec == 'c')       return convert_char(fmt, ap);
else if (fmt->spec == 's')  return convert_str(fmt, ap);
else if (fmt->spec == 'p')  return convert_ptr(fmt, ap);
else if (fmt->spec == 'd'
      || fmt->spec == 'i')  return convert_int(fmt, ap);
else if (fmt->spec == 'u')  return convert_uint(fmt, ap);
else if (fmt->spec == 'x'
      || fmt->spec == 'X')  return convert_hex(fmt, ap);
else if (fmt->spec == '%')  return convert_percent(fmt);
return (0);
```

**Why not a function-pointer jump table?**  
A jump table (`void *table[256]`) requires either a 256-entry array of mostly-NULL pointers or a mapping step that adds indirection without reducing code. For eight specifiers the lookup gain is negligible. A jump table also hides control flow from the compiler's inliner and makes the code harder to read during code review and peer evaluation.

**Why not a `switch` statement?**  
A `switch` with fall-through shares the same specifiers across `d`/`i` and `x`/`X`. Norminette forbids `switch` entirely in some campus configurations, and `if/else` communicates intent equally clearly for this small set of cases.

**Why flat `if/else` wins here?**  
With only eight cases the chain is O(1) in practice (the first three specifiers cover the vast majority of real-world calls). It compiles to the same branch prediction structure as a `switch`, requires no auxiliary data structure, and every branch is explicit and independently readable.

---

### 4. Base-agnostic recursive `ft_putnbr_base()`

```c
int ft_putnbr_base(unsigned long n, char *base, int blen)
```

A single recursive function handles every numeric base used by the project:

| Call site | `base` argument | `blen` |
|-----------|----------------|--------|
| `%d`, `%i`, `%u` | `"0123456789"` | 10 |
| `%x` | `"0123456789abcdef"` | 16 |
| `%X` | `"0123456789ABCDEF"` | 16 |
| `%p` | `"0123456789abcdef"` | 16 |

**Recursion unwinds the digit stack for free.**  
The most-significant digit must be written first. An iterative approach needs an auxiliary buffer to reverse the digits; recursion uses the call stack as that buffer at no extra memory cost.

**Why not separate `ft_putnbr_decimal()` / `ft_putnbr_hex()` functions?**  
Two near-identical functions would be a maintenance hazard: any bug fix (e.g., handling `0` correctly) would need to be applied twice. A base string parameter generalises cleanly to any future base without adding new functions.

**Why pass `blen` explicitly instead of calling `strlen(base)` each digit?**  
`strlen` is O(n) on the base string. Since the base is a compile-time constant, the caller passes its length as a constant integer, making the division `n / blen` and modulo `n % blen` one operation each, not two plus a strlen scan per recursion level.

**Error propagation:**  
`ft_putnbr_base` calls `ft_putchar_fd`, which calls `write(2)` and returns its result. Each recursive call checks the return of the recursive descent and propagates `-1` upward to `dispatch()` and ultimately to `ft_printf`, which calls `va_end` and returns `-1`.
