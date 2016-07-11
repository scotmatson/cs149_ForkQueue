# PYTHON LIBS
import sys
import random
import string
try: from Queue import PriorityQueue
except: from queue import PriorityQueue
from collections import OrderedDict
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


###    NOTE: HERE IS THE LOCALITY OF REFERENCE STUB
# def locality_of_reference_select(process):

    # get the index of process's last accessed page
    # last_accessed_page_index = process.last_page_accessed

    # Now select a page to be touched; really, this line of code is just generating the correct index of the page
    # to be selected.
    # Make a 70% chance that the page selected will be the page at the index "last_accessed_page_index - 1" or
    # "last_accessed_page_index + 1"
    # <line of code to select index here>

    # Now return the page at that index
    # <line of code to fetch and return the page at that index here>



# helper function; it "touches" a page
def access_page(clock, page_table, page):
    print ("in access_page")
    # update the time of access for that page
    page.last_accessed = clock

    # increase that page's frequency
    page.frequency += 1

    ############################
    #######  PAGE REPLACEMENT EVENT
    ############################

    # add the page to the page_table.memory
    page_table.touch(page)
    #newprocess = page_table.memory.pop(page.process_id)
    print "Touched page's process ID:", page.process_id
    # update the parent process of that page so that it knows which page was last accessed
    # this code will be necessary for locality of reference, which is yet to be coded
    # THIS CODE NEEDS TO BE TESTED

    # testProcess = page_table.memory.get(page.process_id)
    # print "testing inside access_page", testProcess.name
    # testIndex = testProcess.pages.index(page.name)
    # index_of_page = page_table.memory.get(page.process_id).pages.index(page.name)
    # page_table[page.name].last_accessed_page = index_of_page

    # if there are less than 4 slots left in page_table.memory, replace a page using an algo
    if page_table.memory.__sizeof__() < MEMORY_MIN:
        print ("page replacement")
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

def main():
    '''
    This is the main() function and entry point for the Paging Simulator.
    We are treating main() as an Operating System and named it accordingly so.
    '''
    print ("in main os")
    # Makes the processes, populate them with pages
    process_list = []
    active_process_list = OrderedDict()
    page_table = PageTable()

    # Make a set of 150 processes, add to process_list
    for x in range(NUMBER_OF_PROCESSES):
        name_int = 0
        name = "P" + str(name_int)
        arrival_time = random.randint(0, MAX_ARRIVAL_TIME)
        duration = random.randint(MIN_DURATION, MAX_DURATION)
        number_of_pages = random.choice(PROCESS_SIZE)
        pages = []

        process = Process(name, arrival_time, duration, pages, 0)

        for x in range(number_of_pages):
            page_name_num = random.randint(0, 1000)
            page_name_string = ''.join(random.sample(string.ascii_lowercase, 5))
            page_name = page_name_string + str(page_name_num)
            last_accessed = 0

            new_page = Page(page_name, process.name, last_accessed)
            process.pages.append(new_page)

        # Must test pages, new creation, this will break
        process_list.append(process)
        name_int += 1



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
    #   NOTE: right now, the os() code is just selecting a random page from a random process. Someone needs to
    #   implement the locality of reference thing, which means that the random page that is selected is not entirely
    #   random; there is a 70% chance that the page selected from the random process will be one to the left or
    #   one to the right of the page that was last accessed from that process. That's what the i - 1 and i + 1 means
    #   in the assignment. I put a tag where I think this code needs to be implemented down below.
    ##################################################################################################################
    ##################################################################################################################


    # BEGINNING OF MASTER LOOP
    clock = 0
    # for 60000 cycles
    for x in range(EXECUTION_TIME):
        # check if the process_list is empty; if it has processes in there, then they have to be loaded into memory
        if process_list:
        # peek at the process_list, check if the next arrival_time == clock
            if process_list[0].arrival_time == clock:
                # if so, capture that process and pop it off the process_list
                new_process = process_list[0]
                process_list.pop(0)

                # add the new_process to the active_process_list
                active_process_list[new_process.name] = new_process

                # decrement that process's duration
                new_process.duration = new_process.duration - 1

                ######################################################################################
                #  PAGE REPLACE EVENT (1): ADDING PAGES OF A NEW PROCESS
                ######################################################################################

                # add all of that process's pages, one by one, into memory using touch
                for page in new_process.pages:
                    access_page(clock, page_table, page)

                # if the process's duration is 0, remove all of its pages from memory
                # this is a stub, still needs implementation
                if new_process.duration == 0:
                    new_process.clear(page_table)



        # increment the master clock counter
        clock += 1

        # check if the clock is at a 100ms interval
        if clock % 100 == 0 and active_process_list:

            # if so, then it's time to touch a random page of a random process in the active_process_list
            # choose a random process from the active process list
            # NOTE: This line of code does not need to be changed by the person is doing the locality of reference
            # thing!! This code just selects a random process
            random_process = random.choice(active_process_list.keys())

            # decrement the duration counter for that randomly selected process
            print "testing  ", active_process_list[random_process.name].name

            if active_process_list[random_process.name].duration == 0:
                new_process.clear(page_table)

            ######################################################################################
            # PAGE REPLACE EVENT (2): TOUCHING A RANDOM PAGE OF A RANDOM PROCESS
            ######################################################################################

                # NOTE: implement the 70% shit here!!
                # the code that selects a random page from the random_process is inside the following function:
                #       random.choice(random_process.pages)
                # Instead of this code, there needs to be a function called locality_of_reference_select, or
                # special_page_select, whatever you want to call it. It will take in as a parameter a process and return
                # a page. Based on the process.last_page_accessed attribute, which tracks the index "i" of the last page
                # accessed, the function has a 70% chance to select "i-1" or "i+1" as the page to be "touched".
                #


            access_page(clock, page_table, random.choice(random_process.pages))









################################################################################
if __name__ == '__main__':
    main();
    sys.exit()
