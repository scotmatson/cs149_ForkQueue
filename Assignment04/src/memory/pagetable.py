import sys
try: from Queue import PriorityQueue
except: from queue import PriorityQueue
try: from memory import page
except: import page
from collections import OrderedDict

# Disable bytecode generation
sys.dont_write_bytecode = True

class PageTable(object):
    '''
        Simulates the operations of the Memory Management Unit Page Table.
    '''
    def __init__(self):
        '''
        Constructor function
        '''
        self.disk = OrderedDict()
        self.memory = OrderedDict()

    def __getitem__(self, process_id, orderedDict):
        '''
        '''
        for p in orderedDict:
            if p == process_id:
                return orderedDict[process_id]
                

    def print_memory_map(self):
        '''
        Used to print all pages currently in memory
        or on the disk
        '''
        memory_output = '\n\tPages in Memory:'
        for key in self.memory:
            memory_output += '\n\t\t' + str(self.memory[key])
            
        disk_output = '\n\n\tPages on Disk:'
        for key in self.disk:
            disk_output += '\n\t\t' + str(self.disk[key])

        output = memory_output + disk_output
        return output


    def touch(self, page, clock):
        '''
        Touch is called any time a page is accessed
        '''
        # if page not in memory, add it
        if page.name not in self.memory.keys():
            self.memory[page.name] = page
        # if page had been evicted to disk and is currently there
        if page.name in self.disk.keys():
            del self.disk[page.name]

