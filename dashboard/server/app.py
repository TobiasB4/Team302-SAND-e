import asyncio
import websockets
import json

async def handler(websocket):
    async for message in websocket:
        print(message)
    # event = {
    #     "type":"kinetics",
    #     "velocity": "123",
    #     "acceleration": "456"
    # }
    


async def main():
    async with websockets.serve(handler,"",8000):
        await asyncio.Future()

if __name__ == "__main__":
    asyncio.run(main()) 