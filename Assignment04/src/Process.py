import random

class Process:
	PROCESS_SIZES = [5, 11, 17, 31]
	MIN_DURATION = 1
	MAX_DURATION = 5

	MIN_ARRIVAL_TIME = 0
	MAX_ARRIVAL_TIME = 599

	def __init__(self, name, PROCESS_SIZES, MIN_ARRIVAL_TIME, MAX_ARRIVAL_TIME, MIN_DURATION, MAX_DURATION):
		self.name = name
		self.size = random.choice(PROCESS_SIZES)
		self.arrival_time = random.randint(MIN_ARRIVAL_TIME, MAX_ARRIVAL_TIME)
		self.duration = random.randint(MIN_DURATION, MAX_DURATION)



