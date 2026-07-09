try:
    # with...as : automatically closes the file after the block is executed
    with open('data.txt', 'r') as file:
        content = file.read()
        print(content)
except FileNotFoundError:
    print("The file 'data.txt' was not found.")