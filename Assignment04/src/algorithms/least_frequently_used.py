import copy

def least_frequently_used(page_table):
    print("hi")
    eviction_page_name = "" #For holding name of evicted page
   # first_page = OrderedDict([])
   # first_page[page_table.keys()[0]] = page_table.values()[0] #Store first element of page_table for comparator
    lowest_freq_dict = OrderedDict([]) #Used to store all the lowest freq pages
    lowest_freq_value = min(page_table.memory.itervalues().frequency) #Store the current lowest frequency value

    #Check which page has least frequency and store them in lowest_freq_dict
    for key, value in page_table.memory.items(): #Loop through whole page_table
         if value.frequency == lowest_freq_value: #If page's frequency matches lowest value
            lowest_freq_dict.update({key : value}) #Store all lowest frequency pages into this dict


    oldest_last_accessed_value = min(lowest_freq_dict.itervalues().last_accessed) #Store the oldest time value out of the lowest_freq_dict

    #Now find the oldest last accessed page in lowest_freq_dict
    for key, value in lowest_freq_dict.items(): #Loop through whole lowest_freq_dict
        if value.last_accessed == oldest_last_accessed_value: #If last_accessed of low freq page matches oldest access
            eviction_index = key #Store the name of the oldest and lowest freq page

    page_table.memory[eviction_page_name].frequency = 0 #Reset the page's frequency count to 0 because it got evicted
    #page_table.disk[eviction_page_name] = page_table.memory[eviction_page_name] #Add that page to disk
    del page_table.memory[eviction_page_name] #Delete that page frm memory
    print("hi")
