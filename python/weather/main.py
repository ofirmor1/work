import requests

api_key = "9530406042a597d6374ae5b4d6f39921"
OWM_Endpoint = "https://api.openweathermap.org/data/2.5/onecall"

parameters = {
    "lat": 31.778014,
    "lon": 35.235442,
    "appid": api_key,
    "exclude": "current,minutely,daily,alerts"
}
response = requests.get(OWM_Endpoint, params=parameters)
response.raise_for_status()

weather_data = response.json()
weather_slice = weather_data["hourly"][:12]

will_rain = False

for hour_data in weather_slice:
    condition_code = hour_data["weather"][0]["id"]
    if int(condition_code) < 700:
        will_rain = True
if will_rain:
    print("Bring an umbrella")


# print(weather_slice)
# print(weather_data["hourly"][0]["weather"][0]["id"])

