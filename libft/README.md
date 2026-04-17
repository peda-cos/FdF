*This project has been created as part of the 42 curriculum by peda-cos.*

# libft

## Description

**libft** is the first project of the 42 school Common Core curriculum. Its goal is to re-implement a selection of standard C library functions from scratch, deepening the understanding of how they work internally, and to build a personal utility library that can be reused in future school projects.

The library is organized into three parts:

- **Part 1 — Libc re-implementations**: Functions that replicate the behavior of well-known standard C library functions (`<string.h>`, `<ctype.h>`, `<stdlib.h>`), prefixed with `ft_` to avoid name collisions.
- **Part 2 — Additional functions**: Utility functions not present in the standard library (or present in a different form), useful for string manipulation, memory allocation, and output.
- **Part 3 (Bonus) — Linked-list functions**: A set of functions to create and manipulate singly-linked lists using the `t_list` type.

All functions are written in C, comply with the 42 Norm (v4), and produce the static library archive `libft.a`.

---

## Instructions

### Requirements

- A C compiler (`cc`) with the flags `-Wall -Wextra -Werror`
- `ar` (archiver) — **do not** use `libtool`
- `make`

### Clone the repository

```bash
git clone https://github.com/<your-username>/ft_libft.git
cd ft_libft
```

### Compile the library

```bash
make
```

This compiles all mandatory source files and creates `libft.a` at the root of the repository.

### Compile with bonus (linked-list functions)

```bash
make bonus
```

This also compiles the bonus `_bonus.c` files and includes the linked-list functions in `libft.a`.

### Other Makefile targets

| Target | Effect |
|---|---|
| `make` / `make all` | Compile mandatory sources → `libft.a` |
| `make bonus` | Compile mandatory + bonus sources → `libft.a` |
| `make clean` | Remove object files (`.o`) |
| `make fclean` | Remove object files **and** `libft.a` |
| `make re` | `fclean` then `all` |

### Using the library in your project

Copy `libft.a` and `libft.h` into your project, then compile with:

```bash
cc -Wall -Wextra -Werror your_file.c -L. -lft -o your_program
```

---

## Library Reference

### Part 1 — Libc Re-implementations

These functions replicate standard C library functions. They must not rely on any external functions.

| Function | Prototype | Description |
|---|---|---|
| `ft_isalpha` | `int ft_isalpha(int c)` | Returns `1` if `c` is an alphabetic character, `0` otherwise. |
| `ft_isdigit` | `int ft_isdigit(int c)` | Returns `1` if `c` is a decimal digit (`0`–`9`), `0` otherwise. |
| `ft_isalnum` | `int ft_isalnum(int c)` | Returns `1` if `c` is alphanumeric, `0` otherwise. |
| `ft_isascii` | `int ft_isascii(int c)` | Returns `1` if `c` is a 7-bit ASCII character (0–127), `0` otherwise. |
| `ft_isprint` | `int ft_isprint(int c)` | Returns `1` if `c` is a printable character (including space), `0` otherwise. |
| `ft_strlen` | `size_t ft_strlen(const char *s)` | Returns the number of bytes in the string `s`, not including the terminating `'\0'`. |
| `ft_memset` | `void *ft_memset(void *b, int c, size_t len)` | Fills `len` bytes of memory area `b` with the byte value `c`. Returns `b`. |
| `ft_bzero` | `void ft_bzero(void *s, size_t n)` | Sets `n` bytes of memory area `s` to zero. |
| `ft_memcpy` | `void *ft_memcpy(void *dst, const void *src, size_t n)` | Copies `n` bytes from `src` to `dst` (no overlap handling). Returns `dst`. |
| `ft_memmove` | `void *ft_memmove(void *dst, const void *src, size_t len)` | Copies `len` bytes from `src` to `dst`, handling overlapping regions correctly. |
| `ft_strlcpy` | `size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)` | Copies up to `dstsize - 1` characters of `src` to `dst`, NUL-terminating. Returns the total length of `src`. |
| `ft_strlcat` | `size_t ft_strlcat(char *dst, const char *src, size_t dstsize)` | Appends `src` to `dst` up to `dstsize - 1` bytes total. Returns the intended total length. |
| `ft_toupper` | `int ft_toupper(int c)` | Converts a lowercase letter to uppercase. Returns the converted character. |
| `ft_tolower` | `int ft_tolower(int c)` | Converts an uppercase letter to lowercase. Returns the converted character. |
| `ft_strchr` | `char *ft_strchr(const char *s, int c)` | Returns a pointer to the first occurrence of character `c` in string `s`, or `NULL`. |
| `ft_strrchr` | `char *ft_strrchr(const char *s, int c)` | Returns a pointer to the last occurrence of character `c` in string `s`, or `NULL`. |
| `ft_strncmp` | `int ft_strncmp(const char *s1, const char *s2, size_t n)` | Compares at most `n` characters of `s1` and `s2`. Returns negative, zero, or positive. |
| `ft_memchr` | `void *ft_memchr(const void *s, int c, size_t n)` | Scans `n` bytes of memory area `s` for the first occurrence of byte `c`. Returns a pointer or `NULL`. |
| `ft_memcmp` | `int ft_memcmp(const void *s1, const void *s2, size_t n)` | Compares `n` bytes of `s1` and `s2`. Returns negative, zero, or positive. |
| `ft_strnstr` | `char *ft_strnstr(const char *haystack, const char *needle, size_t len)` | Locates the first occurrence of `needle` in at most `len` characters of `haystack`. Returns a pointer or `NULL`. |
| `ft_atoi` | `int ft_atoi(const char *str)` | Converts the initial portion of string `str` to an `int`, skipping leading whitespace and handling an optional sign. |
| `ft_calloc` | `void *ft_calloc(size_t nmemb, size_t size)` | Allocates `nmemb * size` bytes of zero-initialized memory using `malloc`. Returns a pointer or `NULL` on failure. |
| `ft_strdup` | `char *ft_strdup(const char *s1)` | Allocates and returns a duplicate of string `s1` using `malloc`. Returns `NULL` on failure. |

