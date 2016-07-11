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

# Simulation Variables, should be 60000 if 100ms quanta in one minute
EXECUTION_TIME = 60000  # There are 60000 milliseconds in one minute
PAGE_INTERVAL = 100     # Every 100 milliseconds, perform a random page access

# Process Variables
NUMBER_OF_PROCESSES = 150
PROCESS_SIZE = [5, 11, 17, 31]  # Randomly chosen, think of the size as 1 MB per page

# durations are the number of times you should run a process; this decrements every time it is ran
MIN_DURATION = 1
MAX_DURATION = 5
MAX_ARRIVAL_TIME = 59999

# MEMORY_MIN is the minimum number of pages that can be in page_table memory; if there are fewer than this number,
# then a page replacement event must occur
MEMORY_MIN = 4

# helper function; it "touches" a page
def access_page(clock, page_table, page):
    # update the time of access for that page
    page.last_accessed = clock

    # increase that page's frequency
    page.frequency += 1

    ############################
    #######  PAGE REPLACEMENT EVENT
    ############################

    # add the page to the page_table.memory
    page_table.touch(page)

    # if there are less than 4 slots left in page_table.memory, replace a page using an algo
    if page_table.memory.__sizeof__() > MEMORY_MIN:
        print "page replacement"
        # call page_replacement

def os():
    '''
    This is the main() function and entry point for the Paging Simulator.
    We are treating main() as an Operating System and named it accordingly so.
    '''

    # Makes the processes, populate them with pages
    process_list = []
    active_process_list = []
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
            last_accessed = 0

            new_page = Page(page_name, process.name, last_accessed)
            process.pages.append(new_page)

        # Must test pages, new creation, this will break
        process_list.append(process)



    #######################################
    #### ALGORITHM AND MAIN STARTS HERE
    #######################################



    ##################################################################################################################
    ##################################################################################################################
    # NOTE TO ALGO WRITERS:
    # There will be two opportunities when the OS will need to replace a page
    #
    #  PAGE REPLACEMENT EVENT (1): ADDING PAGES OF A NEW PROCESS
    #   Newly arrived processes will have all of their pages added into memory using the "touch" method. Any or all of
    #   the adds may require a page replacement.
    #
    # PAGE REPLACEMENT EVENT (2): TOUCHING A RANDOM PAGE OF A RANDOM PROCESS
    #   The assignment HW4 requires that at every 100ms, the OS selects a random active process; this process will
    #   try to access a single random page from its own page list in process.pages. To fetch this page for the process,
    #   the OS will again call touch on that page, resulting in another opportunity to replace a page.
    ##################################################################################################################
    ##################################################################################################################


    # BEGINNING OF MASTER LOOP
    clock = 0
    # for 60000 cycles
    for x in range(EXECUTION_TIME):
        # check if the process_list is empty; if it has processes in there, then they have to be loaded into memory
        if not process_list.isEmpty():

        # peek at the process_list, check if the next arrival_time == clock
            if process_list[0].arrival_time == clock:
                # if so, capture that process and pop it off the process_list
                new_process = process_list[0]
                process_list.pop(0)

                # add the new_process to the active_process_list
                active_process_list.append(new_process)

                # decrement that process's duration
                new_process.duration = new_process.duration - 1


                ######################################################################################
                #  PAGE REPLACE EVENT (1): ADDING PAGES OF A NEW PROCESS
                ######################################################################################

                # add all of that process's pages, one by one, into memory using touch
                for page in new_process.pages:
                    access_page(clock, page_table, page)



        # increment the master clock counter
        clock += 1

        # check if the clock is at a 100ms interval
        if clock % 100 == 0:

            # if so, then it's time to touch a random page of a random process in the active_process_list
            random_process = random.choice(active_process_list)
            random_page = random.choice(random_process.pages)

            ######################################################################################
            # PAGE REPLACE EVENT (2): TOUCHING A RANDOM PAGE OF A RANDOM PROCESS
            ######################################################################################
            access_page(clock, page_table, random_page)









################################################################################
if __name__ == '__os__':
    os();
    sys.exit()
