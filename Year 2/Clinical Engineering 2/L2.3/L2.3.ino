#include <avr/io.h>
#include <util/delay.h>

static inline void initTimer(void) {
  TCNT1=61630;
}

static inline void initIOPorts(void) {
  DDRB = 0b00100000; //port 13 as output
  TCCR1B = 0b00000101; //prescaler: 1024
  TIMSK1 |= (1 << TOIE1); // overflow interrupt enable 
}
ISR(TIMER1_OVF_vect) {
  if(PORTB == 0b00100000){
    PORTB = 0b00000000;
  } else {
    PORTB = 0b00100000;
  }
}
int main(void) {
  noInterrupts();           
  initIOPorts();
  initTimer();
  interrupts();
  while(1) {
  }
  return (0);
}
