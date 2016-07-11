from collections import OrderedDict
import copy
d = OrderedDict([('first', 111),('second', 160), ('third', 20), ('fourth', 50 )] )
#print d.items()

#print d.popitem()

#print d.values()

#for k,v in d.items():
#    print k, v

#print len(d)
#print d.keys()[0]
#print d.values()[0]
d2 = OrderedDict([])
clone_page = copy.deepcopy(d)
#d2[d.keys()[0]] = d.values()[0]
print len(clone_page)
#print clone_page
min_val = min(d.itervalues())
print min_val
index = ""
for key, value in d.items():
    if value < clone_page.values()[0]:
        #d2.update({key:value})
        index = value

d['first'] = d['second']
#print d.items()
#print d2.items()
#d2.update({d.keys()[1]: d.values()[1]})
#print d2.items()
#index = d.keys()
print index
