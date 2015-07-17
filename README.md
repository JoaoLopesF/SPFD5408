#SPFD5408 Library

This library is the Adafruit TFT Libraries changed to works in TFT 2.4 shields with the SPFD5408 controler

This library is the last version of Adafruit, inclusive with buttons features.

The TFT 2.4 is cheap TFT, that generally is form China. 
With poor documentation, libraries e how to works

When we try to use the TFT 2.4 with SPFD5408 controller in sketches with Adafruit TFT libraries,
several things can happen :

	- White Screen
	- Screen with noise
	- Touch does not work
	- The colors are reversed
	- And other things

After trying for several days trying the solutions I found on the web, and none works 100%.
So I decided to do a specific to this controller.
And it was easy for those who are beginning to work with TFT.
And avoid much headache in this.

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

INSTALATION:

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder to SPFD5408. 

Place the SPFD5408 library folder your <arduinosketchfolder>/libraries/ folder. 
You may need to create the libraries subfolder if its your first library.

Or more simple, you access the Arduinos’s IDE menu : sketch/add library

Restart the IDE

If you download any code that uses Adafruit Libraries, please verify it:

—-  Pinout XM XP, must be:

	#define YP A1  // must be an analog pin, use "An" notation!
	#define XM A2  // must be an analog pin, use "An" notation!
	#define YM 7   // can be a digital pin
	#define XP 6   // can be a digital pin

	(please verify it, if only a blank screen or noise is showed or touch doesnt works)

—- Calibrate before run 

	Exists one sketch written for my, to help in calibration of touch
	See it in examples folder
	Run it and change this parameters:

	#define TS_MINX 150
	#define TS_MINY 120
	#define TS_MAXX 920
	#define TS_MAXY 940
	
	(please verify it if the point of touch is not accurate)

————————

All changes in Adafruit code is marked with:


  // ### SPFD5408 change -- Begin

  (change)

  // ### SPFD5408 change -- End

  This is useful if You see the points that be workeds for any touble
  
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

