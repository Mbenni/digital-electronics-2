# Project BPA-DE2

## Team members
- Mehdi Bennani
- Benjamin Della Maggiore Mahiques

## Hardware description

![image](https://user-images.githubusercontent.com/115087529/206517397-f3814c5e-a0bf-4396-a704-cb619e413d11.png)

![image](https://user-images.githubusercontent.com/115087529/206517477-b447cb3a-be0f-4a4e-aef1-59eb16b421ad.png)

On the two diagrams above we can see the assembly that we have made for each device.
For our project, we have used the following connections : 

**Connections LCD to Arduino :**
We use the down layer for J1(1 to 6) and J2(1 to 6):  
	J11  ->  PD4  
	J12  ->  PD5  
	J13  ->  PD6  
	J14  ->  PD7  
	J15  ->  POWER GND  
	J16  ->  +5V  
	J21  ->  PD8  
	J22  ->  GND  
	J23  ->  PD9  
	J25  ->  POWER GND  
	J26  ->  +5V  

**Connections Joystick to Arduino :**  
	GND  ->  POWER GND  
	5V     ->  5V  
	VRx  ->  PC0 (A0)  
	VRy  ->  PC1 (A1)  
	SW   ->  PD9  

Here is the list of components used:
- Arduino Uno with AtmelMega328P MCU.
- Joystick with 2ADC signals and a switch.
- Digilent PmodCLP LCD module.
- A breadboard

## Description of component

Below you can find a description of each component.

### Arduino Uno ATmega328P

![image](https://user-images.githubusercontent.com/115087529/206517795-929a856f-2cbb-4f8b-937a-d43260e10e9b.png)

The Arduino Uno is an open-source microcontroller board based on the Microchip ATmega328P microcontroller that can be integrated into a variety of electronic projects.
It offers 14 digital input/output pins and 6 analog inputs, and a 16MHZ clock signal among others.

### Joystick

![image](https://user-images.githubusercontent.com/115087529/206517723-990521b5-93a9-40ea-9d40-5b40264de34a.png)

The Analog Joystick is a set of two connected potentiometers that provides vertical (Y-axis) and horizontal (X-axis) position information.
There are five pins: GND, VCC. VRx (corresponds to x-axis) and VRy (corresponds to y-axis) are analog signals. Then, SW a digital signal.

### Digilent PmodCLP LCD module

The Digilent PmodCLP is a 16x2 character LCD used to display up to 32 different characters at a time. It uses a 8-bit parallel data interface for communication.

### Breadboard

![image](https://user-images.githubusercontent.com/115087529/206517941-1f2c4093-6160-4314-9d03-dc65829fafcc.png)

A breadboard is a solderless construction base used for developing an electronic circuit and wiring for projects with microcontroller boards like Arduino.

## Description of the implementation

We are connected a joystick, a screen aid to an Arduino. The joystick allows you to move. The voltage analog value is retrieved and converted into digital value from the ADC channel 0 or 1 to finally display it on the LCD screen. It also displays whether the joystick goes right, left, up, down, or center.

## Software description

Our project's library and source has the following structure:
```
├── lib
│   ├── gpio
│   │   ├── gpio.c
│   │   └── gpio.h
│   └── lcd
│       ├── lcd.c
│       ├── lcd.h
│       └── lcd_definitions.h
│       
├── include
│   └── timer.h
│
└── src
    └── main.c
```

Let's describe all our files.

### GPIO

AVR MCU control registers are defined in the GPIO library. The library is divided into two types of files: header files and source files.
The first file contains data type definitions, function prototypes, includes, definitions, and C preprocessor commands. As the name suggests, the header file extension is .h.
The source .c file is used to implement the code.

gpio.c : https://github.com/Mbenni/digital-electronics-2/blob/main/Project_Benjamin_Mehdi/lib/gpio/gpio.c  
gpio.h : https://github.com/Mbenni/digital-electronics-2/blob/main/Project_Benjamin_Mehdi/lib/gpio/gpio.h

### LCD

lcd.c : https://github.com/Mbenni/digital-electronics-2/blob/main/Project_Benjamin_Mehdi/lib/lcd/lcd.c  
lcd.h : https://github.com/Mbenni/digital-electronics-2/blob/main/Project_Benjamin_Mehdi/lib/lcd/lcd.h  
lcd_definitions.h : https://github.com/Mbenni/digital-electronics-2/blob/main/Project_Benjamin_Mehdi/lib/lcd/lcd_definitions.h  

### INCLUDE

timer.h : https://github.com/Mbenni/digital-electronics-2/blob/main/Project_Benjamin_Mehdi/include/timer.h  

### main

main.c : https://github.com/Mbenni/digital-electronics-2/blob/main/Project_Benjamin_Mehdi/src/main.c  

## Flow chart

# Interrupt service routine on Timer1  
  
Use single conversion mode and start ADC conversion every 33 ms.  
  
![image](./Flowchart_ISR_(TIM1).png)

# Interrupt service routine on Timer2  
  
Read the push buttons' values every 16ms and display the happenening on the LCD screen .  

![image](./Flowchart_ISR(TIM2).png)

# Interrupt service routine on ADC  
  
Read ADC value and display the direction of the joystick depending on this value. Every time an ADC occurs the ADC channel is swapping between 1 and 0.  

![image](./flowchart_ISR(adc_vect).png)


## Video

You can fin a link for a the video of our project :  
https://youtube.com/shorts/slyg9RKW3N8?feature=share

## References

Joystick : https://navody.dratek.cz/navody-k-produktum/arduino-joystick-ps2.html   
	 	   https://lastminuteengineers.com/joystick-interfacing-arduino-processing/  
Pmod LCD : https://digilent.com/reference/pmod/pmodclp/start

















