# this test creates processes from Process.py, then puts them into a set and prints out the attributes for each
#from queue import PriorityQueue
from process import Process
from queue import PriorityQueue


NUMBER_OF_PROCESSES = 150

processSet = set()
pq = PriorityQueue()
# make a set of 150 processes, add to processSet
for x in range(NUMBER_OF_PROCESSES):
	name = "P" + str(x)
	process = Process(name)
	processSet.add(process)

for process in processSet:
	print("Name: \t\t\t", process.name)
	print("Size: \t\t\t", process.size)
	print("Arrival Time: \t", process.arrival_time)
	print("Duration: \t\t", process.duration, "\n")
	pq.put((process))

print("\n\n\n\nPRINTING PQ")

# test if PriorityQueue implemented comparison correctly by using "get" each item; they should increment in order
for x in range (150):
	print(pq.get().arrival_time)
