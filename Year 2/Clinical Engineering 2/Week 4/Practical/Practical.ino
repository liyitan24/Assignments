#include <avr/io.h>

int cyclesBeforeOneSec{15625};
int cyclesBeforeOverflow{1000}; //Max heart rate is about 200ish bpm, so 3hz-ish
int _adc{0};
int doPrint{0};
static inline void initTimer(void) {
    TCCR0B = 0b00000101; //prescaler: 1024
    TCNT0 = 2^8-cyclesBeforeOverflow;
    TIMSK0 |= (1 << TOIE1); // overflow interrupt enable 
}
static inline int countToOneSec(void) {
    TCNT1=2^16-cyclesBeforeOneSec;
    TCCR1B = 0b00000101; //prescaler: 1024
    return TCNT1;
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
ISR(TIMER0_OVF_vect) {
    ADCSRA |= (1 << ADSC); //Start Conversion
    TCNT1=2^8-cyclesBeforeOverflow;//Reset timer
}

ISR(ADC_vect) {
    _adc = ADC;
    #if 0 //Let me know something is happening
        if(ADC > 0) {
            PORTB = 0b00100000;
        } else {PORTB = 0b00000000;}
    #endif
    doPrint=1;
}

int main(void) {
    Serial.begin(250000);
    noInterrupts();           
    initIOPorts();
    countToOneSec();
    initTimer();
    initADC();
    interrupts();
  
    while(countToOneSec() > 1) {
        Serial.flush();
        if(doPrint==1){
            Serial.println(_adc);
            doPrint=0;
        }
    }
    return (0);
}
