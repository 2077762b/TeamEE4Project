SOFTWARE INFORMATION

The contained software is for the use with the Team VoltsWagen steering wheel display.

This was developed as part of our fourth year Team Project EE4 course at Glasgow University.

Christopher Brown
Jack Croal
Cameron Houston
Alex Smith
Jokubas Surgailis

The software works with the Arduino Due, and all required libraries are included in the 'Libraries' folder.

DEVICE OPERATION

The device has 3 modes of operation: Display Mode, Diagnostics Mode and Configuration Mode.

    Display Mode
    
        This is the default mode of operation for the device.
        When plugged in to a CAN bus, the display will show the various values and units associated with the 
        status of the car.
        The CAN identifiers used for this mode are:
            0x2000
            0x2001
            0x2002
            0x2003
            0x2004
            0x2005
            
    Diagnostics Mode
    
        This mode allows the user to see the raw CAN data being submitted to the device.
        It displays the configured CAN identifiers on the right of the screen, and the incoming data on the left (HEX)
        Pages have been implemented and can be 'turned' using the change page function.

    Configuration Mode
    
        This is activated by plugging the device to an arduino Serial USB port on a computer.
        When propted, the user will be able to change the various configuraton settings for the device.
        This includes:
            Threshold for coolant temperature error symbol
            Speed units in MPH or KPH
            CAN frame identifiers for use with the diagnostics software