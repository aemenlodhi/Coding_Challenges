from sets import Set


def processCase(m1,m2,rIds,cNumber):

	'''
	print "Case number: " + str(cNumber)	
	print "Row 1: " + str(rIds[0])
	print "Matrix 1: ", str(m1)
	print "Row 2: " + str(rIds[1])
	print "Matrix 2: ", str(m2)
	'''
	set1=set(m1[int(rIds[0])-1])
	set2=set(m2[int(rIds[1])-1])
	
	#print set1, set2

	commonElements=set1 & set2

	if(len(commonElements)==0):
		print "Case #" + str(cNumber) + ": Volunteer cheated!"

	elif(len(commonElements)==1):
		x=list(commonElements)
		print "Case #" + str(cNumber) + ": " + str(x[0])
	
	else:
		print "Case #" + str(cNumber) + ": Bad magician!"
	

numCases=0
lineCounter=0
caseLineCounter=0
caseNumber=0
fileName="A-small-practice.in"
#fileName='Magic_trick_input.txt'
rowIds=[]
matrix1=[[0 for j in range(4)] for i in range(4)]
matrix2=[[0 for j in range(4)] for i in range(4)]

f=open(fileName,'r')

for line in f:
	
	input=line.split()
	lineCounter+=1

	#print "Input: ", input

	if lineCounter==1:
		numCases=input[0]

	else:
		caseLineCounter+=1
		
		if len(input)==1:
			rowIds.append(input[0])
			
		else:
			if len(rowIds)==1:
				for i in range(4):
					if(all([j==0 for j in matrix1[i]])):
						matrix1[i]=input
						break
			else:
				for i in range(4):
					if(all([j==0 for j in matrix2[i]])):
						matrix2[i]=input
						break
			
			if((caseLineCounter%10)==0):
				caseNumber+=1
				processCase(matrix1,matrix2,rowIds,caseNumber)
				matrix1=[[0 for j in range(4)] for i in range(4)]
				matrix2=[[0 for j in range(4)] for i in range(4)]
				del(rowIds[:])
				caseLineCounter=0			
