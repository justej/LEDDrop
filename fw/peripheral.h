#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

#define MGPIO(pin_name) (pin_name##_GPIO)
#define MPIN(pin_name)  (pin_name##_GPIO_PIN)
#define MGCLK(pin_name) (pin_name##_GPIO_CLK)
#define MPCLK(pin_name) (pin_name##_GPIO_PIN_CLK)

#define DATA_GPIO       GPIOD
#define DATA_GPIO_PIN   GPIO_PIN_3

#define CLK_GPIO        GPIOC
#define CLK_GPIO_PIN    GPIO_PIN_7

#define LATCH_GPIO      GPIOC
#define LATCH_GPIO_PIN  GPIO_PIN_6

#define MRST_GPIO       GPIOD
#define MRST_GPIO_PIN   GPIO_PIN_2

#define DBG_GPIO        GPIOC
#define DBG_GPIO_PIN    GPIO_PIN_3

//#define DATA_GPIO       GPIOC
//#define DATA_GPIO_PIN   GPIO_PIN_3
//
//#define CLK_GPIO        GPIOC
//#define CLK_GPIO_PIN    GPIO_PIN_4
//
//#define LATCH_GPIO      GPIOC
//#define LATCH_GPIO_PIN  GPIO_PIN_5
//
//#define MRST_GPIO       GPIOB
//#define MRST_GPIO_PIN   GPIO_PIN_4

#define DBG_SET()       GPIO_WriteHigh(MGPIO(DBG), MPIN(DBG))
#define DBG_RESET()     GPIO_WriteLow(MGPIO(DBG), MPIN(DBG))

#endif // PERIPHERAL_H_