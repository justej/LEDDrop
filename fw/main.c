#include <stdlib.h>
#include <stm8s_conf.h>
#include "peripheral.h"
#include "macros.h"
#include "main.h"

uint8_t ledArray[LED_ARRAYS_COUNT * LEDS_PER_ARRAY];

static void initClock()
{
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
}

static void initGPIO()
{
  // Data  
  GPIO_Init(MGPIO(DATA), MPIN(DATA), GPIO_MODE_OUT_PP_LOW_FAST);
  // Clock
  GPIO_Init(MGPIO(CLK), MPIN(CLK), GPIO_MODE_OUT_PP_LOW_FAST);
  // Latch
  GPIO_Init(MGPIO(LATCH), MPIN(LATCH), GPIO_MODE_OUT_PP_LOW_FAST);
  // Master reset
  GPIO_Init(MGPIO(MRST), MPIN(MRST), GPIO_MODE_OUT_PP_LOW_FAST);
  // Debug pin
  GPIO_Init(MGPIO(DBG), MPIN(DBG), GPIO_MODE_OUT_PP_LOW_FAST);
}

static void initTimer()
{
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 1);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
}

static void start()
{
  rim();
  TIM4_Cmd(ENABLE);
}

static void delay(volatile uint32_t period)
{
  period *= 128;
  while (period--) {
  }
}

/* Effect functions */
uint8_t fxTimeWave(uint8_t ledArray[], uint8_t size)
{
  static int8_t brightness = 0x00;
  register uint8_t i;
  uint8_t t;

  t = abs(brightness) << 1;
  for (i = size; i-- > 0; ) {
    ledArray[i] = t;
  }
  brightness++;
  
  return 255 / (t + 1) + 10;
}

uint8_t fxLineWave(uint8_t ledArray[], uint8_t size)
{
  static int8_t brightness = 0x00;
  register uint8_t i;

  for (i = size; i-- > 0; ) {
    ledArray[i] = abs(brightness) << 1;
    brightness += 15;
  }
  
  return 100;
}

uint8_t fxSingleRun(uint8_t ledArray[], uint8_t size)
{
  static uint8_t i = 0;

  if (i < size) {
    if (i) {
      ledArray[i - 1] = 0;
    }
    ledArray[i] = 255;
  }
  else if (i < size * 2) {
    ledArray[size - 1] = 0;
  }
  else {
    i = 0;
  }
  ++i;
  
  return 50;
}

uint8_t fxBrightness1(uint8_t ledArray[], uint8_t size)
{
  register uint8_t i;

  for (i = size; i-- > 0; ) {
    ledArray[i] = 1;
  }
  
  return 100;
}

/* Program entry point */
int main(void)
{
  FXFunction_t fx[] = {fxTimeWave, fxLineWave, fxSingleRun, fxBrightness1};
  uint8_t effectNo = 0;
  uint32_t cycleCounter = 0;
  
  /* Initialize peripheral */
  initClock();
  initGPIO();
  initTimer();

  /* Initialize array */
  (fx[effectNo])(ledArray, ARRAY_SIZE(ledArray));
  
  /* Clear registers */
  GPIO_WriteLow(MGPIO(MRST), MPIN(MRST));
  GPIO_WriteHigh(MGPIO(MRST), MPIN(MRST));
  
  /* Go!!! */
  start();
  while (42) {
    delay((fx[effectNo])(ledArray, ARRAY_SIZE(ledArray)));
    cycleCounter++;
    if (cycleCounter & 0x080) {
      cycleCounter = 0;
      effectNo++;
      effectNo %= ARRAY_SIZE(fx);
    }
  }
}