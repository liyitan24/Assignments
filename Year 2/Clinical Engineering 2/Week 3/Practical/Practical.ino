#include <avr/io.h>

int x;
int cyclesBeforeOF = 3906;

static inline void initTimer(void) {
    TCNT1=65536-cyclesBeforeOF;
    TCCR1B = 0b00000101; //prescaler: 1024
    TIMSK1 |= (1 << TOIE1); // overflow interrupt enable 
}

static inline void initIOPorts(void) {
  DDRB |= 0b00100000; //Port 13 as output
}

static inline void initADC(void) {
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC Prescaler: 8
    ADCSRA |= (1 << ADIE); // ADC Interrupt enabled
    ADCSRA |= (1 << ADEN); // ADC Enable
    ADCSRA &= ~(1 << ADATE); //ADC Autotrigger - Make sure it's off, otherwise it triggers without interrupts.
}

// ------ Interrupt Service Routine ------ //
ISR(TIMER1_OVF_vect) {
    ADCSRA |= (1 << ADSC); //Start Conversion
    TCNT1=65536-cyclesBeforeOF;//Reset timer
}

ISR(ADC_vect) {
    x = ADC;
    if(ADC > 0) { //Let me know something is happening
        PORTB = 0b00100000;
    } else {
        PORTB = 0b00000000;
    }
}

int main(void) {
    Serial.begin(250000);
    noInterrupts();           
    initIOPorts();
    initTimer();
    initADC();
    interrupts();
  
    while(1) {
        Serial.flush();
        Serial.println(x);
        // You will have to add code here to send x through the serial port
        // At its  most basic the code will be Serial.println(x) though you
        // may need some more.
    }
    return (0);
}
