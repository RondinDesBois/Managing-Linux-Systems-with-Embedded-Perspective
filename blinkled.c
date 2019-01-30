#include <wiringPi.h>
#include <stdio.h>

#define LedPin 0

int main(void) {
	// wiringPiSetup() do: 
	//		-Set the offsets into the memory interface
	//		-Get the board ID information
	//		-Map the individual hardware components (GPIO; PWM; Clock control (needed for PWM); The drive pads; The system timer; )
	//		-Set the timer to free-running, 1MHz.
	//		-Export the base addresses for any external software that might need them

        if(wiringPiSetup() == -1) {      //when initialize wiringPi failed, print message to screen
                printf("setup wiringPi failed !\n");
                return -1;
        }

        pinMode(LedPin, OUTPUT); // Sets the mode of a pin to be input, output or PWM output
        while(1) {
                digitalWrite(LedPin, LOW);   //led on
                printf("led on\n");
                delay(1000);			     // wait 1 sec
                digitalWrite(LedPin, HIGH);  //led off
                printf("led off\n");
                delay(1000);                 // wait 1 sec
        }
        return 0;
}
