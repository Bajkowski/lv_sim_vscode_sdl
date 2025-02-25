/**
 * @file my_main.h
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"

// Global objects
lv_obj_t * base_screen;
lv_obj_t * meter;


// Main draw functions
void start_ui();
void draw_screen();
void draw_main_widgets();
void draw_clock();

// Button handlers
void btn_event_cb(lv_event_t * e);
void set_value(void * indic, int32_t v);
