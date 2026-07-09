try:
    pwd=int(input("Enter your password: "))
    print("Your password is: ", pwd)
except ValueError:
    print("Invalid input. Please enter a valid integer for the password.")
except Exception as e:
    print("An unexpected error occurred:", str(e))
else:
    print("Password accepted.") 
finally:
    print("Execution completed.")


try:
    value = int(input("Enter a number: "))
    result = 10 / value
    print("Result is:", result)
except ValueError:
    print("Invalid input. Please enter a valid integer.")
except Exception as e:
    print("An unexpected error occurred:", str(e))