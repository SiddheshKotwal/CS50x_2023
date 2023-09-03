class Jar:
    def __init__(self, capacity):
        if not isinstance(capacity, int) or capacity < 0:
            raise ValueError("Capacity must be a non-negative integer")
        self.capacity = capacity
        self.cookies = 0

    def __str__(self):
        return "🍪" * self.cookies

    def deposit(self, n):
        if not isinstance(n, int) or n < 0:
            raise ValueError("Number of cookies to deposit must be a non-negative integer")
        if self.cookies + n > self.capacity:
            raise ValueError("Not enough room in the jar to deposit that many cookies")
        self.cookies += n

    def withdraw(self, n):
        if not isinstance(n, int) or n < 0:
            raise ValueError("Number of cookies to withdraw must be a non-negative integer")
        if self.cookies - n < 0:
            raise ValueError("Not enough cookies in the jar to withdraw that many")
        self.cookies -= n

    def capacity(self):
        return self.capacity

    def size(self):
        return self.cookies

def main():
    jar = Jar(12)
    print(jar.capacity)  # Output: 10
    print(str(jar))     # Output: ""

    jar.deposit(2)
    print(str(jar))     # Output: "🍪🍪"

    jar.withdraw(1)
    print(str(jar))     # Output: "🍪"

    jar.deposit(8)
    print(str(jar))     # Output: "🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪"

    jar.withdraw(3)    # Raises ValueError with "Not enough cookies in the jar to withdraw that many" message

if __name__ == "__main__":
    main()