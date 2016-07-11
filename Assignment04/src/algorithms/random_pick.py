import random
'''
This file includes implementation of the random_pick page replacement algorithm
Solves CS149 Homework#4
@author Tyler Jones
'''
def random_pick(page_table):
    #pick a random page in memory to evict
    eviction_page_name = random.choice(page_table.memory.keys())
    print ("The eviction_page_name in random_pick = %s" % eviction_page_name)
    #Reset the page's frequency count to 0 because it got evicted
    page_table.memory[eviction_page_name].frequency = 0
    #Add the evicted page to disk
    page_table.disk[eviction_page_name] = page_table.memory[eviction_page_name]
    #Delete that page frm memory
    del page_table.memory[eviction_page_name]

