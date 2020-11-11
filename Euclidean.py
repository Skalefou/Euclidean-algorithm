print("PGCD")
a = input("Enter the first number : ")
b = input("Enter the second number : ")

a = int(a)
b = int(b)

while b != 0:
    r = a % b
    a = b
    b = r
print("PGCD : ", a)