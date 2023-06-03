import json
from FlightRadar24.api import FlightRadar24API
from flask import Flask

app = Flask(__name__)


@app.route('/')
def hello_world():
    return "Fids is Ready!"


@app.route('/fids', methods=['GET'])
def get_value():
    j = {"dest": "", "number": "", "aircraft_model": "", "airline_name": ""}
    fr_api = FlightRadar24API()
    flights = fr_api.get_flights(bounds="35.798,35.615,51.115,51.331")
    if len(flights) != 0:
        j["dest"] = flights[0].destination_airport_name
        j["number"] = flights[0].number
        j["aircraft_model"] = flights[0].aircraft_model
        j["airline_name"] = flights[0].airline_name
    return json.dumps(j)


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')

