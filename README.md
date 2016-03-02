# bassman

## Project Name: Sound Reactive T-Shirt

## Abstract

A microphone picks up the music playing in the background with the LED strips attached to the cloth material reacting to the beats of the music being played using Adafruits Arduino Compatible Wearables Platform, Flora which will be handing the processing. 

## Components

* Hardware 
	* **Adafruit Flora -** Adafruit's Arduino-Compatible Wearables Platform
	* **Electret Microphone Amplifier -** Microphone for listening/recording the song
	* **Adafruit NeoPixel Digital RGB LED -** LED Strip which will be attached to the cloth and connected to the Flora.
	* Soldering Iron 
	* Ribbon Cables

* Software
	* Programming Language - C/C++ 
	* Arduino 1.6.x IDE

* Algorithms
	* Fast Fourier Transform to find peak values of songs

## Use cases

* Target Demographic
	* Concert Goers
	* Music Enthusiasts
	* Deaf people.
	* If not used on cloth material, it can be used to detect sounds in a room and output it with a light, which can then be used to send alerts as well.

* Significant contributions
	* Dancers and Choreographers, can use this make a dance routine which can react to pre-recorded music and tell a story with the music.
	* Allow deaf people to know what specific sounds mean, example knowing when someone is behind you.


## Coolness and Novelty
* Sound Reactive Clothes That’s pretty cool honestly, and with the right music and dance techniques you would stand out of the crowd.

## Circuit Diagrams

![Circuit Diagram](/img/circuit_diagram.png)

* **Analog** - Microphone connected to pin A9
* **Digital** - LED’s connected to pin D6

## Libraries Used

* Adafruit_NeoPixel.h (https://github.com/adafruit/Adafruit_NeoPixel)
* math.h

## Challenges 

A couple of challenges arose during the project
* Soldering small pieces of wire to achieve the shape of LED’s.
* Debugging Mic readings to find peak values.
* Realizing setting brightness of LED’s can risk of crashing when running on a 3.7 V battery, can increase brightness with more voltage.

## Pictures

![Final Design](/img/final_design.png)

## Videos

[Demo of video](https://www.youtube.com/watch?v=A1DoPsuxhUY)

## Contributors

* Mohsiur Rahman
	* [Twitter - mohsiurr](https://twitter.com/mohsiurr)
	* Email : mohsiurr@buffalo.edu

## License

The MIT License (MIT)

Copyright (c) 2015 Mohsiur Rahman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER


