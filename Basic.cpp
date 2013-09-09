using namespace std;      
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#define NOEMP 10
#include<time.h>
int flag=1, pfl=1;
class emp
{    public:
	 int empid;
	 int plevel,j;
	 int arrtime;
	 int nop;
	 int completiontime;
	 int waitingtime;
	 public:
	 emp()
	 {
		 completiontime=0;
		 waitingtime=0;
	}
	 void display()
	 { 
	    if(flag)
	    {
	      cout<<"Employee ID\tPriorityLevel\tNo.ofPages\tArrival Time\tCompletion\tWaiting\n\n";
	      flag=0;
	    }
	    cout<<empid<<"\t\t";
	    cout<<plevel<<"\t\t";
	    cout<<nop<<"\t\t";
	    cout<<arrtime<<"\t\t";
	    cout<<completiontime<<"\t\t";
	    cout<<waitingtime<<"\t";
	    cout<<endl<<endl;
	   
	 }
	 int getplevel()
	 {
		 return plevel;
	 }
	 int getnop()
	 {
		 return nop;
	 }
	 int getarrtime()
	 {
		  return arrtime;
	 }		
};
class queue
{
	
	int front;
	static int i; 
	emp epq[NOEMP];
	int rear, q;
	public:
	class emp e[NOEMP];
	queue()//Constructor
		{
			front=-1;
			rear=-1;
		}
	 void setvalues(int m, int n)
	 {
		   for(q=0;q<NOEMP;q++)
		   
		   /*{
			    e[i].empid = i+1;
			    e[i].nop=(rand()%n)+1; //To generate random nos from L to U (rand()%U)+L
			    e[i].plevel=(rand()%4)+1;
			    e[i].arrtime=(rand()%m)+1;
			    e[i].display();
			    i++;
	       }*/
	       //To provide input manually
	       
	       for(q=0;q<NOEMP;q++)
		   {
			    e[i].empid=i+1;
			    cin>>e[i].nop; //To generate random nos from L to U (rand()%U)+L
			    cin>>e[i].plevel;
			    cin>>e[i].arrtime;
			    i++;
		   }	   
	  }
    //PROCESSING OF PRINT REQUESTS
	void process()
    {
        int j=0;
	    for (j=0 ; j< NOEMP ;j++ )
	    {
		  add (e[j]) ;
	    }
     }
     //Add item to priority queue
     void add (emp dt)
     {
	   emp temp ;
	   int k, j ;
       if (rear == NOEMP - 1 )
	   {
		 printf ( "\nQueue is full." ) ;
		 return ;
	   }
       rear++ ;
	   epq[rear] = dt ;
	   if (front == -1 )
		   front = 0 ;
		//sort by arrivaltime
       for (k =front ; k<=rear ; k++ )
	   {
		 for ( j = k + 1 ; j <=rear ; j++ )
		  {
			  if (epq[k].getarrtime()>epq[j].getarrtime() )
			  {
				 temp = epq[k] ;
				 epq[k] = epq[j] ;
				 epq[j] = temp ;
			  }
		   }
	    } 
	    //sort by priority klevel
	    for (k =front;k<=rear;k++)
	    {
		   for (j=k+1;j<=rear;j++)
		    {
			   
				if (epq[k].getarrtime() == epq[j].getarrtime() )
				{
					if ( epq[k].getplevel()> epq[j].getplevel() )
					{
                      temp = epq[k] ;
				      epq[k] = epq[j] ;
				      epq[j] = temp ;
					}
				}
			}
		}
		//sort by nop
		for (k=front;k<=rear;k++)
	    {
		   for (j=k+1;j<=rear;j++)
		    {
			   if(epq[k].getarrtime()==epq[j].getarrtime())
				  if (epq[k].getplevel() == epq[j].getplevel() )
					if ( epq[k].getnop()> epq[j].getnop() )
					  {
                        temp = epq[k] ;
				        epq[k] = epq[j] ;
				        epq[j] = temp ;
					  }
				  
			}
		}
		
	  
 }
    void displaypq()
    {
		::flag=1;
		int j;
		for(j=0;j<NOEMP;j++)
		epq[j].display();
    }
    void calcctime()
    {
		int p=0, s, c,nf=1, cnt;
		//Assume every page takes 1 second to print
		while(p<NOEMP)
		{
		    cout<<"Iteration: "<<p<<endl;
			if(p==0)//first element
			{		
						epq[p].completiontime=epq[p].nop+epq[p].arrtime;
						//cout<<epq[p].completiontime;
						epq[p].waitingtime=0;
			}
		    s=p;//s=0
		    //cout<<"s: "<<s<<endl;
		    c=s;//c=0
		    cnt=0;
		    while(s<NOEMP&&(epq[s+1].arrtime<=epq[p].completiontime))
		       {
		       	      //cout<<"Tracking "<<s+1<<" time.\n";
		          	  if(cnt==0)//to avoid assigning nf more than once.
					  {
					      if(epq[s+1].arrtime==epq[p].completiontime)		//
		          	     {
		          	       nf=0;//sort from p itself 
		          	       cnt=1;
		          	     }
		          	  else 
					    {
					      nf=2;//sort from position directly succeeding p
					      cnt=1;
					    }
				      }
					  
					  s+=1;
		       }
		          if(nf==0)
		          rearrange(c,s);
		          else if(nf==2)
		          rearrange(c+1,s);
			if(p+1!=0&&(epq[p].completiontime<=epq[p+1].arrtime))//there is a gap between arrival time of job and copletion time of previous job 
			{
			 epq[p+1].completiontime=epq[p+1].arrtime+epq[p+1].nop;
			 epq[p+1].waitingtime=0;
		    }  
		    else
			{//job arrived while it is printing current job
			        if(p+1!=0)
			      	{
			      	epq[p+1].completiontime=epq[p].completiontime+epq[p+1].nop;
			      	epq[p+1].waitingtime=epq[p].completiontime-epq[p+1].arrtime;
			        }
		    }
		    cout<<epq[p+1].completiontime<<endl;  
		 p++;
		}
	}
	void rearrange(int c,int s)
    {
      int j,k, l; emp temp;
      //rearrange plvel
	  for(j=c;j<=s;j++)
	     for(k=j+1;k<=s;k++)
	      if(epq[j].getplevel()>epq[k].getplevel() )
			  {
				 temp = epq[j] ;
				 epq[j] = epq[k] ;
				 epq[k] = temp ;
			  }
		//rearrange no. of pages
	
		 for(j=c;j<=s;j++)
		 {
	          for(k=j+1;k<=s;k++)
		        if (epq[j].getplevel() == epq[k].getplevel() )
					if ( epq[j].getarrtime()> epq[k].getarrtime() )		
					  {
                        temp = epq[j] ;
				        epq[j] = epq[k];
				        epq[k] = temp ;
					  }
		}
		
		for(l=0;l<NOEMP;l++)
		epq[l].display();	
		cout<<endl;	
    }
    void avgtime()
    {
    	int sum1=0, sum2=0, sum3=0, sum4=0, n1=0, n2=0, n3=0, n4=0;
		for(int m=0; m<NOEMP;m++)
    	switch(epq[m].getplevel())
		{
			case 1: sum1+=epq[m].waitingtime;
			        n1+=1;
			        break;
			case 2: sum2+=epq[m].waitingtime;n2++;
			        break;
			case 3: sum3+=epq[m].waitingtime;n3++;
			        break;
			case 4: sum4+=epq[m].waitingtime;n4++;
			        break;
		}
        cout<<"Average waiting times of priority levels:\n";
        cout<<"Level 1: "<<(float)sum1/n1<<endl;
        cout<<"Level 2: "<<(float)sum2/n2<<endl;
        cout<<"Level 3: "<<(float)sum3/n3<<endl;
        cout<<"Level 4: "<<(float)sum4/n4<<endl;
    }
};
int queue::i;//defining static member i
int main()
{
  	  srand(time(NULL));
  	  int m, n;
  	  cout<<"\nEnter last time of arrival and no.of pages separated by a space:\n";
  	  cin>>m>>n;
  	  queue obj;
  	  obj.setvalues(m,n);
	  obj.process();
	  obj.displaypq();//Basic priority sort
	  obj.calcctime();
	  obj.displaypq();
	  obj.avgtime();
	  return 0;
}
