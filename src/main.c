#include <allegro5/allegro5.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#define ALLEGRO_COLOR_PICKER_IMPLEMENTATION
#include "al_color_picker.h"
#include <stdio.h>
#include <stdint.h>

static const float picker_x = 50.0f;
static const float picker_y = 50.0f;
static const float picker_size = 400.0f;
static const float PICKER_PADDING  = 40.0f;
static const float DISPLAY_WIDTH = 600.0f;
static const float DISPLAY_HEIGHT = 600.0f;
static const ALLEGRO_COLOR APP_BACKGROUND_COLOR = { 0.75294f, 0.75294f, 1.0f, 1.0f };
static const ALLEGRO_COLOR PICKER_BACKGROUND_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
static const ALLEGRO_COLOR TEXT_COLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
static const ALLEGRO_COLOR TEXT_SHADOW = { 1.0f, 1.0f, 1.0f, 1.0f };

typedef struct APP_INFO
{
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
	ALLEGRO_COLOR_PICKER* m_picker;
	ALLEGRO_FONT* m_font;
	ALLEGRO_COLOR m_color;
	double m_time;
	bool m_update;
	bool m_running;
} APP_INFO;

int32_t init(APP_INFO* app_info);
void destroy(APP_INFO* app_info);
void loop(APP_INFO* app_info);
void process_events(APP_INFO* app_info);
void update(APP_INFO* app_info);
void render(const APP_INFO* app_info);

int main()
{
	APP_INFO app_info =
	{
		.m_display = NULL,
		.m_timer = NULL,
		.m_event_queue = NULL,
		.m_picker = NULL,
		.m_font = NULL,
		.m_color = { 1.0f, 0.5f, 0.0f, 1.0f },
		.m_time = 0.0,
		.m_update = false,
		.m_running = true
	};

	if (init(&app_info) == 0)
	{
		loop(&app_info);
	}

	destroy(&app_info);

	return 0;
}

int32_t init(APP_INFO* app_info)
{
	if (!app_info)
	{
		return -1;
	}

	if (!al_init())
	{
		return -1;
	}

	if (!al_init_font_addon())
	{
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		return -1;
	}

	if (!al_install_mouse())
	{
		return -1;
	}

	if (!al_install_keyboard())
	{
		return -1;
	}

	al_set_new_display_flags(ALLEGRO_OPENGL|ALLEGRO_PROGRAMMABLE_PIPELINE|ALLEGRO_WINDOWED);
	app_info->m_display = al_create_display((int32_t)DISPLAY_WIDTH, (int32_t)DISPLAY_HEIGHT);
	if (!app_info->m_display)
	{
		return -1;
	}

	app_info->m_timer = al_create_timer(1.0 / 60.0);
	if (!app_info->m_timer)
	{
		return -1;
	}

	app_info->m_event_queue = al_create_event_queue();
	if (!app_info->m_event_queue)
	{
		return -1;
	}

	al_register_event_source(app_info->m_event_queue, al_get_display_event_source(app_info->m_display));
	al_register_event_source(app_info->m_event_queue, al_get_timer_event_source(app_info->m_timer));
	al_register_event_source(app_info->m_event_queue, al_get_keyboard_event_source());
	al_register_event_source(app_info->m_event_queue, al_get_mouse_event_source());

	if (!al_init_color_picker())
	{
		return -1;
	}

	app_info->m_font = al_create_builtin_font();
	if (!app_info->m_font)
	{
		return -1;
	}

	app_info->m_picker = al_create_color_picker(picker_x, picker_y, picker_size);
	if (!app_info->m_picker)
	{
		return -1;
	}

	al_color_picker_set_color(app_info->m_picker, app_info->m_color);

	return 0;
}

void destroy(APP_INFO* app_info)
{
	if (!app_info)
	{
		return;
	}

	if (app_info->m_picker)
	{
		al_destroy_color_picker(app_info->m_picker);
	}

	al_shutdown_color_picker();

	if (app_info->m_font)
	{
		al_destroy_font(app_info->m_font);
		app_info->m_font = NULL;
	}

	if (app_info->m_event_queue)
	{
		al_destroy_event_queue(app_info->m_event_queue);
		app_info->m_event_queue = NULL;
	}

	if (app_info->m_timer)
	{
		al_destroy_timer(app_info->m_timer);
		app_info->m_timer = NULL;
	}

	if (app_info->m_display)
	{
		al_destroy_display(app_info->m_display);
		app_info->m_display = NULL;
	}
}

