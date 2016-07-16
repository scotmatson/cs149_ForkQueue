from collections import OrderedDict

def most_frequently_used(page_table):
    print ('\n\nCALLING MFU')
    eviction_page_name = "" #For holding name of evicted page
    highest_freq_dict = OrderedDict([]) #Used to store all the highest freq pages

    #Find the highest_freq_value of all the pages
    highest_freq_value = 0 #Set to 0 for algorithm
    for key in page_table.memory:
        if page_table.memory[key].frequency >= highest_freq_value:
            highest_freq_value = page_table.memory[key].frequency

    #print ("Highest frequency value: ", highest_freq_value) #Test code

    #Put all highest_freq_value pages into highest_freq_dict
    #If page's frequency matches highest value
    for key, value in page_table.memory.items():
        if page_table.memory[key].frequency == highest_freq_value:
            highest_freq_dict.update({key : value}) #Store all lowest frequency pages into highest_freq_dict

    oldest_last_accessed = 60000 #Max range of last_accessed

    #Find the oldest page in highest_freq_dict based on last_accessed time
    for key in highest_freq_dict:
        if highest_freq_dict[key].last_accessed < oldest_last_accessed:
            oldest_last_accessed = highest_freq_dict[key].last_accessed

    #print ("Oldest last accessed time: ", oldest_last_accessed) #Test code


    #Now find the oldest last accessed page in lowest_freq_dict
    for key, value in highest_freq_dict.items():
        if highest_freq_dict[key].last_accessed == oldest_last_accessed:
            eviction_page_name = key

    #print ("Eviction_page_name for most_frequently_used: ", eviction_page_name)

    page_table.memory[eviction_page_name].frequency = 0 #Reset the page's frequency count to 0 because it got evicted
    page_table.disk[eviction_page_name] = page_table.memory[eviction_page_name] #Add that page to disk
    del page_table.memory[eviction_page_name] #Delete that page from memory
    return eviction_page_name
