# Flight Information Display System (FIDS)
This is a Python application that uses the `FlightRadar24` API to retrieve information about flights and provide it via a REST API endpoint.
The endpoint returns JSON-formatted data containing the destination airport name, flight number, aircraft model, and airline name for the latest flight available.

## Installation
1. Clone the repository using `git https://github.com/ArmanJR/mehrabad-fids.git`.
2. Navigate to the project directory using `cd mehrabad-fids/server`.
3. Install the required dependencies using `pip install -r requirements.txt`.

## Usage
1. Start the Flask server by running `python wsgi.py`.
2. The server will be hosted on `http://localhost:5005`.
3. Send a `GET` request to `http://localhost:5005/fids` to retrieve the latest flight information in JSON format.