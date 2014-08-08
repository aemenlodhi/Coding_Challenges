import math
from collections import defaultdict

palindromesWithZero=({})
palindromesWithoutZero=({})

def isPalindrome(inputString):

	#print "In isPalindrome " + inputString
	
	if len(inputString)<=1:
		return True
	
	elif len(inputString)==2:
		if(inputString[0]==inputString[1]):
			return True
		else:
			return False
	else:		
		if(inputString[0]==inputString[-1] and isPalindrome(inputString[1:-1])):
			return True
		else:
			return False	

def genPalindromesOfDigits(numDigits,isZeroAllowedInBeginning):
	
	global palindromesWithZero, palindromesWithoutZero
	
	
	if isZeroAllowedInBeginning:
		if numDigits in palindromesWithZero:
			return palindromesWithZero[numDigits] 

	else:
		if numDigits in palindromesWithoutZero:
			return palindromesWithoutZero[numDigits]

	ourPalindromes=[]
	shorterPalindromes=[]	

	if(numDigits==0):
		return ourPalindromes
	
	elif(numDigits==1):
		if(isZeroAllowedInBeginning):
			ourPalindromes=[str(i) for i in range(0,10)]	
		else:		
			ourPalindromes=[str(i) for i in range(1,10)]

	elif(numDigits==2):
		if(isZeroAllowedInBeginning):
			ourPalindromes=[str(i)+str(i) for i in range(0,10)]
		else:
			ourPalindromes=[str(i)+str(i) for i in range(1,10)]

	else:
		shorterPalindromes=genPalindromesOfDigits(numDigits-2,True)
		for sps in shorterPalindromes:
			if(isZeroAllowedInBeginning):
				ourPalindromes.extend(str(i) + sps + str(i) for i in range(0,10))
			else:
				ourPalindromes.extend(str(i) + sps + str(i) for i in range(1,10))		
	
	if isZeroAllowedInBeginning:
		palindromesWithZero[numDigits]=ourPalindromes
	else:
		palindromesWithoutZero[numDigits]=ourPalindromes
	
	return ourPalindromes	

def processCase(min,max):

	numValidPalindromes=0
	
	#print "Min: " + str(min) + " Max: " + str(max)

	#print min, max

	#print type(min)
	#print type(max)	
	
	maxLimit=long(math.sqrt(max))+1
	minLimit=long(math.sqrt(min))-1
	#maxLimit=maxLimit//1
	#minLimit=minLimit//1	
	
	strMaxLimit=str(maxLimit)
	strMinLimit=str(minLimit)

	#print strMinLimit, strMaxLimit	

	numDigitsMax=len(strMaxLimit)
	numDigitsMin=len(strMinLimit)

	#print strMinLimit, strMaxLimit
	#print numDigitsMin, numDigitsMax

	
	palindromesToCheck=[]	

	for i in range(numDigitsMin,numDigitsMax+1):
		palindromesToCheck.extend(genPalindromesOfDigits(i,False))
	
	#print "Number of palindromes: " + str(len(palindromesToCheck))
	
	#for palin in palindromesToCheck:
	#	print palin


	for i in palindromesToCheck:
		num=long(i,10)

		sq=num**2

		#print num,
		#print sq		
		
		#print "Squared number: " + str(sq)
	
		if(sq>=min and sq<=max):
			
			#print str(sq) + " is within range"	
		
			strSq=str(sq)
			if(isPalindrome(strSq)):

				#print "And " + str(sq) + " is a palindrome" 
				numValidPalindromes+=1
			
	return numValidPalindromes
		

lineCounter=0
caseNumber=0

#fileName="C-small-practice.in"
fileName="C-large-practice-2.in"
#fileName="Fair_And_Square_Palindrome.txt"
f=open(fileName,'r')

for line in f:
	
	input=line.split()
	lineCounter+=1
	if lineCounter==1:
		numCases=input[0]
		#print numCases
	else:
		caseNumber+=1
		min=long(input[0])
		max=long(input[1])
		
		#print min, max

		print "Case #" + str(caseNumber) + ": " + str(processCase(min,max))
		#processCase(min,max)


#testRun=genPalindromeOfDigits(3,True)
#print testRun
