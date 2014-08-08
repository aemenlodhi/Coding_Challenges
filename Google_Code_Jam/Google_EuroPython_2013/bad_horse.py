from collections import defaultdict

fileName="C-small-practice-2.in"
#fileName="Bad_horse_input.txt"
f=open(fileName,'r')

numCases=0
numPairs=0
lineCounter=0
pairCounter=0
caseNumber=0

adjList=defaultdict(set)

def flipColor(c):
	
	if c=="BLUE":
		return "RED"
	else:
		return "BLUE"	


def processCase(cNumber):

	global adjList
	colors=dict({})	

	'''
	print "Case #" + str(cNumber) + ": " 
	for key in adjList:
		print key, adjList[key]
	'''
	
	graphTraversalQueue=[]
	
	for key in adjList:
		if(key not in graphTraversalQueue):
			graphTraversalQueue.append(key)
			col="BLUE"
			for node in graphTraversalQueue:
				if(node not in colors):
					colors[node]=col
				for neighbor in adjList[node]:
					if(neighbor not in graphTraversalQueue):
						graphTraversalQueue.append(neighbor)
						colors[neighbor]=flipColor(colors[node])
					else:
						if(colors[neighbor]==colors[node]):
							return False
	return True					


for line in f:
	
	input=line.split()
	lineCounter+=1

	if lineCounter==1:
		numCases=int(input[0])

	else:
		if(input[0].isdigit()):
			numPairs=int(input[0])
			caseNumber+=1

		else:
			pairCounter+=1
			adjList[input[0]].add(input[1])
			adjList[input[1]].add(input[0])
			if(pairCounter==numPairs):
				if(processCase(caseNumber)):
					print "Case #" + str(caseNumber) + ": Yes"
				else:
					print "Case #" + str(caseNumber) + ": No" 
				adjList.clear()
				numPairs=0
				pairCounter=0	
		
