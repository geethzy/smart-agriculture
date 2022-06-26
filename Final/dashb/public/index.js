var config = {
            apiKey: "AIzaSyA8tXTFoe_k299y9Cr6rAbxOHge3CrUFxQ",
            authDomain: "ghouse-3215e.firebaseapp.com",
            databaseURL: "https://ghouse-3215e-default-rtdb.firebaseio.com",
            projectId: "ghouse-3215e",
            storageBucket: "ghouse-3215e.appspot.com",
            messagingSenderId: "449512899037",
    };

    firebase.initializeApp(config);
  
(function() {
    var database = firebase.database();

    //monitor sensors
    const tempElement = document.getElementById('temperature');
    const humElement = document.getElementById('humidity');
    const ligElement = document.getElementById('intensity');
    const moiElement = document.getElementById('moisture');

    const tempRef = database.ref('sensors').child('temp');
    const humRef = database.ref('sensors').child('humi');
    const ligRef = database.ref('sensors').child('light');
    const moiRef = database.ref('sensors').child('moist');

    tempRef.limitToLast(1).on('value', function(snapshot) {
        snapshot.forEach(function(childSnapshot) {
            var childData = childSnapshot.val();
            console.log("temperature: " + childData);
            tempElement.innerText = childData;
        });
    });
    humRef.limitToLast(1).on('value', function(snapshot) {
        snapshot.forEach(function(childSnapshot) {
            var childData = childSnapshot.val();
            console.log("humidity: " + childData);
            humElement.innerText = childData;
        });
    });
    ligRef.limitToLast(1).on('value', function(snapshot) {
        snapshot.forEach(function(childSnapshot) {
            var childData = childSnapshot.val();
            console.log("light: " + childData);
            ligElement.innerText = childData;
        });
    });
    moiRef.limitToLast(1).on('value', function(snapshot) {
        snapshot.forEach(function(childSnapshot) {
            var childData = childSnapshot.val();
            console.log("moisture: " + childData);
            moiElement.innerText = childData;
        });
    });

//get image
const imgElement = document.getElementById('urli');
const imgRef = database.ref('picam').child('images');
imgRef.limitToLast(1).on('value', function(snapshot) {
    snapshot.forEach(function(childSnapshot) {
        var childData = childSnapshot.val();
        console.log("cputemp: " + childData);
        //imgElement.innerText = childData;
        img.src = childData; 
    });
});

//get CPU temp
const ctempElement = document.getElementById('cputemp');
const ctempRef = database.ref('Settings').child('cpuTemp');
ctempRef.limitToLast(1).on('value', function(snapshot) {
    snapshot.forEach(function(childSnapshot) {
        var childData = childSnapshot.val();
        console.log("cputemp: " + childData);
        ctempElement.innerText = childData;
    });
});

//get time
const timeElement = document.getElementById('getTime');
const timeRef = database.ref('Settings').child('last_update_datetime');
timeRef.limitToLast(1).on('value', function(snapshot) {
    snapshot.forEach(function(childSnapshot) {
        var childData = childSnapshot.val();
        console.log("currenttime: " + childData);
        timeElement.innerText = childData;
    });
});


//control light with intensity
const geeElement = document.getElementById('intensityText');
const geeRef = database.ref('control').child('lightPosi');
geeRef.limitToLast(1).on('value', function(snapshot) {
    snapshot.forEach(function(childSnapshot) {
        var childData = childSnapshot.val();
        console.log("curre: " + childData);
        var lightRef = firebase.database().ref().child("lightRelay");
        if(childData ==3){
            geeElement.innerText = ("Indoor is DARK, switched ON the bulb");
        }
        if(childData ==2){
            geeElement.innerText = ("The light is in perfect range");
        }
        if(childData ==1){
            geeElement.innerText = ("Indoor is BRIGHT, switched OFF the bulb");
        }
    });
});


//control valve with moisture
const moElement = document.getElementById('moistureText');
const moRef = database.ref('control').child('valvePosi');
moRef.limitToLast(1).on('value', function(snapshot) {
    snapshot.forEach(function(childSnapshot) {
        var childData = childSnapshot.val();
        console.log("moi: " + childData);
        var lightRef = firebase.database().ref().child("valveRelay");
        if(childData ==3){
            moElement.innerText = ("Soil is DRY, switched ON the valve");
        }
        if(childData ==2){
            moElement.innerText = ("The soil moisture is in perfect range");
        }
        if(childData ==1){
            moElement.innerText = ("Soil is WET, switched OFF the valve");
        }
    });
});


//create pie chart
       new Chart(document.getElementById("chart"), {
    type: 'doughnut',
    data: {
      labels: ["Free", "Used"],
      datasets: [{
        label: "RAM Usage",
        backgroundColor: ["#B09B71", "#87805E"],
        data: [3530.3, 114.8]
      }]
    },
});

//create pie chart2
       new Chart(document.getElementById("chart2"), {
    type: 'doughnut',
    data: {
      labels: ["Free", "Used"],
      datasets: [{
        label: "Disk Space",
        backgroundColor: ["#B09B71", "#87805E"],
        data: [3.6, 10.4]
      }]
    },
});
}());

//manual control light
$(document).ready(function(){
  var database = firebase.database();
  var lightStat;

  database.ref().on("value", function(snap){
    lightStat = snap.val().lightRelay;
    if(lightStat == 1){
      $(".lightText").text("The light is switched ON");
    } else {
      $(".lightText").text("The light is switched OFF");
    }
  });
});
document.addEventListener('DOMContentLoaded', function () {
  var checkbox = document.querySelector('#ligtog');

  checkbox.addEventListener('change', function () {
  var lightRef = firebase.database().ref().child("lightRelay");
    if (checkbox.checked) {
      lightRef.set(1);
      lightStat = 1;  
      console.log('Checked');
    } else {
      lightRef.set(0);
      lightStat = 0;
      console.log('Not checked');
    }
  });
});


//manual control valve
$(document).ready(function(){
  var database = firebase.database();
  var lightStat;

  database.ref().on("value", function(snap){
    lightStat = snap.val().valveRelay;
    if(lightStat == 1){
      $(".valveText").text("The valve is switched ON");
    } else {
      $(".valveText").text("The valve is switched OFF");
    }
  });
});
document.addEventListener('DOMContentLoaded', function () {
  var checkbox = document.querySelector('#valtog');

  checkbox.addEventListener('change', function () {
  var valveRef = firebase.database().ref().child("valveRelay");
    if (checkbox.checked) {
      valveRef.set(1);
      lightStat = 1; 
      console.log('Checked');
    } else {
      valveRef.set(0);
      lightStat = 0;
      console.log('Not checked');
    }
  });
});


//create line chart
new Chart(document.getElementById("line-chart"), {
  type: 'line',
  data: {
    labels: [1500,1600,1700,1750,1800,1850,1900,1950,1999,2050],
    datasets: [{ 
        data: [86,114,106,106,107,111,133,221,783,2478],
        label: "Africa",
        borderColor: "#3e95cd",
        fill: false
      }
    ]
  },
  options: {
    title: {
      display: true,
      text: 'World population per region (in millions)'
    }
  }
});
