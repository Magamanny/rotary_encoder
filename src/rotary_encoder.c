#include "rotary_encoder.h"
#include <stddef.h>

#define DEBOUNCE_TICKS 5  // 50ms debounce time (5 * 10ms)

void rotary_encoder_init(rotary_encoder_t *encoder) {
    encoder->position = 0;
    encoder->has_button = false;
    encoder->button_pressed_cb = NULL;
    encoder->button_released_cb = NULL;
    encoder->rotation_cb = NULL;
    encoder->debounce_counter = 0;
    encoder->state_a = 0;
    encoder->state_b = 0;
    encoder->button_state = 0;
}

void rotary_encoder_setup(rotary_encoder_t *encoder, uint8_t pin_a_state, uint8_t pin_b_state) {
    rotary_encoder_init(encoder);
    encoder->state_a = pin_a_state;
    encoder->state_b = pin_b_state;
    encoder->has_button = false;
}

void rotary_encoder_setup_with_button(rotary_encoder_t *encoder, uint8_t pin_a_state, uint8_t pin_b_state, uint8_t button_state) {
    rotary_encoder_init(encoder);
    encoder->has_button = true;
    encoder->state_a = pin_a_state;
    encoder->state_b = pin_b_state;
    encoder->button_state = button_state;
}

void rotary_encoder_set_button_pressed_callback(rotary_encoder_t *encoder, void (*callback)(void)) {
    encoder->button_pressed_cb = callback;
}

void rotary_encoder_set_button_released_callback(rotary_encoder_t *encoder, void (*callback)(void)) {
    encoder->button_released_cb = callback;
}

void rotary_encoder_set_rotation_callback(rotary_encoder_t *encoder, void (*callback)(rotary_encoder_direction_t direction)) {
    encoder->rotation_cb = callback;
}

void rotary_encoder_update(rotary_encoder_t *encoder, uint8_t pin_a_state, uint8_t pin_b_state, uint8_t button_state) {
    if (pin_a_state != encoder->state_a || pin_b_state != encoder->state_b) {
        if (pin_a_state != encoder->state_b) {
            encoder->position++;
            if (encoder->rotation_cb) {
                encoder->rotation_cb(ROTARY_ENCODER_CLOCKWISE);
            }
        } else {
            encoder->position--;
            if (encoder->rotation_cb) {
                encoder->rotation_cb(ROTARY_ENCODER_COUNTERCLOCKWISE);
            }
        }
    }

    encoder->state_a = pin_a_state;
    encoder->state_b = pin_b_state;

    if (encoder->has_button) {
        if (button_state != encoder->button_state) {
            if (encoder->debounce_counter == 0) {
                encoder->debounce_counter = DEBOUNCE_TICKS;
            }
            encoder->button_state = button_state;
        } else if (encoder->debounce_counter > 0) {
            encoder->debounce_counter--;
            if (encoder->debounce_counter == 0) {
                if (button_state == 0) {  // Assuming LOW is 0 (button pressed)
                    if (encoder->button_pressed_cb) {
                        encoder->button_pressed_cb();
                    }
                } else {
                    if (encoder->button_released_cb) {
                        encoder->button_released_cb();
                    }
                }
            }
        }
    }
}

int32_t rotary_encoder_get_position(const rotary_encoder_t *encoder) {
    return encoder->position;
}

void rotary_encoder_set_position(rotary_encoder_t *encoder, int32_t position) {
    encoder->position = position;
}