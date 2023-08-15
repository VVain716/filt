from PIL import Image
import sys
import os

flags = ['-g', '-s', '-r', '-b']
extensions = ['jpeg', 'jpg', 'png', 'bmp']
def main():
    usage = """usage = python3 convert.py [flag] infile outfile"""

    if len(sys.argv) != 4:
        print(usage)
        exit(1)

    elif sys.argv[1] not in flags:
        print('Flag must be either -g for grayscale, -s for sepia, -r for reverse or -b for blur')
        exit(2)
    
    input_extension = sys.argv[2].split('.')
    if len(input_extension) != 2 or input_extension[1] not in extensions:
        print("Input file doesn't have valid extension")
        exit()

    output_extension = sys.argv[3].split('.')
    if len(output_extension) != 2 or output_extension[1] not in extensions:
        print("Output file doesn't have valid extension")
        exit()
    
    try:
        inputImage = Image.open(sys.argv[2])
    except FileNotFoundError:
        print("File not found")
        exit()
    os.system('mkdir temp')
    inputImage.save(f"temp/{input_extension[0]}.bmp")
    os.system(f'./filter {sys.argv[1]} temp/{input_extension[0]}.bmp temp/{output_extension[0]}.bmp')
    outputImage = Image.open('temp/' + output_extension[0] + '.bmp')
    outputImage.save(sys.argv[3])
    os.system('rm temp/*')
    os.system('rmdir temp')
main()
