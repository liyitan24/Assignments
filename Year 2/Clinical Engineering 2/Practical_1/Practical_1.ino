#include <avr/io.h>
#include <util/delay.h>

static inline void initADC0(void) {
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADEN);
}
void setup() {
  // put your setup code here, to run once:
  DDRB = 0b00100000;
}

void loop() {
  uint16_t adcValue;
  Serial.begin(9600);
  initADC0();

  while(1){
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    adcValue = ADC;
    Serial.println(adcValue);
    if(adcValue > 675) {
    PORTB = 0b00100000;
    } else {PORTB = 0b00000000;}
  }
}
