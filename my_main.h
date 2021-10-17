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

// Main draw functions
void start_ui();
void draw_screen();
void draw_main_widgets();

// Button handlers
void btn_event_cb(lv_event_t * e);
