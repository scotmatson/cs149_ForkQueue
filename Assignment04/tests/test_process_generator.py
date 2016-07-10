# this test creates processes from Process.py, then puts them into a set and prints out the attributes for each
#from queue import PriorityQueue
from TestProcess import Process
from Queue import PriorityQueue
import random


NUMBER_OF_PROCESSES = 150
PROCESS_SIZES = [5, 11, 17, 31]
MIN_DURATION = 1
MAX_DURATION = 5

MIN_ARRIVAL_TIME = 0
MAX_ARRIVAL_TIME = 599

processSet = set()
pq = PriorityQueue()
# make a set of 150 processes, add to processSet
for x in range(NUMBER_OF_PROCESSES):
    name = "P" + str(x)
    arrival_time = random.randint(0, 60000)
    duration = random.randint(1, 5)
    # must test pages, new creation, this will break
    process = Process(name, arrival_time, duration)
    processSet.add(process)

for process in processSet:
	print "Name: ", process.name
	print "          Arrival Time: ", process.arrival_time
	print "          Duration: ", process.duration, "\n"
	pq.put((process))

print("\n\n\n\nPRINTING PQ")

# test if PriorityQueue implemented comparison correctly by using "get" each item; they should increment in order
for x in range (150):
	print(pq.get().arrival_time)