void loop(APP_INFO* app_info)
{
	al_start_timer(app_info->m_timer);

	while (app_info->m_running)
	{
		double current_time = al_get_time();

		process_events(app_info);

		if (app_info->m_update)
		{
			update(app_info);
			app_info->m_update = false;
		}
		
		render(app_info);

		app_info->m_time = al_get_time() - current_time;

		al_rest(0.01);
	}

	al_stop_timer(app_info->m_timer);
}

void process_events(APP_INFO* app_info)
{
	ALLEGRO_EVENT event;
	static bool mouse_dragging = false;

	while (!al_is_event_queue_empty(app_info->m_event_queue))
	{
		al_get_next_event(app_info->m_event_queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
		{
			app_info->m_update = true;
		} break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			app_info->m_running = false;
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			if (event.mouse.button == 1
				&& al_grab_color_picker(app_info->m_picker, (float)event.mouse.x, (float)event.mouse.y, &app_info->m_color))
			{
				mouse_dragging = true;
			}
			// Handle mouse button down event here
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			if (event.mouse.button == 1)
			{
				al_release_color_picker(app_info->m_picker);
				mouse_dragging = false;
			}
			// Handle mouse button up event here
		} break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			if (mouse_dragging)
			{
				al_drag_color_picker(app_info->m_picker, (float)event.mouse.x, (float)event.mouse.y, &app_info->m_color);
			}
			// Handle mouse movement event here
		} break;
		case ALLEGRO_EVENT_KEY_UP:
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				app_info->m_running = false;
			}
		} break;
		default: break;
		}
	}
}

void update(APP_INFO* app_info)
{
	// Update game logic here
}

static void draw_text(const ALLEGRO_FONT* font, float x, float y, const char* text)
{

	ALLEGRO_TRANSFORM current_transform;
	ALLEGRO_TRANSFORM text_transform;

	al_copy_transform(&current_transform, al_get_current_transform());

	al_identity_transform(&text_transform);
	al_scale_transform(&text_transform, 2.0f, 2.0f);
	al_translate_transform(&text_transform, x, y);
	al_use_transform(&text_transform);

	al_draw_text(font, TEXT_SHADOW, 1.0f, 1.0f, 0, text);
	al_draw_text(font, TEXT_COLOR, 0.0f, 0.0f, 0, text);

	al_use_transform(&current_transform);
}

static void draw_color_text(const APP_INFO* app_info, float x, float y)
{
	char text[64] = { 0 };
	float h[3] = { 0.0f, 0.0f, 0.0f };
	uint8_t c[3] = { 0, 0, 0 };

	al_color_picker_get_hsv(app_info->m_picker, &h[0], &h[1], &h[2]);
	al_unmap_rgb(app_info->m_color, &c[0], &c[1], &c[2]);

	sprintf_s(text, sizeof(text), "FPS: %.2f", 1.0 / app_info->m_time);
	draw_text(app_info->m_font, x, y, text);

	sprintf_s(text, sizeof(text), "RGB: #%02x%02x%02x", c[0], c[1], c[2]);
	draw_text(app_info->m_font, x, y + 20.0f, text);

	if (h[0] < 0.0f)
	{
		h[0] = 360.0f + h[0];
	}

	sprintf_s(text, sizeof(text), "HSV: %.1f %.2f %.2f", h[0], h[1], h[2]);
	draw_text(app_info->m_font, x, y + 40.0f, text);
}

void render(const APP_INFO* app_info)
{
	al_clear_to_color(APP_BACKGROUND_COLOR);

	al_draw_filled_rectangle(
		picker_x - PICKER_PADDING , 
		picker_y - PICKER_PADDING ,
		picker_x + picker_size + PICKER_PADDING  - 1.0f,
		picker_y + picker_size + PICKER_PADDING  - 1.0f,
		app_info->m_color);

	al_draw_color_picker(app_info->m_picker, PICKER_BACKGROUND_COLOR);

	draw_color_text(app_info, picker_x - PICKER_PADDING, picker_y + picker_size + PICKER_PADDING + 10.0f);

	al_flip_display();
}
