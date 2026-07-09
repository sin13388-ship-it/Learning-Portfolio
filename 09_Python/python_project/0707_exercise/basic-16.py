#10~20之間的質數
for num in range(10, 21):
    print(f"num={num}")
    #for else 的用法: 當for迴圈正常執行完畢(沒有break)時,執行else區塊
    for i in range(2,int(num/2)+1): #根據數學定理,若一個數不是質數,則必定有一個因數小於等於它的一半
        if num%i==0:
            print(f"{num}不是質數")
            break
    else:
        print(f"{num}是質數")

