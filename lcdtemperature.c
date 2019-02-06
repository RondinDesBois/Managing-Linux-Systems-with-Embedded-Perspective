#include <wiringPi.h>          
#include <lcd.h>                

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>

//USE WIRINGPI PIN NUMBERS
#define LCD_RS  25               //Register select pin
#define LCD_E   24               //Enable Pin
#define LCD_D4  23               //Data pin 4
#define LCD_D5  22               //Data pin 5
#define LCD_D6  21               //Data pin 6
#define LCD_D7  14               //Data pin 7

#define ButtonPin 1

static FILE* FICHIER = NULL; 



int main()
{
    int lcd;
    char c;
    int temp;
    double temperatureC;
    short int isbuttonperssed = 0;


    wiringPiSetup(); // wiringPiSetup() do: 
	//					-Set the offsets into the memory interface
	//					-Get the board ID information
	//					-Map the individual hardware components (GPIO; PWM; Clock control (needed for PWM); The drive pads; The system timer; )
	//					-Set the timer to free-running, 1MHz.
	//					-Export the base addresses for any external software that might need them

    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);	// lcdInit do :
    																						// -clear only the appropriate bits, not the whole PORT
    																						// -Give some time to the LCD to start function properly
    																						// -Send reset signal to the LCD
        																					// -Specify the data lenght to 4 bits
        																					// -Set cursor to move from left to right
        																					// -Turn on display and set cursor off

    /*---------------------------*/
    while(1) { // infinit loop

    	if(digitalRead(ButtonPin) == 0) { //if button is pressed 
            if(isbuttonperssed == 0) {

                isbuttonperssed = 1;
                FICHIER = fopen("/sys/devices/w1_bus_master1/10-0008031c2e96/w1_slave", "r"); //open a file

                if (FICHIER != NULL) { // if the file is opened correctly

                    do c = fgetc(FICHIER);  // move the cursor into the file
                    while (c != '=');       // until he find the first '=' 
                    do c = fgetc(FICHIER);  // then until he find the 2nd '='
                    while (c != '=');       
                    fscanf(FICHIER, "%d", &temp); // then take the decimal value after the cursor and put it into the variable temp
                    printf("decimal:%d\n", temp);
                    fclose(FICHIER); // close the file

                }
		    }
		    lcdPosition(lcd, 0, 0);
		    lcdPrintf(lcd, "Temperature: ");
		    lcdPosition(lcd, 0, 1);
		    lcdPrintf(lcd, "%0.4f", temperatureC);
		    temperatureC = temp * 0.0001; // put the . for have the right value

    	} else {
		 isbuttonperssed = 0;
 	   	}

    }


    printf("float:%0.4f\n", temperatureC); // print with 4 digit acruacy 

    /*---------------------------*/
    


    
    return 0;
}

