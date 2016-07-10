# by Francisco

import random

class Process(object):

    def __init__(self, name, size, arrival, duration):
        self.name = name
        self.size = size
        self.arrival_time = arrival
        self.duration = duration
        self.pages = None # This is something the process probably doesn't care about

    def __lt__(self, other):
        return self.arrival_time < other.arrival_time

    def set_pages(self):
        pass
