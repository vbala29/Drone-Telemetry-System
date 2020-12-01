# Drone-Telemetry-System
Problem: How can we track the location of a drone, as well as additional data such as its bearings, acceleration, and gyroscope readings. 

Solution: Create a telemetry system composed of a physical display with automatically and manually updated components, as well as a phone app service allowing us to track the drone. 

**Solution Image**
![IMG_25632 copy](https://user-images.githubusercontent.com/56012430/100781017-7becc880-33d8-11eb-8ec2-02723ae42b97.jpg)

Overview: ESE111 Final Project by Vikram Bala and Miles Batley. Contains files to retrieve data from two ESP8266s mounted on a drone connected to a GY-521 Accelerometer and a NEO-6M GPS module. This data is sent to an adafruit.io online feed (see below for how to set up Adafruit.io key and wifi). Also contains files to  retrieve data from Adafruit via HTTP API GET requests on a nodeMcu connected to a display module (see images). Files allow for this ground station nodeMCU to send data via UART to an Arduino UNO connected to a 7 segment 4-digit display, as well as an Arduino uno connnected to the large display module box seen below. Lastly, data is sent to an iOS application, "Blynk", which displays the location of the drone on a map with information about latitude, longitude, compass direction, and GPS satillites acquired. **These programs require you to input your own wifi credentials and API key as well as API HTTP requests to access feed data.**

# Code Cited and Feed Supplier
Adafruit.io is the provider of this feed service. Please read their terms of use before using their data for any purposes. 
Blynk is a third party application availiable for download from the iOS App Store. 
Please see headers of .ino code files for credit to where some code was derived from. 

# Components: 
**DRONE MOUNTED - GY-521 and Neo-6M GPS, Two ESP8266s (NodeMCU)**
Related Directories: GPS_BLYNK & DroneNodeMCU

On a DJI Spark drone, a GY-521 and Neo-6M GPS were mounted, as well as two ESP8266 boards (NodeMCUs). The GY-521 allows for data concerning
acceleration and gyroscopic values on three axes to be collected. The Neo-6M GPS was used to track compass heading, and latitude/longitude. 
One NodeMCU was used to send data from the GY-521 to the Adafruit.io cloud. The code for this operation can be found in the directory "DroneNodeMCU."
Gyroscope values are in degrees per second, and accelerometer values are in "g"s. Specifically, we tracked acceleration on the x, y, and z axis, and gyroscope measurements to track angular velocity in the y direction of the accelerometer, which was the drone's pitch axes. While the accelerometer data was send to the Adafruit.io cloud, and could be viewed on their online dashboard (see next section figure 4), the GPS data was sent to the Blynk cloud, and was able to be viewed on the Blynk app (see next section figure 5). Note that the Neo-6M GPS takes about 10 minutes to warm up and acquire sufficient sattilites for geolocation. The GY-521 gyroscope values were quite sensititve, and often displayed values of 2-3 deg/sec even when the drone was laid flat. 

Figure 1: Picture of the drone flipped upside down. 
![IMG_0024](https://user-images.githubusercontent.com/56012430/100530094-cb09e200-31bb-11eb-9947-90f02a060a60.JPG)

Figure 2: Side view of the drone flipped upside down. 
![IMG_0022](https://user-images.githubusercontent.com/56012430/100530106-dfe67580-31bb-11eb-9a57-0bcbf322cc47.JPG)

Figure 3: View of the drone upright
![IMG_0021](https://user-images.githubusercontent.com/56012430/100530115-f2f94580-31bb-11eb-815d-4f5ac277fbf5.jpg)

Figure 4: Adafruit.io online dashboard. Ac = acceleration, where x, y, and z are the corresponding axes. Gyy is the angular velocity on the drone's pitch axis, which is the y-axis of the GY-521. 
<img width="800" alt="Screen Shot 2020-11-28 at 7 04 51 PM" src="https://user-images.githubusercontent.com/56012430/100530282-17562180-31be-11eb-9f58-9d788313af70.png">



**GROUND STATION - Blynk Application (iOS 14)**
The first part of our ground station was the Blynk application, which displayed heading (compass bearing) of the drone, its latitude/longitude,
and the amount of satillites acquired by the GPS module. This application was chosen because it was easy to implement in code, and allowed for features such
as plotting a lat/long pair side by side with the phone's location on a dynamic map (both satillite and road map). 


Figure 5: Blynk Application while Drone Telemetry System is un use. Note that the feature that displays location of the drone on a road map has been 
cropped out, due to privacy concerns. In addition, decimal points for the lat/longitude have been redacted for simliar concerns. 
![100530340-be3abd80-31be-11eb-936f-618c0a8c5af1](https://user-images.githubusercontent.com/56012430/100571395-0500e400-32a1-11eb-88a4-33c666a705c2.PNG)



**GROUND STATION - ESP8266 (NodeMCU)/ARDUINO UNO & 7-segment 4-Digit Display**
Related directories: APIRequester & 7-Seg_Display 

The API Requester directory pertains to a NodeMCU that was mounted behint the display module/box (See figure 7). This nodeMCU used HTTP Get commands
to access the Adafruit API and return data about acx, acy, acz, and gyy (see figure 4)—the acceleration and gyroscope. This data was then sent via serial TX to two Arduinos. One Arduino was connected to a 7-segment 4-digit display (non I2C, so a lot of wires!). This Arduino parsed the data it recieved over its serial RX port and converted the gyroscope pitch value to something that could be displayed on the 7-segment display. Note that only the absolute value was displayed, as we valued significant figures more than the direction of the angular velocity. THe 7-Seg_Display directory contains a folder of redacted code that was ineffecient and bug filed. The new code uses a library that makes writing multi digit numbers to a 7-segment display much easier. 


**GROUND DISPLAY BOX - Arduino (Arduino/C: Controls LCD, 3 Status LEDs, and a Button)**
Related Directories: DroneTelemetryDisplay & APIRequester
This display box has an Arduino that controls three LEDs, a button, and an LCD. Note that the yellow button depicted does not currently serve any purpose, but is wired to support a future need (e.g. reset). Currently, the green LED blinks when the Arduino controlling the LCD has recieved new data from the NodeMCU that requests from the API. The LED on the far left is always on when power is supplied, and is simply to trobuleshoot if/when power is being supplied (in the case that the LCD has stopped working). The LED in the center blinks when serial data is not being recieved, and is more of an indicator of where in the program the Arduino is, rather than serving any purpose for the user.

The LCD displays acy, acx, acz, and gyy when the user presses the blue button. Once the blue button is pressed, the LCD will cycle through displaying each of these values, before continually displaying the gyy (pitch gyroscope) value until the user presses the blue button again, where the cycle is repeated. Pressing the blue button when no new serial data has been recieved will not yield any change in values. The user will not recieve a response if they press the blue button while the LCD is cycling through values (takes a few seconds), or if the LCD is recieving serial data (which only takes a second). The display box has additional features, such as a fans which turn on only if both the Arduino and a seperate USB cable (that powers the fans) are plugged in; a simple AND gate was used for this. 


Figure 6: The Display Box, 7-segment display, and redcated Blynk application display. 
![IMG_25632 copy](https://user-images.githubusercontent.com/56012430/100781017-7becc880-33d8-11eb-8ec2-02723ae42b97.jpg)

Figure 7: The backend of the display box and 7-segment display. Note the LCD here was used for testing purposes to see if serial data could be 
sent to two Arduinos at once. 
![IMG_9889 copy](https://user-images.githubusercontent.com/56012430/100530440-3a81d080-31c0-11eb-8688-2368d6057a89.jpg)




# Additional Images of Hardware

Figure 8: Side view of the display module (without the phone)
![IMG_0025](https://user-images.githubusercontent.com/56012430/100530521-1bd00980-31c1-11eb-9c70-3ee06535c210.JPG)




