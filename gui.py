class ADF453xRegister:
    """ Documentation
    
    Class to create C++ struct like data packed into a 32 bit binary variable 
    to write to a register in a the ADF4351 PLL chip
    """
# Class attributes 
  register =  '{0:32b}'.format(0) # create a 32 bit binary number as register data 
#  address =  '{0:3b}'.format(0) # 3 bit binary number address of register LSBits of register 
  
# Create class instance 
  def __init__(self, reg_name, **variables[name, length, data]):
# Instance attributes
# creates a new list containing the data passed to each instance - can be of arbitrary length
# In the format [variable_name, variable length(bits), variable data(binary)]
    self.data = [**variables]   
    self.name = reg_name # each instance has a name
    
    for d in variables
        register = register = d.data
        register = >>register, d.length

# Class methods 
# Pack binary data into register
  def create_reg():
    pass

# Program 32 bit register
# 3 wire serial interface MSB first
  def program_reg():
    pass

# get and set individual variables 
  def get_data():
    pass

  def set_data():
    pass
