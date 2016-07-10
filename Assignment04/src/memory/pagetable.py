import page

class PageTable(object):
    '''
    '''

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

    def get_page():
        pass
