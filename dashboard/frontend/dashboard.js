/*
COMPASS SECTION
*/

function startCompass() {
    //get heading from websocket to be done later
    window.addEventListener("orientation",updateCompass,true);
}

function updateCompass(e){
    const compassCircle = document.querySelector(".compass-cirlce");
    const myPoint = document.querySelector(".my-point");

    let compass;
    compass = e.webkitCompassHeading || Math.abs(e.alpha - 360);
    writeBearing(compass);
    compassCircle.style.transform = `translate(-1%,-2%) rotate(${-compass}deg)`
}

function writeBearing(angle){
    document.getElementById("bearing-text").innerHTML = angle + "°";
}

/*
ACTIONS SECTION -> SET HOME AND RETURN HOME
*/

function parseCoordinates(text){
    text = text.replace('[','').replace(']','').replace(' ','').replace('\n', '');
    const latlong = text.split(',');
    const coordinate = {lat: latlong[0],long: latlong[1]};
    return coordinate;
}
//import {sendHome_ws} from './websocket.js';
function setHome(){
    var input = prompt("Please enter home coordinates:","[49.28451838370452, -123.14407949644797]");
    var text;
    if(input == null || input == ""){
        text = "Invalid input";
    }else{
        text = input;
    }
    coordinate = parseCoordinates(text)

    //Replace console log with some server interaction
    sendHome_ws(coordinate,websocket);

    updateLog(coordinate.lat);
    updateLog(coordinate.long);
}

function returnHome(){
    //Send home command

    //want to call updateLog somehow
    updateLog("going home");
}

/*
LOG CONSOLE SECTION
*/

function startLog(){
    //get info from log
    //window.addEventListener("log",updateLog,true);
    for(let i = 0; i< 10; i++){
        updateLog("hello" + i);
    }
}

function updateLog(x){
    const scrollbox = document.querySelector(".scrollbox");

    var newElement = document.createElement('div');
    newElement.setAttribute('id', String(x));
    newElement.innerHTML = x;

    scrollbox.appendChild(newElement);
}

/*
POWER SECTION
*/

function shutdown(){
    //send command to PI to shutdown
    updateLog("shutting down");
}

function restart(){
    //send command to PI to restart
    updateLog("restarting");
}

/*
MAP SECTION
*/

function initMap(){
    //Origin
    const origin = { lat: 49.2863, lng:-123.1435};

    const map = new google.maps.Map(document.querySelector(".map"),{
        zoom:16,
        center: origin,
    });

    const marker = new google.maps.Marker({
        position: origin,
        map: map,
    });
}