import random
from queue import PriorityQueue
import sys
from .. import Process

EXECUTION_TIME = 100
NUMBER_OF_PROCESSES = 150
PROCESS_NAME = range(11)
PROCESS_SIZE = [5, 11, 17, 31]
PROCESS_RUNTIME = range(1, 6)

# make a set of 150 processes
pq = PriorityQueue(maxsize=0) # If maxsize is 0, queue size is infinite
for x in range(NUMBER_OF_PROCESSES):
	name = "P" + str(x)
	process = Process(name)
	pq.put((process['arrival_time'], process))

while not pq.empty():
    p = pq.get()
    print(p)
