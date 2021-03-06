const websocket = new WebSocket("ws://147.182.255.197:8000");

websocket.onopen = function () {
    recieveData_ws(websocket);
    const interval = setInterval(function () { updatePage(websocket); }, 500);
    websocket.onclose = function () {
        clearInterval(interval);
        console.log("Lost connection");
    }
}

/*
COMPASS SECTION
*/

function updateCompass(angle){
    const compassCircle = document.querySelector(".compass-circle");
    compassCircle.style.transform = `translate(-1%,-2%) rotate(${-angle}deg)`
}


/*
ACTIONS SECTION -> SET HOME AND RETURN HOME
*/

function verifyCoordinates(text){
    if(!(text.startsWith('['))){
        return false;
    }
    if(!(text.endsWith(']') || text.endsWith('\n'))){
        return false;
    }
    text = text.replace('[','').replace(']','');
    coordinate = text.split(',');
    if(coordinate.length != 2){
        return false;
    }
    if(isNaN(coordinate[0]) || isNaN(coordinate[1])){
        return false;
    }
    return true;
}

function parseCoordinates(text){
    text = text.replace('[','').replace(']','').replace(' ','').replace('\n', '');
    const latlong = text.split(',');
    const coordinate = {lat: parseFloat(latlong[0]),lng: parseFloat(latlong[1])};
    return coordinate;
}

function setHome(){
    var input = prompt("Please enter home coordinates:","[49.28451838370452, -123.14407949644797]");
    var text;
    if(input == null || input == "" ){
        text = "Invalid input";
    }else{
        text = input;
    }

    //Make sure valid coordinate and 
    if(verifyCoordinates(text)){
        coordinate = parseCoordinates(text);
        setHome_ws(coordinate,websocket);
        updateLog("New Home: " + text);
    }else{
        updateLog("Invalid input");
    }

}
function returnHome(){
    //Send home command
    sendHome_ws(websocket);
    //Update log console
    updateLog("Going home...");
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

function updateLog(text){
    const scrollbox = document.querySelector(".scrollbox");

    var newElement = document.createElement('div');
    newElement.setAttribute('id', String(text));
    newElement.innerHTML = text;

    scrollbox.appendChild(newElement);
}

/*
POWER SECTION
*/

function shutdown(){
    //send shutdown command
    shutdown_ws(websocket);
    updateLog("shutting down");
}

function restart(){
    //send restart command
    restart_ws(websocket);
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

function updateMarker(location, map){
    const marker = new google.maps.Marker({
        position: location,
        map: map,
    });
}

