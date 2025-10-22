#include <Arduino.h>


uint8_t ledPin = LED_BUILTIN;
uint8_t RED = A0;
uint8_t GREEN = A1;
uint8_t BLUE = A2;

#define		red_color		digitalWrite(RED, HIGH); digitalWrite(GREEN, LOW); digitalWrite(BLUE, LOW);
#define 	green_color		digitalWrite(RED, LOW); digitalWrite(GREEN, HIGH); digitalWrite(BLUE, LOW);
#define 	blue_color		digitalWrite(RED, LOW); digitalWrite(GREEN, LOW); digitalWrite(BLUE, HIGH);
#define 	violeta_color	digitalWrite(RED, HIGH); digitalWrite(GREEN, LOW); digitalWrite(BLUE, HIGH);
#define		off_color		digitalWrite(RED, LOW); digitalWrite(GREEN, LOW); digitalWrite(BLUE, LOW);