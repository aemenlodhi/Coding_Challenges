import sys

numRows=4
numColumns=4
gameBoard=[[x for x in range(numColumns)] for y in range(numRows)]

lineCounter=0
numCases=0
caseNumber=1
caseLineCounter=0

def checkArrays():
	global gameBoard
	
	for row in gameBoard:
		if(all(boxes=='X' for boxes in row )):
			return 'X'
		if(all(boxes=='O' for boxes in row )):
			return 'O'
	xCounter,oCounter=0,0
	for row in gameBoard:
		if(any(boxes=='T' for boxes in row )):
			xCounter,oCounter=0,0
			for b in row:	
				if(b=='X'):
					xCounter+=1
				elif(b=='O'):
					oCounter+=1
				else:
					pass
			if(xCounter==3):
				return 'X'
			elif(oCounter==3):
				return 'O'
		
	return 'I'

def checkColumns():
	global gameBoard

	for column in range(0,4):
		if(all(boxes[column]=='X' for boxes in gameBoard)):
			return 'X'
		if(all(boxes[column]=='O' for boxes in gameBoard)):
			return 'O'
	xCounter,yCounter=0,0
	for column in range(0,4):
		if(any(boxes[column]=='T' for boxes in gameBoard)):
			xCounter,oCounter=0,0
			for row in range(0,4):
				if(gameBoard[row][column]=='X'):
					xCounter+=1
				elif(gameBoard[row][column]=='O'):
					oCounter+=1		
				if(xCounter==3):
					return 'X'
				elif(oCounter==3):
					return 'O'
				else:
					pass
					#do nothing
	return 'I'

def checkDiagonals():
	global gameBoard
	diagonal=list()
	
	for x in range(0,4):
		diagonal.append(gameBoard[x][x])

	if(all(box=='X' for box in diagonal)):
		return 'X'
	
	if(all(box=='O' for box in diagonal)):	
		return 'O'

	if(any(box=='T' for box in diagonal)):
		xCounter,oCounter=0,0
		for elem in diagonal:
			if elem=='X':
				xCounter+=1
			if elem=='O':
				oCounter+=1
		
		if xCounter==3:
			return 'X'
		if oCounter==3:
			return 'O'

		
	del(diagonal[:])
	
	for x in range(0,4):
		diagonal.append(gameBoard[x][3-x])
	
	if(all(box=='X' for box in diagonal)):
		return 'X'
	
	if(all(box=='O' for box in diagonal)):	
		return 'O'

	if(any(box=='T' for box in diagonal)):
		xCounter,oCounter=0,0
		for elem in diagonal:
			if elem=='X':
				xCounter+=1
			if elem=='O':
				oCounter+=1
		
		if xCounter==3:
			return 'X'
		if oCounter==3:
			return 'O'

	return 'I'
		
	
		
def checkDraw():
	global gameBoard

	for row in gameBoard:
		#print "In DCheck: row: ",
		#print row
		if(any(box=='.' for box in row)):
			return 'G'
	return 'D'			

def processCase():
		
	gameStatus='I'
	
	gameStatus=checkArrays()
	if(gameStatus!='I'):
		#print "Processed rows and rows show status: " + str(gameStatus)
		return gameStatus
	
	gameStatus=checkColumns()
	if gameStatus!='I':
		#print "Processed columns and columns show status: " + str(gameStatus)
		return gameStatus

	gameStatus=checkDiagonals()
	if gameStatus!='I':
		#print "Processed diagonals and diagonals show status: " + str(gameStatus)
		return gameStatus

	gameStatus=checkDraw()
	if gameStatus=='D':
		#print "Processed draw status and the status is : D"
		return 'D'
		
	else:
		#print "The game is found to be incomplete"
		return 'G'


def printCase():
	
	for row in range(0,4):
		for column in range(0,4):
			print str(gameBoard[row][column]) + " ",
			if(column==3):
				print ""

	
fileName="A-large-practice.in"
#fileName=raw_input("Enter file name: ")
f=open(fileName,'r')

'''
for x in range(4):
	for y in range(4):
		print str(gameBoard[x][y]) + " ",
		if(y==3):
			print ""
'''

for line in f:
	
	input=line
	lineCounter+=1

	#print input
	#print input[0]	
		
	if lineCounter==1:
		numCases=line[0]
		continue

	if lineCounter>=2:	
		if(len(input)>0):
			#print "Input " + input
			caseLineCounter+=1
			if caseLineCounter<=4:
				for x in range(0,4):
					#print str(caseLineCounter-1) + " " + str(x) + " " + input[x]
					gameBoard[caseLineCounter-1][x]=input[x]
			
			else:
				#print "Case Number: " + str(caseNumber)
				#printCase()
				
				gameStatus=processCase()
				#'''
				if gameStatus=='X':
					print "Case #" + str(caseNumber) + ": X won"
				elif gameStatus=='O':
					print "Case #" + str(caseNumber) + ": O won"
				elif gameStatus=='D':
					print "Case #" + str(caseNumber) + ": Draw"
				else:
					print "Case #" + str(caseNumber) + ": Game has not completed" 	
				#'''
				caseLineCounter=0
				caseNumber+=1
				#sys.exit()






