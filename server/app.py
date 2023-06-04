import json
from FlightRadar24.api import FlightRadar24API
from flask import Flask

app = Flask(__name__)


@app.route("/")
def hello_world():
    return "Fids is Ready!"


@app.route("/fids", methods=["GET"])
def get_value():
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
        "latitude",
        "longitude"
    ]
    # almost whole Shiraz provicne zone
    zone_iran = "32.288310,30.957088,53.770085,55.528620"

    flights = fr_api.get_flights(bounds=zone_iran)

    # iterate over first 3 flights only - for testing purpose
    flights = flights[0:2]

    if len(flights) != 0:
        for flight in flights:
            details = fr_api.get_flight_details(flight.id)
            flight.set_flight_details(details)

    selected_flights = [
        {key: getattr(flight, key) for key in req_params} for flight in flights
    ]
    return json.dumps(selected_flights)


if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=5050)
