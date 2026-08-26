
import weather
def main():
	# 依 API 文件填入查詢參數，例如 city="Taipei" 或 location="臺北市"。
	weatherData = weather.get_weather()
	print(weatherData)


if __name__ == "__main__":
	main()
	