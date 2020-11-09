
// -------- Functions --------- //
static inline void initTimer(void) {
  TCNT1 = 63973;
}

static inline void initIOPorts(void) {
  DDRB |= 0b00100000; //Port 13 as output
  TCCR1B |= 0b00000101; //prescaler: 1024
  TIMSK1 |= (1 << TOIE1); // overflow interrupt enable 
}

static inline void initADC(void) {
  ADMUX |= (1 << REFS0);
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC Prescaler: 8
  ADCSRA |= (1 << ADIE); // Interrupt enabled
  ADCSRA |= (1 << ADEN); // ADC Enable
}

// ------ Interrupt Service Routine ------ //
ISR(TIMER1_OVF_vect) {
  /*This is the interrupt service routine for Timer 1 Overflow*/
  ADCSRA |= (1 << ADSC); //Start Conversion
}

ISR(ADC_vect) {
  if(ADC > 512) {
  PORTB = 0b00100000;
  } else {PORTB = 0b00000000;}
}

/*You don't need to modify anything in the code below*/
int main(void) {

  noInterrupts();           
  initIOPorts();
  initTimer();
  initADC();
  interrupts();
  
  while(1) {

  }
  return 0;                            /* This line is never reached */
}
