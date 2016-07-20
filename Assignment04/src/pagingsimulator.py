# pagingsimulator.py
'''
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
fifo_hits = fifo_total_accesses = fifo_total_processes = 0
lfu_hits = lfu_total_accesses = lfu_total_processes = 0
lru_hits = lru_total_accesses = lru_total_processes = 0
mfu_hits = mfu_total_accesses = mfu_total_processes = 0
rp_hits = rp_total_accesses = rp_total_processes = 0

def generate_processes(number_of_processes, max_arrival, duration, process_size):
    '''
    Creates processes and randomly assigns them pages
    '''
    page_set = set([])
    page_name_index = 0
    out = list()
    process_name_index = 0

    # While loop to add page_names to set to avoid duplicates
    while len(page_set) < MAX_PAGES_NEEDED:
        page_name_num = random.randint(1000, 9999)
        page_name_string = ''.join(random.sample(string.ascii_lowercase, 4))
        page_name = page_name_string + str(page_name_num)
        page_set.add(page_name)

    # Create all of the processes
    for x in range(number_of_processes):
        name = "P" + str(process_name_index)
        arrival_time = random.randint(0, max_arrival)
        this_duration = random.choice(duration)
        number_of_pages = random.choice(process_size)
        process = Process(name, arrival_time, this_duration, 0)

        # Add pages to all of the processes
        for x in range(number_of_pages):
            last_accessed = 0
            this_page_name = page_set.pop()
            #double check to make sure all instances are definitely gone
            if this_page_name in page_set:
                page_set.remove(this_page_name)
            new_page = Page(this_page_name, process.name, last_accessed)
            new_page.order_assigned = page_name_index
            process.pages.append(new_page)
            page_name_index += 1

        out.append(process)
        process_name_index += 1
    return out

def locality_of_reference_select(process):
    '''
    Decides which page of a process will be accessed next.
    '''
    num_of_pages = len(process.pages)
    #if the page hasnt been referenced yet...
    if process.current_page == -1:
        current_page = random.randint(0, num_of_pages - 1)  #random index for page
    else:
        r = random.randint(0, num_of_pages - 1)
        if r <= num_of_pages * LOCATION_REFERENCE_PROBABILITY:
            delta = random.choice([-1, 0, 1])
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

        # If current_page + delta puts us past the last index
        if (process.current_page + delta) >= (num_of_pages - 1):
            current_page = (process.current_page + delta) % (num_of_pages - 1)
        else:
            current_page = process.current_page + delta

    process.current_page = current_page
    return process.pages[current_page]

def access_page(process, clock, page_table, page, new_page):
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
    
    # Touch this page now
    page_table.touch(page, clock)

    # Page replacement event, use page replacement algorithms
    evicted_page = None
    evicted_page_name = None
    evicted_page_process = None
    page_in_memory = "In Memory"
    # less than 4 slots left in page_table.memory, replace page using an algo
    if len(page_table.memory) > MAX_MEMORY_USED:
        if main_count <= 5:
            evicted_page = algorithms.first_in_first_out(page_table)
        elif 5 < main_count <= 10:
            evicted_page = algorithms.least_frequently_used(page_table)
        elif 10 < main_count <= 15:
            evicted_page = algorithms.least_recently_used(page_table)
        elif 15 < main_count <= 20:
            evicted_page = algorithms.most_frequently_used(page_table)
        else:
            evicted_page = algorithms.random_pick(page_table)

    # Determine if a page was evicted on this reference
    if evicted_page is not None:
        page_in_memory = "Not In Memory"
        evicted_page_process = evicted_page.process_id
        evicted_page_name = evicted_page.name

    # Calculate Total accesses and hits for each algorithms
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

    if not new_page:
        # update the time of access for that page
        page.last_accessed = clock
        # increase that page's frequency
        page.frequency += 1
        # Only print stats for 1 run of each algorithm
        run = [1, 6, 11, 16, 21]
        if main_count in run:
            dash_border = 45*'-'
            print('%s PAGE REFERENCE EVENT %s' % (dash_border, dash_border))
            print('Time Stamp:',clock/1000,'  Process Name:',process.name,
                '  Page Referenced:',page.name,'  Page:',page_in_memory,
                '  Evicted Page:',evicted_page_process,'::',evicted_page_name)

def main():
    '''
    Entry point for the Paging Simulator application
    '''
    global main_count
    global fifo_total_processes
    global lfu_total_processes
    global lru_total_processes
    global mfu_total_processes
    global rp_total_processes

    while main_count <= 25:
        active_process_list = OrderedDict()
        page_table = PageTable()
        # Generate all of the processes ahead of time
        process_list = generate_processes(
            NUMBER_OF_PROCESSES,
            MAX_ARRIVAL_TIME,
            DURATION,
            PROCESS_SIZE)
        outer_hash_boarder = 100*'#'
        hash_border = 40*'#'
        # Only print title at the begining of each algorithms run
        if main_count == 1:
            print('\n\n\n'+outer_hash_boarder)
            print('%s FIRST IN FIRST OUT %s' % (hash_border, hash_border))
            print(outer_hash_boarder)
        elif main_count == 6:
            print('\n\n\n'+outer_hash_boarder)
            print('\n\n\n%s LEAST FREQUENTLY USED %s' % (hash_border, hash_border))
            print(outer_hash_boarder)
        elif main_count == 11:
            print('\n\n\n'+outer_hash_boarder)
            print('\n\n\n%s LEAST RECENTLY USED %s' % (hash_border, hash_border))
            print(outer_hash_boarder)
        elif main_count == 16:
            print('\n\n\n'+outer_hash_boarder)
            print('\n\n\n%s MOST FREQUENTLY USED %s' % (hash_border, hash_border))
            print(outer_hash_boarder)
        elif main_count == 21:
            print('\n\n\n'+outer_hash_boarder)
            print('\n\n\n%s RANDOM PICK %s' % (hash_border, hash_border))
            print(outer_hash_boarder)

        clock = 0
        for x in range(EXECUTION_TIME):
            # iterate process list to get arrived processes
            for p in process_list:
                # get the process if the arrival_time == clock
                if p.arrival_time == clock:
                    # If so, capture that process and remove it from the process_list
                    new_process = p
                    process_list.remove(p)
                    # Add the new_process to the active_process_list
                    active_process_list[new_process.name] = new_process

                    # Only print stats for 1 run of each algorithm
                    run = [1, 6, 11, 16, 21]
                    if main_count in run:
                        dollar_border = 20*'$'
                        outer_dollar_border = 67*'$'
                        print('\n%s NEW PROCESS ARRIVAL EVENT %s' % (dollar_border, dollar_border))
                        print('Time Stamp:',clock/1000,'  Process Name:',new_process.name,'  Size:',
                            len(new_process.pages),'MB  Duration:',new_process.duration/1000)
                        print(outer_dollar_border)

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

                    # add all of that process's pages, one by one, into memory using access_page
                    for page in new_process.pages:
                        access_page(new_process, clock, page_table, page, True)

                    # Only print memory map for 1 run of each algorithm after pages have been accessed
                    run = [1, 6, 11, 16, 21]
                    if main_count in run:
                        # Print the memory map at this time
                        print(page_table.print_memory_map())
                # end of for p in process_list: loop

            # increment the master clock counter
            clock += 1
            # check if the clock is at a 100ms interval and there are still processes in the list
            if (clock % 100 == 0) and active_process_list:

                # access correct page of every active_process
                for key in list(active_process_list.keys()):
                    active_process = active_process_list[key]

                    # use locality of reference to determine next page to be accessed
                    locality_page = locality_of_reference_select(active_process)
                    access_page(active_process, clock, page_table, locality_page, False)
                    
                    # decrease the process's duration by 100ms for this run
                    active_process.duration = active_process.duration - 100

                    # if the process's duration is 0, remove all of its pages from memory
                    if active_process.duration <= 0:
                        active_process.exit_time = clock
                        # Only print stats and memory map for 1 run of each algorithm
                        run = [1, 6, 11, 16, 21]
                        if main_count in run:
                            x_border = 20*'X'
                            outer_x_border = 64*'X'
                            print('\n%s NEW PROCESS EXIT EVENT %s' % (x_border, x_border))
                            print('Time Stamp:',clock/1000,'  Process Name:',active_process.name,
                                '  Size:',len(active_process.pages),'MB  Duration: 0')
                            print(outer_x_border)
                            # Print the memory map at this time after process is removed
                            print(page_table.print_memory_map())
                        # Delete process data
                        active_process.clear(page_table)
                        del active_process_list[active_process.name]

            # end for x in range(EXECUTION_TIME): loop
        main_count += 1
    # end while COUNT <= 25: loop

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
    dash_border = 115*'-'
    print (dash_border)
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
