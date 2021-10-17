#include "my_main.h"
/*************************************************************************************
 * 
 * Main draw functions
 * 
 * **********************************************************************************/
void start_ui() {
    draw_screen();
    draw_main_widgets();
}

void draw_screen() {
    base_screen = lv_obj_create(NULL);
    lv_scr_load(base_screen);
    lv_obj_set_style_bg_color(base_screen, lv_color_black(), 0);
}

void draw_main_widgets() {
    lv_obj_t * btn = lv_btn_create(base_screen);     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);

    draw_clock();
}

void draw_clock () {
    meter = lv_meter_create(lv_scr_act());
    lv_obj_set_size(meter, 220, 220);
    lv_obj_center(meter);

    /*Create a scale for the minutes*/
    /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    lv_meter_scale_t * scale_min = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_min, 61, 1, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_range(meter, scale_min, 0, 60, 360, 270);

    /*Create an other scale for the hours. It's only visual and contains only major ticks*/
    lv_meter_scale_t * scale_hour = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
    lv_meter_set_scale_major_ticks(meter, scale_hour, 1, 2, 20, lv_color_black(), 10);    /*Every tick is major*/
    lv_meter_set_scale_range(meter, scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/

    LV_IMG_DECLARE(img_hand)

    /*Add a the hands from images*/
    lv_meter_indicator_t * indic_min = lv_meter_add_needle_img(meter, scale_min, &img_hand, 5, 5);
    lv_meter_indicator_t * indic_hour = lv_meter_add_needle_img(meter, scale_min, &img_hand, 5, 5);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 60);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_time(&a, 2000);     /*2 sec for 1 turn of the minute hand (1 hour)*/
    lv_anim_set_var(&a, indic_min);
    lv_anim_start(&a);

    lv_anim_set_var(&a, indic_hour);
    lv_anim_set_time(&a, 24000);    /*24 sec for 1 turn of the hour hand*/
    lv_anim_set_values(&a, 0, 60);
    lv_anim_start(&a);
}

/*************************************************************************************
 * 
 * Button Handlers
 * 
 * **********************************************************************************/
void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}
