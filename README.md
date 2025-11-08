# MHTML → OpenGL Renderer  
**A C++ parser + OpenGL visualizer** for a custom **MHTML-like templating language** that **draws every element in 2D using OpenGL**.

From `@div { "Hello" }` → **on-screen rectangles, text, and layout**.

---

## Goal

> **Parse `.mhtml` files → Build AST → Render every element with OpenGL**

No more printing trees — **see your layout live on screen!**

---

## Features

| Feature | Status |
|-------|--------|
| Custom `.mhtml` parser (lexer + recursive descent) | Done |
| AST with tags, classes, properties, text | Done |
| **OpenGL 2D rendering engine** | In Progress |
| Draw `@div`, `@img`, `@h1`, etc. as colored rectangles | In Progress |
| Render text with **FreeType** or bitmap fonts | Planned |
| CSS-like class support (`.card`, `.primary`) | Planned |
| Layout system (flexbox-like) | Planned |

---

## Syntax (`.mhtml`)

```mhtml
@div .card .primary id:main {
    @h1 { "Hello World" }
    @p { "This is a paragraph with text." }
    @img src:"logo.png" w:200 h:100 { }
    @button .success { "Click Me" }
}
```

### Supported:
- `@tag` → rectangle
- `.class` → styling (color, border, etc.)
- `prop:value` → width, height, padding, etc.
- Text → rendered inside
- Nested layout

---

## Project Structure

```
mhtml-opengl/
├── main.cpp           ← Entry + OpenGL loop
├── parser.h           ← AST + token defs
├── parser.cpp         ← Lexer + Parser
├── renderer.h/.cpp    ← OpenGL drawing
├── shaders/           ← GLSL vertex/fragment
├── fonts/             ← TTF or bitmap fonts
├── index.mhtml        ← Input file
└── README.md
```

---

## Build & Run

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt install libglfw3-dev libgl1-mesa-dev libfreetype6-dev
```

### Compile

```bash
g++ -std=c++17 main.cpp parser.cpp renderer.cpp \
    -lglfw -lGL -lfreetype -o mhtml-viewer
```

### Run

```bash
./mhtml-viewer
```

---

## Example: `index.mhtml`

```mhtml
@div .container {
    @h1 .title { "MHTML + OpenGL" }
    @div .card {
        @p { "This is a card" }
        @button { "Click" }
    }
}
```

---

- Uses **GLFW + GLAD**
- **Orthographic projection** (2D)
- **Immediate mode** style (for simplicity)
- **Shader-based coloring**

---


## Debug Mode([COMMING SOON])

Run with:

```bash
./mhtml-viewer --debug
```

→ Prints **AST tree** + **render log**

---

## Contributing

Love 2D rendering? Want to help draw buttons?

1. Fork
2. Create branch: `feature/text-rendering`
3. Commit
4. Open PR

**Ideas welcome:**
- Font system
- Layout algorithms
- Shader effects
- Animation

---


**From syntax to screen — powered by C++ and OpenGL.**

> *"If it doesn’t render, it doesn’t exist."*  
> — Every graphics programmer, ever.

---

**Star if you’re building the future of declarative UIs in C++!**
