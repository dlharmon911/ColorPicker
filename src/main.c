#include <allegro5/allegro5.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_primitives.h>
#define ALLEGRO_COLOR_PICKER_IMPLEMENTATION
#include "al_color_picker.h"
#include <stdint.h>

typedef struct APP_INFO
{
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
	ALLEGRO_COLOR_PICKER* m_picker;
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

	al_set_new_display_flags(ALLEGRO_OPENGL|ALLEGRO_RESIZABLE|ALLEGRO_PROGRAMMABLE_PIPELINE|ALLEGRO_WINDOWED);
	app_info->m_display = al_create_display(800, 600);
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

	app_info->m_picker = al_create_color_picker(100.0f, 100.0f, 400.0f);
	if (!app_info->m_picker)
	{
		return -1;
	}

	al_color_picker_set_color(app_info->m_picker, al_map_rgb(102, 128, 51));

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

	if (app_info->m_event_queue)
	{
		al_destroy_event_queue(app_info->m_event_queue);
	}

	if (app_info->m_timer)
	{
		al_destroy_timer(app_info->m_timer);
	}

	if (app_info->m_display)
	{
		al_destroy_display(app_info->m_display);
	}
}

void loop(APP_INFO* app_info)
{
	al_start_timer(app_info->m_timer);

	while (app_info->m_running)
	{
		process_events(app_info);

		if (app_info->m_update)
		{
			update(app_info);
			app_info->m_update = false;
		}
		
		render(app_info);
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
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
		{
			al_acknowledge_resize(app_info->m_display);
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			if (event.mouse.button == 1)
			{
				if (al_color_picker_grab_wheel(app_info->m_picker, (float)event.mouse.x, (float)event.mouse.y, NULL))
				{
					mouse_dragging = true;
				}
			}
			// Handle mouse button down event here
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			if (event.mouse.button == 1)
			{
				al_color_picker_release_wheel(app_info->m_picker);
				mouse_dragging = false;
			}
			// Handle mouse button up event here
		} break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			if (mouse_dragging)
			{
				al_color_picker_move_wheel(app_info->m_picker, (float)event.mouse.x, (float)event.mouse.y, NULL);
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

void render(const APP_INFO* app_info)
{
	al_clear_to_color(al_map_rgb(192, 192, 255));
	al_color_picker_draw(app_info->m_picker, al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f));
	al_flip_display();
}
