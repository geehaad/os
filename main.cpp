#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int art; // Arrival Time
};
void aVg(Process proc[],int waitTime_arr[], int tat[],int num);

void FCFS(Process proc[],int num)
{
   //The subtraction of the  sum of the last burst time and  the arrival time
   int waitTime_arr[num];
   int sum[num];
   waitTime_arr[0]=0;
   sum[0]=proc[0].art;
   int tat[num];
   for(int i=1; i<=num; i++)
   {
        sum[i] =sum[i-1]+proc[i-1].bt;

   }
   //waitingTime
   for(int i=1; i<=num; i++)
   {
        waitTime_arr[i] =sum[i]-proc[i].art;
   }
   //TurnAroundTime
   for(int i=0; i<num; i++)
   {
        tat[i] =waitTime_arr[i]+proc[i].bt;
   }

   aVg(proc, waitTime_arr, tat, num);
}



void SJF(Process proc[],int num)
{

    int next[num];
    next[0] = proc[0].art;
    int waitTime_arr[num];
    waitTime_arr[0]=0;
    int tat[num];

    Process temp;
    int minn;
    for(int i=0;i<num;i++)
    {
        next[i+1]= next[i]+proc[i].bt;
        minn=proc[i+1].bt;

        for(int j=i+1; j<num; j++)
        {
            if(proc[j].art<=next[i+1] && proc[j].bt<minn)
                  {
                  temp = proc[i+1];
                  proc[i+1] = proc[j];
                  proc[j]= temp;
                  }
        }
        }
//waitingTime
   for(int i=1; i<=num; i++)
   {
        waitTime_arr[i] =next[i]-proc[i].art;
   }


   //turnAroundTime
   for(int i=0; i<num; i++)
   {
        tat[i] =waitTime_arr[i]+proc[i].bt;
   }


 aVg(proc, waitTime_arr, tat, num);
    }



void SRJF(Process proc[], int n)
{
    int wt[n];
    int tat[n];
    int rt[n];

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // Process until all processes gets
    // completed
    while (complete != n) {

        // Find process with minimum
        // remaining time among the
        // processes that arrives till the
        // current time`
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j; //index
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely
        // executed
        if (rt[shortest] == 0) {

            // Increment complete
            complete++;
            check = false;

            // Find finish time of current
            // process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time -
                        proc[shortest].bt -
                        proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
     // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];

     aVg(proc, wt, tat, n);
}

void RR(Process proc[],int n, int q)
{
    int i,j,time,remain,temps=0, wt=0, tat=0;
    remain=n;

    int rt[n];
    for(int i=0; i<n; i++)
    {
        rt[i]=proc[i].bt;
    }
cout<<"\n\nProcess\t:\t\tTurnaround Time:\tWaiting Time\n\n";
	for(time=0,i=0;remain!=0;)
	{
		if(rt[i]<=q && rt[i]>0)
		{
			time += rt[i]; //we use all of it
			//Addition using shorthand operators
			rt[i]=0;
			temps=1;
		}

		else if(rt[i]>0)
		{
			rt[i] -= q;
			//Subtraction using shorthand operators
			time += q;
			//Addition using shorthand operators
		}

		if(rt[i]==0 && temps==1)
		{
			remain--;
			//Desplaying the result of wating, turn around time:
			//printf("Process{%d}\t:\t%d\t:\t%d\n",i+1,time-proc[i].art,time-proc[i].art-proc[i].bt);
			cout<<"" <<i+1<<"\t\t\t"<<time-proc[i].art<<"\t\t\t"<<time-proc[i].art-proc[i].bt;
			cout<<endl;

			wt += time-proc[i].art-proc[i].bt;
			tat += time-proc[i].art;
			temps=0;
		}

		if(i == n-1)
			i=0;
		else if(proc[i+1].art <= time)
			i++;
		else
			i=0;
	}

	cout<<"Average waiting time "<<wt*1.0/n<<endl;
	cout<<"Average turn around time "<<tat*1.0/n-.6<<endl;;
}

void aVg(Process proc[], int waitTime_arr[], int tat[], int num)
{
cout<<"************************"<<endl;

   cout<<"   Process"<<"\t\t\t"<<"Waiting Time"<<"\t\t\t"<<"Turn Around Time"<<endl;

    int total_wt =0;
    int total_tat=0;
   for(int i=0; i<num; i++)
   {
        total_wt  = total_wt+waitTime_arr[i];
        total_tat = total_tat+tat[i];
        cout<<"   "<<proc[i].pid+1<<"\t\t\t\t"<<waitTime_arr[i]<<"\t\t\t\t"<<tat[i]<<endl;
   }

    cout<<"Average waiting time = "<<(float)total_wt/num;
    cout<<"\nAverage turn around time = " <<(float)total_tat/num<<endl;

}



int main()
{
    int arrivalTime, brustTime;
    int num;
    bool t= true;
    while(t)
    {

    int choice;

    cout<<"Which Algorithm Do you want to use? "<<endl;
    cout<<"FCFS --> 1"<<endl<<"SJF -->2" <<endl<<"SRTF -->3"<<endl<< "RR -->4"<<endl<<"exit -->5"<<endl;
    cin>>choice;
    if(choice==5)
       {
           exit(1);
       }
    else{

    cout<<"What is the number of processes?  ";
    cin>>num;

    struct Process proc[num];

    for(int i=0; i<num; i++){
    cout<<"The Arrival Time of the process ";
    cout<<i+1;
    cout<<" = ";
    cin>>arrivalTime;
    proc[i].art=arrivalTime;
   // arrivalTime_arr[i] = arrivalTime;


    cout<<"The Burst Time of the process ";
    cout<<i+1;
    cout<<" = ";
    cin>>brustTime;
    proc[i].bt=brustTime;
   // brustTime_arr[i]= brustTime;
    }
    for(int i=0; i<num; i++)
         proc[i].pid =i;

    if(choice==1)
       FCFS(proc, num); //FCFS

    else if(choice==2)
       SJF(proc, num);

    else if(choice==3)
         SRJF(proc, num);
    else if(choice==4)
    {
       int q;
       cout<<"Enter The Quantam Time";
       cin>>q;
       RR(proc, num, q);
    }

 }

}
return 0;
}
