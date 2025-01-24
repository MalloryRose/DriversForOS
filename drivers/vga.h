#pragma once
#include <stdint.h>


// Video Configuration
void vga_set_mode(uint8_t mode);
void vga_vertical_sync();
void vga_set_palette_mask(uint8_t mask);
void vga_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

// Adapter Query
void vga_get_color(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b);
uint8_t *vga_get_address();

