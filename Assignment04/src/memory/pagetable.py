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
        '''
        counter = 0
        output_string = "\n\tPages in Memory Map:\n"
        entry = "     "
        line_counter = 2
        map_line_string = "Count" + str(line_counter) + "\t\t"

        for key in self.memory:
            counter += 1

            if counter < 3:
                map_line_string += (key + " :: " + self.memory[key].process_id + entry)
            else:
                output_string += (map_line_string + "\n")
                counter = 0
                line_counter += 2
                map_line_string = "Count" + str(line_counter) + "\t\t"

        print(output_string)

    def print_disk(self):
        '''
        '''
        counter = 0
        output_string = "\n\tPages in Disk:\n"
        entry = "     "
        line_counter = 2
        map_line_string = "Count" + str(line_counter) + "\t\t"

        for key in self.disk:
            counter += 1

            if counter < 3:
                map_line_string += (key + " :: " + self.disk[key].process_id + entry)
            else:
                output_string += (map_line_string + "\n")
                counter = 0
                line_counter += 2
                map_line_string = "Count" + str(line_counter) + "\t\t"
        print(output_string)

    def touch(self, page):
        '''
        Adds or relocates a page to the front of the memory

        Arguments:
            page (Page): The page that will be added to memory
        '''
        if page.name in self.memory.keys():
            del self.memory[page.name]
            self.memory.update({page.name: page})
        elif page.name in self.disk.keys():
            del self.disk[page.name]
            self.memory.update({page.name: page})
        else:
            self.memory.update({page.name: page})
