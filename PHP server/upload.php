<?php

require 'firebaseLib.php';

const DEFAULT_URL = 'https://xxxxxxxx.firebaseio.com/';
const DEFAULT_TOKEN = 'xxxxxxxxxxxxxxxxxxxxxxxqCk';
$DEFAULT_PATH = '/a';

$a = $_POST["a"];

date_default_timezone_set('Asia/Kolkata');

// $a = array_map('floatval', $a); // if you want to send an array of data points

$_devicestatus= array(
    'a' => $a 
);
        
$firebase = new \Firebase\FirebaseLib(DEFAULT_URL, DEFAULT_TOKEN);

$firebase->push($DEFAULT_PATH, $_devicestatus); // for a new entry everytime 

// To update the same field, use "update" instead of push

print("POST_SUCCESSFUL");

?>