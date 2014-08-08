
numCases=0
caseNumber=0

#fileName="Cookie_clicker_alpha.txt"
fileName="B-large-practice.in"
f=open(fileName,'r')

timeToGetFarms={}

def getTimeToGetFarms(n,C,F):
	
	global timeToGetFarms

	#print "Key: " + str(n)
	
	if(n<=0):
		return 0

	elif n in timeToGetFarms:
		return timeToGetFarms[n]
	
	else:
		timeToGetFarms[n]=(C/(2+(n-1)*F))+getTimeToGetFarms(n-1,C,F)
		return timeToGetFarms[n]
		

def getTimeWithFarms(n,C,F,X):

	return X/(2+n*F)+getTimeToGetFarms(n,C,F)


def processCase(cn,C,F,X):

	prevTime=X/2
	
	numFarms=1

	#print "Time with " + str(numFarms-1) + " farms is: " + str(prevTime)
	
	while True:
		
		newTime=getTimeWithFarms(numFarms,C,F,X)
				
		#print "Time with " + str(numFarms) + " farms is: " + str(newTime)
			
		if(newTime<prevTime):
			numFarms+=1
			prevTime=newTime

		else:
			print "Case #"+ str(cn) + ": " + str(round(prevTime,6))
			break
for line in f:

	input=line.split()
	
	if(len(input)==1):
		numCases=input[0]

	else:
		caseNumber+=1
		C,F,X=float(input[0]), float(input[1]), float(input[2])
		processCase(caseNumber,C,F,X)
		timeToGetFarms.clear()
		#break
