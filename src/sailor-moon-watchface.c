//forever sailor moon trash -Connie

#include <pebble.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static Window *window;				//creating the pointer to the main window
static TextLayer *time_layer;		//pointer to text layer that will display time
static BitmapLayer *symbol_layer;	//pointer to bitmap layer for planet symbols
static GBitmap *symbol_bitmap;		//pointer to gbitmap layer for planet symbols


static void window_load(Window *window) {}


static void window_unload(Window *window) {
	bitmap_layer_destroy(symbol_layer);
	gbitmap_destroy(symbol_bitmap);
	bitmap_layer_destroy(symbol_layer);
	text_layer_destroy(time_layer);
  	
}

static void update_time() {
  
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  static char buffer[] = "00:00";
  
  if(clock_is_24h_style() == true) {
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else { 
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  text_layer_set_text(time_layer, buffer);
}

static void update_sailorscout_symbol(struct tm *current_time){


    Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

	time_layer = text_layer_create(GRect(0, 120, bounds.size.w, 50));
    text_layer_set_background_color(time_layer, GColorBlack);
    text_layer_set_text_color(time_layer, GColorWhite);
    text_layer_set_text(time_layer, "00:00");
    GFont custom_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_CRAFTY_GIRLS_30));
    text_layer_set_font(time_layer, custom_font);
    text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
    

	int dayOfTheWeek = current_time->tm_wday;
    
		if(dayOfTheWeek==0){	//Sunday
			
			int random_number = rand()%3;	//generates random index to pick Outer Sailor Scout for Sunday

			if(random_number==0){
				symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PLUTO);
			} else if (random_number==1){
				symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_URANUS);
			} else if (random_number==2){
				symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_NEPTUNE);
			}

		} else if (dayOfTheWeek==1){	//Monday
			symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MOON);
		} else if (dayOfTheWeek==2){	//Tuesday
			symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MARS);
		}else if (dayOfTheWeek==3){		//Wednesday
			symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MERCURY);
		}else if (dayOfTheWeek==4){		//Thursday
			symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_JUPITER);
		}else if (dayOfTheWeek==5){		//Friday
			symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_VENUS);
		}else if (dayOfTheWeek==6){		//Saturday
			symbol_bitmap = gbitmap_create_with_resource(RESOURCE_ID_SATURN);		
		}

	symbol_layer = bitmap_layer_create(GRect(0, 25, bounds.size.w, 90));
    bitmap_layer_set_background_color(symbol_layer, GColorBlack);
    bitmap_layer_set_compositing_mode(symbol_layer, GCompOpSet);
    bitmap_layer_set_bitmap(symbol_layer, symbol_bitmap);
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(symbol_layer));
    window_set_background_color(window, GColorBlack); 

}


static void init(void) {
  window = window_create();

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  
  time_t updateTime = time(NULL); 
  struct tm *sailor_moon_time = localtime(&updateTime);
  
  update_sailorscout_symbol(sailor_moon_time);
  
  window_stack_push(window, true);
  
  update_time();
  
}

static void deinit(void) {
  text_layer_destroy(time_layer);
  window_destroy(window);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}


int main(void) {
  init();
  app_event_loop();
  deinit();
}
