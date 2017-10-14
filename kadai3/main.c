#include "support.h"
#include <stdio.h>
int 
main(int argc, char *argv[])
{
    check_arg(argc, argv);
    input(argc, argv);
    
/*scheduling start*/
	int tasklist[total_task]; //check the tasks can be done, 1 is cant be done
	int checklist[total_task]; //check whether tasks are done, 1 is undone
	int doinglist[total_task];//check whether being done, 1 is un being
	int petime[total_pe][2]; //check the time of each task
	int i,j,k,l; //i and k is counter, j is end checker, l is task end checker
	for(i = 0;i<total_task;i++){
	    tasklist[i] = 1;
	    checklist[i] = 1;
	    doinglist[i]=1;
	}
	for(i = 0;i<total_pe;i++){
	    petime[i][0] = 0;
	    petime[i][1] = 0;
	}
    
    int maxtask = 1; //task current num with maximum time
    int minpe = 0; // pe current num with minimum time
    int min2pe = 0;// second smallest time pe
    int maxpe = 0;
    
    for(i = 0;i<total_task;i++){
        if(task[i].total_pre == 0) //update task list
	        tasklist[i] = 0;
	    if((tasklist[i]==0) && (checklist[i]==1)) //check undone to be done
	        checklist[i] = 0;
	}
	
	j = 1; //null
    while(j!=0){
        for(i = 0;i<total_pe;i++) //get min pe
            if(petime[i][0]<=petime[minpe][0])
                minpe = i;
        maxtask = 0;
        
        for(i = 0;i<total_pe;i++){
            if(petime[minpe][0]>=(petime[i][0]-task[pe[i].task_no[petime[i][1]]].cost)){
                for(k = 0;k<=petime[i][1];k++)
                    checklist[pe[i].task_no[k]]=0;
            }
        }
        
         for(i = 0;i<total_task;i++){
            if(tasklist[i]){
                l = 0;
                for(k = 0;k<task[i].total_pre;k++)
                     l += checklist[task[i].pre[k]];
              if(l == 0)
                tasklist[i] = 0;
            }
        
        }
        
                
        for(i = 0;i<total_task;i++)//get max task
            if(checklist[i]&&(tasklist[i]==0)&&doinglist[i])
                if(task[i].cost>=task[maxtask].cost)
                    maxtask = i;
        j = 0;
        if(maxtask==0){//for no more execution
        for(i = 0;i<total_pe;i++){
                if(petime[i][0]>petime[minpe][0]){
                    min2pe = i;
                }
        }
        for(i = 0;i<total_pe;i++){
                if((petime[i][0]>petime[minpe][0])&&(petime[i][0]<petime[min2pe][0])){
                    min2pe = i;
                }
        }
        for(i = 0;i<total_pe;i++){
            if(petime[i][0]==petime[min2pe][0])
                checklist[pe[min2pe].task_no[petime[min2pe][1]]] = 0;
        }
         printf("%d,%d,%d\n",minpe,maxtask,petime[min2pe][0] - petime[minpe][0]);
        pe[minpe].task_no[petime[minpe][1]]=maxtask;
        pe[minpe].task_cost[petime[minpe][1]]=petime[min2pe][0] - petime[minpe][0]; //using greedy algorithm to calculate      
        petime[minpe][0] = petime[min2pe][0];
        petime[minpe][1]=petime[minpe][1]+1;
        
        }
        else{//for normal situations
        doinglist[maxtask] = 0;   
        petime[minpe][0] = task[maxtask].cost + petime[minpe][0];
        pe[minpe].task_no[petime[minpe][1]]=maxtask;
        pe[minpe].task_cost[petime[minpe][1]]=task[maxtask].cost; //using greedy algorithm to calculate
        printf("%d,%d,%d\n",minpe,maxtask,task[maxtask].cost);
        petime[minpe][1]=petime[minpe][1]+1;
        }
           j = 0;
        
        for(i = 0;i<total_task;i++){        
            j+=checklist[i];

        }
    }
      for(i = 0;i<total_pe;i++) //get min pe
            if(petime[i][0]>=petime[maxpe][0])
                maxpe = i;
        
        total_cost = petime[maxpe][0];

/*scheduling end*/
    
    output(argv);
    
    return 0;
}
