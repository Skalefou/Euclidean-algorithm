print("GCD")
a = int(input("Enter the first number : "))
b = int(input("Enter the second number : "))

while b != 0:
    r = a % b
    a = b
    b = r
print("PGCD : ", a)
