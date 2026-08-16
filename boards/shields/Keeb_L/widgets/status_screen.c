#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <lvgl.h>

#include <zmk/battery.h>
#include <zmk/keymap.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static lv_obj_t *layer_label;
static lv_obj_t *battery_label;

static void update_status(lv_timer_t *timer) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    uint8_t battery = zmk_battery_state_of_charge();

    if (layer_label != NULL) {
        lv_label_set_text_fmt(layer_label, "Layer %d", layer);
    }

    if (battery_label != NULL) {
        lv_label_set_text_fmt(battery_label, "Batt %d%%", battery);
    }
}

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);
    if (screen == NULL) {
        LOG_ERR("status_screen: failed to create screen object");
        return NULL;
    }

    layer_label = lv_label_create(screen);
    if (layer_label == NULL) {
        LOG_ERR("status_screen: failed to create layer label");
    } else {
        lv_obj_set_style_text_font(layer_label, &lv_font_montserrat_12, 0);
        lv_obj_align(layer_label, LV_ALIGN_TOP_LEFT, 2, 2);
        lv_label_set_text(layer_label, "Layer 0");
    }

    battery_label = lv_label_create(screen);
    if (battery_label == NULL) {
        LOG_ERR("status_screen: failed to create battery label");
    } else {
        lv_obj_set_style_text_font(battery_label, &lv_font_montserrat_12, 0);
        lv_obj_align(battery_label, LV_ALIGN_TOP_LEFT, 2, 17);
        lv_label_set_text(battery_label, "Batt --%");
    }

    update_status(NULL);

    lv_timer_create(update_status, 5000, NULL);

    return screen;
}