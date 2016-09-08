#include <pebble.h>
#include <pebble-events/pebble-events.h>

static Window *main_window;
static TextLayer *time_layer, *date_layer;
static GColor background_color, text_color;
static char date_format[12];

static void update_time()
{
	time_t temp = time(NULL);
	struct tm *tick_time = localtime(&temp);
	
	//Time
	static char t_buffer[8];
	strftime(t_buffer, sizeof(t_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
	text_layer_set_text(time_layer, t_buffer);
	
	//Date
	static char d_buffer[12];
	strftime(d_buffer, sizeof(d_buffer), date_format, tick_time);
	text_layer_set_text(date_layer, d_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
	update_time();
}

static void window_refresh()
{	
	//Update colors
	window_set_background_color(main_window, background_color);
	text_layer_set_text_color(time_layer, text_color);
	
	update_time();
}

static void main_window_load(Window *window)
{
	//Set root layer and bounds
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	
	//Create layers and set properties
	time_layer = text_layer_create(GRect(0, bounds.size.h / 2 - 44, bounds.size.w, 44));
	text_layer_set_background_color(time_layer, GColorClear);
	text_layer_set_text_color(time_layer, GColorBlack);
	text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
	
	date_layer = text_layer_create(GRect(0, bounds.size.h / 2 + 4, bounds.size.w, 26));
	text_layer_set_background_color(date_layer, GColorClear);
	text_layer_set_text_color(date_layer, GColorBlack);
	text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
	
	//Add layers to root layer
	layer_add_child(window_layer, text_layer_get_layer(time_layer));
	layer_add_child(window_layer, text_layer_get_layer(date_layer));
}

static void main_window_unload(Window *window)
{
	//Destroy time layer
	text_layer_destroy(time_layer);
	text_layer_destroy(date_layer);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context)
{
	Tuple *data = dict_find(iterator, MESSAGE_KEY_back);
	if(data)
	{
		int value = data->value->uint32;
		background_color = GColorFromHEX(value);
	}
	
	data = dict_find(iterator, MESSAGE_KEY_text);
	if(data)
	{
		int value = data->value->uint32;
		text_color = GColorFromHEX(value);
	}
	
	data = dict_find(iterator, MESSAGE_KEY_date_show);
	if(data)
	{
		if(data->value->int32 == 1)
		{
			layer_set_hidden(text_layer_get_layer(date_layer), false);
		}
		else
		{
			layer_set_hidden(text_layer_get_layer(date_layer), true);
		}
	}
	
	data = dict_find(iterator, MESSAGE_KEY_date_format);
	if(data)
	{
		strcpy(date_format, data->value->cstring);
	}
	
	window_refresh();
}

static void inbox_dropped_callback(AppMessageResult reason, void *context)
{
	APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context)
{
	APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context)
{
	APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void init()
{
	//Set default date format
	strcpy(date_format, "%Y-%m-%d");
	
	//Create main window, set handlers and push to stack
	main_window = window_create();
	window_set_window_handlers(main_window, (WindowHandlers) {.load = main_window_load, .unload = main_window_unload});
	window_stack_push(main_window, true);
	
	//Register tick handler
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	update_time();
	
	//Setup and open appmessage
	events_app_message_request_inbox_size(1024);
	events_app_message_register_inbox_received(inbox_received_callback, NULL);
	events_app_message_register_inbox_dropped(inbox_dropped_callback, NULL);
	events_app_message_register_outbox_failed(outbox_failed_callback, NULL);
	events_app_message_register_outbox_sent(outbox_sent_callback, NULL);
	events_app_message_open();
}

static void deinit()
{
	//Destroy main window
	window_destroy(main_window);
}

int main(void)
{
	init();
	app_event_loop();
	deinit();
}