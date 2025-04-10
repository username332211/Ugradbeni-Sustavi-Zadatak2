#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

const int ledPin = 13;
const int buttonPin = 2;

volatile bool wakeUpByWatchdog = false;
volatile bool wakeUpByButton = false;

// ISR za tipkalo
void wakeUpExternal() {
  wakeUpByButton = true;
}

// ISR za Watchdog timer
ISR(WDT_vect) {
  wakeUpByWatchdog = true;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Arduino je pokrenut.");

  attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUpExternal, FALLING);

  setupWatchdog8s();
}

void loop() {
  // LED se budi ili preko Watchdog-a, ili preko tipkala 
  if (wakeUpByWatchdog || wakeUpByButton) {
    Serial.println("Probudio se!");

    // LED svijetli 5s
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);

    wakeUpByWatchdog = false;
    wakeUpByButton = false;

    // Watchdog se resetira kako bi cooldown svaki put iznosio 8s od zadnjeg buđenja
    setupWatchdog8s();

    // ulazak u sleep mode na 8s
    Serial.println("Ulazak u sleep...");
    enterSleep();
  }
}

/// funkcija za postavljanje Watchdog timer-a na 8 sekundi
void setupWatchdog8s() {
  cli(); // privremeno zaustavi prekide
  wdt_reset(); // resetiraj Watchdog timer

  MCUSR &= ~(1 << WDRF); // očisti Watchdog timer reset zastavicu
  WDTCSR |= (1 << WDCE) | (1 << WDE); // omogući Watchdog timer konfiguraciju
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // 8s prekid
  sei(); // omogući prekide
}

/// funkcija za ulazak u sleep mode
void enterSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // najniži power-down mode
  sleep_enable();
  cli();
  sei();
  sleep_cpu(); // mikrokontroler ide u sleep dok ne stigne Watchdog timer prekid
  sleep_disable();
}
