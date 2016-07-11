class Page:
    '''
    A class which simulates pages used by memory
    '''
    def __init__(self, name, process_id, last_accessed):
        self.name = name
        self.process_id = process_id
        self.last_accessed = last_accessed
        self.frequency = 0

