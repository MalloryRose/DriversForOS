#include "mouse.h"
#include <dos.h> // For BIOS calls in real-mode

int mouse_reset() {
    unsigned short status;
    _asm {
        mov ax, 0x00     // Reset function
        int 0x33         // Mouse interrupt
        mov status, ax   // Save mouse availability in status
    }
    return (status == 0xFFFF); // Mouse available if AX == 0xFFFF
}

int mouse_get_button_presses(int16_t button) {
    unsigned short presses;
    _asm {
        mov ax, 0x05     // Get button presses
        mov bx, button   // Set button number
        int 0x33
        mov presses, bx  // Store press count
    }
    return presses;
}

int mouse_get_button_releases(int16_t button) {
    unsigned short releases;
    _asm {
        mov ax, 0x06     // Get button releases
        mov bx, button   // Set button number
        int 0x33
        mov releases, bx // Store release count
    }
    return releases;
}

void mouse_get_mickeys(int16_t *mickeys_x, int16_t *mickeys_y) {
    int16_t temp_cx, temp_dx;

    _asm {
        mov ax, 0x0B         // Function to get mickey counts
        int 0x33             // Mouse interrupt
        mov temp_cx, cx      // Store horizontal mickey count in temp variable
        mov temp_dx, dx      // Store vertical mickey count in temp variable
    }

    *mickeys_x += temp_cx;
    *mickeys_y += temp_dx;
}

void mouse_calculate_pos(int16_t* value, int16_t* mickeys, int16_t rate) {

    *value += *mickeys / rate; // Update position by integer division
    *mickeys = *mickeys % rate; // Keep the remainder in mickeys for next calculation
}


void mouse_show_cursor() {
    _asm {
        mov ax, 0x01     // Show cursor
        int 0x33
    }
}

void mouse_hide_cursor() {
    _asm {
        mov ax, 0x02     // Hide cursor
        int 0x33
    }
}

void mouse_set_limits_x(int16_t minimum, int16_t maximum) {
    _asm {
        mov ax, 0x07     // Set X limits
        mov cx, minimum
        mov dx, maximum
        int 0x33
    }
}

void mouse_set_limits_y(int16_t minimum, int16_t maximum) {
    _asm {
        mov ax, 0x08     // Set Y limits
        mov cx, minimum
        mov dx, maximum
        int 0x33
    }
}

void mouse_set_position(int16_t x, int16_t y) {
    _asm {
        mov ax, 0x04     // Set position
        mov cx, x
        mov dx, y
        int 0x33
    }
}

void mouse_get_state(struct mouse_state* state) {
    unsigned short button_status;
    unsigned short pos_x, pos_y;

    _asm {
        mov ax, 0x03          // Get cursor/button state
        int 0x33
        mov pos_x, cx         // Store X position in pos_x
        mov pos_y, dx         // Store Y position in pos_y
        mov button_status, bx // Store button status in button_status
    }
    
    state->x = pos_x;
    state->y = pos_y;
    state->left = (button_status & 1) != 0;
    state->right = (button_status & 2) != 0;
    state->middle = (button_status & 4) != 0;
}


void mouse_set_movement_rate(int16_t rate_x, int16_t rate_y) {
    int16_t temp_x = rate_x * 8;
    int16_t temp_y = rate_y * 8;

    _asm {
        mov ax, 0x0F     // Set mickeys/coord rate
        mov cx, temp_x
        mov dx, temp_y
        int 0x33
    }
}

void mouse_set_sensitivity(int16_t level_x, int16_t level_y) {
    _asm {
        mov ax, 0x1A     // Set sensitivity level
        mov bx, level_x
        mov cx, level_y
        int 0x33
        
    }
}

void mouse_get_sensitivity(int16_t *level_x, int16_t *level_y) {
    int16_t temp_bx, temp_cx;

    _asm {
        mov ax, 0x1B        
        int 0x33             
        mov temp_bx, bx    
        mov temp_cx, cx  
           
    }

    *level_x = temp_bx;
    *level_y = temp_cx;
    
}
