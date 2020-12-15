int timePassed = 0;        // increases every 4 seconds have passed for sustained pressure
int fsrADC = 0;            // global variable to store ADCvalue
int newAdcValue = 0;              // to implement main loop after every ADC conversion
const int forceThreshold {130};
const int healthyStandingTime {0};
const int healthyNumberOfSteps {0};
// Functions //
float calculateForce(int voltage) {
    const float VCC = 4.98;         // measured voltage of arduino 5V line
    const float R_DIV = 3230.0;     // measured resistance of 3.3k resistor
    const float fsrV = voltage*VCC/1023.0;
    const float fsrR = R_DIV * (VCC/fsrV - 1.0);
    const float fsrG = 1.0/fsrR;
    
    if (fsrR <= 600) { 
    force = (fsrG - 0.00075) / 0.00000032639;
    } else {
    force =  fsrG / 0.000000642857;
    }
    Serial.println("Force: " + String(force) + " g");
    Serial.println();
    return force;
}
void startCounting() {
    stepCounter++; 
    initTimer0();
}
void stopCounting() {
    TIMSK0 |= (0 << TOIE0);         // Disable Timer0 Overflow
    timePassed = 0;                 // reset time count for sustained pressure
}
void warnuser(int _timePassed, int _stepCounter) {
  if (_timePassed >= healthyStandingTime || _stepCounter > healthyNumberOfSteps) {
      //do something
    }
}

static inline void initTimer(void) {
  /*Code to initialize Timer 1*/
  TCCR1B = 0b00000101;          // setting prescaler of 1024
  TIMSK1 |= (1 << TOIE1);       // enabling timer1 overflow interrupt
  TCNT1 = 62411;                // 65536 - 15625/5 = 62411 overflow after 1/5 seconds (sampling rate)
}

static inline void initTimer0 (void) {
  /*Code to initialize Timer 0*/
  TCCR0A = 0;                     
  TCCR0B |= 0b00000101;           // prescaler set for 1024
  TIMSK0 |= (1 << TOIE0);         // Enable Timer0 Overflow
  TCNT0 = 3036;                   // 2^16 - 62500 = 3036 overflow after 4 seconds
}

static inline void initIOPorts(void) {
  /*Code to initiate the GPIO ports (pins) needed*/
  
  pinMode (A0, INPUT);          // settting A0 as input pin for force sensor  
}

static inline void initADC(void) {
  /*Write code to initialize the ADC*/  
  ADMUX |= (1 << REFS0);         // reference voltage
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1); // ADC prescaler of 8
  ADCSRB |= (1 << ADTS2) | (1 << ADTS1); // auto triggered source = timer1 overflow
  ADCSRA |= (1 << ADATE);       // enable auto triggered conversion 
  ADCSRA |= (1 << ADEN);        // enable ADC conversion
  ADCSRA |= (1 << ADIE);        // enable ADC interrupt
}

// Interrupt Service Routine //
ISR(TIMER0_OVF_vect) {
  /*Interrupt service routine for Timer0 overflow*/
  /*Keeps track of time passed as standing still, warns after 1 minute*/
  timePassed++;                 // timer0 counts up to 4 seconds, increase timePassed by 1

  TCNT0 = 3036;                 // reload timer0 to count up to 4 seconds again
}

ISR(TIMER1_OVF_vect) {
  /*Interrupt service routine for Timer1 Overflow*/
  TCNT1 = 62411;                // reload timer1
}

ISR(ADC_vect) { /*Interrupt service routine for ADC*/
    fsrADC = ADC;             // variable to store ADC value
    newAdcValue = 1;                 // leads to main loop 
}

int main(void) {
  noInterrupts();
  initIOPorts();
  initTimer();
  initADC();
  interrupts();
  Serial.begin(9600);

  int stepCounter = 0;           // increases every step taken (repetitive pressure)
  float force = 0;

  while(1) {
    if(newAdcValue) {
      force = calculateForce(fsrADC);
      (force > forceThreshold) ? startCounting() : stopCounting();
      newAdcValue = 0;
    }
    warnUser(timePassed, stepCounter);
  }
  return 0;
}
