# Allegro Color Picker Addon

A shader-based HSV color picker addon for Allegro 5 that provides an intuitive circular color wheel with an embedded triangle for selecting saturation and value.

## Features

- **Circular Color Wheel**: Select hue from a 360° color wheel (radius 0.8 to 1.0)
- **HSV Triangle**: Select saturation and value within an embedded triangle
- **Visual Indicator**: Black circle indicator shows the current saturation/value position
- **Multiple Color Formats**: Support for RGB, HSV, and ALLEGRO_COLOR
- **Shader-Based Rendering**: Utilizes OpenGL shaders for smooth color gradients
- **Interactive**: Click and drag support for both the wheel and triangle
- **Header-Only Library**: Shaders are embedded directly - no external files needed

## Requirements

- Allegro 5
- Allegro Primitives addon
- Allegro Color addon
- Allegro OpenGL addon
- OpenGL 3.3+ (for GLSL shaders)

## Installation

This is a **header-only library** with embedded GLSL shaders.

1. Copy the header files to your project:
   - `include/al_color_picker.h`

2. In your code, define the implementation in **one** C/C++ file before including:
```c
#define ALLEGRO_COLOR_PICKER_IMPLEMENTATION
#include "al_color_picker.h"
```

3. In other files, simply include without the define:
```c
#include "al_color_picker.h"
```

**No external shader files required!** The shaders are embedded as string constants.

## Quick Start

```c
#include <allegro5/allegro5.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include "al_color_picker.h"

int main(int argc, char** argv)
{
    // Initialize Allegro
    al_init();
    al_install_mouse();
    
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    
    // Initialize the color picker addon
    if (!al_init_color_picker())
    {
        // Handle initialization error
        return -1;
    }
    
    // Create a color picker at position (100, 100) with size 400
    ALLEGRO_COLOR_PICKER* picker = al_create_color_picker(100.0f, 100.0f, 400.0f);
    
    bool running = true;
    bool dragging = false;
    ALLEGRO_COLOR selected_color = al_map_rgb(255, 0, 0);
    
    while (running)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (al_grab_color_picker(picker, event.mouse.x, event.mouse.y, &selected_color))
            {
                dragging = true;
            }
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            al_release_color_picker(picker);
            dragging = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES && dragging)
        {
            al_drag_color_picker(picker, event.mouse.x, event.mouse.y, &selected_color);
        }
        
        // Draw
        al_clear_to_color(al_map_rgb(50, 50, 50));
        al_draw_color_picker(picker);
        al_flip_display();
    }
    
    // Cleanup
    al_destroy_color_picker(picker);
    al_shutdown_color_picker();
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    
    return 0;
}
```

## Usage Overview

### Initialization

```c
// Initialize the addon
al_init_color_picker();

// Create a picker
ALLEGRO_COLOR_PICKER* picker = al_create_color_picker(x, y, size);
```

### Setting Colors

```c
// Using RGB
al_color_picker_set_rgb(picker, 1.0f, 0.0f, 0.0f);

// Using HSV
al_color_picker_set_hsv(picker, 120.0f, 0.8f, 0.9f);

// Using ALLEGRO_COLOR
ALLEGRO_COLOR color = al_map_rgb(255, 128, 64);
al_color_picker_set_color(picker, color);
```

### Getting Colors

```c
// Get as RGB
float r, g, b;
al_color_picker_get_rgb(picker, &r, &g, &b);

// Get as HSV
float h, s, v;
al_color_picker_get_hsv(picker, &h, &s, &v);

// Get as ALLEGRO_COLOR
ALLEGRO_COLOR color;
al_color_picker_get_color(picker, &color);
```

### Mouse Interaction

```c
// On mouse down
if (al_grab_color_picker(picker, mouse_x, mouse_y, &color))
{
    // Color was successfully grabbed
}

// While dragging
al_drag_color_picker(picker, mouse_x, mouse_y, &color);

// On mouse up
al_release_color_picker(picker);
```

### Rendering

```c
al_draw_color_picker(picker, ALLEGRO_COLOR background);
```

### Cleanup

```c
al_destroy_color_picker(picker);
al_shutdown_color_picker();
```

## Architecture

The color picker consists of:
- **Outer Ring (radius 0.8-1.0)**: Color wheel for selecting hue (0-360°)
- **Inner Triangle**: Saturation and value selector
  - Horizontal axis: Value (0.0-1.0)
  - Vertical axis: Saturation (0.0-1.0)
- **Visual Indicator**: Black circle with white border showing current saturation/value position

## License

This is an open-source addon for Allegro 5. See the license file for details.

## See Also

- [API Reference](api_reference.md)
- [Allegro 5 Documentation](https://liballeg.org/a5docs/trunk/)
