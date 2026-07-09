# Python 基本

import math

counter =100
miles =1000.0
name = "John"
flag1=True
flag2=False

print(f"counter = {counter}")
print("miles ", str(miles))
print("miles ", str(miles), sep="&", end=" ") #sep 可以更換字元, end 可以更換結尾字元; 預設是\n
print("test1")
print("name ", name, sep=",", end="\n") #sep 可以更換字元, end 可以更換結尾字元; 預設是\n
print("test2")

# 參數格式化:%
# 和C語言一樣
# '%(a,b) 放參數
print("參數格式化: % ====")
print("%s 的成績是 %d"%(name, counter))
print("PI=%f"%(math.pi))
print("PI=%10.3f"%(math.pi)) #總長度10, 小數為3, [.] 算一個
print("PI=%6.0f"%(math.pi)) #總長度6, 沒有小數點


# 參數格式:format
# {}, format(parameter1, parameter2,...)
print("參數格式: .format ====")
print("{}的成績為{}".format(name, counter))
print("PI={}".format(math.pi))
print("PI={:10.3f}".format(math.pi)) #總長度10, 小數為3, [.] 算一個
print("PI={:6.0f}".format(math.pi)) #總長度6, 沒有小數點


# f-String:after Python 3.6
print("f-String ====")

print(f"{name}的成績為{counter}")
print(f"PI={math.pi}")
print(f"PI={math.pi:10.3f}")
print(f"PI={math.pi:6.0f}")
print(f"PI={math.pi:.3}") #保留總共3位的有效數字 (沒有 '.')
print(f"PI={math.pi:.3f}") #保留小數點3位

