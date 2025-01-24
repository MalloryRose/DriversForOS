#ifndef MOUSE_H
#define MOUSE_H

#include <stdint.h>

struct mouse_state {
    int left;      // Use int instead of bool for compatibility
    int right;
    int middle;
    int16_t x;
    int16_t y;
};



// Hardware Polling
int mouse_reset();
int mouse_get_button_presses(int16_t button);
int mouse_get_button_releases(int16_t button);
void mouse_get_mickeys(int16_t *mickeys_x, int16_t *mickeys_y);
void mouse_calculate_pos(int16_t* value, int16_t* mickeys, int16_t rate);

// BIOS State
void mouse_show_cursor();
void mouse_hide_cursor();
void mouse_set_limits_x(int16_t minimum, int16_t maximum);
void mouse_set_limits_y(int16_t minimum, int16_t maximum);
void mouse_set_position(int16_t x, int16_t y);
void mouse_get_state(struct mouse_state* state);
void mouse_set_movement_rate(int16_t rate_x, int16_t rate_y);
void mouse_set_sensitivity(int16_t level_x, int16_t level_y);
void mouse_get_sensitivity(int16_t *level_x, int16_t *level_y);

#endif // MOUSE_H
