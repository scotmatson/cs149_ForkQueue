try: from Queue import PriorityQueue
except: from queue import PriorityQueue

try: from memory import page
except: import page

from collections import OrderedDict

class PageTable(object):
    '''
    This class simulates the Page Table. The purpose of the Page Table is to make
    user level processes believe that all of their data is in memory, which may
    or may not be the case. Due to limitations on physical memory, some of the data
    may have to reside on disk and be brought back into memory when it is accessed,
    or "touched," by a process. Slots in physical memory are tracked using the
    RAM_tokenCounter.
    '''

    def __init__(self):
        '''
        Constructor function
        '''
        self.disk = OrderedDict()
        self.memory = OrderedDict()

    def touch(self, page):
        '''
        TODO: Francisco needs to document this logic
        '''
        if self.memory.has_key(page.name):
            del self.memory[page.name]
            self.memory[page.name] = page
        elif self.disk.has_key(page.name):
            del self.disk[page.name]
            self.memory[page.name] = page
            # run algo @ main
        else:
            self.memory[page.name] = page
            # run algo @ main
