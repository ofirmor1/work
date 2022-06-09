import requests
from datetime import datetime
MY_LAT = 31.778014
MY_LNG = 35.235442

parametes = {
    "lat": MY_LAT,
    "lng": MY_LNG,
    "formatted": 0
}

time = datetime.now()
print(time)
print("")
response = requests.get("https://api.sunrise-sunset.org/json", params=parametes)
response.raise_for_status()



data = response.json()
# print(data)
sunrise = data["results"]["sunrise"]
print(sunrise)
print("")
sunset = data["results"]["sunset"]
print(sunset)