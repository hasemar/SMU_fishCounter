# SMU_fishCounter
laser curtain fish counter developed by SMU senior design group

----NOTEPAD CHANGE LOG MAINTAINED BEFORE GITHUB MIGRATION-------
This version is in development and built from Fish_Counter_20161222:

The velocity measurement method will be integrated into this version
The main functions of logging to a LOG.TXT file and creating a matrix file work.

1/10/17:  Eliminated shift registers. Now lasers fire from individual outputs 22-whatever...
	  Has been compiled but not tested.

1/11/17: Wired in second row of lasers and tested program. It works.

1/12/17: Programmed in level sensor functionality. Works with a potentiometer

1/13/17: Working on 2 photo resistor rows. Trying to figure out recData function
	 might want to have 2 logTime vars and take the difference.
	 Created doubles of the variables involved in the main loop. Super ugly but just trying to get it to work.
	 I can't figure out how to get the velocity yet. I was trying to take the difference between the initial log (when the initial 	 breakage happened and the time when the second row breakage happened.)

1/18/17: added in some velocity stuff changing to Blakes version

1/19/17: changed the way we handle both columns. Uses multi-dimentional arrays (lasers x columns)
	 added pitot tube sensor and added water-object velocity comparison. 
	 added scenario comparison to determin when to log something 
	 currently compiles but have not tested on hardware yet.
