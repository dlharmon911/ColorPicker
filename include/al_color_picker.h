#ifndef _SHADER_COLOR_PICKER_H
#define _SHADER_COLOR_PICKER_H

/**
 * @file al_color_picker.h
 * @brief Header-only HSV color picker addon for Allegro 5 with embedded GLSL shaders.
 * 
 * This is a header-only library. To use it:
 * 1. Include this header wherever you need the API declarations
 * 2. In exactly ONE C/C++ file, define ALLEGRO_COLOR_PICKER_IMPLEMENTATION before including:
 *    #define ALLEGRO_COLOR_PICKER_IMPLEMENTATION
 *    #include "al_color_picker.h"
 * 
 * The shaders are embedded directly - no external shader files required.
 */

#include <allegro5/allegro5.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief A color picker addon for Allegro 5.
*/
typedef struct ALLEGRO_COLOR_PICKER ALLEGRO_COLOR_PICKER;

/**
* @brief Initializes the color picker addon. Must be called before using any other functions in this addon.
*        Compiles the embedded GLSL shaders and initializes the primitives addon.
* @param None.
* @return true if the addon was initialized successfully, false otherwise.
* @note The shaders are embedded directly in the header files - no external files required.
*/
bool al_init_color_picker();

/**
* @brief Checks if the color picker addon is initialized.
* @param None.
* @return true if the addon is initialized, false otherwise.
*/
bool al_is_color_picker_initialized();

/**
* @brief Shuts down the color picker addon and releases any resources it was using.
* @param None.
* @return None.
*/
void al_shutdown_color_picker();

/**
* @brief Creates a new color picker instance at the specified position and size.
* @param x The x-coordinate of the top-left corner of the color picker.
* @param y The y-coordinate of the top-left corner of the color picker.
* @param size The size of the color picker (width and height).
* @return A pointer to the newly created color picker instance, or NULL if creation failed.
*/
ALLEGRO_COLOR_PICKER* al_create_color_picker(float x, float y, float size);

/**
* @brief Destroys a color picker instance and releases any resources it was using.
* @param picker A pointer to the color picker instance to destroy.
* @return None.
*/
void al_destroy_color_picker(ALLEGRO_COLOR_PICKER* picker);

/**
* @brief Sets the color of the color picker using RGB values.
* @param picker A pointer to the color picker instance.
* @param red The red component (0.0 to 1.0).
* @param green The green component (0.0 to 1.0).
* @param blue The blue component (0.0 to 1.0).
* @return None.
*/
void al_color_picker_set_rgb(ALLEGRO_COLOR_PICKER* picker, float red, float green, float blue);

/**
* @brief Gets the current color of the color picker as RGB values.
* @param picker A pointer to the color picker instance.
* @param red A pointer to store the red component.
* @param green A pointer to store the green component.
* @param blue A pointer to store the blue component.
* @return None.
*/
void al_color_picker_get_rgb(const ALLEGRO_COLOR_PICKER* picker, float* red, float* green, float* blue);

/**
* @brief Sets the color of the color picker using an ALLEGRO_COLOR.
* @param picker A pointer to the color picker instance.
* @param color The color to set.
* @return None.
*/
void al_color_picker_set_color(ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR color);

/**
* @brief Gets the current color of the color picker as an ALLEGRO_COLOR.
* @param picker A pointer to the color picker instance.
* @param color A pointer to store the color.
* @return None.
*/
void al_color_picker_get_color(const ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR* color);

/**
* @brief Sets the color of the color picker using HSV values.
* @param picker A pointer to the color picker instance.
* @param hue The hue component (0.0 to 360.0).
* @param saturation The saturation component (0.0 to 1.0).
* @param value The value component (0.0 to 1.0).
* @return None.
*/
void al_color_picker_set_hsv(ALLEGRO_COLOR_PICKER* picker, float hue, float saturation, float value);

/**
* @brief Gets the current color of the color picker as HSV values.
* @param picker A pointer to the color picker instance.
* @param hue A pointer to store the hue component.
* @param saturation A pointer to store the saturation component.
* @param value A pointer to store the value component.
* @return None.
*/
void al_color_picker_get_hsv(const ALLEGRO_COLOR_PICKER* picker, float* hue, float* saturation, float* value);

