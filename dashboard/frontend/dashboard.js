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

const scrollbox = document.getElementById("scrollbox");

function startLog(){
    //get info from log
    //window.addEventListener("log",updateLog,true);
    for(let i = 0; i< 10; i++){
        updateLog("hello" + i);
    }
}
function updateLog(x){

    var newElement = document.createElement('div');
    newElement.setAttribute('id', String(x));
    newElement.innerHTML = x;

    scrollbox.appendChild(newElement);
}

updateLog("Hello addafsjhaskdjfhaksjf");