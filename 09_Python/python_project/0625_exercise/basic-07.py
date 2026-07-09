# Dictionary
# 使用｛｝ 建立
# dictionary 是無序的

dict1={"name":"John", "code":6734, "dept":"sales"}
print(dict1)

# add
# dict_name[key]=value
# 如果不存在則為新增，存在則為修改
dict1['one']=1

#可以給一個空{}，之後再新增
dict2={}
dict2["one"]=1
dict2[2]="two"
print(dict2)

#修改
dict2[2]="2" #存在的直接修改
print(dict2)

# 刪除
del dict1['code']
print(dict1)

# get data
print(dict1["dept"]) #不存在會拋出例外

#safe call
print(dict1.get("test", "the element does not exist")) #取得對應的資料，失敗回傳指定訊息

#Travel
print("-----Travel-1---")
#只會回傳key，用key再去取得value
for key in dict1:
    print(f"{key}->{dict1[key]}")

print("-----Travel-2---")
#使用items取得集合(tuple)
for item in dict1.items():
    print(item)
    print(f"{item[0]}->{item[1]}")

print("-----Travel-3---")
#使用items 取得集合 key, value
for key, value in dict1.items():
     print(f"{key}->{value}")

#clear
dict1.clear()
print(dict1)
