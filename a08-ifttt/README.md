Will get this working for Arduino eventually.

So far I expect an IFTTT webhook that has the event name test-webhook. You have to go to the webhooks documentation page that shows you your key. In my code I have the key as jjjjjjjjjjjjjjjjjjjjjjj  Then go to the view activity, refresh after sending and see if the values value1, value2, value3 have been send. First step. Then we have to recieve some information and that might be the hardest part.






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

Best to have a public folder and run using gitpod and the command

```
apachectl start


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
