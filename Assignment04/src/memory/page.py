class Page(object):
    '''
    A class which simulates pages used by memory
    '''
    pages = set()

    def __init__(self, page_id, page_size, last_accessed):
        self.page_id = page_id
        self.page_data = None
        self.last_accessed = last_accessed
        self.pages.add(self)

    def store_data(self, data):
        '''
        Stores data to the page

        Arguments:
            data: Data to store in the page
        '''
        self.page_data = data

    def clear(self):
        '''
        Clears stored data from page memory
        '''
        self.page_data = None

    def access(self):
        '''
        Retrieves the stored data

        Returns:
            self.data: The stored page data
        '''
        return self.page_data
