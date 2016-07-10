# this test creates processes from Process.py, then puts them into a set and prints out the attributes for each
#from queue import PriorityQueue
from Process import Process


NUMBER_OF_PROCESSES = 150

processSet = set()

# make a set of 150 processes, add to processSet
for x in range(NUMBER_OF_PROCESSES):
	name = "P" + str(x)
	process = Process(name)
	#pq.put((process['arrival_time'], process))
	processSet.add(process)

for process in processSet:
	print "Name: \t\t\t", process.name
	print "Size: \t\t\t", process.size
	print "Arrival Time: \t", process.arrival_time
	print "Duration: \t\t", process.duration, "\n"
