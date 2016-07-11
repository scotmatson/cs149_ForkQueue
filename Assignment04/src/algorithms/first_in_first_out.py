def first_in_first_out(workload, page_table, min_pages):
    '''
    Demonstrates the First-in-first-out algorithm
    for managing processes in an operating system
    '''
    # TEMP, Use this to prevent infinite loops
    test_counter = 0
    while not workload.empty() and test_counter < 3:
        test_counter += 1
        if page_table.available_pages() >= min_pages:
            page_table.touch(min_pages, workload.get())
