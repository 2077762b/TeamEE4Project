

Config Mode (serial)

 - x number of 'slots', one for each debug value
 - Serial mode allows the user to change what is going to be displayed in each slot
 - When a user wishes to change the information in a slot, they are promted with:
     - name of new debug value (needs a char limit)
     - CAN id
     - size of value (bytes)
     - starting byte of value in CAN frame
 - This means a function for displaying all the slots and the name of the value that's
   in them is needed

 - Allows for the changing of the threshold value of coolant and RPM

Debug Mode

 - Allows user to view information from the x number of slots selected by the config mode
 - One line of text across screan per slot