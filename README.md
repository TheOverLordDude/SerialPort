# SerialPort
A class for C++ to handle Serial Port read/write on what is currently a minimal level. 
No selection of baudrates based on parameters, or partial read/write. 
It basically jsut reads/writes at the moment for widnows. 
Will possibly work later on linux/mac. 
It is header only, relying on windows.h include, so it can be used by Mingw for sure

The SerialPortV2.h just needs to be included to your project, and declare a SerialPortV2 object, and go from there. 
The read/write works in strings, though the write has a buffer maximum of 64 at the moment.
This may change to become a parameter of the function

Any updates/additions are welcome. Be it add compatibility with Linux, OSX, or improving the current functions.
It is requested it is all kept to the single file to prevent unneeded complexity.
However, seperate "WindowsSerialPortV2.h" "LinuxSerialPortV2.h" and "OSXSerialPort.h" are acceptable
