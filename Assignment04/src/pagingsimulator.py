# PYTHON LIBS
import sys
import random
import string
try: from Queue import PriorityQueue
except: from queue import PriorityQueue

# USER LIBS
import algorithms
from process import Process
from memory import Page
from memory import PageTable

def os():
    '''
    This is the main() function and entry point for the Paging Simulator.
    We are treating main() as an Operating System and named it accordingly so.
    '''
    # Simulation Variables, should be 60000 if 100ms quanta in one minute
    EXECUTION_TIME  = 60000           # Unit of time in milliseconds
    QUANTA = 100                      # Unit of time in milliseconds

    # Memory Variables
    MAIN_MEMORY       = 100             # Units as MB
    PAGE_SIZE         = 1               # The size of a page in MB
    TOTAL_PAGES       = 100             # Maximum number of pages held by the page table
    PAGES_PER_PROCESS = 4               # The minimum number of pages required to assign a process

    # Process Variables
    NUMBER_OF_PROCESSES = 150
    PROCESS_NAME_SIZE    = range(11)
    PROCESS_SIZE    = [5, 11, 17, 31] # Randomly chosen, Size as MB
    PROCESS_RUNTIME = [1, 2, 3, 4, 5] # Randomly chosen, Time as seconds
    MIN_DURATION = 1
    MAX_DURATION = 5
    MIN_ARRIVAL_TIME = 0
    MAX_ARRIVAL_TIME = 59999

    # Makes the processes, populate them with pages
    process_list = []
    pq = PriorityQueue()
    page_table = PageTable()

    # Make a set of 150 processes, add to process_list
    for x in range(NUMBER_OF_PROCESSES):
        name = "P" + str(x)
        arrival_time = random.randint(0, MAX_ARRIVAL_TIME)
        duration = random.randint(MIN_DURATION, MAX_DURATION)
        number_of_pages = random.choice(PROCESS_SIZE)
        pages = []

        process = Process(name, arrival_time, duration, pages)

        for x in range(number_of_pages):
            page_name_num = random.randint(0, 1000)
            page_name_string = ''.join(random.sample(string.ascii_lowercase, 5))
            page_name = page_name_string + str(page_name_num)
            last_accessed = random.randint(0, 59999)

            new_page = Page(page_name, process.name, last_accessed)
            process.pages.append(new_page)

        # Must test pages, new creation, this will break
        process_list.append(process)

################################################################################
if __name__ == '__os__':
    os();
    sys.exit()
