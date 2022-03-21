const port = 8000;
const websocket = new WebSocket("ws://localhost:"+String(port));

function recieveData_ws(websocket){
    websocket.addEventListener("message", ({data}) =>{
        const event = JSON.parse(data);
        switch(event.type){
            case "status":
                updateLog(event.message);
                break;
            case "coordinate":
                const coordinate = {lat: event.lat,lng: event.long};
                updateMarker(coordinate,map);
                break;
            case "orientation":
                document.getElementById("bearing-text").innerHTML(event.angle+"°");
                break;
            case "kinetics":
                document.getElementById("velocity").innerHTML = "V: " + event.velocity;
                document.getElementById("acceleration").innerHTML = "A: " + event.acceleration;
                console.log("Working!");
                break;
            default:
                console.log("Unsupported event type: ${event.type}.");
        }
    });
}

function setHome_ws(coordinates,websocket){

    if(coordinates.lat === undefined || coordinates.lng === undefined){
        return;
    }
    const event = {
        type: "coordinate_web",
        lat: coordinates.lat,
        long: coordinates.lng
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