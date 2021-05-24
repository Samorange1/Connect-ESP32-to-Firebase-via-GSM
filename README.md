# Connect-ESP32-with-Firebase-via-GSM
Connect ESP32+GSM (Sim800l) to Google Firebase to send sensor data.

# Background

As Firebase only accepts HTTPS requests, it becomes a bit difficult to send sensor data to the realtime Database with an ESP32 and a GSM Module. I did not find any resource for this when I was doing my project, so I am keeping this here for anyone who needs it in the future. I was using a [LILYGO TTGO-TCALL ESP32+ Sim800L](https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800) for this project.

In this tutorial I am sending the sensor data to a PhP server via an HTTP POST request and the server is using the php Firebase Library to send the data from the POST request to RTDB in Firebase. I am assuming you have your Firebase set up done (it's quite simple just google it!)
# Instructions
## Libraries used:
- [TinyGSM](https://github.com/vshymanskyy/TinyGSM): its a simple library that works well with SIM800L

## Steps:
1. Create a PHP server that accepts a HTTP POST request  and sends the data to Firebase
- I used [000webhost](https://in.000webhost.com/) that allows you to set up a free php server that can handle HTTP requests

- After signing up and setting a website, go to the folder public.html in the File manager and upload the files in the "PHP server folder". _NOTE: DO NOT UPLOAD THE FOLDER, JUST THE FILES INSIDE IT._

- Make the neecessary changes in the upload.php file to add the details of your Firebase RealTime Database

2. Make the necessary changes in the Arduino file (I have indicated the places that need changes). 

3. Flash the code and run it, you will se an "8" on your database
