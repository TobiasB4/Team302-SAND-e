import asyncio
import websockets
import secrets
import json

JOIN = {}

async def error(websocket, message):
    event = {
        "type": "error",
        "message": message
    }
    await websocket.send(json.dumps(event))

async def go(websocket, connected):
    async for message in websocket:
        messages = json.loads(message)
        event = updateEvent(messages)

        websockets.broadcast(connected, json.dumps(event))

async def start(websocket):
    connected = {websocket}
    join_key = 12345
    JOIN[join_key] = connected

    try:
        event = {
            "type": "init",
            "join": join_key,
        }
        await websocket.send(json.dumps(event))
        await go()
    finally:
        del JOIN[join_key]

async def join(websocket,join_key):
    try:
        connected = JOIN[join_key]
    except KeyError:
        await error(websocket,"key not found")
        return
    
    connected.add(websocket)
    try:
        pass
    finally:
        connected.remove(websocket)

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


async def handler(websocket):
    # message = await websocket.recv()
    # event = json.loads(message)
    
    # if "join" in event:
    #     await join(websocket,event["join"])
    # else:
    #     await start(websocket)
    async for message in websocket:
        event = {
            "type": "kinetics",
            "velocity": 123,
            "acceleration": 456
        }
        await websocket.send(json.dumps(event))
        print(message)



async def main():
    async with websockets.serve(handler,"",8000):
        await asyncio.Future()

if __name__ == "__main__":
    asyncio.run(main()) 