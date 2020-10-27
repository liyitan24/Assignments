#include <avr/io.h>

int cyclesBeforeOverflow = 3906;
int _adc;
int doPrint=0;
static inline void initTimer(void) {
    TCNT1=65536-cyclesBeforeOverflow;
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
    TCNT1=65536-cyclesBeforeOverflow;//Reset timer
}

ISR(ADC_vect) {
    _adc = ADC;
    if(ADC > 0) { //Let me know something is happening
        PORTB = 0b00100000;
    } else {
        PORTB = 0b00000000;
    }
    doPrint=1;
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
        if(doPrint==1){
            Serial.println(_adc);
            doPrint=0;
        }
    }
    return (0);
}
