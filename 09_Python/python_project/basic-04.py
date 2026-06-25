str1="Hello world"
print(str1) 
print(str1[0]) #print 單一字元 'H'
print(str1[2:7]) #左閉右開 (2~6 的字元) "llo w"
print(str1[2:]) #從2開始到 EOL
print(str1 *2) #列印兩次
print(f"the length of str1: {len(str1)}")

#Travel
for letter in str1:
    print(f"current letter:{letter}")