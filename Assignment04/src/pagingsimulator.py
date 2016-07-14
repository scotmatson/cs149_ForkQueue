'''
    file:
        pagingsimulator.py

    description:
        Aside from being the main point of executionf or this
        application, the main() method is used to carry out basic
        operating system procedures for memory management

    Authors:
        Francisco, Scot, Tyler, Daniel

    Group:
        ForkQueue

    Copyright (c) 2016
'''
# PYTHON LIBS
import sys
import random
import string
import time

try: from Queue import PriorityQueue
except: from queue import PriorityQueue
from collections import OrderedDict
# USER LIBS
import algorithms
from process import Process
from memory import Page
from memory import PageTable

# Disable byte code creation
sys.dont_write_bytecode = True

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
# Location_reference_probability from assignment
LOC_REF_PROB = .70


def locality_of_reference_select(process):
    #get the number of pages belonging to this process
    num_of_pages = len(process.pages)
    #if the page hasnt been referenced yet
    if process.current_page == -1:
        current_page = random.randint(0, num_of_pages - 1)  #random index for this process's pages
    else:
        r = random.randint(0, num_of_pages - 1)
        if r <= num_of_pages * LOC_REF_PROB:
            delta = random.randint(-1, 1) #delta is -1, 0, or 1
        else:
            if (num_of_pages - 1) - (process.current_page + 2) <= 0:
                top_rand = num_of_pages - 1
            else:
                top_rand = random.randint(process.current_page + 2, num_of_pages - 1)

            if (process.current_page - 2) <= 0:
                bottom_rand = 0
            else:
                bottom_rand = random.randint(0, process.current_page - 2)

            choices = [bottom_rand, top_rand]
            delta = random.choice(choices)

        #if current_page + delta puts us past the last index
        if (process.current_page + delta) >= (num_of_pages - 1):
            current_page = (process.current_page + delta) % (num_of_pages - 1)
        else:
            current_page = process.current_page + delta

    process.current_page = current_page
    return process.pages[current_page]

# # helper printer function; after every touch, print <time stamp, process name, Enter/exit, Size, Duration, Memory-map>
def print_status(process, clock, page_table):
    print("\nUNIX time: ", int(time.time()), "     Clock: ", clock, "     Process: ", process.name, "     " \
        "Arrival: ", process.arrival_time, "     Exit: ", process.exit_time, "     Duration: ", process.duration)

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
   # algorithms.random_pick(page_table)
    #algorithms.most_frequently_used(page_table)
    """
    #Run five time
    #for x in range(0,4):
        if x == 0:
            print ("Printing FIFO")
            algorithms.first_in_first_out(page_table)
        elif x == 1:
            print ("Printing LRU")
            #algorithms.least_recently_used(page_table)
        elif x == 2:
            print ("Printing LFU")
            algorithms.least_frequently_used(page_table)
        elif x == 3:
            print ("Printing MFU")
            algorithms.most_frequently_(page_table)
        elif x == 4:
            print ("Printing Random pick")
            algorithms.random_pick(page_table)
    """
    if page_table.memory.__sizeof__() < MEMORY_MIN:
        print("page replacement")
        #least_frequently_used(page_table)

        # page_replacement(algorithm_name, page_table)        # you need to write this function!!
        #
        # You need to write a function here in pagingsimulator called page_replacement, and it will take the algorithm
        # and the page_table as parameters. You decide how this works - do you want to make a menu for it like in
        # assignment2? I don't know what works for you, you have to decide. If you need more parameters, like the
        # active_process_list, then say let me know.
        #
        # The function, I imagine, will be something like page_replacement(FIFO, page_table), which means
        # "perform the page replacement algorithm FIFO on the object page_table"; this means the algorithm will have to
        # select a page in page_table.memory, remove it from page_table.memory, and put it in page_table.disk.
        # I don't imagine that any changes will need to be made to pagingsimulator.py, but I can't know that ahead of
        # time; you actually have to try and write the replacement algorithms.

def generate_processes(number_of_processes, max_arrival, min_duration, max_duration, process_size):
    '''
    Generates a list of random processes
    '''
    out = list()
    process_name_index = 0
    for x in range(number_of_processes):
        name = "P" + str(process_name_index)
        arrival_time = random.randint(0, max_arrival)
        duration = random.randint(min_duration, max_duration)
        number_of_pages = random.choice(process_size)

        process = Process(name, arrival_time, duration, 0)

        for x in range(number_of_pages):
            page_name_num = random.randint(0, 1000)
            page_name_string = ''.join(random.sample(string.ascii_lowercase, 5))
            page_name = page_name_string + str(page_name_num)
            last_accessed = 0

            new_page = Page(page_name, process.name, last_accessed)
            process.pages.append(new_page)

        # Must test pages, new creation, this will break
        out.append(process)
        process_name_index += 1
    return out

