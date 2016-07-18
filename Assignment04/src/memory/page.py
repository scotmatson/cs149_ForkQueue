import sys

# Disable bytecode generation
sys.dont_write_bytecode = True

class Page(object):
    '''
    A class which simulates pages used by memory
    '''
    def __init__(self, name, process_id, last_accessed):
        '''
        Constructor function

        Arguments:
            name (string)       : Page identifier in form P[int]
            process_id (int)    : Numerical identifier of stored process
            last_accessed (int) : Time in execution when page was accessed
            order_assigned (int): If order_assigned == 5, this was
                                  the 5th page assigned to a process
        '''
        self.name = name
        self.process_id = process_id
        self.last_accessed = last_accessed
        self.order_assigned = 0
        self.frequency = 0
        
    def __str__(self):
        '''
        Python toString for page printing
        '''
        return '%s :: %s' % (self.name, self.process_id)

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
