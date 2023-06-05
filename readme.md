# Forked version

include some changes as per below:

1. consider latest FlightRadar24API changes (to get flights details)
2. custom zone setter
3. custom required parameters to reduce json file size

# Mehrabad FIDS

Codes for ESP32 + 1602 LCD Mehrabad FIDS

## Hardware

- ESP32 microcontroller
- 1602 LCD with IIC/I2C/TWI
- 5V Power
- Remote server to deploy the flask app

## Software

First upload the `esp32-code.ino` to your microcontroller using Arduino IDE. Then serve the server files on your host and replace `serverName` with the url.

By default, the script will loop every 25 seconds which is changable via `timerDelay` in the code. Decreasing this may rate-limit your client.

## Contribution

Pull requests are welcome.

## License

This project is under WTFPL License (Do What the Fuck You Want To Public License).
