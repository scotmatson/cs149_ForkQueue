from collections import OrderedDict
from operator import attrgetter

def least_frequently_used(page_table):
    eviction_page_name = "" #For holding name of evicted page
    lowest_freq_dict = OrderedDict([]) #Used to store all the lowest freq pages

    #Find the lowest_freq_value of all the pages
    lowest_freq_value = 100 #Arbitrary high number
    for key in page_table.memory:
        if page_table.memory[key].frequency <= lowest_freq_value:
            lowest_freq_value = page_table.memory[key].frequency

    print ("Lowest frequency value: ", lowest_freq_value) #Test code

    #Put all lowest_freq_value pages into lowest_freq_dict
    #if value.frequency == lowest_freq_value: #If page's frequency matches lowest value
    for key, value in page_table.memory.items():
        if page_table.memory[key].frequency == lowest_freq_value:
            lowest_freq_dict.update({key : value}) #Store all lowest frequency pages into this dict

    oldest_last_accessed = 60000 #Max range of last_accessed
   #Find the oldest page based on last_accessed time
    for key in lowest_freq_dict:
       if lowest_freq_dict[key].last_accessed < oldest_last_accessed:
           oldest_last_accessed = lowest_freq_dict[key].last_accessed

    print ("Oldest last accessed time: ", oldest_last_accessed) #Test code


    #Now find the oldest last accessed page in lowest_freq_dict
    for key, value in lowest_freq_dict.items():
        if lowest_freq_dict[key].last_accessed == oldest_last_accessed:
            eviction_page_name = key

    print ("Eviction_page_name: ", eviction_page_name)

    page_table.memory[eviction_page_name].frequency = 0 #Reset the page's frequency count to 0 because it got evicted
    page_table.disk[eviction_page_name] = page_table.memory[eviction_page_name] #Add that page to disk
    del page_table.memory[eviction_page_name] #Delete that page from memory
