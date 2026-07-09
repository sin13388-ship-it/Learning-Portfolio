#!/usr/bin/python     
#coding=utf-8

# ≥ 10000	8 折	金額 × 0.8
# ≥ 5000 且 < 10000	85 折	金額 × 0.85
# ≥ 3000 且 < 5000	9 折	金額 × 0.9
# ≥ 1000 且 < 3000	95 折	金額 × 0.95
# < 1000	不打折	原價

#nested if-else
money = int(input("請輸入購物金額："))
if(money >= 1000):
    if(money >= 10000):
        print(str(money * 0.8)+"元\n")  #八折
    elif(money >= 5000):
        print(str(money * 0.85)+"元\n")  #八五折
    elif(money >= 3000):
        print(str(money * 0.9)+"元\n")  #九折
    else:
        print(str(money * 0.95)+"元\n")  #九五折
else:
    print(str(money)+"元\n")  #未打折


# money = int(input("請輸入購物金額："))

if money >= 10000:
    print(str(money * 0.8) + "元\n")     # 八折
elif money >= 5000 and money < 10000:
    print(str(money * 0.85) + "元\n")    # 八五折
elif money >= 3000 and money < 5000:
    print(str(money * 0.9) + "元\n")     # 九折
elif money >= 1000 and money < 3000:
    print(str(money * 0.95) + "元\n")    # 九五折
else:
    print(str(money) + "元\n")           # 未打折