
/*
  Arduino board to drive an ADF4351 Fractional N PLL synthesizer 
  Richard Hosking Aug 2019
  richardh@iinet.net.au
  Using Qduino board for 3.3V operation 
  Code borrowed from Energia sketch 
 */

<<<<<<< HEAD
    #define DEBUGMODE // comment out this line if you dont want debugging via
=======
    //#define DEBUGMODE // comment out this line if you dont want debugging via
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
                        // The serial port 
                        // Note that device will hang on startup until serial 
                        // port is opened


    #include "ADF435x.h" 	// Class ADF435x 
    #include <SPI.h>
    #include <SD.h>
    #include "Qduino.h"
    #include "Wire.h"


    ADF435x PLL;     // Class Constructor creates a ADF534x object called PLL 
    qduino q;        // Class instance of Qduino
     
   
    void setup() {
        
    q.setup();

     
    #ifdef DEBUGMODE 
    //Initialize serial port for debugging and wait for port to open:

    Serial.begin(9600);
    while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
    }
 
    #endif  
 
<<<<<<< HEAD
    int frequency = 40121;    // Output frequency initially 40.121 MHz - figure in KHz
=======
    int frequency = 4000000;    // Output frequency initially 40MHz - figure in Hz divided by 10 to fit in 32 bit integer
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    int referenceClock = 25;    // Reference clock 25MHz 

  
    PLL.initialize(frequency,referenceClock);

    delay(100); 
    
   #ifdef DEBUGMODE 
  
    PLL.debug();
    #endif  
 
}

void loop() {
    //PLL.programRegister(0b10101010101010101010101010101010);
    delay(1000);
    //Serial.println("Updated");
 
}
