import asyncio
import websockets
import secrets
import json

events = {
    "type": "update",
    "velocity": 0,
    "acceleration": 0,
    "current_coord": [49.28451838370452,-123.14407949644797],
    "message": "",
    "connected": True,
    "home": [49.28451838370452,-123.14407949644797],
    "return_home": False,
    "orientation": 0,
    "shutdown": False,
    "restart": False,
}


async def updateEvent(message):
    global events
    etype = message["type"]
    event = {
            "type" : "confirmation",
            "recieve" : False
        }
    if(etype == "init"):
        event["recieve"] = True
    elif(etype == "coordinate_web"):
        #Update home coordinates
        events["home"][0] = message["lat"]
        events["home"][1] = message["lng"]
        event["recieve"] = True
    elif(etype == "home_web"):
        #Return home
        events["return_home"] = True
        event["recieve"] = True
    elif(etype == "shutdown_web"):
        #Shutdown
        events["shutdown"] = True
        event["recieve"] = True
    elif(etype == "restart_web"):
        #Restart
        events["restart"] = True
        event["recieve"] = True
    elif(etype == "error_bot"):
        #Error message
        events["message"] = message["message"]
        event["recieve"] = True
    elif(etype == "status_bot"):
        #Status message
        events["message"] = message["message"]
        event["recieve"] = True
    elif(etype == "coordinate_bot"):
        #Set current coordinates
        events["current_coord"][0] = message["lat"]
        events["current_coord"][1] = message["lng"]
        event["recieve"] = True
    elif(etype == "kinetics_bot"):
        #Set velocity and acceleration
        events["velocity"] = message["velocity"]
        events["acceleration"] = message["acceleration"]
        event["recieve"] = True
    elif(etype == "orientation_bot"):
        #Set bearing
        events["orientation"] = float(message["orientation"])
        event["recieve"] = True
    return event


async def handler(websocket):
    global events
    async for message in websocket:
        event = json.loads(message)
        if(event['type'] == "update"):
            await websocket.send(json.dumps(events))
        elif(event != {}):
            event = await updateEvent(event)
            await websocket.send(json.dumps(event))
        else:
            event = {
                "type":"error",
                "message":"Invalid event"
            }
            await websocket.send(json.dumps(event))



async def main():
    async with websockets.serve(handler,"",8000):
        await asyncio.Future()

if __name__ == "__main__":
    asyncio.run(main()) 