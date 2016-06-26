#ifndef GLOBALS_H_
#define GLOBALS_H_

#define LED_ARRAYS_COUNT	2
#define LEDS_PER_ARRAY		8

typedef uint8_t (*FXFunction_t)(uint8_t [], uint8_t);

extern uint8_t ledArray[LED_ARRAYS_COUNT * LEDS_PER_ARRAY];

#endif // GLOBALS_H_