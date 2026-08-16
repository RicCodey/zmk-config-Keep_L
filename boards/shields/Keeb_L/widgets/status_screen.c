#include <zephyr/kernel.h>
#include <lvgl.h>

#include <zmk/battery.h>
#include <zmk/keymap.h>

static lv_obj_t *layer_label;
static lv_obj_t *battery_label;
static lv_style_t label_style;

static void update_status(lv_timer_t *timer) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    uint8_t battery = zmk_battery_state_of_charge();

    lv_label_set_text_fmt(layer_label, "Layer %d", layer);
    lv_label_set_text_fmt(battery_label, "Batt %d%%", battery);
}

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);

    lv_style_init(&label_style);
    lv_style_set_text_font(&label_style, &lv_font_montserrat_12);

    layer_label = lv_label_create(screen);
    lv_obj_add_style(layer_label, &label_style, 0);
    lv_obj_align(layer_label, LV_ALIGN_TOP_LEFT, 2, 2);
    lv_label_set_text(layer_label, "Layer 0");

    battery_label = lv_label_create(screen);
    lv_obj_add_style(battery_label, &label_style, 0);
    lv_obj_align(battery_label, LV_ALIGN_TOP_LEFT, 2, 17);
    lv_label_set_text(battery_label, "Batt --%");

    update_status(NULL);
    lv_timer_create(update_status, 5000, NULL);

    return screen;
}