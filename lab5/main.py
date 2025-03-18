import random
import subprocess


def random_string(length: int, charset: str) -> str:
    return "".join(random.choices(charset, k=length))


def main():
    charset = "abcdef0123456789"
    print("n T(n)")
    for i in range(7, 15):
        length = 2 ** i
        n1, n2 = ["+" + random_string(length, charset) for _ in range(2)]
        process = subprocess.run(["./prog", n1, n2], capture_output=True)

        output = process.stdout.decode()
        print(length, output, end="")


if __name__ == "__main__":
    main()