/**
* @brief Sets the hue component of the color picker.
* @param picker A pointer to the color picker instance.
* @param hue The hue component (0.0 to 360.0).
* @return None.
*/
void al_color_picker_set_hue(ALLEGRO_COLOR_PICKER* picker, float hue);

/**
* @brief Gets the current hue component of the color picker.
* @param picker A pointer to the color picker instance.
* @param hue A pointer to store the hue component.
* @return None.
*/
void al_color_picker_get_hue(const ALLEGRO_COLOR_PICKER* picker, float* hue);

/**
* @brief Sets the saturation component of the color picker.
* @param picker A pointer to the color picker instance.
* @param saturation The saturation component (0.0 to 1.0).
* @return None.
*/
void al_color_picker_set_saturation(ALLEGRO_COLOR_PICKER* picker, float saturation);

/**
* @brief Gets the current saturation component of the color picker.
* @param picker A pointer to the color picker instance.
* @param saturation A pointer to store the saturation component.
* @return None.
*/
void al_color_picker_get_saturation(const ALLEGRO_COLOR_PICKER* picker, float* saturation);

/**
* @brief Sets the value component of the color picker.
* @param picker A pointer to the color picker instance.
* @param value The value component (0.0 to 1.0).
* @return None.
*/
void al_color_picker_set_value(ALLEGRO_COLOR_PICKER* picker, float value);

/**
* @brief Gets the current value component of the color picker.
* @param picker A pointer to the color picker instance.
* @param value A pointer to store the value component.
* @return None.
*/
void al_color_picker_get_value(const ALLEGRO_COLOR_PICKER* picker, float* value);

/**
* @brief Sets the position of the color picker.
* @param picker A pointer to the color picker instance.
* @param x The x-coordinate of the top-left corner.
* @param y The y-coordinate of the top-left corner.
* @return None.
*/
void al_color_picker_set_position(ALLEGRO_COLOR_PICKER* picker, float x, float y);

/**
* @brief Gets the current position of the color picker.
* @param picker A pointer to the color picker instance.
* @param x A pointer to store the x-coordinate.
* @param y A pointer to store the y-coordinate.
* @return None.
*/
void al_color_picker_get_position(const ALLEGRO_COLOR_PICKER* picker, float* x, float* y);

/**
* @brief Sets the size of the color picker.
* @param picker A pointer to the color picker instance.
* @param size The size of the color picker (width and height).
* @return None.
*/
void al_color_picker_set_size(ALLEGRO_COLOR_PICKER* picker, float size);

/**
* @brief Gets the current size of the color picker.
* @param picker A pointer to the color picker instance.
* @param size A pointer to store the size.
* @return None.
*/
void al_color_picker_get_size(const ALLEGRO_COLOR_PICKER* picker, float* size);

/**
* @brief Draws the color picker at its current position.
* @param picker A pointer to the color picker instance.
* @param background The background color to use when drawing the picker.
* @return None.
*/
void al_color_picker_draw(const ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR background);

/**
* @brief Handles a mouse grab event on the color picker wheel or triangle.
* @param picker A pointer to the color picker instance.
* @param x The x-coordinate of the mouse position.
* @param y The y-coordinate of the mouse position.
* @param color A pointer to store the resulting color, or NULL.
* @return true if the grab was successful (inside the picker), false otherwise.
*/
bool al_color_picker_grab_wheel(ALLEGRO_COLOR_PICKER* picker, float x, float y, ALLEGRO_COLOR* color);

/**
* @brief Handles a mouse move event while grabbing the color picker wheel.
* @param picker A pointer to the color picker instance.
* @param x The x-coordinate of the mouse position.
* @param y The y-coordinate of the mouse position.
* @param color A pointer to store the resulting color, or NULL.
* @return None.
*/
void al_color_picker_move_wheel(ALLEGRO_COLOR_PICKER* picker, float x, float y, ALLEGRO_COLOR* color);

/**
* @brief Releases the grab on the color picker wheel.
* @param picker A pointer to the color picker instance.
* @return None.
*/
void al_color_picker_release_wheel(ALLEGRO_COLOR_PICKER* picker);

#ifdef __cplusplus
}
#endif

#ifdef ALLEGRO_COLOR_PICKER_IMPLEMENTATION

#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <math.h>
#include "al_color_picker.h"


