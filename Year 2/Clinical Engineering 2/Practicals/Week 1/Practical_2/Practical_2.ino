#include <avr/io.h>
#include <util/delay.h>

static inline void initADC0(void) {
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADIE);
  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADSC);
}

void setup() {
  DDRB |= 0b00100000; //initiate IO ports
  initADC0();
}

ISR (ADC_vect) {
  if(ADC > 512) {
  PORTB = 0b00100000;
  } else {PORTB = 0b00000000;}
  ADCSRA |= (1 << ADSC);
}

void loop() {
  Serial.begin(9600);
  sei();
  
  while(1){
    PORTB ^= 0b00100000;
    Serial.println(ADC);

  }
}
