# hrssystem
HRS Reconstruction System

## What is HRS Reconstruction System?
HRS Reconstruction System is an experiment in computer vision. In this program
I try to replace difficult mathematical calculations with a rendering on a video card. 

## System requirements 
qt5-devel package.
proprietary drivers for your video card, because program uses opengl pixel buffer.

## Building program
Type in your console	
	cd ./path_to_program
	qmake
	make
For executing program type 
	./bin/hrssystem

## Examples
Please view examples in directory ./examples.
Start program and open some of this projects. Then start reconstruction. 
If you increase steps of reconstruction the precision will increasing too, but reconstruction
may becoming very slow. View as mesh action is experimental use it careful.

## Contributions
If you want to develop this project, please write mail to me.
	 
## Author
Hramchenko Vitaliy <hramchenko@bk.ru>
