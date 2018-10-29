// Whole-script strict mode syntax
'use strict';

function locatorCall() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {   // XMLHttpRequest.DONE == 4
           if (xmlhttp.status == 200) {
               document.getElementById("myDiv").innerHTML = xmlhttp.responseText;
           }
           else if (xmlhttp.status == 400) {
              alert('There was an error 400');
           }
           else {
               alert('something else other than 200 was returned');
           }
        }
    };


    xmlhttp.open("GET", APPLICATION_SETTINGS.locator.cameraURL, true);
    xmlhttp.send();
}

function locatorCommunication() {

    var SETTINGS = APPLICATION_SETTINGS.locator;        // locator settings
    var pollingIntervalID;                              // is going to hold setInterval id
    var xmlHttpRqst = new XMLHttpRequest();                 // Ajax request object

    this.init = function()
    {
        // set polling request callback
        xmlHttpRqst.onreadystatechange = function() {
            if (xmlHttpRqst.readyState == XMLHttpRequest.DONE) {
                if (xmlHttpRqst.status == 200) {
                    console.info("Risposta ricevuta:");
                    console.info(xmlHttpRqst.responseText);
                }
                else if (xmlHttpRqst.status == 400) {
                    GUI_show_error('There was an error 400');
                }
                else {
                    GUI_show_error('something else other than 200 was returned');
                }
            }
        };
        // set polling timer interval
        this.pollingIntervalID = window.setInterval(function(){

            xmlHttpRqst.open("GET", SETTINGS.cameraURL, true);      // open
            xmlHttpRqst.send();                                     // send
        }, SETTINGS.pollingTimeInMilliseconds);
    }

    var dataReceived = function() {

    };

}

var LOCATOR = new locatorCommunication();
LOCATOR.init();