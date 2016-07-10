import page

class PageList(object):
    '''
    '''

    def __init__(self, number_of_pages, page_size):
        '''
        Arguments:
            free_pages (int): The number of pages in the page list
        '''
        self.pages = set() # may have to change this into a Linked List per assignment
        for i in range(number_of_pages):
            p = page.Page(i, page_size)
            self.pages.add(p)

    def available_pages(self):
        '''
        Returns the number of free pages remaining in the
        page list as an int value. Empty pages are represented
        by None type.

        Returns:
            The number of available pages in the page list
        '''
        return sum(x.access() == None for x in self.pages)

    def get_page():
        pass
