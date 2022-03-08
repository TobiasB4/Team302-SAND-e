# https://pypi.org/project/websockets/
# https://realpython.com/async-io-python/

import asyncio
import websockets

async def echo(websocket):
    async for message in websocket:
        await websocket.send(message)

async def main():
    async with serve(echo, "localhost", 8765):
        await asyncio.Future()

asyncio.run(main())