---

### Part 2 — Additional Functions

These functions are not part of the standard C library (or differ in behavior) and provide useful string/IO utilities.

| Function | Prototype | Description |
|---|---|---|
| `ft_substr` | `char *ft_substr(char const *s, unsigned int start, size_t len)` | Allocates and returns a substring of `s` starting at index `start` with at most `len` characters. Returns `NULL` on allocation failure. |
| `ft_strjoin` | `char *ft_strjoin(char const *s1, char const *s2)` | Allocates and returns a new string that is the concatenation of `s1` and `s2`. Returns `NULL` on failure. |
| `ft_strtrim` | `char *ft_strtrim(char const *s1, char const *set)` | Allocates and returns a copy of `s1` with all leading and trailing characters found in `set` removed. Returns `NULL` on failure. |
| `ft_split` | `char **ft_split(char const *s, char c)` | Allocates and returns an array of strings by splitting `s` using character `c` as delimiter. The array is `NULL`-terminated. Returns `NULL` on failure. |
| `ft_itoa` | `char *ft_itoa(int n)` | Allocates and returns a string representation of integer `n` (handles negative numbers). Returns `NULL` on failure. |
| `ft_strmapi` | `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` | Applies function `f` to each character of `s` (with its index) and returns the resulting new string. Returns `NULL` on failure. |
| `ft_striteri` | `void ft_striteri(char *s, void (*f)(unsigned int, char*))` | Applies function `f` to each character of `s` in-place, passing the index and a pointer to the character. |
| `ft_putchar_fd` | `void ft_putchar_fd(char c, int fd)` | Writes character `c` to file descriptor `fd` using `write`. |
| `ft_putstr_fd` | `void ft_putstr_fd(char *s, int fd)` | Writes string `s` to file descriptor `fd` using `write`. |
| `ft_putendl_fd` | `void ft_putendl_fd(char *s, int fd)` | Writes string `s` followed by a newline to file descriptor `fd` using `write`. |
| `ft_putnbr_fd` | `void ft_putnbr_fd(int n, int fd)` | Writes the decimal representation of integer `n` to file descriptor `fd` using `write`. |

---

### Part 3 (Bonus) — Linked-List Functions

These functions manipulate singly-linked lists of type `t_list`, defined in `libft.h` as:

```c
typedef struct s_list
{
    void          *content;
    struct s_list *next;
}   t_list;
```

| Function | Prototype | Description |
|---|---|---|
| `ft_lstnew` | `t_list *ft_lstnew(void *content)` | Allocates and returns a new node with `content` set and `next` set to `NULL`. Returns `NULL` on failure. |
| `ft_lstadd_front` | `void ft_lstadd_front(t_list **lst, t_list *new)` | Inserts node `new` at the beginning of the list pointed to by `lst`. |
| `ft_lstsize` | `int ft_lstsize(t_list *lst)` | Returns the number of nodes in the list. |
| `ft_lstlast` | `t_list *ft_lstlast(t_list *lst)` | Returns a pointer to the last node of the list. |
| `ft_lstadd_back` | `void ft_lstadd_back(t_list **lst, t_list *new)` | Appends node `new` at the end of the list pointed to by `lst`. |
| `ft_lstdelone` | `void ft_lstdelone(t_list *lst, void (*del)(void *))` | Frees the content of node `lst` with `del`, then frees the node itself. Does **not** free subsequent nodes. |
| `ft_lstclear` | `void ft_lstclear(t_list **lst, void (*del)(void *))` | Deletes and frees every node of the list using `del` and `free`, then sets `*lst` to `NULL`. |
| `ft_lstiter` | `void ft_lstiter(t_list *lst, void (*f)(void *))` | Iterates over the list and applies function `f` to the content of every node. |
| `ft_lstmap` | `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` | Creates a new list by applying `f` to each node's content. Uses `del` on failure. Returns the new list or `NULL` on failure. |

---

## Resources

### References

- [C Standard Library — cppreference.com](https://en.cppreference.com/w/c)
- [The GNU C Library (glibc) Manual](https://www.gnu.org/software/libc/manual/)
- POSIX man pages for `string.h`, `ctype.h`, `stdlib.h` functions (`man 3 strlen`, `man 3 memset`, etc.)
- [BSD `<bsd/string.h>` — for testing `strlcpy`, `strlcat`, `bzero` on glibc systems](https://manpages.debian.org/bsd-dev/bsd/string.3bsd.en.html)
- [norminette — 42 School Norm checker](https://github.com/42School/norminette)

### AI Usage Disclosure

The `README.md` file was drafted with the assistance of **Claude by Anthropic** (accessed via the [OpenCode](https://opencode.ai/) development tool).

Specifically, the AI was used for:
- Generating the initial draft of this `README.md` (all sections: Description, Instructions, Library Reference, Resources)

No source code (`.c` files, `libft.h`, or `Makefile`) was generated or modified by AI — all C implementations were written by **peda-cos** as part of the 42 curriculum.
