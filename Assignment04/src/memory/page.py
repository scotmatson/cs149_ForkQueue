class Page(object):
    '''
    A class which simulates pages used by memory
    '''

    def __init__(self, name, process_id, last_accessed, frequency):
        self.name = name
        self.process_id = process_id
        self.last_accessed = last_accessed
        self.frequency = frequency

    def store(self, data):
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
