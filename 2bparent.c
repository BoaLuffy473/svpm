#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX 25
void quicksort(int qarr[],int,int);
int main(int argc, char *argv[])
{
FILE *fp;
int pid,status;
int merge[MAX],i,n,quick[MAX];
char *newargv[] = {NULL, "sort.txt", NULL };
char *newenviron[] = { NULL };
printf("Enter the total number of elements: ");
scanf("%d",&n);
printf("Enter the elements which to be sort: ");
for(i=0;i<n;i++)
{
scanf("%d",&merge[i]);
}
for(i=0;i<n;i++)
{
quick[i] = merge[i];
}
newargv[0] = argv[1];
pid=fork();
if(pid==0)
{
execve(argv[1],newargv,NULL);
wait(0);
}
else if(pid>0)
{
quicksort(quick,0,n-1);
printf("\nSorted elements by parent(Quick sort):");
fp=fopen("sort.txt", "w");
if (fp == NULL)
{
printf("Error: can't open file.\n");
return 1;
}
else
{
printf("File opened successfully.\n");
}
for(i=0;i<n;i++)
{
fprintf(fp," %d",quick[i]);
1}
fclose(fp);
wait(&status);
}
else
printf("\nError.\n");
return 0;
}
void quicksort(int x[10],int first,int last){
int pivot,j,temp,i;
if(first<last)
{
pivot=first;
i=first;
j=last;
while(i<j)
{
while(x[i]<=x[pivot]&&i<last)
i++;
while(x[j]>x[pivot])
j--;
if(i<j){
temp=x[i];
x[i]=x[j];
x[j]=temp;
}
}
temp=x[pivot];
x[pivot]=x[j];
x[j]=temp;
quicksort(x,first,j-1);
quicksort(x,j+1,last);
}
}
