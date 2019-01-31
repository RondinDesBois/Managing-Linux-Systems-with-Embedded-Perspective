#include <wiringPi.h>
#include <stdio.h>

#define LedPin    0
#define ButtonPin 1

int main(void)
{
	wiringPiSetup() ;

	pinMode(LedPin, OUTPUT);
	pinMode(ButtonPin, INPUT);

	pullUpDnControl(ButtonPin, PUD_UP);  //pull up to 3.3V,make GPIO1 a stable level
	// remove the line up there for deal with a resistor
 	while(1){
		digitalWrite(LedPin, HIGH);
		if(digitalRead(ButtonPin) == 0){ //indicate that button has pressed down
			digitalWrite(LedPin, LOW);   //led on
			delay(100);
		}
	}

	return 0;
}



