def scope():
    var1=1
    print(f"local variable var1: {var1}")

var1=2
scope()
print(f"global variable var1: {var1}")
