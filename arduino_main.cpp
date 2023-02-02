/*
 * Change Logs:
 * Date           Author       Notes
 * 02-02-2023     Stanley Lwin   first version
 */

#include <Arduino.h>

const byte ledPin = LED_BUILTIN;
const byte interruptPin = D16;

volatile byte state = LOW;
volatile int count = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 5000;

void ISR__blink() //ISR - hook
{
    
    if ((millis() - lastDebounceTime) > debounceDelay || lastDebounceTime == 0)
    {
        state = !state;
        count++;
        Serial.println("count: ");
        Serial.println(count);

        lastDebounceTime = millis();
    }
}

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), ISR__blink, FALLING);
    /*
        FALLING - when button is pressed - LOW
        RISING - when button is released - HIGH

        digitalPinToInterrupt -> convert pin number to interrupt vector for memory address of the interrupt Pin D16

     */
}

void loop()
{
    digitalWrite(ledPin, state);
}
