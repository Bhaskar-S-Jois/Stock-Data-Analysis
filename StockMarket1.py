from datetime import timedelta, date
import subprocess
import numpy as numpy
import pandas as pd
from apyori import apriori
from itertools import combinations 



def daterange(date1, date2):
    for n in range(int ((date2 - date1).days)+1):
        yield date1 + timedelta(n)
date1 = input("Enter from year")
date2 = input("Enter to year")
day1=int(date1)
day2=int(date2)
f=open("date.txt","w")
start_dt = date(day1, 1, 1)
end_dt = date(day2, 12, 31)
for dt in daterange(start_dt, end_dt):
    f.write(dt.strftime("%Y-%m-%d"))
    f.write("\n")
subprocess.call(["cc", "stockk.c"])
support_user=subprocess.call("./a.out")


df = pd.read_csv('apron.csv')

df = df.dropna(how = 'all')

#print(df.shape)
rows=df.shape[0]
records = []

for i in range(0,df.shape[0]):
	records.append([str(df.values[i,j]) for j in range(0,df.shape[1])])

D = []
for i in range(0,df.shape[1]/2):
	D.append('D'+str(i))
	D.append('R'+str(i))

#print("--------------------------------------------------")
#print("Details of stock market:")
#for i in range(0,len(records)):
	#print(i+1,": ",records[i])
print("--------------------------------------------------")

c = 2
n = len(D)
while(c<3):
	comb = combinations(D,c)
	# print(list(comb))
	comb1 = []
	for each in list(comb):
	 comb1.append(list(each))
	# print(comb1)
	d = []
	for i in range(0,len(comb1)):
		d.append(0);

	#findin number of supCount
	for each in records:
		for each1 in comb1:
			flag = 1
			for each2 in each1:
				if(each2 not in each):
					flag = 0
			if(flag == 1):
				d[comb1.index(each1)] = d[comb1.index(each1)]+1
	#removing items with supcount less than 6
	for i in range(0,len(d)):
		support = ((d[i]*100)/float(rows))
		if(support<support_user):
			print(support)
			d[i]=0
			comb1[i]=[]
	# print(comb1)
	# print(d)
	while 0 in d:d.remove(0)
	while [] in comb1:comb1.remove([])
	if(c==2):
		if(len(d) >0):
			for i in range(0,len(d)):
				if(comb1[i][0][0]=='R' and comb1[i][1][0]=='R'):
					print("Profit of company "+comb1[i][0][1]+" and profit of company "+comb1[i][1][1]+" occur together" )
				elif(comb1[i][0][0]=='R' and comb1[i][1][0]=='D'):
					print("Profit of company "+comb1[i][0][1]+" and loss   of company "+comb1[i][1][1]+" occur together" )
				elif(comb1[i][0][0]=='D' and comb1[i][1][0]=='R'):
					print("Loss   of company "+comb1[i][0][1]+" and profit of company "+comb1[i][1][1]+" occur together" )
				elif(comb1[i][0][0]=='D' and comb1[i][1][0]=='D'):
					print("Loss   of company "+comb1[i][0][1]+" and loss   of company "+comb1[i][1][1]+" occur together" )
				
				
		else:
			print("no combinations of count ",c," has sup count greater than 2")
	
	else:
		if(len(d) >0):
			for i in range(0,len(d)):
				print(comb1[i],"   ",d[i])
		else:
			print("no combinations of count ",c," has sup count greater than 2")
	print(" ")
	D = []
	for each in comb1:
		for each1 in each:
			if(each1 not in D):
				D.append(each1)
	
	c=c+1

	n=len(D)

