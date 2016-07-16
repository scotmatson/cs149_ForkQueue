import sys
from memory import PageTable

# Disable bytecode generation
sys.dont_write_bytecode = True

class Process(object):
    '''
    '''

    def __init__(self, name, arrival_time, duration, last_accessed_page):
        '''
        Constructor function for the Process class

        Arguments:
            name (string): The name of the process
            arrival_time (int): The arrival time which marks the time of execution
            duration (int): The duration of execution
            last_accessed_page (int): The ID of the last page that was accessed
        '''
        self.name = name
        self.arrival_time = arrival_time
        self.duration = duration
        self.pages = []
        # this variable is initialized to zero but must be updated by the OS, i.e. main()
        self.last_accessed_page = 0
        #this variable is used for the locality reference
        self.current_page = -1
        self.exit_time = 0

    def __lt__(self, other):
        '''
        Overloads the comparator operation to allow the comparison
        of two processes by arrival time.
        '''
        return self.arrival_time < other.arrival_time

    def clear(self, page_table):
        '''
        '''
        for page in self.pages:
            page_table.memory.pop(page.name, None)
            page_table.disk.pop(page.name, None)

