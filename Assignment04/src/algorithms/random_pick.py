import sys
import random

sys.dont_write_bytecode = True

def random_pick(page_table):
    '''
    This file includes implementation of the random_pick page replacement algorithm
    Solves CS149 Homework#4
    @author Tyler Jones
    '''
    #pick a random page in memory to evict
    # changed this to random.sample instead random.choice
    page_list = list()
    for key in page_table.memory:
        page_list.append(key)
    eviction_page_name = random.choice(page_list)
    #Reset the page's frequency count to 0 because it got evicted
    page_table.memory[eviction_page_name].frequency = 0
    # Get the actual evicted page
    eviction_page = page_table.memory[eviction_page_name]
    # Add page to disk
    page_table.disk[eviction_page_name] = eviction_page
    # Delete page from memory
    del page_table.memory[eviction_page_name]
    return eviction_page
