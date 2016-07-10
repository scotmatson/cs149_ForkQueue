from Queue import PriorityQueue

pq = PriorityQueue()

pq.put((1, "king"))
pq.put((3, "jack"))
pq.put((2, "queeen"))

print pq.get()
print pq.get()