# list
# 用 []  宣告一個list
list_data=['abc',786,2.23,'john',70.2,786,786]
tinylist=[123,'joe']
# Get elements
print(list_data)
print(list_data[0])
print(list_data[1:3]) # 1~2 元素, return a list
print(list_data[2:])
print(tinylist*2) #Doble your list [123, 'joe', 123, 'joe']
print(list_data+tinylist) #concat list

# Set
list_data[2]='bbb'
print(list_data)

#delete 移除一個index
del list_data[2]
print(list_data)

#remove 某個值
list_data.remove('john')
print(list_data)

#append 在後面新增
list_data.append('ddd')
print(list_data)

#insert 指定位置插入，元素後移
list_data.insert(2,'bob')
print(list_data)

#travel
for ele in list_data:
    print(ele, end='\t')
print()

#length
print(f"the length of list = {len(list_data)}")

#count 
print(f"count for 786 = {list_data.count(786)}")