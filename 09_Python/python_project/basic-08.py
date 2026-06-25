# Baisc I/O, math
#input 會回傳字串
ch=input("Please input your chinese score: ")
eng=input("Please input your eng score: ")
math=input("Please input your math score: ")
# print(f"ch:{ch}, eng:{eng}, math:{math}")
sum=ch+eng+math #會變成字串相加
#使用type檢查型態
print(type(sum))

sum=int(ch)+int(eng)+int(math) #要casting
avg =sum/3
print(type(avg))
print(avg)

