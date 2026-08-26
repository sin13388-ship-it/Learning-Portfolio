import requests


# 請將下列設定替換成你的氣象資料平台資訊
API_URL = "https://opendata.cwa.gov.tw/api/v1/rest/datastore/O-A0001-001?Authorization=CWA-A85E41CE-929E-4365-BA73-F551A540F9DB&format=JSON"
API_KEY = "CWA-A85E41CE-929E-4365-BA73-F551A540F9DB"


def get_weather():
	"""向氣象資料平台提出請求並回傳 JSON 資料。

	將 API_KEY_PARAM 改成平台要求的參數名稱；其他查詢參數依平台文件調整。
	"""
	
	

	try:
		response = requests.get(API_URL)
		allData=response.json
		return allData
		
	except requests.exceptions.RequestException as error:
		raise RuntimeError(f"氣象資料請求失敗：{error}") from error
	except ValueError as error:
		raise RuntimeError("伺服器回傳的內容不是有效 JSON") from error


