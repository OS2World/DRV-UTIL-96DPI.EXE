README.TXT for 96DPI 1.0.0
--------------------------

INSTALLATION
------------
To install 96dpi, simply copy the file 96dpi.exe into a
suitable directory and run it from WinOS/2.


USAGE
-----
Start the program from a WinOS/2 session.

It determines the currently used WinOS/2-video-driver.
If it is one of the GRADD drivers (IFGDI2VM.DRV for Fullscreen or
ISGDI2VM.DRV for Seamless) it checks if the patch is applicable.
If yes it makes a copy (I?GDI2VM.BAK) of the original driver and 
patches the driver.

Finally you have to restart WinOS/2.

If you create a program-item in the WinOS/2 StartUp folder
it will pacht the driver whenever a new driver is installed.



PARAMETERS
----------


REMARKS
-------
96DPI patches only the currently used gradd-driver.
To patch fullscreen you have to run it from a FS-WinOS/2
likewise for seamless.


STATUS
------
This program is free software; you can redistribute it and/or modify it.


DISCLAIMER
----------
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
The entire risk is with you.


Content of package
------------------
96DPI.EXE         The executable
README.TXT        This file
SOURCE.ZIP        Source (Borland C++ 3.1 project)
