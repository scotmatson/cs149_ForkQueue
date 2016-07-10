import page

class page_table(object):
    '''
    '''
    RAM = {}
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
            p = page.Page(i, page_size)
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
