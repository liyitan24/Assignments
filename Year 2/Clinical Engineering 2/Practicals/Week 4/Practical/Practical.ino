#include <avr/io.h>

int cyclesPerSample{79}; //200 Hz; 2x maximum frequency of ECG
//long int cyclesPerSample{80000}; //200 Hz; 2x maximum frequency of ECG
int _adc{0};
int doPrint{0};
static inline void initSampler(void) {
    TCCR0B = 0b00000101; //prescaler: 1024
//    TCCR0B = 0b00000001; //No scaling
    TIMSK0 |= (1 << TOIE1); // overflow interrupt enable 
    TCNT0 = 2^8-cyclesPerSample;
}
static inline void countToOneSec(void) {
    TCCR1B = 0b00000101; //prescaler: 1024
    TCNT1=2^16-15625; //cycles to 1 second
}

static inline void initIOPorts(void) {
    DDRB |= 0b00100000; //Port 13 as output
}

static inline void initADC(void) {
    ADMUX  |= (1 << REFS0);
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC Prescaler: 8
    ADCSRA |= (1 << ADIE); // ADC Interrupt enabled
    ADCSRA |= (1 << ADEN); // ADC Enable
    ADCSRA &= ~(1 << ADATE); //ADC Autotrigger - Make sure it's off, otherwise it triggers without interrupts.
}

// ------ Interrupt Service Routine ------ //
ISR(TIMER0_OVF_vect) {
    ADCSRA |= (1 << ADSC); //Start Conversion
    TCNT0=2^8-cyclesPerSample;//Reset timer
}

ISR(ADC_vect) {
    _adc = ADC;
    doPrint=1;
    #if 0 //Let me know something is happening
        if(ADC > 0) {
            PORTB = 0b00100000;
        } else {PORTB = 0b00000000;}
    #endif
}

int main(void) {
    Serial.begin(250000);
    noInterrupts();           
    initIOPorts();
    initADC();
    countToOneSec();
    initSampler();
    interrupts();
  
     while(TCNT1 > 0) {
         Serial.flush();
         if(doPrint){
             Serial.println(_adc);
             doPrint=0;
         }
     }
    return (0);
}
