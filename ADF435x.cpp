/* 
   ADF435x.cpp - ADF435x PLL Communication Library
   Created by Neal Pisenti, 2013.
   JQI - Strontium - UMD
 Substantially modified by Steve Pettitt, SEC Ltd 2016
 Modified further by Richard Hosking 

  */

#include "ADF435x.h" 

  
<<<<<<< HEAD
// Initializes a new ADF435x object referenceClock (in MHz), and initial frequency KHz

void ADF435x::initialize(uint32_t frequency, uint32_t referenceClock){
    _freq = frequency; 
    _refClk = referenceClock;
    phase = 1;
    
    // Setup Port pins
    pinMode(ChipEnable, OUTPUT);  
    pinMode(LoadEnable, OUTPUT);
    pinMode(DataClock, OUTPUT);
    pinMode(LockDetect, INPUT);
    pinMode(MultiplexData, INPUT);
    pinMode(SerialData, OUTPUT);
    
    
    _feedbackType = 0;  // 0=fractional, 1=integer
    _ABP = 0;		// antibacklash pulse width 6ns for Fractional N mode 

    //    reference divider and multiplier both 1 
    _ref_doubler = 0; 	// reference doubler 1
    _ref_halve = 0; 	// reference divider 1
=======
// Initializes a new ADF435x object referenceClock (in MHz), and initial frequency Hz/10 to fit in 2^32

void ADF435x::initialize(uint32_t frequency, uint32_t referenceClock){
    _freq = frequency; // one tenth of real value REMEMBER!
    _refClk = referenceClock;
    phase = 1;

    _feedbackType = 0;  //0=fractional, 1=integer
    if (_feedbackType) _ABP = 1;
    _doubler = 0; //
    _halve = 0; //
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    _channelSpacing = 25000; //25KHz
    _powerdown = 0;
    _auxOnOff = 0;
    _rfEnabled = 1;
<<<<<<< HEAD
    _prescaler = 0;  // 4/5 or 8/9...

    // default power out = -5dbm or 0 in this case... (0-3)
=======
    _prescaler = 1;  // 4/5 or 8/9...

    // default power = -5dbm or 0 in this case... (0-3)
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    _auxPower = 0;
    _rfPower = 0;

    // sets register values which don't have dynamic values...
    ADF435x::setR1();
    ADF435x::setR3();
    ADF435x::setR5();

    ADF435x::setFreq(_freq);
    
<<<<<<< HEAD
=======

>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    ADF435x::update();
}

// gets current frequency setting
int ADF435x::getFreq(){
    return _freq;
}
<<<<<<< HEAD

// Set Frequency depending on keyboard input 
// Range 32 to 4400 MHz 1 KHz steps 
// set up for approx 40 MHz out temporary so I can see it on the Spectrum analyser

void ADF435x::setFreq(uint32_t freq){
    
  // Reference clock on this board is 25MHz
  
    R_counter = 25;  	// divide reference by 25 to make INT step size 1MHz 
    _mod = 1000;	// Modulus of Frac N section 1000 to give final freq step size of 1 KHz  
    
    if (_freq > 2200000) {
        _divider = 0; 		// output_divider = 1;
     }
    else if (_freq > 1100000) {
        _divider = 1;           // divide output by 2;
          }
        else if (_freq > 550000) {
            _divider = 2;            // divide output by 4 
              }
            else if (_freq > 275000) {
                    _divider = 3;          // divide output by 8  
                  }
                else if (_freq >137500) {
                        _divider = 4;               // divide output by 16 
                     }
                    else if (_freq >68750) {
                            _divider = 5;               // divide output by 32 
                         }
                        else {  			//_freq lies between 34.375MHz to 68.75MHz
                            _divider = 6;               // divide output by 64 
                        }
 
// VCO Output division = 2^(_divider)
int output_division = 2^(_divider);

//Final freq = 1000*(INT + frac/mod)/(output division) KHz
//    quotient = dividend / divisor;
//    remainder = dividend % divisor;

// Hence 
uint32_t VCO = _freq *output_division;

_INT = (uint32_t)(VCO/1000) ; //quotient integer part 

_frac = (uint32_t)(VCO%1000)*1000 ; // remainder X 1000 

// If VCO has to go above 3.6GHz prescaler should be set to 8/9
if (VCO > 3600000) {
  _prescaler = 1 ;
  }
 
}


=======
// set up for approx 40 MHz out temporary
void ADF435x::setFreq(uint32_t freq){
    R_counter = 250; // Divide 25 MHz to 100 KHz for channel spacing
    _divider = 6; // divide main output by 64 for low freq out 
    _mod = 1562; // 25 MHz clock 100KHz channel spacing 
    _frac = 101; // reduce with fractional N to 1KHz channel spacing 
    _integ = 29921; //Ref Freq 100KHz VCO range 2-4.5GHz 
}

/*void ADF435x::setFreq(uint32_t freq){
// frequency passed is one tenth real value to stay within 32-bit value
    _freq = freq;
    int multiplier;
    // selects the right divider range (ie, output divider is 2^(_divider))
    // the multiplier is required if you're using fundamental feedback to N-counter
    if (_freq > 220000000) {
        _divider = 0;
        multiplier = 1;
        R_counter = 50;
    }
    else if (_freq > 110000000) {
        _divider = 1;               // divide output by 2 
        multiplier = 2;
        R_counter = 25;
        }
        else if (_freq > 55000000) {
            _divider = 2;            // divide output by 4 
            multiplier = 4;
            R_counter = 16;
            }
            else if (_freq > 27500000) {
                    _divider = 3;          // divide output by 8  
                    multiplier = 8;
                    R_counter = 8;
                }
                else if (_freq >13750000) {
                        _divider = 4;               // divide output by 16 
                        multiplier = 16;
                        R_counter = 4;
                    }
                    else if (_freq >6875000) {
                            _divider = 5;               // divide output by 32 
                            multiplier = 32;
                            R_counter = 2;
                        }
                        else {  //_freq lies between 34.375MHz to 68.75MHz
                            _divider = 6;               // divide output by 64 
                            multiplier = 64;
                            R_counter = 1;
                        }
 
  

        _mod = _refClk/_channelSpacing; // 10000000/100 = 1000000
        _mod *= _doubler; //_doubler should always be set
        _mod >>= _divider;
        _mod /= R_counter;
 
        while (_mod < 4096) {
            if(!_mod){_mod++;} // if _mod is zero loop will hang 
            _mod *=2; // set mod as close to 4095 as possible...
        }
        _mod /= 2; //restore to less than 4096

    uint64_t test = _freq*10;
    test <<= _divider;
    test *= R_counter;
    uint32_t tast = _refClk << _doubler;
    tast >>= _halve;
    _integ = (uint64_t)(test/tast);
    _frac = ((uint64_t)(test % tast)*_mod)/(int32_t)tast;
    
    // reduce the frac/mod fraction....
    uint32_t x=1, y, z;
    y = _mod; z = _frac;
    while (x != 0) {
        if (y>z) {
            x = y - z;
        }
        else x = z - y;
        y = z;
        z = x;
    }
    _mod /= y; _frac /= y;
   

}
*/
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
// updates dynamic registers, and writes values to PLL board
void ADF435x::update(){
    ADF435x::setR0();
    ADF435x::setR1();
    ADF435x::setR2();
    ADF435x::setR3();
    ADF435x::setR4();
    ADF435x::setR5();
    
<<<<<<< HEAD
    digitalWrite(ChipEnable,LOW); // Disable chip to write data 
=======
    digitalWrite(ChipEnable,LOW);
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23

    // writes registers to device
    ADF435x::programRegister(R5.reg5);
    ADF435x::programRegister(R4.reg4);
    ADF435x::programRegister(R3.reg3);
    ADF435x::programRegister(R2.reg2);
    ADF435x::programRegister(R1.reg1);
    ADF435x::programRegister(R0.reg0);
    
    digitalWrite(ChipEnable,HIGH);
}

void ADF435x::setFeedbackType(bool feedback){
    _feedbackType = feedback;
}

void ADF435x::powerDown(bool pd){
    _powerdown = pd;
    ADF435x::setR2();
    ADF435x::update();

}

void ADF435x::rfEnable(bool rf){
    _rfEnabled = rf;
    ADF435x::setR4();
    ADF435x::update();
}

// CAREFUL!!!! pow must be 0, 1, 2, or 3... corresponding to -4, -1, 3, 5 dbm.
void ADF435x::setRfPower(int pow){
    _rfPower = pow;
    ADF435x::setR4();
    ADF435x::update();
}

void ADF435x::auxEnable(void){
    _auxOnOff = 1;
    ADF435x::setR4();
    ADF435x::write4Bytes(R4.reg4);
}

void ADF435x::auxDisable(void){
    _auxOnOff = 0;
    ADF435x::setR4();
    ADF435x::write4Bytes(R4.reg4);
<<<<<<< HEAD
    ADF435x::update();
=======
//    ADF435x::update();
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
}

// CAREFUL!!!! pow must be 0, 1, 2, or 3... corresponding to -4, -1, 3, 5 dbm.
void ADF435x::setAuxPower(int pow){
    _auxPower = pow;
    ADF435x::setR4();
    ADF435x::update();
}

// REGISTER UPDATE FUNCTIONS

void ADF435x::setR0(){
    R0.d0.reserved = 0;
<<<<<<< HEAD
    R0.d0.integer = _INT; // not less than 23 decimal
=======
    R0.d0.integer = _integ; // not less than 23 decimal
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    R0.d0.frac = _frac;
    R0.d0.ctrl = 0;
}

void ADF435x::setR1(){
    R1.d1.reserved = 0;
    R1.d1.phaseAdjust = 0; // disabled
<<<<<<< HEAD
    R1.d1.prescaler = _prescaler; //  0 for 4/5 or 1 for 8/9 - VCO > 3.6GHz
=======
    R1.d1.prescaler = 1; //  4/5 or 8/9?
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    R1.d1.phaseValue = 1; //recommended value
    R1.d1.modulus = _mod;
    R1.d1.ctrl = 1;
}

void ADF435x::setR2(){
    R2.d2.reserved = 0;
    R2.d2.noiseMode = 3;
    R2.d2.Muxout = 6;
<<<<<<< HEAD
    R2.d2.refDoubler = _ref_doubler;
    R2.d2.refDivBy2 = _ref_halve;
=======
    R2.d2.refDoubler = _doubler;
    R2.d2.refDivBy2 = _halve;
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    R2.d2.rCounter = R_counter;  
    R2.d2.doubleBuffer = 0;
    R2.d2.chargePump = 7;
    R2.d2.LDF = _feedbackType; //fractional(0) or integer(1)?
    R2.d2.LDP = 0; //10nS (or 6nS if 1)
    R2.d2.PD_Polarity = 1;// 1 for noninverting or passive filter
    R2.d2.PD = 0;
    R2.d2.CP3state = 0;
    R2.d2.counterReset = 0;
    R2.d2.ctrl = 2;
}

void ADF435x::setR3(){
    R3.d3.reserved1 = 0;
    R3.d3.bandSelCkMode = 0;
    R3.d3.ABP = _ABP;
    R3.d3.chargeCancel = 0;
    R3.d3.reserved2 = 0;
    R3.d3.CSR = 0;
    R3.d3.reserved3 = 0;
    R3.d3.clockDivMode = 0b10;
    R3.d3.clockDivider = 1000; //divide by 1000 25Khz steps
    R3.d3.ctrl = 3;
}

void ADF435x::setR4(){
    R4.d4.reserved = 0;
    R4.d4.feedbackSel = 1;          //0= divided, 1= fundamental
    R4.d4.RF_div = _divider;
    R4.d4.bandSelCkDiv = 160;
    R4.d4.VCO_PD = 0;               // VCO powered up
    R4.d4.MTLD = 0;                 // Mute til lock disabled
    R4.d4.auxOutEnable = _auxOnOff;
    R4.d4.auxOutSel = 0;            //0 divided 1 fundamental
    R4.d4.auxOutPower = _auxPower;
    R4.d4.RF_OutEn = 1;
    R4.d4.OutputPower = _rfPower;
    R4.d4.ctrl = 4;

 }

void ADF435x::setR5(){
    R5.d5.reserved1 = 0;
    R5.d5.LD_Mode = 0b11; //lock detect mode pin goes high with lock
    R5.d5.reserved2 = 0;
    R5.d5.reserved3 = 0b11;
    R5.d5.reserved4 = 0;
    R5.d5.ctrl = 0b101;
}


// Program one 32 bit register on the ADF4351
// data bits 0-2 specify which register
// Note for double buffered data R0 must be written to again to clock in data 

void ADF435x::programRegister(uint32_t registerData) {
    
<<<<<<< HEAD
=======
    pinMode(ChipEnable, OUTPUT);  // Setup port
    pinMode(LoadEnable, OUTPUT);
    pinMode(DataClock, OUTPUT);
    pinMode(LockDetect, INPUT);
    pinMode(MultiplexData, INPUT);
    pinMode(SerialData, OUTPUT);

    
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    digitalWrite(LoadEnable, LOW);
    digitalWrite(DataClock, LOW);
    digitalWrite(SerialData, LOW);  // Initialize all data lines 
    bool bitdata = 0;
    uint32_t data = registerData;
    
  for (int i = 31; i >= 0; i--) {
        bitdata = bitRead(data, i); // Get each bit of register data, starting with MSB
    
        digitalWrite(SerialData, bitdata);  // and write to ADF4351
        //delay(10);
        digitalWrite(DataClock, HIGH);
        //delay(10);
        digitalWrite(DataClock, LOW);
        //delay(10);
  }
     
  digitalWrite(LoadEnable, HIGH);
         //delay(10);
  digitalWrite(LoadEnable, LOW);
         //delay(10);
  
}


// debugging only
void ADF435x::debug(){
    Serial.print("\nFrequency(KHz) = ");Serial.println(_freq);
<<<<<<< HEAD
    Serial.print("Integer = ");Serial.println(_INT);
=======
    //Serial.print("fPFD = ");Serial.println(tast);
    Serial.print("Integer = ");Serial.println(_integ);
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    Serial.print("Modulus = ");Serial.println(_mod);
    Serial.print("Fraction = ");Serial.println(_frac);
    Serial.print("R Counter = ");Serial.println(R_counter);
    Serial.print("Divider = ");Serial.println(_divider);
<<<<<<< HEAD
=======
    //Serial.print("Multiplier = ");Serial.println(multiplier);
    Serial.print("Channel Spacing = ");Serial.println(_channelSpacing);
    Serial.print("Reference Clock = ");Serial.println(_refClk);
>>>>>>> 058a5e32b4fc44428ffc6072c7e1b297d710ee23
    Serial.print("R0 = ");
    Serial.println(R0.reg0,HEX);
    Serial.print("R0 = ");
    Serial.println(R0.reg0,BIN);
    Serial.print("R1 = ");
    Serial.println(R1.reg1,HEX);
    Serial.print("R1 = ");
    Serial.println(R1.reg1,BIN);
    Serial.print("R2 = ");
    Serial.println(R2.reg2,HEX);
    Serial.print("R2 = ");
    Serial.println(R2.reg2,BIN);
    Serial.print("R3 = ");
    Serial.println(R3.reg3,HEX);
    Serial.print("R3 = ");
    Serial.println(R3.reg3,BIN);
    Serial.print("R4 = ");
    Serial.println(R4.reg4,HEX); 
    Serial.print("R4 = ");
    Serial.println(R4.reg4,BIN);
    Serial.print("R5 = ");
    Serial.println(R5.reg5,HEX);
    Serial.print("R5 = ");
    Serial.println(R5.reg5,BIN);
}

