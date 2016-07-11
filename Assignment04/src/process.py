from memory import PageTable

class Process(object):

    def __init__(self, name, arrival_time, duration, pages):
        self.name = name
        self.arrival_time = arrival_time
        self.duration = duration
        self.remaining = duration
        self.pages = pages

    def __lt__(self, other):
        return self.arrival_time < other.arrival_time

    # this still needs to be tested
    def clear(self, page_table):
        # check if each page in self.pages is in either memory or disk
        # dictionary.pop(key, None) is a null-safe way to atomically check and remove an item if it's in there
        for page in self.pages:
            page_table.memory.pop(page.name, None)
            page_table.disk.pop(page.name, None)

