const port = 8000;
const websocket = new WebSocket("ws://localhost:"+String(port));

function sendHome_ws(coordinates,websocket){

    if(coordinates.lat === undefined || coordinates.long === undefined){
        return;
    }
    const event = {
        type: "coordinate",
        lat: coordinates.lat,
        long: coordinates.long
    };
    websocket.send(JSON.stringify(event));
}