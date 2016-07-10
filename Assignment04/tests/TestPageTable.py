import TestPage

# This class simulates the Page Table. The purpose of the Page Table is to make user level processes believe that all of
# their data is in memory, which may or may not be the case. Due to limitations on physical memory, some of the data
# may have to reside on disk and be brought back into memory when it is accessed, or "touched," by a process.
# Slots in physical memory are tracked using the RAM_tokenCounter.

class TestPageTable:

    # RAM keys are strings page.name; value is the Process object itself
    RAM_tokenCounter = 100

    def __init__(self, RAM, disk):

        # RAM keys are strings page.name; value is the Page object itself
        self.RAM = RAM

        # disk keys are strings process.name; value is the Process object itself
        self.disk = disk

    # def touch(self, page):
    #     if page in self.RAM:
    #         print "Adding to RAM: ", page.page_ID
    #         self.RAM.add(page)