def simulate_paging(process_list, execution_time):
    '''
    Algorithms start here

    **There will be two opportunities when the OS will need to replace a page

    PAGE REPLACEMENT EVENT (1): ADDING PAGES OF A NEW PROCESS
        Newly arrived processes will have all of their pages added into memory using the "touch" method. Any or all of
        the adds may require a page replacement.

    PAGE REPLACEMENT EVENT (2): TOUCHING A RANDOM PAGE OF A RANDOM PROCESS
        The assignment HW4 requires that at every 100ms, the OS selects a random active process; this process will
        try to access a single random page from its own page list in process.pages. To fetch this page for the process,
        the OS will again call touch on that page, resulting in another opportunity to replace a page.

    NOTE:
       Right now, the os() code is just selecting a random page from a random process. Someone needs to
       implement the locality of reference thing, which means that the random page that is selected is not entirely
       random; there is a 70% chance that the page selected from the random process will be one to the left or
       one to the right of the page that was last accessed from that process. That's what the i - 1 and i + 1 means
       in the assignment. I put a tag where I think this code needs to be implemented down below.
    '''
    page_table = PageTable()
    active_process_list = OrderedDict()
    # BEGINNING OF MASTER LOOP
    clock = 0
    # for 60000 cycles
    for x in range(execution_time):
        # check if the process_list is empty; if it has processes in there, then they have to be loaded into memory

        # this line of code i don't think is good, it is causing problems
        for p in process_list:
        #if process_list:
        # peek at the process_list, check if the next arrival_time == clock
            if p.arrival_time == clock:
                # if so, capture that process and pop it off the process_list
                print("################################")
                print("New Process Arrival Event: ", p.name)
                print("################################")
                print("Status: ", print_status(p, clock, page_table))

                new_process = process_list.pop(0)

                # add the new_process to the active_process_list
                active_process_list[new_process.name] = new_process

                # decrement that process's duration
                new_process.duration = new_process.duration - 1

                ######################################################################################
                #  PAGE REPLACE EVENT (1): ADDING PAGES OF A NEW PROCESS
                ######################################################################################

                # add all of that process's pages, one by one, into memory using touch
                for page in new_process.pages:
                    #get the correct page using locality_of_reference
                    locality_page = locality_of_reference_select(new_process)
                    access_page(clock, page_table, locality_page)

                # if the process's duration is 0, remove all of its pages from memory
                # this is a stub, still needs implementation
                if new_process.duration == 0:
                    new_process.clear(page_table)

        # increment the master clock counter
        clock += 1

        # check if the clock is at a 100ms interval and there are still processes in the list
        if (clock % 100 == 0) and active_process_list:
            '''
            # Commmenting this out because I think we need to get random pages from all running processes, not just
            # one single random process - moved new code below

            # if so, then it's time to touch a random page of a random process in the active_process_list
            # choose a random process from the active process list
            # NOTE: This line of code does not need to be changed by the person is doing the locality of reference
            # thing!! This code just selects a random process
            random_process_name = random.choice(list(active_process_list.keys()))
            random_process = active_process_list[random_process_name]

            # decrement the duration counter for that randomly selected process
            print("testing  duration: ", active_process_list[random_process.name].duration)
            active_process_list[random_process.name].duration = active_process_list[random_process.name].duration - 1

            if active_process_list[random_process.name].duration <= 0:
                random_process.clear(page_table)
                del active_process_list[random_process.name]
            '''

            ######################################################################################
            # PAGE REPLACE EVENT (2): TOUCHING A RANDOM PAGE OF RUNNING PROCESSES
            ######################################################################################
            # NOTE: implement the 70% shit here!!
            # The code that selects a random page from the random_process is inside the following function:
            #       random.choice(random_process.pages)
            # Instead of this code, there needs to be a function called locality_of_reference_select, or
            # special_page_select, whatever you want to call it. It will take in as a parameter a process and return
            # a page. Based on the process.last_page_accessed attribute, which tracks the index "i" of the last page
            # accessed, the function has a 70% chance to select "i-1" or "i+1" as the page to be "touched".

            #get the correct page using locality_of_reference
            #for key, active_process in active_process_list.items():
            for key in list(active_process_list.keys()):
                active_process = active_process_list[key]
                # decrement the duration counter for the current process
                active_process.duration = active_process.duration - 1

                if active_process.duration <= 0:
                    active_process.clear(page_table)
                    del active_process_list[active_process.name]
                #locality_page = locality_of_reference_select(random_process)
                locality_page = locality_of_reference_select(active_process)
                access_page(clock, page_table, locality_page)

def main():
    '''
    This is the main() function and entry point for the Paging Simulator application
    '''
    # Makes the processes, populate them with pages
    process_list = generate_processes(
        NUMBER_OF_PROCESSES,
        MAX_ARRIVAL_TIME,
        MIN_DURATION,
        MAX_DURATION,
        PROCESS_SIZE)

    simulate_paging(process_list, EXECUTION_TIME)

################################################################################
if __name__ == '__main__':
    main();
    sys.exit()
