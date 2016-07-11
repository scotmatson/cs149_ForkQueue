from TestPage import Page
from TestProcess  import Process
from Queue import PriorityQueue
#from queue import PriorityQueue

import random
import string



##############################################################
###### BEGIN PROCESS TEST CODE.

NUMBER_OF_PROCESSES = 150
PROCESS_SIZE = [5, 11, 17, 31]
MIN_DURATION = 1
MAX_DURATION = 5

MIN_ARRIVAL_TIME = 0
MAX_ARRIVAL_TIME = 59999

processSet = set()
pq = PriorityQueue()
# make a set of 150 processes, add to processSet
for x in range(NUMBER_OF_PROCESSES):
    name = "P" + str(x)
    arrival_time = random.randint(0, 60000)
    duration = random.randint(1, 5)
    page_amount = random.choice(PROCESS_SIZE)
    pages = []

    process = Process(name, arrival_time, duration, pages)

    for x in range(page_amount):
        page_name_num = random.randint(0, 1000)
        page_name_string = ''.join(random.sample(string.ascii_lowercase, 5))
        page_name = page_name_string + str(page_name_num)
        last_accessed = random.randint(0, 59999)

        new_page = Page(page_name, process.name, last_accessed)
        process.pages.append(new_page)

    # must test pages, new creation, this will break
    processSet.add(process)

for process in processSet:
    print "\n     Name: ", process.name, "       Arrival Time: ", process.arrival_time, "       Duration: ", process.duration, "\n"
    for page in process.pages:
        print "Page: ", page.name, "     Process_ID: ", page.process_id, "     Last Accessed: ", page.last_accessed
	pq.put((process))

# print("\n\n\n\nPRINTING PQ")

# test if PriorityQueue implemented comparison correctly by using "get" each item; they should increment in order
# for x in range (150):
# 	print(pq.get().arrival_time)







