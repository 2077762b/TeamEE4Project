Display Mode

 - Speed
 - Coolant temperature
 - Air temperature
 - RPM
 - Gear
 - Volts
 - UGR image (to make it look great!)

Config Mode (serial)

char is_full ( 1 - memory has been written before so obtain values)
             ( 0 - use default hard coded values)

STRUCTURE: int coolant_threshold
           int speed_units (1 for MPH, 0 for KPH)
           int array [256] CAN IDs
           int number_CAN_IDs

 - Coolant Threshold
 - MPH vs KPH
 - CAN IDs (add and remove)

Diagnostics 

 - Columns: CAN ID | CAN Value HEX
 - (Update value only every 1 second)
 - Pages when the number of CAN IDs are too many