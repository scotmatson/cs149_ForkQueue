try: from memory import page
except: pass

try: import page
except: pass


class PageTable(object):
    '''
    This class simulates the Page Table. The purpose of the Page Table is to make
    user level processes believe that all of their data is in memory, which may
    or may not be the case. Due to limitations on physical memory, some of the data
    may have to reside on disk and be brought back into memory when it is accessed,
    or "touched," by a process. Slots in physical memory are tracked using the
    RAM_tokenCounter.
    '''
    Disk = {}
    RAM_tokenCounter = 100

    def __init__(self, number_of_pages, page_size):
        '''
        Arguments:
            free_pages (int): The number of pages in the page list
        '''
        self.ram = dict()
        for i in range(number_of_pages):
            # TODO value of i should be a unique page_id
            p = page.Page(i, page_size)
            self.ram[i] = p

    def available_pages(self):
        '''
        Returns the number of free pages remaining in the
        page list as an int value. Empty pages are represented
        by None type.

        Returns:
            The number of available pages in the page list
        '''
        return sum(page.access() == None for page in self.ram.values())

    def get_free_pages(self, number_of_pages):
        '''
        Returns N number of free pages from the page table
        '''
        free_pages = {}
        for page_id, page in self.ram.items():
            if self.ram[page_id].access() == None and len(free_pages) < 4:
                free_pages[page_id] = page
                if len(free_pages) == 4:
                    return free_pages
        return None

    def touch(self, number_of_pages, process):
        '''
        Gets N free pages and assigns them to a process.
        '''
        free_pages = self.get_free_pages(number_of_pages)
        for page_id, free_page in free_pages.items():
            free_page.store(process)
