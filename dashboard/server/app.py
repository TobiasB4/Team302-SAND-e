import asyncio
import websockets
import secrets
import json

connected = []


async def updateEvent(message):
    messages = json.loads(message)
    etype = messages["type"]
    if(etype == "coordinate_web"):
        return
    elif(etype == "home_web"):
        return
    elif(etype == "shutdown_web"):
        return
    elif(etype == "restart_web"):
        return
    elif(etype == "error_bot"):
        return
    elif(etype == "status_bot"):
        return
    elif(etype == "coordinate_bot"):
        return
    elif(etype == "kinetics_bot"):
        event = {
            "type": "kinetics",
            "velocity": messages["velocity"],
            "acceleration": messages["acceleration"]
        }
        return event
    elif(etype == "orientation_bot"):
        return
    else:
        return
velocity = 0
async def handler(websocket):
    global velocity
    async for message in websocket:
        event = json.loads(message)
        if("key" in event and event["key"] == "robot"):
            velocity += 1
        else:
            event= {
                "type":"kinetics",
                "velocity":velocity,
                "acceleration":5
            }
        await websocket.send(json.dumps(event))
        print(message)
        print("v = " +str(velocity))



async def main():
    async with websockets.serve(handler,"",8000):
        await asyncio.Future()

if __name__ == "__main__":
    asyncio.run(main()) 