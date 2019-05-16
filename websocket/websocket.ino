#include <WebSocketsServer.h>
#include <WiFi.h>

//your wifi credentials
const char* ssid = "AndroidAP";
const char* password = "";


WebSocketsServer webSocket  = WebSocketsServer(80);

//function called when a websocket messsage is received
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    //disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u]Disconnected!\n", num);
      break;
    // New client connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    // Echo text message back to client
    case WStype_TEXT:
      Serial.printf("[%u] Text: %s\n", num, payload);
      webSocket.sendTXT(num, payload);
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}
void setup() {
  Serial.begin(9600);
  // Connect to wifi
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  //wait until the esp is connected to the internet
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }

  // Print out your IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());

  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}
void loop() {
  // Look for and handle WebSocket data
  webSocket.loop();
}

