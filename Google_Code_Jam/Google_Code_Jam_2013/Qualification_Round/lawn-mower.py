
numCases=0
lineCounter=0
caseLineCounter=0
caseNumber=1
N=0
M=0

lawn=[[]]

def processPattern():
	global N,M, lawn
	maxRow,maxColumn=100,100

	#print "N: "+str(N)+" M: "+str(M)

	if(N==1 or M==1):
		return True

	else:
	
		
		for n in range(N):
			maxRow=max(lawn[n])
			#print "Max of row "+str(n)+" is " + str(maxRow)
			#print str(maxRow)
			if(int(maxRow)>100):
				#print "Odd one"
				return False
			for m in range(M):
				if lawn[n][m]<maxRow:
					if lawn[n][m]<max([column[m] for column in lawn]):
						#print "Lawn["+str(n)+"]["+str(m)+"] is problematice"
						return False

		return True

def printCase():
	global N, M, lawn

	for n in range(N):
		for m in range(M):
			print str(lawn[n][m]) + " ",
			if(m==(M-1)):
				print ""
				


#fileName="LawnMower.txt"
#fileName="B-large-practice.in"
fileName=raw_input("Please enter file name: ")

if=open(fileName,'r')

for line in f:
	
	input=line.split()
	lineCounter+=1	

	if lineCounter==1:
		numCases=input[0]
		continue

	if lineCounter>=2:
		caseLineCounter+=1
		if caseLineCounter==1:
			N,M=int(input[0]),int(input[1])
			lawn=[[0 for m in range(M)] for n in range(N)]
			continue
		
		if caseLineCounter>1 and caseLineCounter<=(1+N):
			lawn[caseLineCounter-2]=input

		if caseLineCounter==(1+N):

			#print "Case #" + str(caseNumber)
			#printCase()
		        
			for n in range(N):
				lawn[n]=map(int,lawn[n])	
			
			if(processPattern()):
				print "Case #"+ str(caseNumber) + ": YES"
			else:
				print "Case #"+ str(caseNumber) + ": NO"
			
			caseNumber+=1
			caseLineCounter=0
								
