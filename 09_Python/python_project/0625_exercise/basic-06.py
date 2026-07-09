#tuple
#() 用小括弧宣告， tuple 不能再重新賦值
tuple_data=('abc',786,2.23,'john',70.2,786,786)
tinytuple=(123,'joe')
# Get elements
print(tuple_data)
print(tuple_data[0])
print(tuple_data[1:3]) # 1~2 元素, return a tuple
print(tuple_data[2:])
print(tinytuple*2) #Doble your list (123, 'joe', 123, 'joe')
print(tuple_data+tinytuple) #concat tuple

#travel
for ele in tuple_data:
    print(ele, end='\t')
print()
