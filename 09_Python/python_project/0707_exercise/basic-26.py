# *:可變長度位置參數
def buy(*price):
    print(price)

buy(100,200,300) #tuple
buy("adc", "efg",3) 

data=(1,2,3,"a")
buy(*data) # *unpacking tuple
buy(data) #tuple