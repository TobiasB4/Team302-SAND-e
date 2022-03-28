import asyncio
import json
import websockets

async def hello():
    async with websockets.connect("ws://147.182.255.197:8000") as websocket:
        event = {
            "type":"kinetics_bot",
            "velocity": 125,
            "acceleration": 10,
            "key": "robot",
        }
        await websocket.send(json.dumps(event))
        message = await websocket.recv()
        print(message)


asyncio.run(hello())