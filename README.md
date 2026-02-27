# ImgPik - Screen Color Picker

A simple C-based tool that captures the color of a pixel at your cursor position and copies it as a HEX code.

## Features

- **Cross-platform**: Works on X11 and Wayland (Linux).

## Installation

### Prerequisites

**For X11**:
```bash
maim xdotool xclip
```

**For Wayland**:
```bash
grim slurp wl-clipboard
```

### Install ImgPik

Clone and install the tool:

```bash
git clone https://github.com/6z7y/colpik-c.git
cd colpik-c
make install
```

Run it with:
```bash
colpik
```

## Usage

1. Run `colpik`.
2. Click on the screen to select a pixel.
3. The HEX color code (e.g., `#FF0000`) is printed to the terminal.

### Optional — Copy to Clipboard

You can pipe the output to a clipboard tool:

**wayland**: `colpik | wl-copy`

**x11**: `colpik | xclip -selection clipboard`


## how it works
![Diagram](/diagram/diagram.png)


```

## Troubleshooting

### Common Issues

- **"Command not found" errors**:
  - Ensure dependencies are installed.
  - Verify with: `maim --version` (X11) or `grim --version` (Wayland).

- **Clipboard not working**:
  - X11: Install `xclip` (`sudo apt install xclip`).
  - Wayland: Install `wl-clipboard` (`sudo apt install wl-clipboard`).

- **Color not captured**:
  - Check your display server: `echo $XDG_SESSION_TYPE`.
  - Ensure `/tmp` has write permissions for `/tmp/imgpik.png`.

## FAQ

**Q: Does it work on Windows/macOS?**  
A: Currently supports Linux only (X11/Wayland).

**Q: How do I build without `make`?**  
A: Use:
```bash
cc main.c -o colpik -lm
```