static const char* _ALLEGRO_VERTEX_SHADER_SOURCE =
"#version 330 core\n"
"\n"
"in vec4 al_pos;\n"
"in vec4 al_color;\n"
"uniform mat4 al_projview_matrix;\n"
"out vec4 varying_color;\n"
"\n"
"void main()\n"
"{\n"
"    varying_color = al_color;\n"
"    gl_Position = al_projview_matrix * al_pos;\n"
"}\n";

static const char* _ALLEGRO_PIXEL_SHADER_SOURCE =
"#version 330 core\n"
"\n"
"in vec4 varying_color;\n"
"out vec4 gl_FragColor;\n"
"uniform vec2 u_p1;\n"
"uniform vec2 u_p2;\n"
"uniform vec2 u_p3;\n"
"uniform vec2 u_position;\n"
"uniform vec2 u_resolution;\n"
"uniform vec3 u_hsv;\n"
"\n"
"vec3 rgb_to_hsv(vec3 c)\n"
"{\n"
"    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);\n"
"    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));\n"
"    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));\n"
"\n"
"    float d = q.x - min(q.w, q.y);\n"
"    float e = 1.0e-10;\n"
"    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);\n"
"}\n"
"\n"
"vec3 hsv_to_rgb(vec3 c)\n"
"{\n"
"    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);\n"
"    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);\n"
"    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);\n"
"}\n"
"\n"
"vec3 hsl_to_rgb(float h, float s, float l) \n"
"{\n"
"    // 1. Calculate the base hue colors using a 6-segment wheel\n"
"    vec3 rgb = clamp(abs(mod(h * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0, 0.0, 1.0);\n"
"    \n"
"    // 2. Adjust for saturation and lightness\n"
"    // This formula blends the pure hue with the grayscale based on L and S\n"
"    return l + s * (rgb - 0.5) * (1.0 - abs(2.0 * l - 1.0));\n"
"}\n"
"\n"
"float rad_to_deg(float rad) \n"
"{\n"
"    return rad * 180.0 / 3.14159265;\n"
"}\n"
"\n"
"float deg_to_rad(float deg) \n"
"{\n"
"    return deg * 3.14159265 / 180.0;\n"
"}\n"
"\n"
"vec3 color_wheel(float angle)\n"
"{\n"
"    return hsv_to_rgb(vec3(angle, 1.0, 1.0));\n"
"}\n"
"\n"
"vec2 coordinates(vec2 p, vec2 p1, vec2 p2, vec2 p3)\n"
"{\n"
"    float dy13 = p3.y - p1.y;\n"
"    float dy12 = p2.y - p1.y;\n"
"    float dy1 = p.y - p1.y;\n"
"    float dx13 = p3.x - p1.x;\n"
"    float dx12 = p2.x - p1.x;\n"
"    float dx1 = p.x - p1.x;\n"
"\n"
"    float t = (dy13 - dy12)*dx1 - (dx13 - dx12)*dy1;\n"
"    float a = dx12*dy13 - dx13*dy12;\n"
"    float b = dx12*dy1  - dx1*dy12;\n"
"\n"
"    return vec2(t/a, b/t);\n"
"}\n"
"\n"
"vec2 inverseCoordinates(vec2 p1, vec2 p2, vec2 p3, float t1, float t2) \n"
"{\n"
"    vec2 dp12 = p2 - p1;\n"
"    vec2 dp13 = p3 - p1;\n"
"    vec2 p = p1;\n"
"    p += dp12 * t1;\n"
"    p += (dp13 - dp12) * (t1 * t2);\n"
"    return p;\n"
"}\n"
"\n"
"void main()\n"
"{\n"
"    vec4 color = varying_color;\n"
"    float innerRadius = 0.8;\n"
"    float outerRadius = 1.0;\n"
"    float edgeWidth = 0.01; // Smoothness factor\n"
"    vec2 fragCoord = gl_FragCoord.xy - u_position;\n"
"    vec2 uv = fragCoord.xy / u_resolution.xy;\n"
"    vec2 position = uv * 2.0 - 1.0; // Convert to range [-1, 1]\n"
"    float angle = atan(position.y, position.x);\n"
"    float hue_angle = u_hsv.x * 3.14159265 / 180.0;\n"
"    float d = length(position);\n"
"\n"
"    if (d > outerRadius) \n"
"    {\n"
"           gl_FragColor = varying_color;\n"
"           return;\n"
"    } \n"
"    else if (d >= innerRadius)\n"
"    {   \n"
"        float ring = smoothstep(innerRadius - edgeWidth, innerRadius, d) - \n"
"                     smoothstep(outerRadius, outerRadius + edgeWidth, d);\n"
"\n"
"        float a1 = rad_to_deg(angle);\n"
"        float a2 = rad_to_deg(hue_angle);\n"
"\n"
"        if (abs(a1 - a2) < 0.5) \n"
"        {\n"
"            if (abs(a1 - a2) < 0.25) \n"
"            {\n"
"                gl_FragColor = vec4(vec3(1.0), 1.0);\n"
"            } \n"
"            else \n"
"            {\n"
"                gl_FragColor = vec4(vec3(0.0), 1.0);\n"
"            }\n"
"        }\n"
"        else\n"
"        {\n"
"            gl_FragColor = vec4(color_wheel(angle / (2.0 * 3.14159265)) * ring, 1.0);\n"
"        }\n"
"    }\n"
"    else\n"
"    {\n"
"        vec2 t = coordinates(position, u_p1, u_p2, u_p3);\n"
"\n"
"        if (t.x < 0.0 || t.y < 0.0 || t.x > 1.0 || t.y > 1.0) \n"
"        {\n"
"           gl_FragColor = varying_color;\n"
"           return;\n"
"        }       \n"
"\n"
"        // Get the position of the selected saturation and value\n"
"        float sat = u_hsv.y;\n"
"        float val = u_hsv.z;\n"
"        vec2 indicatorPos = inverseCoordinates(u_p1, u_p2, u_p3, val, sat);\n"
"\n"
"        // Calculate distance from current fragment to indicator position\n"
"        float distToIndicator = length(position - indicatorPos);\n"
"\n"
"        // Draw black circle at the indicator position\n"
"        float circleInnerRadius = 0.035;\n"
"        float circleOuterRadius = 0.05;\n"
"\n"
"        if (distToIndicator < circleOuterRadius) \n"
"        {\n"
"            if (distToIndicator >= circleInnerRadius) \n"
"            {\n"
"                gl_FragColor = vec4(1.0);\n"
"                return;\n"
"            }\n"
"        }\n"
"\n"
"        vec3 hsv = vec3(hue_angle / (2.0 * 3.14159265), t.y, t.x);\n"
"        vec3 rgb = hsv_to_rgb(hsv);\n"
"\n"
"        gl_FragColor = vec4(rgb, 1.0);\n"
"    }\n"
"}\n";

