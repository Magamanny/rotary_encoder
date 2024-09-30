#include <stdint.h>
#include "rotary_encoder.h"

// Assume these functions are provided by your GPIO library
extern uint8_t read_pin_a(void);
extern uint8_t read_pin_b(void);
extern uint8_t read_pin_button(void);

void button_pressed(void) {
    // Handle button press
}

void handle_rotation(rotary_encoder_direction_t direction) {
    if (direction == ROTARY_ENCODER_CLOCKWISE) {
        // Handle clockwise rotation
    } else {
        // Handle counter-clockwise rotation
    }
}

int main(void) {
    rotary_encoder_t my_encoder;
    rotary_encoder_setup_with_button(&my_encoder, read_pin_a(), read_pin_b(), read_pin_button());
    rotary_encoder_set_button_pressed_callback(&my_encoder, button_pressed);
    rotary_encoder_set_rotation_callback(&my_encoder, handle_rotation);

    while (1) {
        // Assume this loop runs every 10ms
        rotary_encoder_update(&my_encoder, read_pin_a(), read_pin_b(), read_pin_button());
        // Other loop code...
    }

    return 0;
}