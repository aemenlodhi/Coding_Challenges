from copy import deepcopy

def getNumNeighbors(grid,m,n,i,j):

	numNeighbors=0
	
	if j>0 and grid[i][j-1]>0:
		numNeighbors+=1
	
	if j<(n-1) and grid[i][j+1]>0:
		numNeighbors+=1

	if i>0 and grid[i-1][j]>0:
		numNeighbors+=1

	if i<(m-1) and grid[i+1][j]>0:
		numNeighbors+=1

	return numNeighbors

def filterStates(grid,m,n):

	cell_modified=False

	while True:
		cell_modified=False	
		for i in range(m):
			for j in range(n):
				if grid[i][j]>0:  
					
					if grid[i][j]<12:
						grid[i][j]=0
						cell_modified=True
					
					elif 0==getNumNeighbors(grid,m,n,i,j):
						grid[i][j]=0
						cell_modified=True
		
					else:
						pass
					
		if cell_modified==False:
			break

	return grid

def simultaneousExchange(grid,m,n):

	fs=[[0 for j in range(n)] for i in range(m)]
	
	for i in range(m):
		for j in range(n):
			if(grid[i][j]>0):
				numNeighbors=getNumNeighbors(grid,m,n,i,j)
				#print "Num Neighbors of " + str(i) + " " + str(j) + " " + str(numNeighbors)
				khairat=12/numNeighbors
				#print "Khairat is " + str(khairat)
				

				if(j>0 and grid[i][j-1]>0):
					fs[i][j-1]+=khairat
				if(j<(n-1) and grid[i][j+1]):
					fs[i][j+1]+=khairat
				if(i>0 and grid[i-1][j]>0):
					fs[i-1][j]+=khairat
				if(i<(m-1) and grid[i+1][j]>0):
					fs[i+1][j]+=khairat
	for i in range(m):
		for j in range(n):
			if(grid[i][j]>0):
				grid[i][j]-=12

	#print "After distribution of khairat: ", grid
	#print "Khairat to recieve: ", fs	

	for i in range(m):
		for j in range(n):
			grid[i][j]+=fs[i][j]

	return grid



def processCase(grid,m,n,cNumber):

	#print "Case #" + str(cNumber) + ": "
	#print grid
	
	state_history=[]
	current_state=grid
	future_state=[]
	
	turns=0

	while True:

		#print "Processing current_state: ", current_state
		
		#print "History is: "
		#for history in state_history:
		#	print history

		if(current_state in state_history):
			numChildrenRemaining=0
	
			for i in range(m):
				for j in range(n):
					if current_state[i][j]!=0:
						numChildrenRemaining+=1
				
			print "Case #" + str(cNumber) + ": " + str(numChildrenRemaining) + " children will play forever"
			break
		
				
		current_state=filterStates(current_state,m,n)
		#print "State after filtration: ", current_state
	
		numNonZeroElements=0
		for i in range(m):
			if(all([j==0 for j in current_state[i]])):
				pass
			else:
				numNonZeroElements+=1

		if(numNonZeroElements==0):
			print "Case #" + str(cNumber) + ": " + str(turns) + " turns"
			break		
		
		state_history.append(deepcopy(current_state))
		current_state=simultaneousExchange(current_state,m,n)
	
		#print "After processing of simultaneous exchange the state is: ", current_state
	
		turns+=1


fileName="D-small-practice-2.in"
#fileName="Professor_normal_input.txt"
f=open(fileName,'r')

numCases=0
lineCounter=0
caseLineCounter=0
caseNumber=0
M=-1
N=-1
row=0

for line in f:
	
	input=line.split()
	lineCounter+=1

	#print "Input: " , input

	if lineCounter==1:
		numCases=input[0]

	else:
		if M==-1 and len(input)==1:
			M=int(input[0])
		
		elif N==-1 and len(input)==1:
			N=int(input[0])
			caseNumber+=1
			case=[[0 for j in range(N)] for i in range(M)]
			#print "Case: " + str(caseNumber) + " parameters M: " + str(M) + " N: " + str(N)
			#print case			

		else:
			if(row<M):
				input=[int(x) for x in input]
				case[row]=input

				#print "Data so far: "
				#print case			

				row+=1
				
				if(row==M):
					processCase(case,M,N,caseNumber)
					row,M,N=0,-1,-1
			
