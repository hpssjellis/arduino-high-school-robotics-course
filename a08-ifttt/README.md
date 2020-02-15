Will get this working for Arduino eventually.


Checkout the backups and 

http://sheepdogguides.com/arduino/art4ifttt.htm

IFTTT API at https://platform.ifttt.com/docs/api_reference



https://platform.ifttt.com/docs/api_reference



```

Headers

Accept:          application/json
Accept-Charset:  utf-8
Accept-Encoding: gzip, deflate
Content-Type:    application/json

```
















Using IFTTT with the particle.io Photon

Video [video A08-IFTTT](https://youtu.be/DOlYkTn84Bs?list=PL57Dnr1H_egsL0r4RXPA4PY2yZhOJk5Nr&t=5s) Have your Photon control other devices on the web using https://ifttt.com. Today we just use a button to turn on D7 but using IFTTT we can try to control other students D7 buttons. Note: use a slider to reset your photon's ability to send to IFTTT and a button to actually send the message.

1. Flash a08-ifttt.ino onto your photon
1. connect a push button from 3V3 to D2 and another pushbutton from 3V3 to D4 on the Photon
1. Login to ifttt  https://ifttt.com
1. These steps seem to be constantly changing but the basic idea is to subscribe to an event from your photon capture it 
and send another event back to the Photon





By Jeremy Ellis

Canadian High School Robotics Teacher

Maker of http://www.rocksetta.com

Twitter https://twitter.com/rocksetta

Use at your own risk!
