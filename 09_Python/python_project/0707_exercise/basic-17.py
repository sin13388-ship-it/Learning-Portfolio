#Sum 1~5

num=int(input("請輸入一個整數:"))
sum=0
while num>0:
    sum+=num
    num-=1

print(f"1到輸入的整數的總和為: {sum}")
