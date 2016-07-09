import random

PROCESS_SIZE = [5, 11, 17, 31]
PROCESS_RUNTIME = range(1, 5)

for i in range(10):
    print('Process Size: %d' % random.choice(PROCESS_SIZE))

for i in range(10):
    print('Process Runtime: %d' % random.choice(PROCESS_RUNTIME))
