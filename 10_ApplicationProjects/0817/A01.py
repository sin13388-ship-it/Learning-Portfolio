import RPi.GPIO as GPIO
import time
ledPin=29

GPIO.setmode(GPIO.BOARD)
GPIO.setup(ledPin, GPIO.OUT)

try:

    while(true):
    GPIO.output(ledPin,False)
    time.sleep(1)
    GPIO.output(ledPin,True)
    time.sleep(1)

except KeyboardInterrupt:
    GPIO.cleanup()