static const float _ALLEGRO_PI_2 = 2.0f * (float)ALLEGRO_PI;
static const float _ALLEGRO_PICKER_PADDING = 40.0f;
static const float _ALLEGRO_ANGLE_STEP = 2.0f * (float)ALLEGRO_PI / 3.0f;

enum ALLEGRO_PICKER_STATE
{
	ALLEGRO_PICKER_IDLE = 0,
	ALLEGRO_PICKER_GRABBING_WHEEL = 1,
	ALLEGRO_PICKER_GRABBING_TRIANGLE = 2
};

typedef struct _ALLEGRO_VEC2
{
	float m_x;
	float m_y;
} _ALLEGRO_VEC2;

typedef struct _ALLEGRO_HSV
{
	float m_hue;
	float m_saturation;
	float m_value;
} _ALLEGRO_HSV;

typedef struct ALLEGRO_COLOR_PICKER
{
	_ALLEGRO_HSV m_hsv;
	_ALLEGRO_VEC2 m_points[3];
	_ALLEGRO_VEC2 m_pos;
	float m_size;
	int32_t m_state;
} ALLEGRO_COLOR_PICKER;

static ALLEGRO_SHADER* _shader = NULL;

static int32_t _al_init_picker_addon()
{
	if (_shader)
	{
		return 0;
	}

	if (!al_is_system_installed())
	{
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		return -1;
	}

	_shader = al_create_shader(ALLEGRO_SHADER_GLSL);

	if (!_shader)
	{
		return -1;
	}

	if (!al_attach_shader_source(_shader, ALLEGRO_VERTEX_SHADER, _ALLEGRO_VERTEX_SHADER_SOURCE))
	{
		return -1;
	}

	if (!al_attach_shader_source(_shader, ALLEGRO_PIXEL_SHADER, _ALLEGRO_PIXEL_SHADER_SOURCE))
	{
		return -1;
	}

	if (!al_build_shader(_shader))
	{
		return -1;
	}

	return 0;
}

