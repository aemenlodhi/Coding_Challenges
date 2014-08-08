from collections import defaultdict
import sys
from copy import deepcopy

sys.setrecursionlimit(1000000)

class state:
	def __init__(self,inputKeys,inputPossibleChests,inputVisitedChests):
		self.keys=inputKeys
		self.possibleChests=inputPossibleChests
		self.visitedChests=inputVisitedChests	

	def __eq__(self,other):
		if isinstance(other,self.__class__):
			x=deepcopy(self.possibleChests[1:])
			y=deepcopy(other.possibleChests[1:])
			x=set(x)
			y=set(y)
			return (self.possibleChests[0]==other.possibleChests[0] and x==y)
			#self.__dict__==other.__dict__
		else:
			return False

	def addKey(self,key):
		self.keys.append(key)

	def removeKey(self,key):
		self.keys.remove(key)

	def addPossibleChest(self,chest):
		if(chest not in self.possibleChests):
			self.possibleChests.append(chest)
	
	def removePossibleChest(self,chest):
		self.possibleChests.remove(chest)

	def sortPossibleChests(self):
		self.possibleChests.sort()

	def shufflePossibleChests(self):
		x=self.possibleChests.pop(0)
		self.possibleChests.append(x)

	def addVisitedChest(self,chest):
		self.visitedChests.append(chest)

	def removeVisitedChest(self,chest):
		self.removeVisitedChest(chest)

	def __str__(self):
		#print "Keys: ",
		#print self.keys
		print "Possible chests: ",
		print self.possibleChests
		#print "Visited chests: ",
		#print self.visitedChests
		return ""
	
	
visitedStates=list([])
recoveryStack=list([])

caseNumber=0
numChestsToOpen=0
numKeysToStartWith=0
keysToStartWith=list([])
keyForChest=dict({})
keyOpensChests=defaultdict(set)
keysInChest=defaultdict(list)

lineCounter=0
caseLineCounter=0
chestNumber=0

currentState=state([],[],[])
recoveredState=state([],[],[])
futureState=state([],[],[])
openedChests=[]


def printGlobalElements():
	print "Visited States: "
	for x in visitedStates:
		print x
	print "Recovery Stack: "
	for x in recoveryStack:
		print x

def markStateVisited(stateToMark):
	global visitedStates
	if(stateToMark not in visitedStates):
		visitedStates.append(deepcopy(stateToMark))

def pushOnRecoveryStack(stateToPush):
	global recoveryStack
	recoveryStack.insert(0,deepcopy(stateToPush))


def popFromRecoveryStack():
	global recoveryStack
	return recoveryStack.pop(0)

def recoverState():
	global recoveredState
	global recoveryStack
	global caseNumber
	if(len(recoveryStack)==0):
		return False
	else:
		recoveredState=popFromRecoveryStack()
		return True
		
def isStateVisitedPreviously(stateToCheck):
	global visitedStates
	if (stateToCheck in visitedStates):
		return True
	else:
		return False
			
def determinePossibleChests(keys):
	possibleChests=list([])
	
	for key in keys:
		possibleChests.extend(keyOpensChests[key])

	possibleChests=list(set(possibleChests))
	return possibleChests

def openChests():
	global currentState
	global keyForChest
	global openedChests	

	pc=deepcopy(currentState.possibleChests)
	del(openedChests[:])

	for x in pc:
		if keyForChest[x] in currentState.keys:
			currentState.keys.remove(keyForChest[x])
			currentState.possibleChests.remove(x)
			openedChests.append(x)

	return openedChests


	
iterationLimit=1000000
iterationCounter=0

