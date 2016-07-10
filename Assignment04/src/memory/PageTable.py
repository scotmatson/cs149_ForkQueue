import Page

# This class simulates the Page Table. The purpose of the Page Table is to make user level processes believe that all of
# their data is in memory, which may or may not be the case. Due to limitations on physical memory, some of the data
# may have to reside on disk and be brought back into memory when it is accessed, or "touched," by a process.
# Slots in physical memory are tracked using the RAM_tokenCounter.

class page_table(object):
    '''
    '''
    # RAM keys are strings page.name; value is the Process object itself
    RAM = {}

    # RAM keys are strings page.name; value is the Process object itself

    Disk = {}
    RAM_tokenCounter = 100

    def __init__(self, number_of_pages, page_size):
        '''
        Arguments:
            free_pages (int): The number of pages in the page list
        '''
        self.pages = dict()
        for i in range(number_of_pages):
            # TODO value of i should be a unique page_id
            p = Page.Page(i, page_size)
            self.pages[i] = p
        #self.free_pages = dict.fromkeys(range(number_of_pages))
        #self.page_size = page_size

    def available_pages(self):
        '''
        Returns the number of free pages remaining in the
        page list as an int value. Empty pages are represented
        by None type.

        Returns:
            The number of available pages in the page list
        '''
        return sum(x.access() == None for x in self.pages)
        #return sum(x == None for x in self.free_pages.values())

    def get_page(page):
        pass

    #
    # def touch(page):
    #     page.lastAccessed = clock
	#
    #     # if the page is in memory, update its access and put it at the front of the queue in RAM; else,
    #     # perform the algorithm
    #     if page in RAM:
    #         RAM.put(page)
    #     else
    #         pageReplacement(algorithm)
    #
    #

    def touch(self, page):
        if page in self.RAM:
            print "Adding to RAM: ", page.page_ID
            self.RAM.add(page)
