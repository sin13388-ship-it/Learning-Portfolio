score=total=person=0
while True:
    score=int(input("請輸入分數(-1結束):"))
    if score==-1:
        break
    total+=score
    person+=1
if person>0:
    print(f"總分為: {total}")
    print(f"平均分數為: {total/person: .2f}")
else:
    print("沒有輸入分數")