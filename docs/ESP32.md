# ESP32 HTTP Request
This project sends an HTTP GET request to a server and displays the response on an LCD display.
The code was developed using an `ESP32` microcontroller
and includes libraries for WiFi connectivity, HTTP requests, and JSON parsing.

## Getting Started
To use this code, you will need to have the following components:

- An ESP32 microcontroller
- A WiFi network with its SSID and password
- A server that responds to HTTP GET requests

Once you have all the components,
modify the following lines of code in `esp32-code.ino` with your WiFi credentials and server URL:
```ino
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* serverName = "SERVER_URL";
```
## How it Works
The program sends an HTTP GET request to the specified server every 25 seconds.
If the request is successful, the server responds with a JSON string that contains the destination,
flight number, aircraft model, and airline name.
The program then parses the JSON string and extracts the relevant information.

The extracted information is displayed on a two-line LCD display using the `LiquidCrystal_I2C` library.
The first line shows the destination, and the second line shows the flight number, aircraft model, and airline name (if available).

### Libraries Used
- WiFi.h
- HTTPClient.h
- Arduino_JSON.h
- LiquidCrystal_I2C.h