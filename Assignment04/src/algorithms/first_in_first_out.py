import sys
from process import Process

# Disable bytecode generation
sys.dont_write_bytecode = True

def first_in_first_out(page_table):
    '''
    A First In First Out page replacement algorithm

    Arguments:
        page_table (PageTable): A simulated MMU Page Table

    Returns:
        The name of an evicted page
    '''
    order_assigned_dict = dict()
    for page_name in page_table.memory:
        order_assigned_dict[page_table.memory[page_name].name] = page_table.memory[page_name].order_assigned

    # Evict the first page assigned in memory
    eviction_page_name = min(order_assigned_dict, key=order_assigned_dict.get)

    # Reset page frequency
    page_table.memory[eviction_page_name].frequency = 0

    # Get the actual evicted page
    eviction_page = page_table.memory[eviction_page_name]

    # Add page to disk
    page_table.disk[eviction_page_name] = eviction_page

    # Delete page from memory
    del page_table.memory[eviction_page_name]
    return eviction_page
