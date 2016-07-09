import logging
import datetime
import sys
import random

def main():
    logging.info('Inside main()')

    # ENV initialization
    MAIN_MEMORY     = 100             # Units as MB 
    PAGE_SIZE       = 1               # Size as MB
    PROCESS_SIZE    = [5, 11, 17, 31] # Randomly chosen, Size as MB
    PROCESS_RUNTIME = [1, 2, 3, 4, 5] # Randomly chosen, Time as seconds



################################################################################
if __name__ == '__main__':
    # Logging Init
    current_time = datetime.datetime.strftime(datetime.datetime.now(), '%Y%m%d.%H%M%S')
    logging_file = 'logs/simulator_' + current_time + '.log'
    logging_format = '%(asctime)s %(message)s'
    logging.basicConfig(filename=logging_file, format=logging_format, level=logging.DEBUG)

    # Application entry point
    logging.info('Calling procedure main(), initiating paging simulation')
    main();
    # Application controlled termination
    logging.info('Application execution terminated successfully')
    sys.exit()
