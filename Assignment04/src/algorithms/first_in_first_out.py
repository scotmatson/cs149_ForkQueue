import sys
from process import Process

sys.dont_write_bytecode = True

def first_in_first_out(page_table):
    '''
    This file includes implementation of the first_in_first_out page replacement algorithm
    Solves CS149 Homework#4
    @author Tyler Jones
    '''
    print ('\n\nCALLING FIFO')
    #make a dict with keys as page name and values as page.order_assigned
    order_assigned_dict = dict() #Used to store all the pages order_assigned values
    for key in page_table.memory:
        order_assigned_dict[page_table.memory[key].name] = page_table.memory[key].order_assigned

    #for each process pick the first page assigned in memory to evict
    eviction_page_name = min(order_assigned_dict, key=order_assigned_dict.get)
    #Reset the page's frequency count to 0 because it got evicted
    page_table.memory[eviction_page_name].frequency = 0
    #Add the evicted page to disk
    page_table.disk[eviction_page_name] = page_table.memory[eviction_page_name]
    #Delete that page frm memory
    del page_table.memory[eviction_page_name]
    return eviction_page_name