bool al_init_color_picker()
{
	if (_al_init_picker_addon() != 0)
	{
		al_shutdown_color_picker();
		return false;
	}

	return true;
}

bool al_is_color_picker_initialized()
{
	return _shader != NULL;
}

void al_shutdown_color_picker()
{
	if (_shader)
	{
		al_destroy_shader(_shader);
		_shader = NULL;
	}
}

static void _al_color_coordinates(const _ALLEGRO_VEC2* p, const _ALLEGRO_VEC2* p1, const _ALLEGRO_VEC2* p2, const _ALLEGRO_VEC2* p3, _ALLEGRO_VEC2* out)
{
	float dy13 = p3->m_y - p1->m_y;
	float dy12 = p2->m_y - p1->m_y;
	float dy1 = p->m_y - p1->m_y;
	float dx13 = p3->m_x - p1->m_x;
	float dx12 = p2->m_x - p1->m_x;
	float dx1 = p->m_x - p1->m_x;

	float t = (dy13 - dy12) * dx1 - (dx13 - dx12) * dy1;
	float a = dx12 * dy13 - dx13 * dy12;
	float b = dx12 * dy1 - dx1 * dy12;

	out->m_x = t / a;
	out->m_y = b / t;
}

ALLEGRO_COLOR_PICKER* al_create_color_picker(float x, float y, float size)
{
	ALLEGRO_COLOR_PICKER* picker = (ALLEGRO_COLOR_PICKER*)al_malloc(sizeof(ALLEGRO_COLOR_PICKER));

	if (!picker)
	{
		return NULL;
	}

	picker->m_pos.m_x = x;
	picker->m_pos.m_y = y;
	picker->m_size = size;
	picker->m_state = ALLEGRO_PICKER_IDLE;

	ALLEGRO_COLOR color = { 0.4f, 0.5f, 0.2f, 1.0f };

	al_color_picker_set_rgb(picker, color.r, color.g, color.b);

	return picker;
}

void al_destroy_color_picker(ALLEGRO_COLOR_PICKER* picker)
{
	if (picker)
	{
		al_free(picker);
	}
}

static void _al_color_picker_reset_points(ALLEGRO_COLOR_PICKER* picker)
{
	if (!picker)
	{
		return;
	}
	float angle = picker->m_hsv.m_hue * _ALLEGRO_PI_2 / 360.0f;
	for (size_t i = 0; i < 3; ++i)
	{
		picker->m_points[i].m_x = cosf(angle) * 0.8f;
		picker->m_points[i].m_y = sinf(angle) * 0.8f;
		angle += _ALLEGRO_ANGLE_STEP;
	}
}

static void _al_color_picker_draw_hsv(const ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR background)
{
	ALLEGRO_SHADER* current_shader = al_get_current_shader();
	ALLEGRO_COLOR color = (ALLEGRO_COLOR){ 0.0f, 0.0f, 0.0f, 1.0f };

	if (!picker || !_shader)
	{
		return;
	}

	al_use_shader(NULL);
	al_color_hsv_to_rgb(picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value, &color.r, &color.g, &color.b);
	al_draw_filled_rectangle(picker->m_pos.m_x - _ALLEGRO_PICKER_PADDING, picker->m_pos.m_y - _ALLEGRO_PICKER_PADDING, picker->m_pos.m_x + picker->m_size + _ALLEGRO_PICKER_PADDING - 1.0f, picker->m_pos.m_y + picker->m_size + _ALLEGRO_PICKER_PADDING - 1.0f, color);

	al_use_shader(_shader);

	al_set_shader_float_vector("u_p1", 2, (float[]) { picker->m_points[1].m_x, picker->m_points[1].m_y }, 1);
	al_set_shader_float_vector("u_p2", 2, (float[]) { picker->m_points[2].m_x, picker->m_points[2].m_y }, 1);
	al_set_shader_float_vector("u_p3", 2, (float[]) { picker->m_points[0].m_x, picker->m_points[0].m_y }, 1);
	al_set_shader_float_vector("u_position", 2, (float[]) { picker->m_pos.m_x, picker->m_pos.m_y }, 1);
	al_set_shader_float_vector("u_resolution", 2, (float[]) { picker->m_size, picker->m_size }, 1);
	al_set_shader_float_vector("u_hsv", 3, (float[]) { picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value }, 1);

	al_draw_filled_rectangle(picker->m_pos.m_x, picker->m_pos.m_y, picker->m_pos.m_x + picker->m_size - 1.0f, picker->m_pos.m_y + picker->m_size - 1.0f, background);

	al_use_shader(current_shader);
}

