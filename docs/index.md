## Kinetic Sculptures
Creative Embedded Systems Project 3

## The Assignment:
The goal is to create a kinetic sculpture with the following hardware: ESP32 TTGO T-display, Power source (battery/laptop), 28BYJ-48 Step Motor, DC Brush motor (9000 -25000 RPM (3V-12V)), and L293D. The devices will connect to WiFi in order to access an API endpoint and check if it returns true or false. When the endpoint returns true the device should run for 30 seconds and then stop.  

## Our Project:
For this assignment, we were inspired by the movements of figure skaters and dancers and decided to use the circular motion of stepper and DC motors to imitate some basic moves. I also wanted to learn how to use the 3D printers in the Barnard design center so we decided to look for figurines on thingiverse and use them for our project! This decision ended up being beneficial as the figures were super lightweight and worked pretty well with the motors we used. We did have some difficulty with the DC motors - they needed a little push in order to start spinning efficiently (both with the figurines attached and without). We decided to leave it this way and simply give a light tap to the figurines attached to the DC motors when our sculpture was running. Once we had all of the hardware and software connected, we put all of the pieces together in our enclosure, which resembles an ice skating rink (blue and white themes). 

![IMG_3843](https://user-images.githubusercontent.com/69936719/161873986-1ee746ce-54a0-4a47-b2ce-e41b748eb6bd.jpeg)

General Steps:
* Connecting 2 Stepper Motors
* Connecting 2 DC Motors 
* Building an enclosure
* Writing the software
* Lining up the motors with the enclosure openings 

## Hardware Setup:
* We used the following guidelines in order to connect the motors:
* DC MOTORS - https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_ESP32/blob/master/C/Sketches/Sketch_17.2_Control_Motor_by_L293D/Sketch_17.2_Control_Motor_by_L293D.ino
  * <img width="919" alt="Screen Shot 2022-04-05 at 8 50 56 PM" src="https://user-images.githubusercontent.com/69936719/161874224-c19bfa68-df5c-47ff-b6a9-6a6936c1d627.png">
* STEPPER MOTORS - https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_ESP32/blob/master/C/Sketches/Sketch_19.1_Drive_Stepper_Motor/Sketch_19.1_Drive_Stepper_Motor.ino
  * <img width="914" alt="Screen Shot 2022-04-05 at 8 51 27 PM" src="https://user-images.githubusercontent.com/69936719/161874287-05d4ec24-1e37-475e-b718-6d4df74aece0.png">

## Software Setup:



