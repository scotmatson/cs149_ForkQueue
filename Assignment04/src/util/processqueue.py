class ProcessQueue(Object):
    '''
    A custom Priority Queue for simulated OS processes
    '''
    def __init__(self):
        pass

    def enqueue(self, item):
        '''
        Enqueues a process into the Priority Queue

        Arguments:
            item (tuple): A tuple containing a priority and process

        Returns:
            A boolean value
        '''

        if isinstance(item, tuple):
            priority, process = item
        else:
            raise ValueError('Argument must be tuple as (int, Process)')
        pass

    def dequeue(self):
        pass

    def empty(self):
        pass
