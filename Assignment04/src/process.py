# by Francisco

import random

class Process(object):

	def __init__(self, name, size, arrival, duration):
		self.name = name
		self.size = size
		self.arrival_time = arrival
		self.duration = duration

	def __lt__(self, other):
		return self.arrival_time < other.arrival_time
