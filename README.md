# FdF - Fil de Fer (Wireframe Renderer)

A 3D wireframe visualization project that renders heightmaps in isometric projection. This project reads `.fdf` map files containing 3D coordinates and displays them as beautiful wireframe models with real-time camera controls.

![42 School Project](https://img.shields.io/badge/42-School_Project-000000?style=flat-square&logo=42)
![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![Graphics](https://img.shields.io/badge/Graphics-MLX42-green?style=flat-square)

## 📋 Table of Contents

- [About](#about)
- [Technology Stack](#technology-stack)
- [Project Architecture](#project-architecture)
- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [Key Features](#key-features)
- [Usage](#usage)
- [Controls](#controls)
- [Map File Format](#map-file-format)
- [Development Workflow](#development-workflow)
- [Coding Standards](#coding-standards)
- [License](#license)

## 📖 About

**FdF** (Fil de Fer, meaning "wireframe" in French) is a graphics project from the 42 School curriculum. The program takes a file representing a 3D landscape and renders it in isometric projection as a wireframe model. The visualization supports real-time interaction through keyboard controls for zooming, panning, and adjusting the Z-axis scale.

## 🛠 Technology Stack

### Core Technologies
- **Language:** C (C99)
- **Graphics Library:** MLX42 (42's modern graphics library)
- **Custom Library:** libft (custom C standard library implementation)

### Dependencies
- **GLFW:** For window management and input handling
- **OpenGL:** Via GLAD for rendering
- **CMake:** For building MLX42
- **pthread:** For multi-threading support
- **Math library:** For trigonometric calculations

### Build Tools
- **Compiler:** gcc/clang with flags: `-Wall -Wextra -Werror -Wunreachable-code -Ofast`
- **Build System:** Make
- **Memory Management:** Valgrind (suppressions file included)

## 🏗 Project Architecture

The FdF project follows a modular architecture with clear separation of concerns:

### Core Components

1. **Map Management** (`map_loading.c`, `map_management.c`)
   - File parsing and validation
   - Memory allocation for map data
   - Z-coordinate tracking (min/max)

2. **Camera System** (`camera_controls.c`)
   - Isometric projection transformation
   - Zoom and translation management
   - Z-axis scaling for depth adjustment

3. **Rendering Engine** (`map_rendering.c`, `drawing_helpers.c`)
   - Bresenham line drawing algorithm
   - Pixel-perfect line rendering
   - Boundary checking

4. **Color Processing** (`color_processing.c`)
   - Hexadecimal color parsing
   - Color interpolation for gradient effects
   - RGBA conversion

5. **Input Handling** (`input_hooks.c`)
   - Keyboard event management
   - Real-time camera control
   - Window management

### Data Structures

```c
// Point representation with color
typedef struct s_point {
    int         x, y, z;
    uint32_t    color;
} t_point;

// Map structure
typedef struct s_map {
    unsigned int    width, height, total_points;
    int             min_z, max_z;
    t_point         *points;
} t_map;

// Camera configuration
typedef struct s_camera {
    int     projection_type;
    float   zoom_level;
    double  z_scale_factor;
    int     x_offset, y_offset;
} t_camera;

// Main FdF structure
typedef struct s_fdf {
    t_map       *map;
    t_camera    *camera;
    mlx_t       *mlx_instance;
    mlx_image_t *image;
} t_fdf;
```

## 🚀 Getting Started

### Prerequisites

Ensure you have the following installed:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential cmake libglfw3-dev xorg-dev

# macOS
brew install cmake glfw
```

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/peda-cos/FdF.git
   cd FdF
   ```

2. **Build the project:**
   ```bash
   make
   ```

   This will:
   - Build the custom libft library
   - Compile MLX42 using CMake
   - Compile all FdF source files
   - Link everything into the `fdf` executable

3. **Run the program:**
   ```bash
   ./fdf maps/42.fdf
   ```

### Cleaning

```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Rebuild everything from scratch
```

## 📁 Project Structure

```
FdF/
├── src/                    # Source files
│   ├── main.c              # Entry point
│   ├── fdf.h               # Main header file
│   ├── camera_controls.c   # Camera transformations
│   ├── color_processing.c  # Color handling
│   ├── drawing_helpers.c   # Line drawing utilities
│   ├── input_hooks.c       # Keyboard input
│   ├── map_loading.c       # Map file parsing
│   ├── map_management.c    # Map memory management
│   ├── map_rendering.c     # Rendering logic
│   └── utility_functions.c # Helper functions
├── lib/                    # External libraries
│   ├── libft/              # Custom C library
│   └── MLX42/              # Graphics library
├── maps/                   # Sample map files
│   ├── 42.fdf
│   ├── pyramide.fdf
│   ├── mars.fdf
│   └── ...
├── Makefile              # Build configuration
├── suppressions.supp     # Valgrind suppressions
└── LICENSE               # MIT License
```

## ✨ Key Features

### Rendering
- **Isometric Projection:** 3D visualization with proper depth perception
- **Color Support:** Parse and display custom colors from map files
- **Color Gradients:** Smooth color interpolation between points
- **Wireframe Display:** Clean line-based rendering

### Camera Controls
- **Dynamic Zoom:** Smooth zooming in/out
- **Translation:** Pan the view in all directions
- **Z-Axis Scaling:** Adjust height/depth visualization
- **Reset Function:** Return to default view instantly

### Map Processing
- **Flexible Format:** Support for various map sizes
- **Color Parsing:** Hexadecimal color codes (e.g., `10,0xFF0000`)
- **Validation:** Robust error checking for file format
- **Memory Efficient:** Optimized memory allocation

## 📖 Usage

### Basic Usage

```bash
./fdf <map_file.fdf>
```

### Examples

```bash
# Render the 42 logo
./fdf maps/42.fdf

# Render a pyramid
./fdf maps/pyramide.fdf

# Render Mars terrain
./fdf maps/mars.fdf
```

## 🎮 Controls

| Key          | Action                          |
| ------------ | ------------------------------- |
| **ESC**      | Exit the program                |
| **W**        | Move up                         |
| **S**        | Move down                       |
| **A**        | Move left                       |
| **D**        | Move right                      |
| **Keypad +** | Zoom in                         |
| **Keypad -** | Zoom out                        |
| **J**        | Increase Z-axis scale (flatten) |
| **K**        | Decrease Z-axis scale (amplify) |
| **R**        | Reset camera to default view    |

## 📄 Map File Format

Map files (`.fdf`) consist of numbers representing Z-coordinates (height) at each point:

### Basic Format
```
0  0  0  0  0
0  10 10 10 0
0  10 20 10 0
0  10 10 10 0
0  0  0  0  0
```

### With Colors
```
0  0  0  0  0
0  10,0xFF0000 10,0xFF0000 10,0xFF0000 0
0  10,0x00FF00 20,0xFFFF00 10,0x00FF00 0
0  10,0x0000FF 10,0x0000FF 10,0x0000FF 0
0  0  0  0  0
```

- Numbers represent Z-coordinates (height)
- Optional hexadecimal color after comma (format: `z,0xRRGGBB`)
- Spaces separate points on the same line
- Each line must have the same number of points

## 🔄 Development Workflow

### Building
1. Modify source files in `src/`
2. Run `make` to compile
3. Test with sample maps in `maps/`

### Debugging
- Use `valgrind` with the provided suppressions file:
  ```bash
  valgrind --leak-check=full --suppressions=suppressions.supp ./fdf maps/42.fdf
  ```

### Adding Features
1. Update `fdf.h` with new function prototypes
2. Implement functions in appropriate source files
3. Update Makefile if adding new files
4. Test thoroughly with various map files

## 📝 Coding Standards

This project follows the **42 School Norm**, which includes:

### Code Style
- **Indentation:** Tabs (displayed as 4 spaces)
- **Line Length:** Maximum 80 characters
- **Function Length:** Maximum 25 lines
- **Functions per File:** Maximum 5 functions
- **Parameters:** Maximum 4 parameters per function

### Naming Conventions
- **Functions:** `snake_case` with descriptive names
- **Variables:** `snake_case`
- **Structs:** `typedef struct s_name` with `t_name` alias
- **Macros:** `UPPER_CASE`

### Memory Management
- No memory leaks permitted
- All allocated memory must be freed
- Proper error handling for allocations
- Use of custom `ft_calloc` from libft

### Forbidden
- Global variables (except specific cases)
- Use of `for` loops (while loops only)
- Standard library functions (must use libft)
- External libraries except MLX42 and allowed math functions

## 🧪 Testing

### Sample Maps
The `maps/` directory contains various test cases:
- **Simple shapes:** `pyramide.fdf`, `pyra.fdf`
- **Complex terrain:** `mars.fdf`, `julia.fdf`
- **Edge cases:** `elem-fract.fdf` (fractional coordinates)
- **Color testing:** `elem-col.fdf` (with colors)

### Validation Tests
- Empty file handling
- Invalid file extensions
- Inconsistent line widths
- Invalid number formats
- Color parsing edge cases

## 👤 Author

**Pedro Monteiro** (peda-cos)
- GitHub: [@peda-cos](https://github.com/peda-cos)
- 42 Intra: peda-cos
- Email: peda-cos@student.42sp.org.br

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
Copyright (c) 2025 Pedro Monteiro
```

## 🙏 Acknowledgments

- **42 School** for the project specifications
- **MLX42** library developers for the modern graphics framework
- **Codam Coding College** for MLX42 documentation and examples
- **42 São Paulo** community for support and collaboration

---

*This project is part of the 42 School common core curriculum, focusing on graphics programming, 3D mathematics, and efficient algorithm implementation.*
