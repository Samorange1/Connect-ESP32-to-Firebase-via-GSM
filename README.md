# Connect-ESP32-with-Firebase-via-GSM
Connect ESP32+GSM (Sim800l) to Google Firebase to send sensor data.

# Background

As Firebase only accepts HTTPS requests, it becomes a bit difficult to send sensor data to the Real-time Database with an ESP32 and a GSM Module. I did not find any resource for this when I was doing my project, so I am keeping this here for anyone who needs it in the future. 

## Hardware used
In this project, I develop an IoT application capable of sending data to the Firbase Real-Time database using GPRS and receiving the sent data using a Python script.
We utilize the following components:
- [LILYGO TTGO-TCALL ESP32+ Sim800L](https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800): An excellent IOT module that utilizes ESP32 and SIM800L.The ESP32 has built-in capabilities of WiFI and Bluetooth.


#### Further Requirements - 
- Create an account on [Firebase](https://firebase.google.com/) for data collection.
- Create an account on any website hosting service. We used [000WebHost](https://in.000webhost.com/) a free web server, for hosting our PHP script along with the libraries. 

# Instructions
## Libraries used:
- [TinyGSM](https://github.com/vshymanskyy/TinyGSM): it's a simple library that works well with SIM800L
## Steps: 
- Firstly, `Add Project` on Firebase and give a suitable name to it and `Create Project`. 
- Navigate to `Project Overview` and click `Realtime Database`. Then `Create Database`, select a preferable location for your database (doesn’t matter really) and enable `Test mode`.
- Copy and save the database link (in a format: `https://xxxxx-xxxx-xxxx-xxxx.firebaseio.com/`) 
- Proceed onto the `Project Settings` and under `Service Accounts` click `Database secrets` show and copy the `API KEY`. This is required for authentication in sending and extracting the data.
-  Create an account on Website hosting platform. After signing up and setting a website, go to the folder `public.html` in the File manager and upload the files from the `PHP server` folder. This creates a PHP server that accepts an `HTTP POST` request  and sends the data to Firebase.
     > **NOTE: Do not upload the folder, just the files inside it.**
-  Make the necessary changes in the `upload.php` file to add the details of the database link (`DEFAULT_URL`)and the API key (`DEFAULT_TOKEN`). Also, keep in mind the structure of the database the `$DEFAULT PATH` defines the variable under which the database will record the value. You can add additional paths by adding `/<variable_name>`.
-  Create an Arduino script and copy the provided code. Do not forget to add the necessary details as indicated in the script. 
-  Flash the code and run it, you will see an `8` on your real-time database.
- You can additionally run the python script on a local machine to extract the data. 


## Additional Instructions
This will cover the use of Python script to extract the data from the database for processing. The library in use is a Python interface to the Firebase’s REST API.  
- Install the required library. 
```sh
pip install python-firebase
```
- Go to  your project >>> click on the icon `"</>"` with the tag *add firebase to your web app*
- Copy the information of the form :
```
 var firebaseConfig = {
    apiKey: "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    authDomain: "xxxxx-xxxx.firebaseapp.com",
    databaseURL: "https://xxxxx-xxxxx-xxxxx-xxxxx.firebaseio.com",
    projectId: "xxxx-xxxx",
    storageBucket: "xxxx-xxxx.appspot.com",
    messagingSenderId: "xxxxxxxxxxxxxx",
    appId: "1:xxxxxxxxxxxx:web:xxxxxxxxxxxxxxxxx",
    measurementId: "xxxxxxxxxxxxxxxx"
  };
```
- Then copy this relevent information to the python script as indicated in the script.
- Once you extract the data you can convert it to the required data type/ structure to perform your analysis.
- Additionally you can review this [discussion](https://stackoverflow.com/questions/36528079/how-to-retrieve-data-from-firebase-using-python) on stackoverflow to understand the method.



### Credits:
 [Madhav Rawal](https://www.linkedin.com/in/madhav-rawal/)  
 [Aryaman Patel](https://www.linkedin.com/in/aryaman-patel-ab4504154/)