void al_color_picker_draw(const ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR background)
{
	_al_color_picker_draw_hsv(picker, background);
}

void al_color_picker_set_hsv(ALLEGRO_COLOR_PICKER* picker, float hue, float saturation, float value)
{
	if (!picker)
	{
		return;
	}
	picker->m_hsv.m_hue = hue;
	picker->m_hsv.m_saturation = saturation;
	picker->m_hsv.m_value = value;

	_al_color_picker_reset_points(picker);
}

void al_color_picker_set_rgb(ALLEGRO_COLOR_PICKER* picker, float red, float green, float blue)
{
	if (!picker)
	{
		return;
	}

	float hue = 0.0f;
	float saturation = 0.0f;
	float value = 0.0f;

	al_color_rgb_to_hsv(red, green, blue, &hue, &saturation, &value);

	al_color_picker_set_hsv(picker, hue, saturation, value);

	_al_color_picker_reset_points(picker);
}


void al_color_picker_get_rgb(const ALLEGRO_COLOR_PICKER* picker, float* red, float* green, float* blue)
{
	if (!picker || !red || !green || !blue)
	{
		return;
	}

	al_color_hsv_to_rgb(picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value, red, green, blue);
}

void al_color_picker_set_color(ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR color)
{
	if (!picker)
	{
		return;
	}

	al_color_picker_set_rgb(picker, color.r, color.g, color.b);
}

void al_color_picker_get_color(const ALLEGRO_COLOR_PICKER* picker, ALLEGRO_COLOR* color)
{
	if (!picker || !color)
	{
		return;
	}
	al_color_hsv_to_rgb(picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value, &color->r, &color->g, &color->b);
	color->a = 1.0f;
}


void al_color_picker_get_hsv(const ALLEGRO_COLOR_PICKER* picker, float* hue, float* saturation, float* value)
{
	if (!picker || !hue || !saturation || !value)
	{
		return;
	}

	*hue = picker->m_hsv.m_hue;
	*saturation = picker->m_hsv.m_saturation;
	*value = picker->m_hsv.m_value;
}

void al_color_picker_set_hue(ALLEGRO_COLOR_PICKER* picker, float hue)
{
	if (!picker)
	{
		return;
	}

	picker->m_hsv.m_hue = hue;

	_al_color_picker_reset_points(picker);
}

void al_color_picker_get_hue(const ALLEGRO_COLOR_PICKER* picker, float* hue)
{
	if (!picker || !hue)
	{
		return;
	}
	*hue = picker->m_hsv.m_hue;
}

void al_color_picker_set_saturation(ALLEGRO_COLOR_PICKER* picker, float saturation)
{
	if (!picker)
	{
		return;
	}

	picker->m_hsv.m_saturation = saturation;
	_al_color_picker_reset_points(picker);
}

void al_color_picker_get_saturation(const ALLEGRO_COLOR_PICKER* picker, float* saturation)
{
	if (!picker || !saturation)
	{
		return;
	}
	*saturation = picker->m_hsv.m_saturation;
}

void al_color_picker_set_value(ALLEGRO_COLOR_PICKER* picker, float value)
{
	if (!picker)
	{
		return;
	}

	picker->m_hsv.m_value = value;
	_al_color_picker_reset_points(picker);
}

void al_color_picker_get_value(const ALLEGRO_COLOR_PICKER* picker, float* value)
{
	if (!picker || !value)
	{
		return;
	}
	*value = picker->m_hsv.m_value;
}

void al_color_picker_set_position(ALLEGRO_COLOR_PICKER* picker, float x, float y)
{
	if (!picker)
	{
		return;
	}

	picker->m_pos.m_x = x;
	picker->m_pos.m_y = y;
}

void al_color_picker_get_position(const ALLEGRO_COLOR_PICKER* picker, float* x, float* y)
{
	if (!picker || !x || !y)
	{
		return;
	}

	*x = picker->m_pos.m_x;
	*y = picker->m_pos.m_y;
}

void al_color_picker_set_size(ALLEGRO_COLOR_PICKER* picker, float size)
{
	if (!picker)
	{
		return;
	}
	picker->m_size = size;
}

