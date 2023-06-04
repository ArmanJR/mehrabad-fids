import json
from FlightRadar24.api import FlightRadar24API, Flight
from flask import Flask

app = Flask(__name__)


@app.route("/")
def hello_world():
    return "Fids is Ready!"


@app.route("/fids", methods=["GET"])
def get_value():
    # j = {"dest": "", "number": "", "aircraft_model": "", "airline_name": ""}
    fr_api = FlightRadar24API()
    req_params = [
        "number",
        "aircraft_model",
        "airline_name",
        "origin_airport_name",
        "destination_airport_name",
        "ground_speed",
        "vertical_speed",
        "time_details",
    ]
    # almost whole Tehran provine zone
    zone_iran = "29.996625,29.185917,51.967958,53.478513"

    flights = fr_api.get_flights(bounds=zone_iran)
    if len(flights) != 0:
        # iterate over first 3 flights only - for testing purpose
        for flight in flights[0:2]:
            details = fr_api.get_flight_details(flight.id)
            flight.set_flight_details(details)

    selected_flights = [
        {key: getattr(flight, key) for key in req_params} for flight in flights[0:2]
    ]
    return json.dumps(selected_flights)


if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=5050)
