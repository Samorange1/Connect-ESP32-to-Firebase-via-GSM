#!/usr/bin/env python3
from firebase import Firebase

# Paste the information below.

config = {
    "apiKey": "",
    "authDomain": "",
    "databaseURL": "",
    "projectId": "",
    "storageBucket": "",
    "messagingSenderId": "",
    "appId": "",
    "measurementId": ""
}


firebase = Firebase(config)
auth = firebase.auth()
db = firebase.database()
all_users = db.child("ax").get()   # The 'ax' defines the variable on the data base containing the data points. You can replace it with your required variable name.

l = list()
for user in all_users.each():
    a = user.val()
    for value in a.values():
        l.append(value)

print(l)
