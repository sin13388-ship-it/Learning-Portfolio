#Homework-2

print("Question 1: ")
sum=0
while True:
    donation=int(input("請輸入捐款金額(輸入0結束):"))
    if donation < 0:
        print("捐款金額不能為負數,請重新輸入")
        continue
    if donation == 0:
        break
    sum += donation
print("總捐款金額為:", sum)


print("="*10,"\n")
print("Question 2: \n")
for i in range(1,5):
    print("*"*i,end="\n")

print("\n")

n=4
for i in range(1,5):
        print(" "*(n-i),"*"*(2*i-1),end="\n")
        

        