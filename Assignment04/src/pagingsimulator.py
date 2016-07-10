import logging
import datetime
import sys
import random
from process import Process

def create_job_queue(number, name, size, execution, runtime):
    '''
    Generates random processes and places them into a priority queue
    '''
    # Initialize the processes
    # TODO Enforce unique naming
    # TODO Enforce even distribution
    job_queue = PriorityQueue(maxsize=0) # If maxsize is 0, queue size is infinite
    for i in range(number):
        priority = random.choice(range(execution))
        process = Process(
            random.choice(name),
            random.choice(size),
            priority,
            random.choice(runtime))

        job_queue.enqueue((priority, process))
    return job_queue

def main():
    logging.info('Inside main()')

    # Simulation Variables 
    EXECUTION_TIME  = 600

    # Memory Variables
    MAIN_MEMORY     = 100             # Units as MB 
    TOTAL_FREE_PAGES      = 100
    PAGE_SIZE       = 1               # Size as MB

    # Process Variables
    NUMBER_OF_PROCESSES = 150
    PROCESS_NAME_SIZE    = range(11)
    PROCESS_SIZE    = [5, 11, 17, 31] # Randomly chosen, Size as MB
    PROCESS_RUNTIME = [1, 2, 3, 4, 5] # Randomly chosen, Time as seconds

    book_keeping = list()
    '''
    job_queue = create_job_queue(
        NUMBER_OF_PROCESSES,
        PROCESS_NAME_SIZE,
        PROCESS_SIZE,
        EXECUTION_TIME,
        PROCESS_RUNTIME)
    '''

    # Initialize page_list
    page_list = dict.fromkeys(range(TOTAL_FREE_PAGES))

    #while not job_queue.empty():
        #free_pages = sum(x == None for x in job_queue.values())
        #if free_pages > 3:
            # Assign process







    # TODO Generate an appropriate record whenever starting or completing a job
    #      <time stamp, process name, enter/exit, size, duration, memory-map>


################################################################################
if __name__ == '__main__':
    # Logging Init
    current_time = datetime.datetime.strftime(datetime.datetime.now(), '%Y%m%d.%H%M%S')
    logging_file = 'logs/simulator_' + current_time + '.log'
    logging_format = '%(asctime)s %(message)s'
    logging.basicConfig(filename=logging_file, format=logging_format, level=logging.DEBUG)

    # Application entry point
    logging.info('Calling procedure main(), initiating paging simulation')
    main();
    # Application controlled termination
    logging.info('Application execution terminated successfully')
    sys.exit()



