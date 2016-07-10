# by Francisco

import random

class Process:

    def __init__(self, name, size, arrival, duration):
        self.name = name
        self.size = size
        self.arrival_time = arrival
        self.duration = duration
        self.pages = None

    def __lt__(self, other):
        return self.arrival_time < other.arrival_time

    def set_pages(self):
        pass
