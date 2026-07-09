#Homework1

#Q1
# top=int(input("請輸入上底"))
# bottom=int(input("請輸入下底"))
# heigh = int(input("請輸入高"))
# area=(top+bottom)*heigh/2
# print(f"梯形面積 : {area}")

#Q2

# for i in range(5):

#     heigh=int(input("請輸入身高(cm)"))/100
#     weight= int(input("請輸入體重(kg)"))
#     BMI=round(weight/(heigh*heigh),2)
#     if (BMI >=35):print(f"BMI值為 {BMI}, 屬重度肥胖")
#     elif (BMI>=30) :print(f"BMI值為 {BMI}, 屬中度肥胖")
#     elif (BMI>=27) :print(f"BMI值為 {BMI}, 屬輕度肥胖")
#     elif (BMI>=24) :print(f"BMI值為 {BMI}, 屬稍重")
#     elif (BMI>=18.5) :print(f"BMI值為 {BMI}, 屬正常範圍")
#     else : print(f"BMI值為 {BMI}, 屬體重過輕")

#Q3

mode=int(input("請輸入轉換單位模式: 1: 公尺->英尺| 2: 公斤->英磅 "))

if(mode==1) :
    length=float(input("請輸入欲轉換的長度 (公尺) : "))
    result=length*3.28
    print(f"{length} 公尺->{result} 英尺")
elif(mode==2) :
    weight=float(input("請輸入欲轉換的重量 (公斤) : "))
    result=weight*2.2
    print(f"{weight} 公斤->{result} 英磅")
else: 
    print("模式錯誤")

