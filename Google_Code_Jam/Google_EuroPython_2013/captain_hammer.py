import math
from decimal import *

getcontext().prec=6
getcontext().rounding=ROUND_UP

fileName="B-small-practice.in"
#fileName="captain_hammer.txt"
f=open(fileName,'r')

lineCounter=0
numCases=0
caseNumber=0

def processCase(cn,v,d):
	
	vel=float(v)
	dist=float(d)
	
	val=(9.8*dist)/(vel**2)

	#print "v: " + str(v) + " d: " + str(d) + " Val: " + str(val)

	theta=(180/math.pi)*0.5*math.asin(min(1.0, ((9.8*dist)/(vel**2))))
	
	print "Case #" + str(caseNumber) + ": " + str(theta)
	

for line in f:
	
	input=line.split()
	lineCounter+=1

	if lineCounter==1:
		numCases=int(input[0])

	else:
		caseNumber+=1
		V,D=input[0],input[1]
		processCase(caseNumber,V,D)	
