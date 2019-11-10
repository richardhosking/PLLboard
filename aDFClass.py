
class ADFReg:
    """ Creates a 32 bit number to write to ADF4531 Register containing various parameters
    
    Arbitrary number of parameters , each of arbitrary length 
    Attributes:
    name
    Nested list of parameters
    register 
    Effectively private as it is only called by ADF4531 class 
    """ 
  
# Create class instance 
    def __init__(self, reg_name):
# Instance attributes
# creates a new list containing the data passed to each instance - can be of arbitrary length
         self.data = []   
         self.name = reg_name # each instance has a name
 
# Class methods 

# Create a 32 bit register with binary data 
# Data is list of register definitions of arbitrary length
# in the format [variable_name, variable length(bits), variable data(binary string)]
# MSBit first
# Pack binary data into register using join()

    def add_data(self, data):
         binary_data = '0'
         self.register = 0
         i=0
         for d in data:
             self.data.append(data[i])
             if i==0:
                binary_data = data[i][2]
             else:
                 join_data = (binary_data, data[i][2])
                 binary_data = ''.join(join_data) 
             i+=1
         
         self.register = binary_data    

# end of class definition

class ADF4531:
    """ Class containing variables and functions to drive the ADF4531 Fractional N PLL synthesizer chip
    
    """
# Create instance with instance variables and default values 
    def __init__(self, PLL_name):
        self.output_freq = 0 		# main output frquency KHz
        self.reference_clock = 25000 	# Reference clock 25 MHz in these modules
        self.integer = 0    		# integer part of PLL main divider
        self.phase = 0 			# Output phase can be shifted
        self.rf_divider = '000' 		# Output divider 1(000) to 64 (111)  		
        self.auxPower = '00'		# Output power 00 = -4dBm, 01 = -1dBm, 10 = +2dBm 11 = +5dBm 
        self.mainPower = '00'
        self.modulus = 1000		# Modulus of fractional N divider Int steps 1MHz hence this will give 1KHz steps 
        self.VCO = '0'			# VCO power down 1
        self.fraction = 0		# fraction of fractional N divider
        self.reference_counter = 25	# divide main reference to give phase detector frequency of 1MHz
        self.powerdown = '0' 		# Power the chip down 1
        self.auxRFEnabled = '0' 		# Aux output off 0 
        self.mainRFEnabled = '1' 		# Main RF out 0 = off 
        self.feedbackType = '1' 		# feedback direct to VCO or via output divider 
        self.prescaler = '0' 		# Output prescaler 4/5 if VCO >3.6GHz must be set to 8/9 1
        self.ABP = '0' 			# antibacklash pulse width 6ns for Fractional N mode
        self.ref_doubler = '0'		# Reference doubler to extend range of Phase detector active 1 
        self.ref_halve = '0' 		# reference halve set active 1 
        
        # Port pin assignments
        self.chipEnable = 14;
        self.loadEnable = 5;
        self.dataClock = 3;
        self.serialData = 4;
        self.lockDetect = 15;
        self.multiplexData = 6; 
        
        # ADF4531 Registers with maps of variables 
        # many are "hard-wired" - see below and ADF4531 datasheet for details  
        R0 = ADFReg('R0')
        R0data = [['reserved',1,'1'],  ['integer',16, self.integer],  ['fraction', 12,  self.fraction],  ['address', 3,  '000']]
        
        R1 = ADFReg('R1')
        R1data = [['reserved',3,'000'], ['phase_adj', 1, '0' ],  ['prescaler',  1,  self.prescaler],  ['phase',12, '000000000000'],  ['modulus', 12,  self.modulus],  ['address', 3,  '001']]
        
        R2 = ADFReg('R2')
        R2data = [['reserved',1,'0'], ['noise_spur_mode',  2,  '00' ], ['mux_out',  3,  '000'], ['ref_doubler',  1,  self.ref_doubler] ,  ['ref_halve',  1,  self.ref_halve] , 
        ['reference_counter',10, self.reference_counter], ['double_buffer',  1,  '0'],   ['charge_pump_current', 4,  '1000'], ['LDF',  1,  '0'],  ['LDP',  1,  '0'],  ['PD_polarity',  1,  '0'] ,  
        ['power_down',  1,  '0'],  ['CP_3state',  1,  '0'],  ['reset_counter',  1,  '0'],  ['address', 3,  '010']]
        
        R3 = ADFReg('R3')
        R3data = [['reserved', 8, '00000000'],  ['ABP',  1,  self.ABP],  ['charge_cancel',  1,  '0'], ['reserved', 2, '00'], ['CSR',  1,  '0'],  ['reserved',  1,  '0'], 
        ['clk_div_mode', 2,  '00'], ['clock_divider',  12,  '000000000000'],  ['address', 3,  '011']]
        
        # 
        R4 = ADFReg('R4')
        R4data = [['reserved',8,'00000000'],  ['feedbackType',1, self.feedbackType], ['rfdivider',3, '000'], ['band_select_clk_divider', 8,'00000000'], ['VCO_power_down',  1,  '0'], 
        ['MTLD',  1,  '0'],  ['aux_output_select',  1,  '0'],  ['aux_output_enable',  1,  auxRFEnabled],  ['aux_output_power',  2,  self.auxPower],  ['output_enable',  1,  self.mainRFEnabled],  ['output_power',  2,  self.mainPower],  
        ['address', 3,'100']]
        
        R5 = ADFReg('R5')
        R5data = [['reserved',8,'00000000'],  ['LD_pin_mode',2, '00'],  ['reserved', 19,  '0110000000000000000'],  ['address', 3,  '101']]
        
    def initialize(self):
        pass
        
    def update_device(self):
        pass
        
    def write_to_register(register):
        #digitalWrite(loadEnable, LOW);
        #digitalWrite(DataClock, LOW);
        #digitalWrite(SerialData, LOW);  // Initialize all data lines 
        #bool bitdata = 0;
        #uint32_t data = registerData;
    
        #for (int i = 31; i >= 0; i--) {
        #bitdata = bitRead(data, i); // Get each bit of register data, starting with MSB
    
        #digitalWrite(SerialData, bitdata);  // and write to ADF4351
        #digitalWrite(DataClock, HIGH);
        #digitalWrite(DataClock, LOW);
   
     
        #digitalWrite(LoadEnable, HIGH);
        #digitalWrite(LoadEnable, LOW);
        pass
        
    def get_variable(variable):
        pass
        
    def set_variable(variable):
        pass
        
 
    

     
    
    
    
    
# End of class definition    
r = ADFReg('R1')
rdata = [['reserved',1,'1'],  ['frac',12, '000000000000'],  ['integer', 16,  '1111111111111111'],  ['address', 3,  '001']]
r.add_data(rdata)
print r.data
print r.register

PLL1=ADF4531('PLL1')
