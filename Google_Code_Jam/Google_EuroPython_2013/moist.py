
fileName="A-small-practice-1.in"
#fileName="moistInput.txt"
f=open(fileName,'r')

lineCounter=0
numCases=0
caseNumber=0
numCards=0
caseLineCounter=0

cardDeck=[]

def processCase(caseNumber):
	
	global cardDeck

	cost=0
	
	last_name=cardDeck[0]
	for name in cardDeck[1:]:
		if name<last_name:
			cost+=1
		else:
			last_name=name

	print "Case #" + str(caseNumber) + ": " + str(cost)			



for line in f:

	line=line.strip()

	lineCounter+=1
	if lineCounter==1:
		numCases=int(line[0])
	
	else:	
		if(line.isdigit()):
			caseNumber+=1
			numCards=int(line)
			#print "Case number: " + str(caseNumber) + " Num cards: " + str(numCards)
		else:
			cardDeck.append(line)
			if(len(cardDeck)==numCards):
				processCase(caseNumber)
				del(cardDeck[:])

