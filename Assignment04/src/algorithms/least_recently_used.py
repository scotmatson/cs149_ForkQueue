import sys

sys.dont_write_bytecode = True

def least_recently_used(page_table):
    '''
    This file includes implementation of the least_recently_used page replacement algorithm
    Solves CS149 Homework#4
    @author Tyler Jones
    '''
    #make a dict with keys as page name and values as page.last_accessed
    last_accessed_dict = dict() #Used to store all the pages last_accessed values
    for key in page_table.memory:
        last_accessed_dict[page_table.memory[key].name] = page_table.memory[key].last_accessed

    #find the minimum last_accessed value which is least recently used.
    #  pick least recently used in memory to evict
    eviction_page_name = min(last_accessed_dict, key=last_accessed_dict.get)
    #Reset the page's frequency count to 0 because it got evicted
    page_table.memory[eviction_page_name].frequency = 0
    # Get the actual evicted page
    eviction_page = page_table.memory[eviction_page_name]
    # Add page to disk
    page_table.disk[eviction_page_name] = eviction_page
    # Delete page from memory
    del page_table.memory[eviction_page_name]
    return eviction_page
