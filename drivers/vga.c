#include "vga.h"
#include <dos.h>
#include <stdint.h>
#include <stdio.h>

void vga_set_mode(uint8_t mode) {

    _asm {
        mov ah, 0x00     // Set mode function
        mov al, mode     // Set video mode
        int 0x10
    }
}

void vga_vertical_sync() {
    _asm {
        mov dx, 0x03DA   // VGA Input Status Register 1
    wait_retrace:
        in al, dx        // Read status register into AL
        and al, 0x08     // Check vertical retrace
        jnz wait_retrace // Loop until retrace ends
    }
}

void vga_set_palette_mask(uint8_t mask) {
    _asm {
        mov dx, 0x03C6   // Palette Mask register
        mov al, mask     // Set mask as an 8-bit value in AL
        out dx, al
    }
}

void vga_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    _asm {
        
        mov dx, 0x03C8   // Write Color Index
        mov al, index    // Set color index
        out dx, al
        
        mov dx, 0x03C9   // RGB Data register
        mov al, r        // Set red value (0-63)
        out dx, al
        mov al, g        // Set green value (0-63)
        out dx, al
        mov al, b        // Set blue value (0-63)
        out dx, al
    }
}

void vga_get_color(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b) {
    _asm {
        mov dx, 0x03C7   // Read Color Index
        mov al, index    // Set color index
        out dx, al

        mov dx, 0x03C9   // RGB Data register
        in al, dx
        mov byte ptr [r], al
        in al, dx
        mov byte ptr [g], al
        in al, dx
        mov byte ptr [b], al
    }
}

uint8_t far *vga_get_address() {
    return (uint8_t far *) 0xA0000000; // Return far pointer to VGA video memory
}
