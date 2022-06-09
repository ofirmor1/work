import smtplib
import datetime as dt
import random

my_email = "termix4@gmail.com"
password = "ofir058232"

now = dt.datetime.now()
weekday = now.weekday()
if weekday == 3:
    with open("quotes.txt") as quote_file:
        all_quotes = quote_file.readlines()
        quote = random.choice(all_quotes)

    with smtplib.SMTP("smtp.gmail.com") as connection:
        connection.starttls()
        connection.login(user=my_email, password=password)
        connection.sendmail(from_addr=my_email,
                            to_addrs="ofirmor1991@gmail.com",
                            msg=f"Subject:Motivation quote\n\n{quote} "
                            )
