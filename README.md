*This project has been created as part of the 42 curriculum by peda-cos*

## Description

**FDF** (short for *"fil de fer"*, French for *"wireframe model"*) is a graphics
project from the 42 Common Core. Its goal is to render a 3D landscape as a
wireframe: each cell of a `.fdf` map file represents an `(x, y, z)` point in
space, and neighboring points are connected by line segments (edges). The
result is projected onto a 2D window using an isometric projection.

The project is written in **C**, uses the school's **MiniLibX** graphical
library to handle the window, images, and input events, and relies on a
personal **libft** for common utilities (`get_next_line`, `ft_split`,
`ft_printf`, etc.).

Beyond the mandatory isometric rendering, this implementation also provides:

- A **parallel projection** mode (toggle between projections at runtime).
- **Zoom** in and out (keyboard and mouse wheel).
- **Translation** of the model (arrow keys).
- **Rotation** of the model on the X, Y, and Z axes.
- **Altitude scaling** to exaggerate or flatten the relief.
- **Color gradient** based on altitude for better depth perception.

## Instructions

### Requirements

- A Linux system with X11 development libraries installed
  (`libx11-dev`, `libxext-dev`, `zlib1g-dev`).
- A C compiler (`cc` / `gcc`) and GNU `make`.
- The MiniLibX sources are already bundled in the `minilibx/` directory.
- `libft` is already bundled in the `libft/` directory.

### Build

From the project root:

```sh
make
```

This compiles `libft`, `minilibx`, and then links the `fdf` binary at the
root of the repository. Compilation uses `-Wall -Wextra -Werror` and does
not perform unnecessary relinking.

Other available rules:

| Rule | Action |
|---|---|
| `make` / `make all` | Build the `fdf` binary (default rule). |
| `make bonus` | Same as `all` — bonuses are built into the main binary. |
| `make clean` | Remove object files. |
| `make fclean` | Remove object files and the `fdf` binary. |
| `make re` | `fclean` + `all`. |

### Run

```sh
./fdf maps/42.fdf
```

The program takes a single argument: the path to a `.fdf` map file.
A selection of sample maps is included in the `maps/` directory
(e.g. `42.fdf`, `mars.fdf`, `pyramide.fdf`, `julia.fdf`, …).

### Controls

| Key / Input | Action |
|---|---|
| `ESC` or window close button | Quit cleanly. |
| Arrow keys | Translate the model. |
| `N` / `M` or mouse wheel | Zoom in / zoom out. |
| `J` / `K` | Decrease / increase altitude scale. |
| `W` / `S` | Rotate around the X axis. |
| `A` / `D` | Rotate around the Z axis. |
| `Q` / `E` | Rotate around the Y axis. |
| `P` | Toggle between isometric and parallel projection. |
| `R` | Reset camera to default view. |

### Map format

Each line of the `.fdf` file corresponds to a row of the landscape.
Each whitespace-separated value is the altitude at that `(x, y)` position.
An optional `,0xRRGGBB` suffix may be appended to a value to assign a
color to that point:

```
0  0  10,0xFF0000  10  0
0  0  10           10  0
```

Maps must be rectangular (all rows share the same number of columns).
As stated in the subject, the program assumes that the input file is
properly formatted.

## Project layout

```
.
├── Makefile
├── include/fdf.h          # public types and prototypes
├── libft/                 # personal C utility library
├── minilibx/              # school graphical library (X11 backend)
├── maps/                  # sample .fdf maps (42, mars, pyramide, julia, …)
└── src/
    ├── main.c             # entry point, argument handling, main loop
    ├── parse_map.c        # .fdf file reader
    ├── parse_utils.c      # row/point parsing helpers
    ├── init.c             # MLX and camera initialization
    ├── project.c          # isometric / parallel projections, rotations
    ├── draw_line.c        # Bresenham line-drawing with color interpolation
    ├── render.c           # frame composition from the map + camera state
    ├── color.c            # altitude-based color gradient
    ├── hooks.c            # keyboard, mouse, and close-event handlers
    └── cleanup.c          # memory cleanup and clean exit
```

## Resources

Classic references and documentation used while working on this project:

- **MiniLibX** — official tutorial by Gontjarow:
  <https://harm-smits.github.io/42docs/libs/minilibx>
- **MiniLibX source and intro (42 cursus)**:
  <https://github.com/42Paris/minilibx-linux>
- **Bresenham's line algorithm** (Wikipedia):
  <https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm>
- **Isometric projection** (Wikipedia):
  <https://en.wikipedia.org/wiki/Isometric_projection>
- **Rotation matrices** (Wikipedia):
  <https://en.wikipedia.org/wiki/Rotation_matrix>
- **X11 keysym reference** (`<X11/keysym.h>`) for key-handling constants.
- **42 Norm v4.1** — the coding standard enforced on the project,
  checked with [`norminette`](https://github.com/42School/norminette).

### Use of AI

AI assistants (LLMs) were used in a limited, supervised way during this
project, mostly as a rubber-duck / reference tool. Specifically:

- **Explaining concepts** — clarifying the math behind isometric projection,
  rotation matrices, and Bresenham's algorithm when the reference material
  was unclear.
- **Debugging help** — reading compiler / valgrind / norminette errors and
  suggesting where to look in the code.
- **README drafting** — producing the first draft of this file, which was
  then reviewed and edited.

AI was **not** used to generate the core implementation (parsing, projection,
rendering, hook handling, memory management): those were written and
debugged by hand to make sure every line is understood and Norm-compliant.
