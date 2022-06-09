import requests
from datetime import datetime
import os
from dotenv import load_dotenv

if 'APP_ID' in os.environ:
    print('Environment variable exists!')
else:
    print('Environment variable does not exist.')

GENDER = "female"
WEIGHT = 72.5
HEIGHT = 167.64
AGE = 30

APP_ID = "46535866"
# APP_ID = os.environ["YOUR_APP_ID"]
API_KEY = "509b91d575d9d164de05800020727147"
# API_KEY = os.environ["YOUR_API_KEY"]
exercise_endpoint = "https://trackapi.nutritionix.com/v2/natural/exercise"
sheet_endpoint = "https://api.sheety.co/3b681ae1ed721ebe97575e8ddd624bc4/myWorkout/workouts"
# sheet_endpoint = os.environ["YOUR_SHEET_ENDPOINT"]

exercise_text = input("what exercise did you do? ")

headers = {
    "x-app-id": APP_ID,
    "x-app-key": API_KEY,
    "x-remote-user-id": "0"
}

parameters = {
    "query": exercise_text,
    "gender": GENDER,
    "weight_kg": WEIGHT,
    "height_cm": HEIGHT,
    "age": AGE
}

response = requests.post(exercise_endpoint, json=parameters, headers=headers)
result = response.json()
print(result)

today_date = datetime.now().strftime("%d/%m/%Y")
now_time = datetime.now().strftime("%X")

for exercise in result["exercises"]:
    sheet_inputs = {
        "workout": {
            "date": today_date,
            "time": now_time,
            "exercise": exercise["name"].title(),
            "duration": exercise["duration_min"],
            "calories": exercise["nf_calories"]
        }
    }

    sheet_response = requests.post(sheet_endpoint, json=sheet_inputs)

    basic_headers = {
        "Authorization": f"Basic  "
                         f"{os.environ['USERNAME']}"
                         f"{os.environ['PASSWORD']}"
    }

    # Basic auth
    sheet_response = requests.post(
        sheet_endpoint,
        json=sheet_inputs,
        headers=basic_headers
    )

    # # Bearer Token
    # bearer_headers = {
    #     "Authorization": f"Bearer {os.environ['TOKEN']}"
    # }
    #
    # sheet_response = requests.post(
    #     sheet_endpoint,
    #     json=sheet_inputs,
    #     headers=bearer_headers
    # )

    print(sheet_response.text)

