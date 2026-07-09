#homework-3


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

print("=="*5)
print("Question2:")
