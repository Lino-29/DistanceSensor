#include <Arduino.h>


uint8_t ledPin = LED_BUILTIN;
uint8_t RED = PIND4;
uint8_t GREEN = PIND5;
uint8_t BLUE = PIND6;

#define		red_color		digitalWrite(RED, HIGH); digitalWrite(GREEN, LOW); digitalWrite(BLUE, LOW);
#define 	green_color		digitalWrite(RED, LOW); digitalWrite(GREEN, HIGH); digitalWrite(BLUE, LOW);
#define 	blue_color		digitalWrite(RED, LOW); digitalWrite(GREEN, LOW); digitalWrite(BLUE, HIGH);
#define 	violeta_color	digitalWrite(RED, HIGH); digitalWrite(GREEN, LOW); digitalWrite(BLUE, HIGH);
#define		off_color		digitalWrite(RED, LOW); digitalWrite(GREEN, LOW); digitalWrite(BLUE, LOW);