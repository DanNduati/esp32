import websocket

# Connect to server
ws = websocket.WebSocket()
ws.connect("ws://192.168.43.9")
print("Connected!")

# Ask the user for some input and transmit it
data = str(input("input: "))
ws.send(data)

# Wait for server to respond and print it
result = ws.recv()
print("Received: " + result)
#close WebSocket connection
ws.close()
