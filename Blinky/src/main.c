#include "stm32f7xx.h"

void LED_Init();
void BUTTON_Init();

void wait(int time) {
  volatile int j = 0;
  for (int i = 0; i < time; ++i) {
    j++;
  }
}

int main(void) {
  LED_Init();
  BUTTON_Init();

  while(1) {
    if ( GPIOC->IDR & GPIO_IDR_IDR_13 ) {
      // turn on LED
      GPIOB->BSRR |= GPIO_BSRR_BS_7;

    } else {
      // turn off LED
      GPIOB->BSRR |= GPIO_BSRR_BR_7;

    }
  }

  return 0;
}

void BUTTON_Init() {
  // User B1 = PC13

  // Enable the GPIO Clock for Port C using the AHB and RCC
  // PG 184: RCC AHB1 ENR set GPIOC EN (bit 1) to a 1
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // Set any control registers for PortB Pin 7
  // MODER
  // PG 229: Set pin 13 of Port C to input mode
  GPIOC->MODER &= ~GPIO_MODER_MODER13;

  // OSPEEDR
  // PG 230: set to 11 for high speed
  GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;

  // PUPDR
  // PG 230: set [1:0] both to 0 for no pull up / pull down
  GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13;
}

void LED_Init() {
  // User LD2 = PB7

  // Enable the GPIO Clock for Port B using the AHB and RCC
  // PG 184: RCC AHB1 ENR set GPIOB EN (bit 1) to a 1
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // Set any control registers for PortB Pin 7
  // MODER
  // PG 229: Set pin 7 to general purpose output mode 01
  // this flips first bit for MODER7 to one setting our MODER to 01
  GPIOB->MODER |= GPIO_MODER_MODER7_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER7_1;

  // OTYPER
  // PG 229: set to push-pull (zero it out)
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_7;

  // OSPEEDR
  // PG 230: set to 11 for high speed
  GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;

  // PUPDR
  // PG 230: set [1:0] both to 0 for no pull up / pull down
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7;
}
