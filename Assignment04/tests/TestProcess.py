# by Francisco


class Process:
    # def __init__(self, name, size, arrival, duration):
    #     self.name = name
    #     self.size = size
    #     self.arrival_time = arrival
    #     self.duration = duration
    #     self.pages = None

    def __init__(self, name, arrival_time, duration, pages):
        self.name = name
        self.arrival_time = arrival_time
        self.duration = duration
        self.pages = pages


    def __lt__(self, other):
        return self.arrival_time < other.arrival_time
