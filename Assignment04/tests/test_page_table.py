import random
from Queue import PriorityQueue

PROCESS_SIZES = [5, 11, 17, 31]
MIN_DURATION = 1
MAX_DURATION = 5

MIN_ARRIVAL_TIME = 0
MAX_ARRIVAL_TIME = 599

class Process:
	def __init__(self, name):
		self.name = name
		self.size = random.choice(PROCESS_SIZES)
		self.arrival_time = random.randint(MIN_ARRIVAL_TIME, MAX_ARRIVAL_TIME)
		self.duration = random.randint(MIN_DURATION, MAX_DURATION)
		self.pages = {}
	def __lt__(self, other):
		return self.arrival_time < other.arrival_time

class page:
	'''
	A class which simulates pages used by memory
	'''

	def __init__(self, page_id, page_size, last_accessed):
	    # type: (object, object, object) -> object
		self.page_id = page_id
		self.page_data = None
		self.last_accessed = last_accessed


class page_table:
	'''
	'''
	RAM = {}
	Disk = {}
	RAM_tokenCounter = 100

	def __init__(self):
		'''
		Arguments:
			free_pages (int): The number of pages in the page list
		'''
		# self.pages = dict()
		# for i in range(number_of_pages):
		# 	# TODO value of i should be a unique page_id
		# 	p = page.page(i, page_size)
		# 	self.pages[i] = p
		# #self.free_pages = dict.fromkeys(range(number_of_pages))
		# #self.page_size = page_size

	def touch(self, page):
		print "Adding to RAM: ", page.page_ID
		self.RAM.add(page)

		"\nCurrent Pages in RAM: "
		for item in self.RAM:
			print "Page: ", item.page_id


page_table = page_table()
NUMBER_OF_PROCESSES = 150

processSet = set()
pq = PriorityQueue()
# make a set of 150 processes, add to processSet
for x in range(NUMBER_OF_PROCESSES):
	name = "P" + str(x)
	process = Process(name)

	for x in range(10):
		page_name = random.randint
		new_page = page(page_name, None, 0)
		process.pages[new_page] = process.name

	processSet.add(process)

for x in range(150):
	print "test"
	print pq.get()







