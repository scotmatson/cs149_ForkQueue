'''
A simple Python script used to calculate the total
distance covered by a mechanical storage disk arm
given N-number of movements across a storage cylinder

Author: Scot Matson
'''
import sys

def parse_args(args):
    '''
    Parses user input into a list of integers
    '''
    return list(map(int, args[1:]))

def abssub(x, y):
    '''
    Returns the difference of two integers
    '''
    return abs(x-y)

def main(argv):
    n = parse_args(argv)
    x = n[0]
    d = 0
    for y in n[1:]:
        d += abssub(x,y)
        x=y
    print('Total Distance: %d' % (d))

################################################################################
if __name__ == '__main__':
        main(sys.argv)
