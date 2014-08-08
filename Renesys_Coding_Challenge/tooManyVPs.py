from sets import Set
from collections import defaultdict

vps=set([])
numEmployees=dict({})
ceo="1"
directEmployees=defaultdict(list)

def computeImportance(vp,boss):

        global numEmployees
        global directEmployees

        if(boss in directEmployees):
                numEmployees[vp]+=len(directEmployees[boss])
                for employees in directEmployees[boss]:
                        computeImportance(vp,employees)




#opening file
f=open("vp_ego.adjacency.txt",'r')

for line in f:
	bossEmployee=line.split()
#	print bossEmployee[0]	
	if bossEmployee[0] == ceo:
		vps.add(bossEmployee[1])
		numEmployees[bossEmployee[1]]=0
	else:
		directEmployees[bossEmployee[0]].append(bossEmployee[1])

for vp in vps:
	computeImportance(vp,vp)
	#print "VP " + repr(vp) + " has " + repr(numEmployees[vp]) + " employees"		

print "VP", "Number of Employees"	
for vp in sorted(numEmployees, key=numEmployees.get):
	print vp, numEmployees[vp]
