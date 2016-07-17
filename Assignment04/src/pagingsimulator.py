'''
    file:
        pagingsimulator.py

    Description:
        Simulates Operating System paging algorithms.

    Authors:
        Francisco, Scot, Tyler, Daniel

    Course:     CS 149-01
    Instructor: Ezzat
    Group:      6

    Copyright (c) 2016
'''
# PYTHON LIBS
import sys
import random
import string
import time
import datetime
from collections import OrderedDict
try: from Queue import PriorityQueue
except: from queue import PriorityQueue

# USER LIBS
from constants import *
import algorithms
from process import Process
from memory import Page
from memory import PageTable

# Disable bytecode generation
sys.dont_write_bytecode = True

# Track loop iteration for printing 
main_count = 1

# Variables for average calculations
fifo_hits = 0
fifo_total_accesses = 0
fifo_total_processes = 0
lfu_hits = 0
lfu_total_accesses = 0
lfu_total_processes = 0
lru_hits = 0
lru_total_accesses = 0
lru_total_processes = 0
mfu_hits = 0
mfu_total_accesses = 0
mfu_total_processes = 0
rp_hits = 0
rp_total_accesses = 0
rp_total_processes = 0

def generate_processes(number_of_processes, max_arrival, min_duration, max_duration, process_size):
    '''
    generate_processes() creates 150 processes and randomly assigns them either 5, 11, 17, or 31
    pages respectively
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

def locality_of_reference_select(process):
    '''
    locality_of_reference() functions to decide which page of a process will be accessed
    next. Due to locality of reference, after referencing a page i, there is a 70% probability 
    that the next reference will be to page i, i-1, or i+1. This def handles that logic
    '''
    #get the number of pages belonging to this process
    num_of_pages = len(process.pages)
    #if the page hasnt been referenced yet
    if process.current_page == -1:
        current_page = random.randint(0, num_of_pages - 1)  #random index for this process's pages
    else:
        r = random.randint(0, num_of_pages - 1)
        if r <= num_of_pages * LOCATION_REFERENCE_PROBABILITY:
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

def access_page(process, clock, page_table, page):
    '''
    access_page() is called whenever a page is needed. if there are less than 4
    slots left in page_table.memory the page replacement algorithms are used.
    This function will also print stats everytime a page is accessed <time-stamp
    in seconds, process Name, page-referenced, if-Page-in-memory, which process/page
    number will be evicted if needed>
    '''
    global fifo_hits
    global fifo_total_accesses
    global lfu_hits
    global lfu_total_accesses
    global lru_hits
    global lru_total_accesses
    global mfu_hits
    global mfu_total_accesses
    global rp_hits
    global rp_total_accesses
    # update the time of access for that page
    page.last_accessed = clock
    # increase that page's frequency
    page.frequency += 1
    # add the page to the page_table.memory
    page_table.touch(page)

    ##################################################################
    #######  PAGE REPLACEMENT EVENT - Use Page Replacement Algorithms
    ##################################################################
    evicted_page = None
    page_process = None
    page_in_memory = "In Memory"
    # if there are less than 4 slots left in page_table.memory, replace a page using an algo
    if len(page_table.memory) > MAX_MEMORY_USED:
        print('##################################################################')
        print('##################################################################')
        print('#### HOLD UP: LEN(PAGE_TABLE.MEMORY) SHOULD 98 RIGHT NOW #########')
        print('#### LEN(PAGE_TABLE.MEMORY):  ' + str(len(page_table.memory)) + ' #################################')

        if main_count <= 5:
            evicted_page = algorithms.first_in_first_out(page_table)
        elif main_count > 5 and main_count <= 10:
            evicted_page = algorithms.least_frequently_used(page_table)
        elif main_count > 10 and main_count <= 15:
            evicted_page = algorithms.least_recently_used(page_table)
        elif main_count > 15 and main_count <= 20:
            evicted_page = algorithms.most_frequently_used(page_table)
        else:
            evicted_page = algorithms.pick(page_table)

    #determine if a page was evicted on this reference
    if evicted_page is not None:
        page_in_memory = "Not In Memory"
        page_process = page.process_id

    #Calculate Total accesses and hits for each algorithms
    if main_count <= 5:
        fifo_total_accesses += 1
        if evicted_page is None:
            fifo_hits += 1
    elif 5 < main_count <= 10:
        lfu_total_accesses += 1
        if evicted_page is None:
            lfu_hits += 1
    elif 10 < main_count <= 15:
        lru_total_accesses += 1
        if evicted_page is None:
            lru_hits += 1
    elif 15 < main_count <= 20:
        mfu_total_accesses += 1
        if evicted_page is None:
            mfu_hits += 1
    else:
        rp_total_accesses += 1
        if evicted_page is None:
            rp_hits += 1

    # Only print stats and memory map for 1 run of each algorithm
    run = [1, 6, 11, 16, 21]
    if main_count in run:
        print('Time Stamp: ', clock/1000, '  Process Name: ', process.name, '  Page Referenced: ', page.name, '  Page: ', page_in_memory, '  Evicted Page: ', page_process, ':', evicted_page)
        # print memory map at this time
        page_table.print_memory_map()
        page_table.print_disk()

def main():
    '''
    This is the main() function and entry point for the Paging Simulator application
    '''
    global main_count
    global fifo_total_processes
    global lfu_total_processes
    global lru_total_processes
    global mfu_total_processes
    global rp_total_processes
    #BEGINNING OF MAIN LOOP
    while main_count <= 25:
        # Makes the processes, populate them with pages
        active_process_list = OrderedDict()
        page_table = PageTable()
        process_list = generate_processes(
            NUMBER_OF_PROCESSES,
            MAX_ARRIVAL_TIME,
            MIN_DURATION,
            MAX_DURATION,
            PROCESS_SIZE)

        # Title for each algorithm that will be printed
        hash_border = 20*'#'
        if main_count == 1:
            print('%s FIRST IN FIRST OUT %s' % (hash_border, hash_border))
        elif main_count == 6:
            print('%s LEAST FREQUENTLY USED %s' % (hash_border, hash_border))
        elif main_count == 11:
            print('%s LEAST RECENTLY USED %s' % (hash_border, hash_border))
        elif main_count == 16:
            print('%s MOST FREQUENTLY USED %s' % (hash_border, hash_border))
        elif main_count == 21:
            print('%s RANDOM PICK %s' % (hash_border, hash_border))
        # BEGINNING OF MASTER CLOCK LOOP
        clock = 0
        # for 60000 cycles
        for x in range(EXECUTION_TIME):
            # check if the process_list is empty; if it has processes in there, then they have to be loaded into memory
            for p in process_list:
                # peek at the process_list, check if the next arrival_time == clock
                if p.arrival_time == clock:

                    # WHAT DOES THIS CODE DO? IF 1 OR 6 OR 11...?
                    run = [1, 6, 11, 16, 21]
                    if main_count in run:
                        print("######### New Process Arrival Event: ", p.name, " ############")

                    # If so, capture that process and pop it off the process_list
                    new_process = p
                    process_list.remove(p)
                    # Add to total_processes counts
                    if main_count <= 5:
                        fifo_total_processes += 1
                    elif main_count > 5 and main_count <= 10:
                        lfu_total_processes += 1
                    elif main_count > 10 and main_count <= 15:
                        lru_total_processes += 1
                    elif main_count > 15 and main_count <= 20:
                        mfu_total_processes += 1
                    else:
                        rp_total_processes += 1

                    # Add the new_process to the active_process_list
                    active_process_list[new_process.name] = new_process

                    # Decrement that process's duration
                    new_process.duration = new_process.duration - 1

                    ######################################################################################
                    #  PAGE REPLACE EVENT (1): ADDING PAGES OF A NEW PROCESS
                    #   Newly arrived processes will have all of their pages added into memory using the 
                    #   "touch" method. Any or all of the adds may require a page replacement.
                    ######################################################################################
                    # add all of that process's pages, one by one, into memory using touch

                    # NO!! YOU JUST TOUCH ALL THE PAGES, YOU DON'T NEED LOCALITY DURING THIS EVENT
                    # unless I am misunderstanding?
                    for page in new_process.pages:
                        # use locality of reference to determine next page to be accessed
                        #locality_page = locality_of_reference_select(new_process)
                        access_page(p, clock, page_table, page)


                    # if the process's duration is 0, remove all of its pages from memory
                    if new_process.duration <= 0:
                        if main_count == 1 or main_count == 6 or main_count == 11 or main_count == 16 or main_count == 21:
                            print("########### Process Exit Event: ", new_process.name, " #############")
                        new_process.exit_time = clock
                        new_process.clear(page_table)
            # end of for p in process_list: loop

            # increment the master clock counter
            clock += 1
            # check if the clock is at a 100ms interval and there are still processes in the list
            if (clock % 100 == 0) and active_process_list:
                ######################################################################################
                # PAGE REPLACE EVENT (2): TOUCHING A RANDOM PAGE OF RUNNING PROCESSES
                #   The assignment HW4 requires that at every 100ms, the OS selects a page from a process; 
                #   this process will try to access a single random page from its own page list in 
                #   process.pages. To fetch this page for the process, the OS will again call touch on 
                #   that page, resulting in another opportunity to replace a page.
                ######################################################################################
                #get the correct page using locality_of_reference
                #for key, active_process in active_process_list.items():
                for key in list(active_process_list.keys()):
                    active_process = active_process_list[key]
                    # decrement the duration counter for the current process
                    active_process.duration = active_process.duration - 1

                    if active_process.duration <= 0:
                        active_process.clear(page_table)
                        del active_process_list[active_process.name]
                    # use locality of reference to determine next page to be accessed
                    # THIS IS THE ONLY PLACE TO USE LOCALITY, ON TOUCHING A RANDOM PAGE OF ALL PROCESSES
                    locality_page = locality_of_reference_select(active_process)
                    access_page(p, clock, page_table, locality_page)
            # end for x in range(EXECUTION_TIME): loop
        main_count += 1
    # end while COUNT <= 5: loop

    #Make final calculations after all runs have completed
    ave_hit_fifo = fifo_hits / fifo_total_accesses
    ave_fifo_processes = fifo_total_processes / 5

    ave_hit_lfu = lfu_hits / lfu_total_accesses
    ave_lfu_processes = lfu_total_processes / 5

    ave_hit_lru = lru_hits / lru_total_accesses
    ave_lru_processes = lru_total_processes / 5

    ave_hit_mfu = mfu_hits / mfu_total_accesses
    ave_mfu_processes = mfu_total_processes / 5

    ave_hit_rp = rp_hits / rp_total_accesses
    ave_rp_processes = rp_total_processes / 5

    #Print Final Stats
    print ('--------------------------------------------------------------------------------------------')
    print ('Average Hit Ratios for each algorithm over 5 runs:')
    print ('    First In First Out: ', ave_hit_fifo)
    print ('    Least Frequently Used: ', ave_hit_lfu)
    print ('    Least Recently Used: ', ave_hit_lru)
    print ('    Most Frequently Used: ', ave_hit_mfu)
    print ('    Random Pick: ', ave_hit_rp)
    print ('Average number of processes swapped in for each algorithm over 5 runs:')
    print ('    First In First Out: ', ave_fifo_processes)
    print ('    Least Frequently Used: ', ave_lfu_processes)
    print ('    Least Recently Used: ', ave_lru_processes)
    print ('    Most Frequently Used: ', ave_mfu_processes)
    print ('    Random Pick: ', ave_rp_processes)

################################################################################
if __name__ == '__main__':
    main();
    sys.exit()
