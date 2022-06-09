from bs4 import *
import requests
import codecs


page = requests.get('https://www.jobnet.co.il/jobs?subprofid=1346')

# print(page.content) ## print the content of the html
soup = BeautifulSoup(page.content, 'html.parser')
# print(soup.prettify()) ## print the content of the html after prettify

file = codecs.open('jobs.txt','w', 'utf-8')

jobs = soup.find_all("div", {"class": "inerbox orange"})
titles = soup.find_all("div", {"class": "title-top"})
dates = soup.find_all("div", {"class": "boxDateCls"})

# print(cities)

for i in range(len(jobs)):
    job = jobs[i]
    # print(item)
    title = job.find(class_='city-title').text
    company = job.find(class_='city-title').text
    date = job.find(class_='temp-info').text
    description = job.find(class_='temp-info').text
    skills = job.find(class_='temp-info').text
    strong = job.find(class_='temp-info').text
    # location = item.find(class_='temp-info').text
   ="jobLocation"




    # print(city)
    # print(temp)
    file.write( f'{title} - \n'
                f'{company} - \n'
                f'{date} - \n'
                f'{description} - \n'
                f'{skills} - \n'
                f'{strong} - \n')
file.close()