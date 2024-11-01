import requests

url = "http://localhost:8080/function/user"
params = {
    "username": "Cornell_1",
    "password": "1111111111"
}

response = requests.get(url, params=params)

print(response.status_code)
print(response.json())