def processCurrentState():
	
	global currentState
	global recoveredState
	global caseNumber
	global numChestsToOpen
	global chestKey
	global keysInChest	
	global iterationLimit
	global iterationCounter	
	global visitedStates
	global recoveryStack
	global openedChests
       	
	print ""
	print "Iteration Counter " + str(iterationCounter)	
	print "Current State: Possible Chests: ", 
	print currentState.possibleChests,
	print "Keys: ",
	print currentState.keys,
	print "Visited Chests: ",
	print currentState.visitedChests
	#print "Global elements "
	#printGlobalElements()
	#print ""
	#'''

	iterationCounter+=1
	if(iterationCounter==iterationLimit):
		print "Case# " + str(caseNumber) + " iteration limit exceeded",
		return	
	
	#print "Iteration Counter " + str(iterationCounter)	

	if(len(currentState.visitedChests)==int(numChestsToOpen)):
		print "Case# " + str(caseNumber) + ":",
		for x in currentState.visitedChests:
			print x,
		return

	elif(len(currentState.possibleChests)==0 or isStateVisitedPreviously(currentState)):
		if(recoverState()):
			recoveredState.shufflePossibleChests()
			
			print "Recovered state: Possible Chests: ",
			print recoveredState.possibleChests
			print "Keys: ",
        		print recoveredState.keys,
        		print "Visited Chests: ",
        		print recoveredState.visitedChests			


			currentState=deepcopy(recoveredState)
			processCurrentState()
		else:
			print "Case# " + str(caseNumber) + ": IMPOSSIBLE"
			return
	
	else:
		markStateVisited(currentState)
		pushOnRecoveryStack(currentState)	

		openedChests=openChests()
	        for x in openedChests:
			currentState.keys.extend(keysInChest[x])	
		currentState.visitedChests.extend(openedChests)

		#currentState.keys.remove(keyForChest[currentState.possibleChests[0]])		
		#currentState.keys.extend(keysInChest[currentState.possibleChests[0]])
		
		currentState.keys.sort()
		#currentState.visitedChests.append(currentState.possibleChests.pop(0))
		
		del currentState.possibleChests[:]
		if(len(currentState.keys)>0):
			currentState.possibleChests=determinePossibleChests(currentState.keys)
		
		if(len(currentState.visitedChests)>0):
			for vc in currentState.visitedChests:
				if(vc in currentState.possibleChests):
					currentState.possibleChests=filter(lambda a: a != vc, currentState.possibleChests)
	
		print "Future state: Possible Chests: ",
		print currentState.possibleChests,
		print "Keys: ",
        	print currentState.keys,
        	print "Visited Chests: ",
        	print currentState.visitedChests	
		
		processCurrentState()
		return


def processCase():

	global currentState	
	processCurrentState()

def initializeCase():

	global currentState
	global keysToStartWith
	global recoveryStack
	global visitedStates

	del recoveryStack[:]
	del visitedStates[:]
	
	del currentState.keys[:]
	del currentState.possibleChests[:]
	del currentState.visitedChests[:]

	currentState.keys=keysToStartWith
	currentState.keys.sort()

	if(len(currentState.keys)>0):
		currentState.possibleChests=determinePossibleChests(currentState.keys)
		


def resetCaseData():

	global caseLineCounter
	global keysToStartWith
	global keyForChest
	global keysInChest
	global keyOpensChests
	global chestNumber
	global iterationCounter

	caseLineCounter=1
        del keysToStartWith[:]
        keyForChest.clear()
        keysInChest.clear()
        keyOpensChests.clear()
        chestNumber=0
	iterationCounter=0
                       
#main reading of cases

#fileName=raw_input("Enter input file name: ")
fileName="D-small-practice.in"
#fileName="i.txt"
f=open(fileName,'r')

for line in f:
        lineCounter+=1
	input=line.split()

        if(lineCounter==1):
                numInputCases=input[0]
                caseLineCounter=1
                continue

        if(caseLineCounter==1):
                caseNumber+=1
		
		if(caseNumber>1):
			print ""

                caseLineCounter+=1
                numKeysToStartWith=input[0]
                numChestsToOpen=input[1]
		#print "Num Chests: " + str(numChestsToOpen)
		continue

        if(caseLineCounter==2):
                caseLineCounter+=1
                keysToStartWith=input[:]
                continue

        if(caseLineCounter>2):
                chestNumber+=1
                keyForChest[chestNumber]=input[0]
                keyOpensChests[input[0]].add(chestNumber)
                caseLineCounter+=1
                if(input[1]>0):
                        keysInChest[chestNumber]=input[2:]

                if(caseLineCounter==(int(numChestsToOpen,10)+3)):

			initializeCase()
			#print "Processing Case: " + str(caseNumber) 		
			processCase()
					
			#sys.exit()			
			resetCaseData()

