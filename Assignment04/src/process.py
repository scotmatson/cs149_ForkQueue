# by Francisco

import random

class Process(object):

    def __init__(self, name, arrival_time, duration, pages):
        self.name = name
        self.arrival_time = arrival_time
        self.duration = duration
        self.pages = pages

    def __lt__(self, other):
        return self.arrival_time < other.arrival_time

    def set_pages(self):
        pass