void al_color_picker_get_size(const ALLEGRO_COLOR_PICKER* picker, float* size)
{
	if (!picker || !size)
	{
		return;
	}
	*size = picker->m_size;
}

bool al_color_picker_grab_wheel(ALLEGRO_COLOR_PICKER* picker, float x, float y, ALLEGRO_COLOR* color)
{
	bool rv = false;

	if (!picker || !_shader)
	{
		return color;
	}

	float px = x;
	float py = y;
	float cx = (picker->m_pos.m_x + picker->m_size * 0.5f);
	float cy = (picker->m_pos.m_y + picker->m_size * 0.5f);

	float distance = sqrtf((px - cx) * (px - cx) + (py - cy) * (py - cy)) / picker->m_size * 2.0f;

	if (distance > 1.0f)
	{
		rv = false;
	}
	else if (distance > 0.8f && distance <= 1.0f)
	{
		picker->m_hsv.m_hue = atan2f(cy - py, px - cx) * 360.0f / _ALLEGRO_PI_2;
		picker->m_state = ALLEGRO_PICKER_GRABBING_WHEEL;

		al_color_picker_set_hsv(picker, picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value);

		if (color)
		{
			al_color_hsv_to_rgb(picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value, &color->r, &color->g, &color->b);
		}

		rv = true;
	}
	else
	{
		px = (px - picker->m_pos.m_x) / picker->m_size * 2.0f - 1.0f;
		py = (1.0f - (py - picker->m_pos.m_y) / picker->m_size) * 2.0f - 1.0f;

		_ALLEGRO_VEC2 mouse_pos = { px, py };
		_ALLEGRO_VEC2 out = { 0.0f, 0.0f };

		_al_color_coordinates(&mouse_pos, &picker->m_points[1], &picker->m_points[2], &picker->m_points[0], &out);

		if (out.m_x >= 0.0f && out.m_x <= 1.0f && out.m_y >= 0.0f && out.m_y <= 1.0f)
		{
			picker->m_state = ALLEGRO_PICKER_GRABBING_TRIANGLE;

			al_color_picker_set_hsv(picker, picker->m_hsv.m_hue, out.m_y, out.m_x);

			if (color)
			{
				al_color_hsv_to_rgb(picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value, &color->r, &color->g, &color->b);
			}
			rv = true;
		}
	}

	return rv;
}

void al_color_picker_move_wheel(ALLEGRO_COLOR_PICKER* picker, float x, float y, ALLEGRO_COLOR* color)
{
	if (!picker || !_shader)
	{
		return;
	}

	float px = x;
	float py = y;
	float cx = (picker->m_pos.m_x + picker->m_size * 0.5f);
	float cy = (picker->m_pos.m_y + picker->m_size * 0.5f);

	if (picker->m_state == ALLEGRO_PICKER_GRABBING_WHEEL)
	{
		picker->m_hsv.m_hue = atan2f(cy - py, px - cx) * 360.0f / _ALLEGRO_PI_2;
	}

	else if (picker->m_state == ALLEGRO_PICKER_GRABBING_TRIANGLE)
	{
		px = (px - picker->m_pos.m_x) / picker->m_size * 2.0f - 1.0f;
		py = (1.0f - (py - picker->m_pos.m_y) / picker->m_size) * 2.0f - 1.0f;
		_ALLEGRO_VEC2 mouse_pos = { px, py };
		_ALLEGRO_VEC2 out = { 0.0f, 0.0f };
		_al_color_coordinates(&mouse_pos, &picker->m_points[1], &picker->m_points[2], &picker->m_points[0], &out);
		if (out.m_x >= 0.0f && out.m_x <= 1.0f && out.m_y >= 0.0f && out.m_y <= 1.0f)
		{
			picker->m_hsv.m_saturation = out.m_y;
			picker->m_hsv.m_value = out.m_x;
		}
	}

	al_color_picker_set_hsv(picker, picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value);

	if (color)
	{
		al_color_hsv_to_rgb(picker->m_hsv.m_hue, picker->m_hsv.m_saturation, picker->m_hsv.m_value, &color->r, &color->g, &color->b);
	}
}

void al_color_picker_release_wheel(ALLEGRO_COLOR_PICKER* picker)
{
	if (!picker || !_shader)
	{
		return;
	}

	picker->m_state = ALLEGRO_PICKER_IDLE;
}

#endif

#endif // !_SHADER_COLOR_PICKER_H
