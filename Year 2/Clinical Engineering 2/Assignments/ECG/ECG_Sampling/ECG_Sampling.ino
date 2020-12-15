#include <avr/io.h>

int cyclesPerSample{79}; // 200 Hz = 5ms; 2x maximum frequency of ECG
int _adc{0};             // Private copy of ADC value. Will be switched with every print.  
int shouldPrint{0};      // Controlled printing. requires truthy value for print

static inline void initSampler(void) {
    TCCR0B = 0b00000101;         // Prescaler: 1024
    TIMSK0 |= (1 << TOIE1);      // Overflow interrupt enable 
    TCNT0 = 2^8-cyclesPerSample; //Count 5 ms
}

static inline void initADC(void) {
    ADMUX  |= (1 << REFS0);                // Set ADC reference voltage to external
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // ADC Prescaler: 8
    ADCSRA |= (1 << ADIE);                 // ADC Interrupt enabled
    ADCSRA |= (1 << ADEN);                 // ADC Enable
    ADCSRA &= ~(1 << ADATE);               // ADC Autotrigger - Make sure it's off, otherwise it triggers without interrupts.
}
// ------ Interrupt Service Routine ------ //
ISR(TIMER0_OVF_vect) { //After cyclesPerSample have elapsed, this starts the ADC conversion and restarts the counting.  
    ADCSRA |= (1 << ADSC);    //Start Conversion
    TCNT0=2^8-cyclesPerSample;//Reset timer
}

ISR(ADC_vect) { //Save current ADC value and allow a print
    _adc = ADC;
    shouldPrint=1;
}

int main(void) {
    Serial.begin(115200);
    noInterrupts();           
    initADC();
    initSampler();
    interrupts();
     while(1) {
        Serial.flush();
        if(shouldPrint){
            Serial.println(_adc);
            shouldPrint = 0;
        }
     }
    return (0);
}
