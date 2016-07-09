import random
from queue import PriorityQueue

EXECUTION_TIME = 100
NUMBER_OF_PROCESSES = 10
PROCESS_NAME = range(11)
PROCESS_SIZE = [5, 11, 17, 31]
PROCESS_RUNTIME = range(1, 6)

# Initialize the processes
pq = PriorityQueue(maxsize=0) # If maxsize is 0, queue size is infinite
for i in range(NUMBER_OF_PROCESSES):
    process = dict()
    process['name'] = random.choice(PROCESS_NAME) # Needs a check to enforce uniqueness
    process['size'] = random.choice(PROCESS_SIZE)
    process['arrival_time'] = random.choice(range(EXECUTION_TIME))
    process['duration'] = random.choice(PROCESS_RUNTIME)
    pq.put((process['arrival_time'], process))

while not pq.empty():
    p = pq.get()
    print(p)
