# KineticSculptures
Creative Embedded Systems Module 3

Group Members: Talia Krumerman and Ariel Goldman 

Project Hardware:
* ESP32 TTGO T-display
* Power source (battery/laptop)
* 28BYJ-48 Step Motor
* DC Brush motor (9000 -25000 RPM (3V-12V))

Project Specs: 
This assignment requires you actuate the physical world - you may choose one of two configurations for this project - either 1) kinetic sculpture or 2) Interactive kinetic art. The difference amounts to whether or not you choose to integrate input from the user into your work.

You may create a team of up to three group members. When working in a group, your hardware resources are pooled. Your device must adhere to the following specification. You must use a minimum of (2 * number of group members) motors and may use as many motors as you have available to your group. The device must have an enclosure or enclosures.

Your device must utilize an API (https://github.com/mbennett12/kinetic-sculpture-webapi) that will allow you to start the device in motion. The device must be safe to operate in intervals of at least 30 seconds multiple times in a row.

Our Project:

* Hardware:
  * ESP32, 2 DC motors, 2 Stepper Motors, and an L293D (driver) all connected to a breadboard and powered by a computer. Additionally, we used an iphone to connect the ESP32 to a hotspot for Wifi 
  * We created an enclosure, cut out holes from the top to make room for the motors and 3D printed figurines. We also used waterbottles to prop the motors up in position.
![IMG_3817](https://user-images.githubusercontent.com/69936719/161862624-041b03ca-6f07-48ce-8086-b0a48a149653.jpeg)
![IMG_3840](https://user-images.githubusercontent.com/69936719/161862632-0bf43f81-7ee3-4b25-807b-91d9225ad538.jpeg)
![IMG_3843](https://user-images.githubusercontent.com/69936719/161862637-c1e29a94-87e7-46bd-b766-a5de667cb356.jpeg)

* Software: 
  * We wrote a program that would work on both cores of the ESP32. One core would constantly check http://134.122.113.13/YOUR UNI/running. The sculpture should start moving when this endpoint returns true. This endpoint will return true for 30s when you press the button at http://165.227.76.232:3000/YOUR-UNI, or when we set all sculptures to run together.
  * The other core dealt with running all the motors once the the endpoint returned true.


Some Links We Found Helpful:
 - https://lastminuteengineers.com/l293d-dc-motor-arduino-tutorial/
 -https://github.com/Freenove/Freenove_Ultimate_Starter_Kit_for_ESP32/blob/master/C/Sketches/Sketch_17.2_Control_Motor_by_L293D/Sketch_17.2_Control_Motor_by_L293D.ino
- https://github.com/mbennett12/kinetic-sculpture-webapi/blob/main/example_HTTP_get.ino
- https://gist.github.com/santolucito/9190ebd85c56f16d47ef32f72e5510cd 
 
3D printed figurines:
 - https://www.thingiverse.com/thing:3088023/files 
 - https://www.thingiverse.com/thing:1000629 
 
