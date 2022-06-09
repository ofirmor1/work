import requests
import os
from twilio.rest import Client
from twilio.http.http_client import TwilioHttpClient

MY_LAT = 35.689487
MY_LONG = 139.691711

OWM_Endpoint = "https://api.openweathermap.org/data/2.5/onecall"
api_key = "8cd00dc837ed5d13d7b60694ede0d0e0"
account_sid = "ACad0276691d70e027e4d5faaf9c5d0878"
auth_token = "dcc25a1845ae3ec26b4588710d7c8087"

parameters = {
    "lat": MY_LAT,
    "lon": MY_LONG,
    "appid": api_key,
    "exclude": "current,minutely,daily,alerts"
}


response = requests.get(OWM_Endpoint, params=parameters)
response.raise_for_status()

will_rain = False

weather_data = response.json()
weather_slice = weather_data["hourly"][:12]
for hour_data in weather_slice:
    condition_code = hour_data["weather"][0]["id"]
    if int(condition_code) < 700:
        will_rain = True

if will_rain:
    proxy_client = TwilioHttpClient()
    proxy_client.session.proxies = {'https': os.environ['https_proxy']}
    client = Client(account_sid, auth_token, http_client=proxy_client)
    message = client.messages \
        .create(
        body="It's going to rain today. Remember to bring an ☂️",
        from_='+19706989693',
        to='+9720504328070'
    )
print(message.status)
