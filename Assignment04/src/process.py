from memory import PageTable

class Process(object):

    def __init__(self, name, arrival_time, duration, last_accessed_page):
        self.name = name
        self.arrival_time = arrival_time
        self.duration = duration
        self.pages = []
        # this variable is initialized to zero but must be updated by the OS, i.e. main()
        self.last_accessed_page = 0
        #this variable is used for the locality reference
        self.current_page = -1

    def __lt__(self, other):
        return self.arrival_time < other.arrival_time

    # this still needs to be tested
    def clear(self, page_table):
        # check if each page in self.pages is in either memory or disk
        # dictionary.pop(key, None) is a null-safe way to atomically check and remove an item if it's in there
        for page in self.pages:
            page_table.memory.pop(page.name, None)
            page_table.disk.pop(page.name, None)

