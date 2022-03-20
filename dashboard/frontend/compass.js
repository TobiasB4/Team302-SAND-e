/*
COMPASS SECTION
*/

const compassCircle = document.querySelector(".compass-cirlce");
const myPoint = document.querySelector(".my-point");

let compass;

function startCompass() {
    //get heading from websocket to be done later
    window.addEventListener("orientation",updateCompass,true);
}

function updateCompass(e){
    compass = e.webkitCompassHeading || Math.abs(e.alpha - 360);
    writeBearing(compass);
    compassCircle.style.transform = `translate(-1%,-2%) rotate(${-compass}deg)`
}

function writeBearing(angle){
    document.getElementById("bearing-text").innerHTML = angle + "°";
}