#include<stdio.h>
#include<string.h>
#include<stdlib.h>
double largest(double a[] ,long long int n)
{
	double lar=a[0];
	for(int i=1;	i<n;	i++)
	{
		if(a[i]>lar)
			lar=a[i];
	}
	return lar;
}
double smallest(double a[] ,long long int n)
{
	double sma=a[0];
	for(int i=1;	i<n;	i++)
	{
		if(a[i]<sma)
			sma=a[i];
	}
	return sma;
}
void emptyScanner(FILE *fp)
{
	char s[10];
	for(int i=0;	i<12;	i++)
	{
		fscanf(fp,"%s",s);	
	}

}
void dirtyRead(FILE *fp)
{
	char s[12];
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
	fscanf(fp,"%s",s);
}
double * median(double data[],long long int n)
{
	double a[n];
	for(int i=0;	i<n;	i++)
		a[i]=data[i];
	for(int i=0;	i<n-1;	i++)
	{
		for(int j=i;	j<n;	j++)
		{
			if(a[i]>a[j])
			{
				int t=a[j];
				a[j]=a[i];
				a[i]=t;
			}
		}
	}
	double q2,q1,q3;
	static double q[3];
	long long int n1;
	if(n%2==0)
		q2=(a[(n/2)-1]+a[(n/2)+1-1])/2.0;
	else
		q2=a[((n+1)/2)-1];
	if(n%4==0)
	{
		q1=(a[(n/4)-1]+a[(n/4)+1-1])/2.0;
		q3=(a[(n/2)+(n/4)-1]+a[(n/2)+(n/4)+1-1])/2.0;
	}
	else if(n%2==0)
	{
		n1=n/2;
		q1=a[((n1+1)/2)-1];
		q3=a[(n1+((n1+1)/2))-1];
	}
	else if(n%4==1)
	{
		n1=(n+1)/2;
		q1=a[((n1+1)/2)-1];
		q3=a[((n/2)+(n1+1)/2)-1];
	}
	else
	{
		n1=(n+1)/4;
		q1=(a[n1-1]+a[n1+1-1])/2.0;
		q3=(a[(n/2)+n1-1]+a[(n/2)+n1+1-1])/2.0;
	}
	printf("\nq1 = %.2f\nq2 = %.2f\nq3 = %.2f\n",q1,q2,q3);
	q[0]=q1;
	q[1]=q2;
	q[2]=q3;
	return q;
}
double* outlier(double q[],double data[],long long int n)
{
	static double a[15000];
	double outL,outH;
	outL=q[0]-(q[2]-q[0])*1.5;
	outH=q[2]+(q[2]-q[0])*1.5;
	printf("outlier L = %.2f \noutlier H = %.2f\n",outL,outH);
	for(int i=0;	i<n;	i++)
	{
		if(data[i]<outL || data[i]>outH)
		{
			a[i]=q[1];
		}
		else
			a[i]=data[i];
	}
	return a;
}
void dataCleaning(double a[],long long int n,double median)
{
	for(int i=0;	i<n;	i++)
	{
		if(a[i]==0.00)
			a[i]=median;
	}
}
double* normalize(double data[],long long int n)
{
	static double a[15000];
	double lar=largest(data,n);
	double sma=smallest(data,n);
	double range=lar-sma;
	printf("\nlargest = %.2f \nsmallest = %.2f \nrange = %.2f\n\n",lar,sma,range);
	for(int i=0;	i<n;	i++)
	{
		a[i]=(data[i]-sma)/range;
	}
	return a;
}
void stock(int k)
{
	FILE *fp,*fw,*fd;
	char date[15000][11],s[11];
	char dataset[20];
	int i=0,count=0;
	char ch[3];
	double *q;
	int r;
	double open[15000],high[15000],low[15000],close[15000],volume[15000],openint[15000];
	double NORopen[15000],NORhigh[15000],NORlow[15000],NORclose[15000],NORvolume[15000],NORopenint[15000];
	double *Popen,*Phigh,*Plow,*Pclose,*Pvolume,*Popenint;
	char filename[20]="stock";
	sprintf(ch, "%d", k);
	strcat(filename,ch);
	strcat(filename,".txt");
	char normal[30]="normalisedStock";
	strcat(normal,ch);
	strcat(normal,".txt");
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("Invalid file name\n");
		return ;
	
	}
	fw=fopen(normal,"w");
		while(fscanf(fp,"%s",s)!=EOF)
		{
			strcpy(date[i],s);
			fscanf(fp,"%s",s);
			fscanf(fp,"%lf",&open[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%lf",&high[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%lf",&low[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%lf",&close[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%lf",&volume[i]);
			fscanf(fp,"%s",s);
			fscanf(fp,"%lf",&openint[i]);
			i++;
		}

	printf("\n\nAnalysis of Stock %d:\n",k);
	int n=i;
	printf("%d tuples found !\n",n);
	printf("####################################################################################");
	printf("\nAnalysis of 'open' field\n");
	printf("Medians and quartiles:");
	q=median(open,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Popen=outlier(q,open,n);
	printf("\nData cleaning and ");
	dataCleaning(Popen,n,q[1]);
	printf("Data normalization");
	Popen=normalize(Popen,n);
	for(int i=0;i<n;	i++)
	{
		NORopen[i]=Popen[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'high' field\n");
	printf("Medians and quartiles:");
	q=median(high,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Phigh=outlier(q,high,n);
	printf("\nData cleaning and ");
	dataCleaning(Phigh,n,q[1]);
	printf("Data normalization");
	Phigh=normalize(Phigh,n);
	for(int i=0;i<n;	i++)
	{
		NORhigh[i]=Phigh[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'low' field\n");
	printf("Medians and quartiles:");
	q=median(low,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Plow=outlier(q,low,n);
	printf("\nData cleaning and ");
	dataCleaning(Plow,n,q[1]);
	printf("Data normalization");
	Plow=normalize(Plow,n);
	for(int i=0;i<n;	i++)
	{
		NORlow[i]=Plow[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'close' field\n");
	printf("Medians and quartiles:");
	q=median(close,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Pclose=outlier(q,close,n);
	printf("\nData cleaning and ");
	dataCleaning(Pclose,n,q[1]);
	printf("Data normalization");
	Pclose=normalize(Pclose,n);
	for(int i=0;i<n;	i++)
	{
		NORclose[i]=Pclose[i];	
	}
	printf("####################################################################################");
	printf("\nAnalysis of 'volume' field\n");
	printf("Medians and quartiles:");
	q=median(volume,n);
	printf("\nOutlier detection and replacement of outlier data:\n");
	Pvolume=outlier(q,volume,n);
	printf("\nData cleaning and ");
	dataCleaning(Pvolume,n,q[1]);
	printf("Data normalization");
	Pvolume=normalize(Pvolume,n);
	for(int i=0;i<n;	i++)
	{
		NORvolume[i]=Pvolume[i];	
	}
	for(int i=0;i<n;	i++)
	{
		NORopenint[i]=openint[i];	
	}
	printf("####################################################################################\n");
	/*for(i=0;	i<n;	i++)
	{
		printf("%s %.2f %.2f %.2f %.2f %.2f %.2f",date[i],open[i],high[i],low[i],close[i],volume[i],openint[i]);
		printf("\n");
	}*/
	for(int i=0;	i<n;	i++)
	{
		fprintf(fw,"%s ",date[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f  ",NORopen[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f  ",NORhigh[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORlow[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORclose[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORvolume[i]);
		fprintf(fw,", ");
		fprintf(fw,"%.2f ",NORopenint[i]);
		fprintf(fw,"\n");
	}
}
void apron(int k)
{
	FILE *fd[k],*fp,*fa,*fc;
	int j=0,n,flg=0,f=0;
	float open,close;
	for(int i=0;	i<k;	i++)
	{
		char ch[3];
		sprintf(ch, "%d", i);
		char normal[30]="normalisedStock";
		strcat(normal,ch);
		strcat(normal,".txt");
		fd[i]=fopen(normal,"r");
	}
	char date[20000][12];
	char s[12];
	fp=fopen("date.txt","r");
	while(fscanf(fp,"%s ",date[j])!=EOF)
	{
		j++;
	}
	fclose(fp);
	n=j;
	fa=fopen("apron.csv","w");
	fc=fopen("linguistic.txt","w");
	int nnn=0;
	fprintf(fa,"0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20\n");
	//
	fprintf(fa, "%d,",nnn);
	for(int i=0;	i<n;	i++)
	{
		f=0;
		
		printf("\rProcessing %s    (Completed : %.2f %%)    ",date[i],((i+1)*100/(float)n));
		for(j=0;	j<k;	j++)
		{
			flg=0;
			while(fscanf(fd[j],"%s",s)!=EOF)
			{
				if(flg==1)
					goto out;
				if(strcmp(s,date[i])==0)
				{
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%f",&open);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%f",&close);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%s",s);
					fscanf(fd[j],"%s",s);
					if(open>close)
					{
						if(j==k-1)
							fprintf(fa,"D%d",j);
						else	
							fprintf(fa,"D%d,",j);
						fprintf(fc,"D%d ",j);
						//fprintf(fa,"NULL,");
						f=1;
					}
					else if(open<close)
					{
						//fprintf(fa,"NULL,");
						if(j==k-1)
							fprintf(fa,"R%d",j);
						else
							fprintf(fa,"R%d,",j);
						fprintf(fc,"R%d ",j);
						f=1;
					}
					else{
						//fprintf(fa,"NULL,");
						fprintf(fc,"N%d ",j);
						if(j==k-1)
							fprintf(fa,"NULL");
						else
							fprintf(fa,"NULL,");
						f=1;
					}

					flg=1;
				}
				else if(flg==0)
				{
					dirtyRead(fd[j]);
				}
			}
			if(flg==0)
				fprintf(fc,"  ");
			out:
			rewind(fd[j]);
		}
		fprintf(fc,"\n");
		 if(f==1){
			 fprintf(fa,"\n");
		 	 nnn++;
			 fprintf(fa, "%d,",nnn);
		 }
	}	
}
float main()
{
	int n;
	float sup;
	printf("Enter the number of stock dataset:\n");
	scanf("%d",&n);
	for(int k=0;	k<n;	k++)
		stock(k);
	apron(n);
	printf("\nDone\n");
	printf("Enter the support count (typically less than 5%% for stock data)\n:");
	scanf("%f",&sup);
	return sup;
}

