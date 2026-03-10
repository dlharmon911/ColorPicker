# Allegro Color Picker API Reference

Complete API reference for the Allegro Color Picker addon.

## Table of Contents

- [Types](#types)
- [Initialization Functions](#initialization-functions)
- [Creation and Destruction](#creation-and-destruction)
- [Color Management](#color-management)
  - [RGB Functions](#rgb-functions)
  - [HSV Functions](#hsv-functions)
  - [ALLEGRO_COLOR Functions](#allegro_color-functions)
  - [Individual Component Functions](#individual-component-functions)
- [Position and Size](#position-and-size)
- [Rendering](#rendering)
- [Mouse Interaction](#mouse-interaction)

---

## Types

### ALLEGRO_COLOR_PICKER

```c
typedef struct ALLEGRO_COLOR_PICKER ALLEGRO_COLOR_PICKER;
```

Opaque structure representing a color picker instance. Contains the current HSV values, triangle points, position, size, and interaction state.

---

## Initialization Functions

### al_init_color_picker

```c
bool al_init_color_picker();
```

**Description:**  
Initializes the color picker addon. Must be called before using any other functions in this addon. This function initializes the primitives addon and loads the required shaders.

**Parameters:**  
None.

**Returns:**  
- `true` if the addon was initialized successfully
- `false` otherwise

**Example:**
```c
if (!al_init_color_picker()) {
    fprintf(stderr, "Failed to initialize color picker addon\n");
    return -1;
}
```

---

### al_is_color_picker_initialized

```c
bool al_is_color_picker_initialized();
```

**Description:**  
Checks if the color picker addon is initialized.

**Parameters:**  
None.

**Returns:**  
- `true` if the addon is initialized
- `false` otherwise

---

### al_shutdown_color_picker

```c
void al_shutdown_color_picker();
```

**Description:**  
Shuts down the color picker addon and releases any resources it was using, including destroying the shader program.

**Parameters:**  
None.

**Returns:**  
None.

---

## Creation and Destruction

### al_create_color_picker

```c
ALLEGRO_COLOR_PICKER* al_create_color_picker(float x, float y, float size);
```

**Description:**  
Creates a new color picker instance at the specified position and size. The picker is initialized with a default color.

**Parameters:**
- `x` - The x-coordinate of the top-left corner of the color picker
- `y` - The y-coordinate of the top-left corner of the color picker
- `size` - The size of the color picker (width and height)

**Returns:**  
A pointer to the newly created color picker instance, or `NULL` if creation failed.

**Example:**
```c
ALLEGRO_COLOR_PICKER* picker = al_create_color_picker(100.0f, 100.0f, 400.0f);
if (!picker) {
    fprintf(stderr, "Failed to create color picker\n");
}
```

---

### al_destroy_color_picker

```c
void al_destroy_color_picker(ALLEGRO_COLOR_PICKER* picker);
```

**Description:**  
Destroys a color picker instance and releases any resources it was using.

**Parameters:**
- `picker` - A pointer to the color picker instance to destroy

**Returns:**  
None.

---

## Color Management

### RGB Functions

#### al_color_picker_set_rgb

```c
void al_color_picker_set_rgb(ALLEGRO_COLOR_PICKER* picker, float red, float green, float blue);
```

**Description:**  
Sets the color of the color picker using RGB values. The values are internally converted to HSV.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `red` - The red component (0.0 to 1.0)
- `green` - The green component (0.0 to 1.0)
- `blue` - The blue component (0.0 to 1.0)

**Returns:**  
None.

**Example:**
```c
al_color_picker_set_rgb(picker, 1.0f, 0.5f, 0.0f); // Orange color
```

---

#### al_color_picker_get_rgb

```c
void al_color_picker_get_rgb(const ALLEGRO_COLOR_PICKER* picker, float* red, float* green, float* blue);
```

**Description:**  
Gets the current color of the color picker as RGB values.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `red` - A pointer to store the red component
- `green` - A pointer to store the green component
- `blue` - A pointer to store the blue component

**Returns:**  
None.

**Example:**
```c
float r, g, b;
al_color_picker_get_rgb(picker, &r, &g, &b);
printf("RGB: %.2f, %.2f, %.2f\n", r, g, b);
```

---

### HSV Functions

#### al_color_picker_set_hsv

```c
void al_color_picker_set_hsv(ALLEGRO_COLOR_PICKER* picker, float hue, float saturation, float value);
```

**Description:**  
Sets the color of the color picker using HSV values.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `hue` - The hue component (0.0 to 360.0 degrees)
- `saturation` - The saturation component (0.0 to 1.0)
- `value` - The value/brightness component (0.0 to 1.0)

**Returns:**  
None.

**Example:**
```c
al_color_picker_set_hsv(picker, 120.0f, 1.0f, 1.0f); // Pure green
```

---

#### al_color_picker_get_hsv

```c
void al_color_picker_get_hsv(const ALLEGRO_COLOR_PICKER* picker, float* hue, float* saturation, float* value);
```

**Description:**  
Gets the current color of the color picker as HSV values.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `hue` - A pointer to store the hue component
- `saturation` - A pointer to store the saturation component
- `value` - A pointer to store the value component

**Returns:**  
None.

**Example:**
```c
float h, s, v;
al_color_picker_get_hsv(picker, &h, &s, &v);
printf("HSV: %.1f°, %.2f, %.2f\n", h, s, v);
```

---

### ALLEGRO_COLOR Functions

#### al_color_picker_set_color

```c
void al_color_picker_set_color(ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR color);
```

**Description:**  
Sets the color of the color picker using an `ALLEGRO_COLOR` structure.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `color` - The color to set

**Returns:**  
None.

**Example:**
```c
ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
al_color_picker_set_color(picker, red);
```

---

#### al_color_picker_get_color

```c
void al_color_picker_get_color(const ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR* color);
```

**Description:**  
Gets the current color of the color picker as an `ALLEGRO_COLOR` structure.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `color` - A pointer to store the color

**Returns:**  
None.

**Example:**
```c
ALLEGRO_COLOR current_color;
al_color_picker_get_color(picker, &current_color);
al_draw_filled_circle(50, 50, 25, current_color);
```

---

### Individual Component Functions

#### al_color_picker_set_hue

```c
void al_color_picker_set_hue(ALLEGRO_COLOR_PICKER* picker, float hue);
```

**Description:**  
Sets the hue component of the color picker without changing saturation or value.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `hue` - The hue component (0.0 to 360.0 degrees)

**Returns:**  
None.

---

#### al_color_picker_get_hue

```c
void al_color_picker_get_hue(const ALLEGRO_COLOR_PICKER* picker, float* hue);
```

**Description:**  
Gets the current hue component of the color picker.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `hue` - A pointer to store the hue component

**Returns:**  
None.

---

#### al_color_picker_set_saturation

```c
void al_color_picker_set_saturation(ALLEGRO_COLOR_PICKER* picker, float saturation);
```

**Description:**  
Sets the saturation component of the color picker without changing hue or value.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `saturation` - The saturation component (0.0 to 1.0)

**Returns:**  
None.

---

#### al_color_picker_get_saturation

```c
void al_color_picker_get_saturation(const ALLEGRO_COLOR_PICKER* picker, float* saturation);
```

**Description:**  
Gets the current saturation component of the color picker.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `saturation` - A pointer to store the saturation component

**Returns:**  
None.

---

#### al_color_picker_set_value

```c
void al_color_picker_set_value(ALLEGRO_COLOR_PICKER* picker, float value);
```

**Description:**  
Sets the value (brightness) component of the color picker without changing hue or saturation.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `value` - The value component (0.0 to 1.0)

**Returns:**  
None.

---

#### al_color_picker_get_value

```c
void al_color_picker_get_value(const ALLEGRO_COLOR_PICKER* picker, float* value);
```

**Description:**  
Gets the current value component of the color picker.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `value` - A pointer to store the value component

**Returns:**  
None.

---

## Position and Size

### al_color_picker_set_position

```c
void al_color_picker_set_position(ALLEGRO_COLOR_PICKER* picker, float x, float y);
```

**Description:**  
Sets the position of the color picker on the screen.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `x` - The x-coordinate of the top-left corner
- `y` - The y-coordinate of the top-left corner

**Returns:**  
None.

---

### al_color_picker_get_position

```c
void al_color_picker_get_position(const ALLEGRO_COLOR_PICKER* picker, float* x, float* y);
```

**Description:**  
Gets the current position of the color picker.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `x` - A pointer to store the x-coordinate
- `y` - A pointer to store the y-coordinate

**Returns:**  
None.

---

### al_color_picker_set_size

```c
void al_color_picker_set_size(ALLEGRO_COLOR_PICKER* picker, float size);
```

**Description:**  
Sets the size of the color picker. The size represents both width and height (square).

**Parameters:**
- `picker` - A pointer to the color picker instance
- `size` - The size of the color picker (width and height)

**Returns:**  
None.

---

### al_color_picker_get_size

```c
void al_color_picker_get_size(const ALLEGRO_COLOR_PICKER* picker, float* size);
```

**Description:**  
Gets the current size of the color picker.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `size` - A pointer to store the size

**Returns:**  
None.

---

## Rendering

### al_color_picker_draw

```c
void al_color_picker_draw(const ALLEGRO_COLOR_PICKER* picker);
```

**Description:**  
Draws the color picker at its current position using the shader-based rendering system. This should be called during your main render loop.

**Parameters:**
- `picker` - A pointer to the color picker instance

**Returns:**  
None.

**Notes:**
- The function temporarily switches shaders and restores the previous shader state after rendering
- A background color rectangle is drawn behind the picker with padding

---

## Mouse Interaction

### al_color_picker_grab_wheel

```c
bool al_color_picker_grab_wheel(ALLEGRO_COLOR_PICKER* picker, float x, float y, ALLEGRO_COLOR* color);
```

**Description:**  
Handles a mouse grab event on the color picker. Detects whether the click is on the color wheel (outer ring) or the triangle (inner area) and updates the color accordingly. Call this when the user presses the mouse button.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `x` - The x-coordinate of the mouse position
- `y` - The y-coordinate of the mouse position
- `color` - A pointer to store the resulting color, or `NULL` if not needed

**Returns:**
- `true` if the grab was successful (the click was inside the picker)
- `false` if the click was outside the picker

**Notes:**
- Updates the picker's internal state to track which component is being grabbed
- If the click is on the wheel (radius 0.8-1.0), only the hue is updated
- If the click is in the triangle, saturation and value are updated

**Example:**
```c
if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
    ALLEGRO_COLOR color;
    if (al_color_picker_grab_wheel(picker, event.mouse.x, event.mouse.y, &color)) {
        // User clicked inside the picker
        dragging = true;
    }
}
```

---

### al_color_picker_move_wheel

```c
void al_color_picker_move_wheel(ALLEGRO_COLOR_PICKER* picker, float x, float y, ALLEGRO_COLOR* color);
```

**Description:**  
Handles a mouse move event while grabbing the color picker. Updates the appropriate color component(s) based on which part of the picker was originally grabbed (wheel or triangle). Call this during mouse drag events.

**Parameters:**
- `picker` - A pointer to the color picker instance
- `x` - The x-coordinate of the mouse position
- `y` - The y-coordinate of the mouse position
- `color` - A pointer to store the resulting color, or `NULL` if not needed

**Returns:**  
None.

**Notes:**
- Only updates the color if the picker is in a grabbing state
- If grabbing the wheel, updates hue based on the angle
- If grabbing the triangle, updates saturation and value based on position within the triangle

**Example:**
```c
if (event.type == ALLEGRO_EVENT_MOUSE_AXES && dragging) {
    ALLEGRO_COLOR color;
    al_color_picker_move_wheel(picker, event.mouse.x, event.mouse.y, &color);
    // Use the updated color
}
```

---

### al_color_picker_release_wheel

```c
void al_color_picker_release_wheel(ALLEGRO_COLOR_PICKER* picker);
```

**Description:**  
Releases the grab on the color picker. Call this when the user releases the mouse button to end the drag operation.

**Parameters:**
- `picker` - A pointer to the color picker instance

**Returns:**  
None.

**Example:**
```c
if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
    al_color_picker_release_wheel(picker);
    dragging = false;
}
```

---

## Complete Mouse Interaction Example

```c
bool dragging = false;
ALLEGRO_COLOR selected_color = al_map_rgb(255, 0, 0);

while (running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);
    
    switch (event.type) {
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            if (al_color_picker_grab_wheel(picker, event.mouse.x, event.mouse.y, &selected_color)) {
                dragging = true;
            }
            break;
            
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            al_color_picker_release_wheel(picker);
            dragging = false;
            break;
            
        case ALLEGRO_EVENT_MOUSE_AXES:
            if (dragging) {
                al_color_picker_move_wheel(picker, event.mouse.x, event.mouse.y, &selected_color);
            }
            break;
    }
    
    // Render
    al_clear_to_color(al_map_rgb(40, 40, 40));
    al_color_picker_draw(picker);
    
    // Show the selected color
    al_draw_filled_circle(700, 50, 30, selected_color);
    
    al_flip_display();
}
```

---

## Color Space Reference

### HSV Color Space

The color picker uses the HSV (Hue, Saturation, Value) color space:

- **Hue (H)**: The color type, measured in degrees from 0° to 360°
  - 0° = Red
  - 120° = Green
  - 240° = Blue
  - 360° = Red (wraps around)

- **Saturation (S)**: The intensity/purity of the color from 0.0 to 1.0
  - 0.0 = Gray (no color)
  - 1.0 = Pure color

- **Value (V)**: The brightness of the color from 0.0 to 1.0
  - 0.0 = Black
  - 1.0 = Maximum brightness

### Visual Layout

```
┌──────────────────────────────────┐
│                                  │
│     ╭─────────────────╮          │
│    ╱       ▲ V=1      ╲         │
│   │   ▲    │           │        │
│   │ S │    ●───► S=1   │        │
│   │   │   ╱            │        │
│    ╲  │  ╱  V=0       ╱         │
│     ╰─▼─────────────╯           │
│      ◀── Hue Ring ──▶            │
│                                  │
└──────────────────────────────────┘
```

---

## Notes

- All functions are safe to call with `NULL` pointers (they will return early)
- The color picker requires OpenGL 3.3+ and GLSL shader support
- Shader files must be present in `shaders/` directory relative to the executable
- The picker includes a 40-pixel padding around its boundaries for the background color display
