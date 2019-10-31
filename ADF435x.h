/* 
   ADF435x.h - ADF435x PLL Communication Library
   Created by Neal Pisenti, 2013.
   JQI - Strontium - UMD

    Massively modified for Energia - Steve Pettitt, SEC 2016
    Modified further by Richard Hosking 
  */

#ifndef ADF435x_h
#define ADF435x_h

#include "Arduino.h"

class ADF435x{
    
    public: 
 
        // Initialize with initial frequency, refClk (defaults to 10Mhz); 
        void initialize(uint32_t, uint32_t );


        // Functions to turn on and off the PLL/VCO
        void powerDown(bool);
        void setRfPower(int);
        void setAuxPower(int);
        void auxEnable(void);
        void auxDisable(void);
        void rfEnable(bool);

        // Gets current frequency
        int getFreq();

        // Sets frequency
        void setFreq(uint32_t);

        void setFeedbackType(bool);

        // Update the device 
        void update();
        void programRegister(uint32_t registerData); 
        
       //Debugging 
        void debug();
        
        // Variables 

        uint32_t _freq, fPFD, _refClk, _INT;   // _INT is integer of main divider
        int phase;
        unsigned int _divider, _auxPower, _rfPower;
        uint32_t _mod;
	// _frac is fraction _modulus is modulus of fractional N divider
        unsigned int _frac, _modulus, _channelSpacing, _outputDivider, _fPDF, R_counter;
    
        // Port pin assignments
    int ChipEnable = 14;
    int LoadEnable = 5;
    int DataClock = 3;
    int SerialData = 4;
    int LockDetect = 15;
    int MultiplexData = 6; 
    
    
    // function to write data to register.
    void setR0();
    void setR1();
    void setR2();
    void setR3();
    void setR4();
    void setR5();
    void writeRegister(byte[4]);
    void write4Bytes(uint32_t);
    
    private:
         // Instance variables for ...
    bool _powerdown, _auxOnOff, _rfEnabled, _feedbackType, _prescaler, _ABP;

    unsigned int _ref_doubler, _ref_halve;
    
    typedef struct R0bitfield{
        unsigned int ctrl:3;
        unsigned int frac:12;       // Fractional N divider 12 bits 
        unsigned int integer:16;    // Integer divider 16 bits 
        unsigned int reserved:1;
    } d0;
    union {
        uint32_t reg0;
        R0bitfield d0;
    } R0;
    
    
    typedef struct R1bitfield{
        unsigned int ctrl:3;
        unsigned int modulus:12;
        unsigned int phaseValue:12;
        unsigned int prescaler:1;      // Prescaler 4/5 or 8/9
        unsigned int phaseAdjust:1;
        unsigned int reserved:3;
    } d1;
    union {
        uint32_t reg1;
        R1bitfield d1;
    } R1;
    
    typedef struct R2bitfield{
        unsigned int ctrl:3;
        unsigned int counterReset:1;
        unsigned int CP3state:1;    // Charge pump 3 state 0 for normal operation 
        unsigned int PD:1;          // Power down if 1 reset at startup
        unsigned int PD_Polarity:1; // Phase detector polarity 1 for noninverting filter 
        unsigned int LDP:1;         // Lock detect precision - window 
        unsigned int LDF:1;         // O = Frac N 1 = Integer cycles 
        unsigned int chargePump:4;     // Set charge pump current according to loop filter design 
        unsigned int doubleBuffer:1;  // Double buffer RF divider select in R4 if 1 
        unsigned int rCounter:10;   // Reference counter - sets channel; spacing 
        unsigned int refDivBy2:1;   // Extend Ref in frequency
        unsigned int refDoubler:1;  // Enable reference doubler 
        unsigned int Muxout:3;      // Select multiplex output 
        unsigned int noiseMode:2;   // Low noise or low spur (dither enabled) 
        unsigned int reserved:1;
    } d2;
    union {
        uint32_t reg2;
        R2bitfield d2;
    } R2;
    
    
    typedef struct R3bitfield{
        unsigned int ctrl:3;
        unsigned int clockDivider:12;
        unsigned int clockDivMode:2;
        unsigned int reserved3:1;
        unsigned int CSR:1;
        unsigned int reserved2:2;
        unsigned int chargeCancel:1;
        unsigned int ABP:1;
        unsigned int bandSelCkMode:1;
        unsigned int reserved1:8;
    } d3;
    union {
        uint32_t reg3;
        R3bitfield d3;
    } R3;
    
    typedef struct R4bitfield{
        unsigned int ctrl:3;
        unsigned int OutputPower:2;
        unsigned int RF_OutEn:1;
        unsigned int auxOutPower:2;
        unsigned int auxOutEnable:1;
        unsigned int auxOutSel:1;
        unsigned int MTLD:1;
        unsigned int VCO_PD:1;
        unsigned int bandSelCkDiv:8;
        unsigned int RF_div:3;
        unsigned int feedbackSel:1;
        unsigned int reserved:8;
    } d4;
    union {
        uint32_t reg4;
        R4bitfield d4;
    } R4;
    
    typedef struct R5bitfield{
        unsigned int ctrl:3;
        unsigned int reserved4:16;
        unsigned int reserved3:2;
        unsigned int reserved2:1;
        unsigned int LD_Mode:2;
        unsigned int reserved1:8;
    } d5;
    union {
        uint32_t reg5;
        R5bitfield d5;
    } R5;
    
        // register values

};
 

#endif
