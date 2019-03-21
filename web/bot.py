import requests
from bs4 import BeautifulSoup

url = "https://webfanat.com/article_id/?id=157"


user_agent = ('Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:50.0) '
              'Gecko/20100101 Firefox/50.0')
session = requests.Session()
data = {"login_username":"login", "login_password":"password"}
response = session.post(url, data=data)

jpage = requests.get(url, headers={'User-Agent':user_agent}, timeout=(10, 0.01))# таймаут на соединения, таймаут на чтение (в секундах)

page = requests.get(url)
print(page.encoding)
with open('test.txt', 'w') as output_file:
    output_file.write(page.text)
