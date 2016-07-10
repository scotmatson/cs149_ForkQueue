class PageList(object):
    '''
    '''

    def __init__(self, free_pages):
        '''
        Arguments:
            free_pages (int): The number of pages in the page list
        '''
        self.free_pages = dict.fromkeys(range(free_pages))

    def available_pages(self):
        '''
        Returns the number of free pages remaining in the
        page list as an int value. Empty pages are represented
        by None type.

        Returns:
            The number of available pages in the page list
        '''
        return sum(x == None for x in self.free_pages.values())
