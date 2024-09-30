#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ROTARY_ENCODER_CLOCKWISE = 1,
    ROTARY_ENCODER_COUNTERCLOCKWISE = -1
} rotary_encoder_direction_t;

typedef struct rotary_encoder_t {
    int32_t position;
    uint8_t state_a;
    uint8_t state_b;
    uint8_t button_state;
    bool has_button;
    void (*button_pressed_cb)(void);
    void (*button_released_cb)(void);
    void (*rotation_cb)(rotary_encoder_direction_t direction);
    uint8_t debounce_counter;
} rotary_encoder_t;

void rotary_encoder_init(rotary_encoder_t *encoder);
void rotary_encoder_setup(rotary_encoder_t *encoder,uint8_t pin_a_state, uint8_t pin_b_state);
void rotary_encoder_setup_with_button(rotary_encoder_t *encoder, uint8_t pin_a_state, uint8_t pin_b_state, uint8_t button_state);
void rotary_encoder_set_button_pressed_callback(rotary_encoder_t *encoder, void (*callback)(void));
void rotary_encoder_set_button_released_callback(rotary_encoder_t *encoder, void (*callback)(void));
void rotary_encoder_set_rotation_callback(rotary_encoder_t *encoder, void (*callback)(rotary_encoder_direction_t direction));
void rotary_encoder_update(rotary_encoder_t *encoder, uint8_t pin_a_state, uint8_t pin_b_state, uint8_t button_state);
int32_t rotary_encoder_get_position(const rotary_encoder_t *encoder);
void rotary_encoder_set_position(rotary_encoder_t *encoder, int32_t position);

#endif // ROTARY_ENCODER_H