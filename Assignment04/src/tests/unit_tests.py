import sys
import os

def main():

    python3 = 'python3'

    # List of tests to run
    test_modules = [
        'test_random_generator.py',
        'test_process_generator.py'
    ]

    # Loops through all tests, outputs to stdout
    for test_file in test_modules:
        cmd = python3+' '+test_file
        os.system(cmd)

################################################################################
if __name__ == '__main__':
    main()
