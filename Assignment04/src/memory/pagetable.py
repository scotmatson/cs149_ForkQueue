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
    or "touched," by a process. Whether or not a page needs to be replaced and the
    page replacement algorithm performed is decided in main(), which we call os()
    because it is simulating the Operating System. For our assignment, the OS, which
    is simulated by pagingsimulator.py, decides when to perform a page replacement.
    The decision is that there must be a minimum of 4 pages remaining in memory for
    performance reasons. If there are currently 96 pages in memory when a "touch"
    is performed, then touch will still insert the page into memory, meaning that
    there will be 97 pages in memory and only 3 slots remaining. The OS has to
    be checking for this and call the page replacement algorithm.

    This checking code is already written and is inside pagingsimulator.py. It is
    not tested yet because there isn't an algorithm built yet to test it with.
    However, there is a clear stub where you need to plug in your algorithm -
    it's in the "access_page" method in pagingsimulator.py. Access_page will
    "touch" the page and update all the necessary attributes of pages and/or
    processes as necessary; the only thing left to do is testing and the
    algorithms.

    '''
    #####################################################
    # HOW DOES PAGETABLE WORK? WHAT ARE THE ATTRIBUTES?
    # Both disk and memory are OrderedDictionaries. Think of them as dictionaries that you can add and remove from
    # as if they were a PriorityQueue. The advantage to having them a dictionary is that you can add/remove at
    # constant time, like a dictionary or a hashMap.

    def __init__(self):
        '''
        Constructor function
        '''
        self.disk = OrderedDict()
        self.memory = OrderedDict()

    def __getitem__(self, process_id, orderedDict):
        for p in orderedDict:
            if p == process_id:
                return orderedDict[process_id]

# This function will add the page to memory. Here's the flow:
    # (1) If the page is already memory, put it at the "front" of memory. To do so, the code removes and then re-adds
    #       the page.
    # (2) Else if the page is NOT in memory, check if it's in the disk. If the page is in the disk, then remove it
    #       from the disk and put it into memory.
    # (3) Else, the page is NEITHER in memory NOR disk. So just put it in memory.
    #
    # A "touch" may bring the amount of pages in memory to 97, meaning there are only 3 slots in memory left. It
    # is the responsibility of the OS to check for this and call the page replacement algorithm as necessary.


    def print_memory_map(self):
        counter = 0
        map_line_string = "     "
        output_string = "\n     Pages in Memory Map:          \n"
        entry = "     "

        for key in self.memory:
            counter += 1

            if counter < 6:
                map_line_string += (key + " :: " + self.memory[key].process_id + entry)
            else:
                output_string += (map_line_string + "\n")
                counter = 0
                map_line_string = "     "

        print output_string

    def touch(self, page):
        if self.memory.has_key(page.name):
            del self.memory[page.name]
            self.memory.update({page.name: page})
            print "\nTouch attempt: Inside already there"
        elif self.disk.has_key(page.name):
            del self.disk[page.name]
            self.memory.update({page.name: page})
            print "\nTouch attempt: Was on disk"
        else:
            self.memory.update({page.name: page})
            print "\nTouch attempt: Newly Inserted"

            # run algo @ main

        self.print_memory_map()

