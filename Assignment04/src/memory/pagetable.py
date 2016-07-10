try:
    from memory import page
except:
    pass

try: import page
except: pass

class PageTable(object):
    '''
    '''
    def __init__(self, number_of_pages, page_size):
        '''
        Arguments:
            number_of_pages (int): The number of pages in the page list
            page_size (int): The size of a page in MB
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
        return sum(page.access() == None for page in self.pages.values())

    def get_free_pages(self, number_of_pages):
        free_pages = {}
        for page_id, page in pages.items():
            if pages[page_id].access() == None:
                free_pages[page_id] = page
        return free_pages
