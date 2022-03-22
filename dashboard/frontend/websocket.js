

function recieveData_ws(websocket){
    websocket.addEventListener("message", ({data}) =>{
        const event = JSON.parse(data);
        if (event.type == "update") {
            //const coordinate = {lat: event.lat,lng: event.long};
            document.getElementById("velocity").innerHTML = "V: " + event.velocity;
            document.getElementById("acceleration").innerHTML = "A: " + event.acceleration;
            //updateLog(event.recieve);
            document.getElementById("bearing-text").innerHTML = event.orientation + "°";
            document.getElementById("current-lat").innerHTML = "[" + event.current_coord[0] + "]";
            document.getElementById("current-lng").innerHTML = "[" + event.current_coord[1] + "]";
        } else if (event.type == "confirmation") {
            console.log(event.recieve);
        } else {
            
            console.log("Unsupported event type:" + event.type);
        }
        
    });
}

function updatePage(websocket) {
    const event = {
        type: "update", key: "web"
    };
    websocket.send(JSON.stringify(event));
}

function setHome_ws(coordinates,websocket){

    if(coordinates.lat === undefined || coordinates.lng === undefined){
        return;
    }
    const event = {
        type: "coordinate_web",
        lat: coordinates.lat,
        lng: coordinates.lng
    };
    websocket.send(JSON.stringify(event));
}

function sendHome_ws(websocket){
    const event = {
        type: "home_web",
        value: true
    };
    websocket.send(JSON.stringify(event));
}

function shutdown_ws(websocket){
    const event = {
        type: "shutdown_web",
        value: true
    };
    websocket.send(JSON.stringify(event));
}

function restart_ws(websocket){
    const event = {
        type: "restart_web",
        value: true
    };
    websocket.send(JSON.stringify(event));
}