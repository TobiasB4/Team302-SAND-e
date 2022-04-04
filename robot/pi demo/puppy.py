import subprocess
import asyncio
import json
import websockets

async def main():
    async with websockets.connect("ws://147.182.255.197:8000") as websocket:
        event = {
            "type": "status_bot",
            "message": "asddf",
        }
        await websocket.send(json.dumps(event))
        message = await websocket.recv()
        print(message)








asyncio.run(main())