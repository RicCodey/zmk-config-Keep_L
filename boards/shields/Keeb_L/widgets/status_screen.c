#include <zephyr/logging/log.h>
#include <lvgl.h>

#include <zmk/battery.h>
#include <zmk/keymap.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static lv_obj_t *layer_label;
static lv_obj_t *battery_label;

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);

    if (screen == NULL) {
        LOG_ERR("Failed to create status screen");
        return NULL;
    }

    layer_label = lv_label_create(screen);

    if (layer_label != NULL) {
        lv_obj_align(layer_label, LV_ALIGN_TOP_LEFT, 2, 0);
        lv_label_set_text(layer_label, "Layer 0");
    }

    battery_label = lv_label_create(screen);

    if (battery_label != NULL) {
        lv_obj_align(battery_label, LV_ALIGN_TOP_LEFT, 2, 14);
        lv_label_set_text(battery_label, "Batt --%");
    }

    return screen;
}