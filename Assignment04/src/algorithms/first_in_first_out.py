import logging

def first_in_first_out(workload, page_table, min_pages):
    '''
    Demonstrates the First-in-first-out algorithm
    for managing processes in an operating system
    '''
    logging.info('Inside FIFO')
    # TEMP, Use this to prevent infinite loops
    test_counter = 0
    while not workload.empty() and test_counter < 3:
        logging.info('workload.empty() == False')
        test_counter += 1
        if page_table.available_pages() >= min_pages:
            logging.info('There are available pages')
            print('Number of Available Pages: %d' % (page_table.available_pages()))
            page_table.touch(min_pages, workload.get())
            print('Number of Available Pages: %d' % (page_table.available_pages()))
