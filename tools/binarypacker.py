#!/usr/bin/env python3

# simply packs a file of numbers into a binary format
import sys

def main (argv):
    # args
    if len(argv) < 3:
        print("usage: ./binarypacker inpath outpath [base]")
        exit(1)
    inpath = argv[1]
    outpath = argv[2]
    base = 16 if len(argv) < 4 else int(argv[3])

    print(f"writing bytes from {inpath} to {outpath} as base {base}")

    # read data from file
    data = b""
    try:
        with open(inpath, "r") as file:
            for dig in file.read().split():
                data += int(dig, base).to_bytes(2, byteorder="big")
    except FileNotFoundError:
        print("The specified file was not found.")
    except IOError as e:
        print("An error occurred while reading the file:", e)

    # pack data into file
    try:
        with open(outpath, 'wb') as file:
            file.write(data)
        print("Binary data successfully written to", outpath)
    except IOError as e:
        print("An error occurred while writing the binary data:", e)

if __name__ == "__main__":
    main(sys.argv)