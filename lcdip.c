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

int main()
{
    int lcd;
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
    int n;
    struct ifreq ifr;
    char iface[] = "wlan0"; 

    n = socket(AF_INET, SOCK_DGRAM, 0); //The socket() function creates an unbound socket in a communications domain, and returns a file descriptor that can be used in later function calls that operate on sockets.
    // int socket(int domain, int type, int protocol);

    ifr.ifr_addr.sa_family = AF_INET; //more info on this struct: http://man7.org/linux/man-pages/man7/netdevice.7.html
    strncpy(ifr.ifr_name , iface , IFNAMSIZ - 1); // copy the string from iface to the field name of the struct
    ioctl(n, SIOCGIFADDR, &ifr); // system call manipulates the underlying device parameters
    							 // of special files.  In particular, many operating characteristics of
       							 // character special files (e.g., terminals) may be controlled with
       							 // ioctl() requests.
    close(n); // close the socket used by ioctl

    lcdPosition(lcd, 0, 0);
    lcdPrintf(lcd, "IP Address: ");

    lcdPosition(lcd, 0, 1);
    lcdPrintf(lcd, ("%s - %s\n" , iface , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr))); // handling internet addresses into inet_nota
    //inet_ntoa function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation.
    //The string is returned in a statically allocated buffer, which subsequent calls will overwrite.
    return 0;
}

