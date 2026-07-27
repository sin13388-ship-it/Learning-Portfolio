#homework-3

import random

print("Question 1: ")
scores=[]
total=0
cnt=1
while True:
    score=int(input(f"請輸入第{cnt}筆成績(輸入-1結束):"))    
    if score == -1:
        if len(scores)==0:
            print("沒有資料輸入")
            break
        else:
            print(f"總分等於={sum(scores)}")
            print(f"平均等於={sum(scores)/len(scores) :.2f}")
            break
    elif score <-1:
        print("Invalid format")
        continue
    else: 
        scores.append(score)
        cnt+=1

# print("=="*5)


# print("Question2:")
# look_up_table={'apple':'蘋果','ball':'球','cat':'貓','dog':'狗'}
# print(look_up_table)
# text=str(input("請輸入要查詢的英文單字: "))
# if (text in look_up_table):
#     print(look_up_table[text])
# else:
#     print("本字典查無此英文單字")


# print("Question3:")

# lottery_numbers=random.sample(range(1,50),6)
# special_number=lottery_numbers[0]
# lottery_numbers.sort()
# print("大樂透中獎號碼為:\n", *(lottery_numbers))
# print("特別號碼為:",special_number,sep="\n")
