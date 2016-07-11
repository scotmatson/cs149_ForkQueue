import logging
import datetime
import sys
import random

# these two are needed for Francisco's machine

from memory import PageTable

import algorithms
from Queue import PriorityQueue
from process import Process
import string
from memory import Page


def create_job_queue(number, name, size, execution, runtime):
    '''
    Generates random processes and places them into a priority queue
    '''
    # Initialize the processes
    # TODO Enforce unique naming
    # TODO Enforce even distribution

    pq = PriorityQueue(maxsize=0) # If maxsize is 0, queue size is infinite
    for i in range(number):
        priority = random.choice(range(execution))
        process = Process(
            random.choice(name),
            random.choice(size),
            priority,
            random.choice(runtime))
        pq.put((priority, process))
    return pq

def main():
    logging.info('Inside main()')

    # Simulation Variables, should be 60000 if 100ms quanta in one minute
    EXECUTION_TIME  = 60000

    # Memory Variables
    MAIN_MEMORY     = 100             # Units as MB 
    PAGE_SIZE       = 1               # The size of a page in MB
    TOTAL_PAGES     = 100             # Maximum number of pages held by the page table 
    MIN_PAGES       = 4               # The minimum number of pages required to assign a process

    # Process Variables
    NUMBER_OF_PROCESSES = 150
    PROCESS_NAME_SIZE    = range(11)
    PROCESS_SIZE    = [5, 11, 17, 31] # Randomly chosen, Size as MB
    PROCESS_RUNTIME = [1, 2, 3, 4, 5] # Randomly chosen, Time as seconds
    MIN_DURATION = 1
    MAX_DURATION = 5
    MIN_ARRIVAL_TIME = 0
    MAX_ARRIVAL_TIME = 59999

    # makes the processes, populate them with pages
    processList = []
    pq = PriorityQueue()
    # this is for Francisco's implementation
    pagetable = PageTable()

    # make a set of 150 processes, add to processSet
    for x in range(NUMBER_OF_PROCESSES):
        name = "P" + str(x)
        arrival_time = random.randint(0, MAX_ARRIVAL_TIME)
        duration = random.randint(MIN_DURATION, MAX_DURATION)
        page_amount = random.choice(PROCESS_SIZE)
        pages = []

        process = Process(name, arrival_time, duration, pages)

        for x in range(page_amount):
            page_name_num = random.randint(0, 1000)
            page_name_string = ''.join(random.sample(string.ascii_lowercase, 5))
            page_name = page_name_string + str(page_name_num)
            last_accessed = random.randint(0, 59999)
            frequency = 0

            new_page = Page(page_name, process.name, last_accessed, frequency)
            process.pages.append(new_page)

        # must test pages, new creation, this will break
        processList.append(process)

    book_keeping = list()
    workload = create_job_queue(
        NUMBER_OF_PROCESSES,
        PROCESS_NAME_SIZE,
        PROCESS_SIZE,
        EXECUTION_TIME,
        PROCESS_RUNTIME)

    # Initialize page_list


    ################################################################################################
    #####   CODE FOR THE REST OF MAIN() AND CALLING ALGO'S GOES HERE #######################################
    ################################################################################################


    # scot, this line is screwed up on my machine
    #page_table = memory.pagetable.PageTable(TOTAL_PAGES, PAGE_SIZE)



    # HAD TO COMMENT OUT CUZ NOT WORKING ON FRANCISCO
    # Execute Algorithms
    # logging.info('BEGIN; FIFO Algorithm')
    # algorithms.first_in_first_out(workload, page_table, MIN_PAGES)
    # logging.info('END; FIFO Algorithm')

    #logging.info('BEGIN; LRU Algorithm')
    #algorithms.least_recently_used(workload, page_table, book_keeping, MIN_PAGES)
    #logging.info('END; LRU Algorithm')

    #logging.info('BEGIN; LFU Algorithm')
    #algorithms.least_frequently_used(workload, page_table, book_keeping, MIN_PAGES)
    #logging.info('END; LFU Algorithm')

    #logging.info('BEGIN; MFU Algorithm')
    #algorithms.most_frequently_used(workload, page_table, book_keeping, MIN_PAGES)
    #logging.info('END; MFU Algorithm')

    #logging.info('BEGIN; RAND Algorithm')
    #algorithms.random(workload, page_table, book_keeping, MIN_PAGES)
    #logging.info('END; RAND Algorithm')
################################################################################
if __name__ == '__main__':
    # Logging Init
    # current_time = datetime.datetime.strftime(datetime.datetime.now(), '%Y%m%d.%H%M%S')
    # logging_file = 'logs/simulator_' + current_time + '.log'
    # logging_format = '%(asctime)s %(message)s'
    # logging.basicConfig(filename=logging_file, format=logging_format, level=logging.DEBUG)
    #
    # # Application entry point
    # logging.info('Calling procedure main(), initiating paging simulation')
    main();
    # Application controlled termination
    logging.info('Application execution terminated successfully')
    sys.exit()



