#######################
### Library: SPFD5408
### Author : Joao Lopes - joaolopesf@gmail.com
### Versions:
### 0.9 - July 2015 - first beta version
### Observations:
### This library is a Adafruit’s libraries for TFT,
### ported to works with SPFD5408 controller of cheap TFT 2.4 Shield
### License:
### MIT license, all text above must be included in any redistribution
#######################

DISCLAIMER:

This Library is NOT provided by AdaFruit and they have not
endorsed it. This library is just a lot of modifications in the Adafruit Library,
to works in TFT with SPFD5408 controller (cheap shields)

ATTENTION: 

Due to variations in Chinese shields with some controller,
there is no guarantee that will work for everyone.

I’ll try a more suppliers in aliexpress to test more variations.

Please let me know if this happens.

Also please send me feedback, problems or suggestions.

INFORMATIONS:

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder to SPFD5408. 

Place the SPFD5408 library folder your <arduinosketchfolder>/libraries/ folder. 
You may need to create the libraries subfolder if its your first library.

Or more simple, you access the Arduinos’s IDE menu : sketch/add library

Restart the IDE

If you download any code that uses Adafruit Libraries, please verify it:

- Pinout XM XP, must be:

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

—- Calibrate before run 
Exists one sketch written for my, to help in calibration of touch
See it in examples folder
Run it and change this parameters:

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

————————

All changes in Adafruit code is marked with:


  // ### SPFD5408 change -- Begin

  (change)

  // ### SPFD5408 change -- End


——————

Examples:

	adafruit_originals

		From Adafruit Libraries — Not works with the SPFD5408

	
	spfd5408_calibrate

		Help the calibration of touch (resistive)

	spfd5408_tftpaint

		example of Adafruit changed to work with the SPFD5408

	spfd5408_graphictest

		example of Adafruit changed to work with the SPFD5408

	spfd5408_rotationtest

		example of Adafruit changed to work with the SPFD5408



		
	
		


