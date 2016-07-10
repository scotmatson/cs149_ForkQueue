#from queue import PriorityQueue
from Process import Process


NUMBER_OF_PROCESSES = 150

# make a set of 150 processes
#pq = PriorityQueue(maxsize=0) # If maxsize is 0, queue size is infinite
mySet = set()
for x in range(NUMBER_OF_PROCESSES):
	name = "P" + str(x)
	process = Process(name)
	#pq.put((process['arrival_time'], process))
	mySet.add(process)

for process in mySet:
	print "Name: \t\t\t", process.name
	print "Size: \t\t\t", process.size
	print "Arrival Time: \t", process.arrival_time
	print "Duration: \t\t", process.duration, "\n"


