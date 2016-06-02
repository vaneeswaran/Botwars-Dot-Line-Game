#include <stdio.h>
#include<stdlib.h>
#define MAX_ROW 5
#define MAX_COL 5
#define INIT 0
#define SUCCESS 0
struct bot_data
{
	int top,left,bottom,right;
	int value;
	int line;
};
struct bot_data grid[25];
int data[MAX_ROW][MAX_COL];
int sq_line=0;
int war_flag=0;
int fut_flag=0;
int arr_r[25];
int arr_l[25];
int arr_b[25];
int arr_t[25];
r_x=0;
l_x=0;
b_x=0;
t_x=0;
int op=0;
void fill_data();
void asc();
int find_pos();
int get_data();
int gen_result(int m);
void ver_grid();
void find_best();
int find_best_fut(struct bot_data grid1[25]);
int pre_fut(int x);
int calc_op(struct bot_data temp[25],int x);
int smart(int x);
int smart_four(int x);
int smart_res(int *arr);
int cmp(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
void init()
{
	int i;
	for(i=0;i<25;i++)
	arr_t[i]=100;
	for(i=0;i<25;i++)
	arr_r[i]=100;
	for(i=0;i<25;i++)
	arr_l[i]=100;
	for(i=0;i<25;i++)
	arr_b[i]=100;
}
int main()
{
    int flag=INIT;
    int player=INIT;
    int stat_flag=-1;
    int m,i;
       	player=get_data();
		fill_data();
		m=find_pos();
		if(m==-2)
		return 0;
		stat_flag=gen_result(m);
		flag=stat_flag;
		
		while(flag!=-1)
   		{
   		 		for(i=m+1;i<25;i++)
		{
		if(grid[i].line==flag)
			{
			    stat_flag=gen_result(i);
			   if(stat_flag==-1)
			   {
			   flag=-1;
			   break;
			    }
			}
		}
		if(i==25)
		{
		    flag++;
		     m=-1;
		}
		if(flag>=3)
		{ 
		    find_best(grid);
   			flag=-1;
				}
		}
        return SUCCESS;
}
void find_best()
{
    struct bot_data grid_copy[25];
    struct bot_data grid_copy1[25];
    int i,j,m,min=1000,min_i=0,min_temp;       
 for(m=0;m<25;m++)//structure copy
 {
     grid_copy[m].top=grid[m].top;
     grid_copy[m].bottom=grid[m].bottom;
     grid_copy[m].left=grid[m].left;
     grid_copy[m].right=grid[m].right;
     grid_copy[m].line=grid[m].line;
     grid_copy[m].value=grid[m].value;
   
 }
    for(m=0;m<25;m++)//structure copy
 {
     grid_copy1[m].top=grid[m].top;
     grid_copy1[m].bottom=grid[m].bottom;
     grid_copy1[m].left=grid[m].left;
     grid_copy1[m].right=grid[m].right;
     grid_copy1[m].line=grid[m].line;
     grid_copy1[m].value=grid[m].value;
   
 }
   for(i=0;i<25;i++)
  {
       for(m=0;m<25;m++)//structure copy
        {
     grid_copy1[m].top=grid[m].top;
     grid_copy1[m].bottom=grid[m].bottom;
     grid_copy1[m].left=grid[m].left;
     grid_copy1[m].right=grid[m].right;
     grid_copy1[m].line=grid[m].line;
     grid_copy1[m].value=grid[m].value;
   
 }
    //if(grid_copy1[i].value<15)
  //  printf("%d\n",i);
      min_temp=calc_op(grid_copy1,i); 
      if(min_temp<=min)
      {
         min_i=i;
          min=min_temp;
      }
  }
       
        i=min_i/5;
		j=min_i%5;  
	//	printf("mid=%d min i=%d",min,min_i);
		if(grid_copy[min_i].top==0)
		printf("%d %d %d",i,j,0);
		else if(grid_copy[min_i].right==0)
		printf("%d %d 1",i,j);
		else if(grid_copy[min_i].bottom==0)
		printf("%d %d 2",i,j);
		else if(grid_copy[min_i].left==0)
		printf("%d %d 3",i,j);
      
}
int gen_result(int m)
{
		int i,j,n,temp;
		n=sq_line;
		i=m/5;
		j=m%5;
		war_flag=0;
		if(sq_line!=3)
		{
			
			if(grid[m].right==0)
			{
				grid[m].right=1;
				grid[m].value+=2;
				grid[m].line+=1;
				if(j!=4)
				{
				    grid[((i)*5)+j+1].left=1;
				    grid[((i)*5)+j+1].value+=8;
				    grid[((i)*5)+j+1].line+=1;
				}
				war_flag=0;
				temp=sq_line;
				find_pos();
				sq_line=temp;
				if(war_flag==1)
				{
				grid[m].right=0;
				grid[m].value-=2;
				grid[m].line-=1;
				if(j!=4)
				{
				    grid[((i)*5)+j+1].left=0;
				    grid[((i)*5)+j+1].value-=8;
				    grid[((i)*5)+j+1].line-=1;
				}
			}
				else
				{
					printf("%d %d %d",i,j,1);
					return -1;
					}
			}
			if(grid[m].bottom==0)
			{
				grid[m].bottom=1;
				grid[m].value+=4;
				grid[m].line+=1;
				if(i!=4)
				{
				    grid[((i+1)*5)+j].top=1;
				    grid[((i+1)*5)+j].value+=1;
				    grid[((i+1)*5)+j].line+=1;
				}
				war_flag=0;
				temp=sq_line;
				find_pos();
				sq_line=temp;
				if(war_flag==1)
				{
				grid[m].bottom=0;
				grid[m].value-=4;
				grid[m].line-=1;
				if(i!=4)
				{
				    grid[((i+1)*5)+j].top=0;
				    grid[((i+1)*5)+j].value-=1;
				    grid[((i+1)*5)+j].line-=1;
				}
				}
				else
				{
					printf("%d %d %d",i,j,2);
					return -1;
					
				}
			}
			if(grid[m].left==0)
			{
				grid[m].left=1;
				grid[m].value+=8;
				grid[m].line+=1;
				if(j!=0)
				{
				    grid[((i)*5)+j-1].right=1;
				    grid[((i)*5)+j-1].value+=2;
				    grid[((i)*5)+j-1].line+=1;
				}
				war_flag=0;
				temp=sq_line;
				find_pos();
				sq_line=temp;
				if(war_flag==1)
				{
				grid[m].left=0;
				grid[m].value-=8;
				grid[m].line-=1;
				if(j!=0)
				{
				    grid[((i)*5)+j-1].right=0;
				    grid[((i)*5)+j-1].value-=2;
				    grid[((i)*5)+j-1].line-=1;
				}
			
				}
				else
				{
					printf("%d %d %d",i,j,3);
					return -1;
					
				}
			}	
			if(grid[m].top==0)
			{
				grid[m].top=1;
				if(i!=0)
				{
				    grid[((i-1)*5)+j].bottom=1;
				    grid[((i-1)*5)+j].value+=4;
				    grid[((i-1)*5)+j].line+=1;
				}
				grid[m].value+=1;
				grid[m].line+=1;
				war_flag=0;
				temp=sq_line;
				find_pos();
				sq_line=temp;
				if(war_flag==1)
				{
				grid[m].top=0;
				grid[m].value-=1;
				grid[m].line-=1;
				if(i!=0)
				{
				    grid[((i-1)*5)+j].bottom=0;
				    grid[((i-1)*5)+j].value-=4;
				    grid[((i-1)*5)+j].line-=1;
				}
				}
				else
				{
					printf("%d %d %d",i,j,0);
				
					return -1;
				}
			}
		}
		else
		{
	    if(pre_fut(m)!=-1)
	    {
		if(grid[m].top==0)
		printf("%d %d %d",i,j,0);
		else if(grid[m].right==0)
		printf("%d %d 1",i,j);
		else if(grid[m].bottom==0)
		printf("%d %d 2",i,j);
		else if(grid[m].left==0)
		printf("%d %d 3",i,j);
	    }
	    //else
	    {
	    //    printf("Warning");
	    }
		return -1;
		}	
	return n;
}
int find_pos()
{
	int m=0;
	int i,j;
	for(m=0;m<25;m++)
	{
	i=m/5;
	j=m%5;
	if(i==0)
	{
	    if(grid[m].line==0)
	    {
	   printf("%d %d 0",i,j);
	    return -2;
	    }
	    
	}
	 else if(j==0)
	 {
	   if(grid[m].line==0)
	    {
	   printf("%d %d 3",i,j);
	    return -2;
	    } 
	    }
	     else if(j==4)
	 {
	   if(grid[m].line==0)
	    {
	   printf("%d %d 1",i,j);
	    return -2;
	    } 
	    }
	     else if(i==4)
	 {
	   if(grid[m].line==0)
	    {
	   printf("%d %d 2",i,j);
	    return -2;
	    } 
	    }
	
	}
	for(m=0;m<25;m++)
	{
		if(grid[m].line==3)
			{
				sq_line=3;
				war_flag=1;
				return m;
			}
	}
	for(m=0;m<25;m++)
	{
   
		if(grid[m].line==0)
		{	
			
			sq_line=0;
			return m;
		}
	}
	for(m=0;m<25;m++)
	{
		if(grid[m].line==1)
			{
				sq_line=1;
				return m;
			}
		
	}
	for(m=0;m<25;m++)
	{
		if(grid[m].line==2)
		{
			sq_line=2;
			return m;
		}
		
	}
		
	
}
int pre_fut(int x)
{
    struct bot_data grid_copy[25];
    int m,ni,nj;
    int count=0,my,ene;
     for(m=0;m<25;m++)//structure copy
    {
     grid_copy[m].top=grid[m].top;
     grid_copy[m].bottom=grid[m].bottom;
     grid_copy[m].left=grid[m].left;
     grid_copy[m].right=grid[m].right;
     grid_copy[m].line=grid[m].line;
     grid_copy[m].value=grid[m].value;
   
 }
 for(m=0;m<25;m++) //count
    {
     if(grid[m].value>=15)
     count++;
   
 }
 //printf("x=%d",x);
 my=calc_op(grid_copy,x);
 my+=1;
 ni=x/5;
                    nj=x%5;
                     if(grid_copy[x].top==0)
				      {
				         
				       grid_copy[x].top=1;
				       if(ni!=0)
				       {
				        grid_copy[((ni-1)*5)+nj].bottom=1;
				        grid_copy[((ni-1)*5)+nj].value+=4;
				        grid_copy[((ni-1)*5)+nj].line+=1;
				        }
				       grid_copy[x].line+=1;
				       grid_copy[x].value+=1;
			         }
				      else if(grid_copy[x].right==0)
				      { 
				       grid_copy[x].right=1;
				       if(nj!=4)
				       {
				        grid_copy[((ni)*5)+nj+1].left=1;
				        grid_copy[((ni)*5)+nj+1].value+=8;
				        grid_copy[((ni)*5)+nj+1].line+=1;
				        }
				        grid_copy[x].line+=1;
				       grid_copy[x].value+=2;
				       }
				      else if(grid_copy[x].bottom==0)
				      {
				        
				       grid_copy[x].bottom=1;
				       if(ni!=4)
				       {
				        grid_copy[((ni+1)*5)+nj].top=1;
				        grid_copy[((ni+1)*5)+nj].value+=1;
				        grid_copy[((ni+1)*5)+nj].line+=1;
				       } 
				       grid_copy[x].line+=1;
				       grid_copy[x].value+=4;
				         }
				      else if(grid_copy[x].left==0)
				      {
				        
				        grid_copy[x].left=1;
				        if(nj!=0)
				       {
				        grid_copy[((ni)*5)+nj-1].right=1;
				        grid_copy[((ni)*5)+nj-1].value+=2;
				        grid_copy[((ni)*5)+nj-1].line+=1;
				        }
				       
				       grid_copy[x].line+=1;
				       grid_copy[x].value+=8; 
				       }
				       for(m=0;m<25;m++)
				       {
				           ni=m/5;
                            nj=m%5;
				           if(grid_copy[m].line==3)
				           {
				               if(grid_copy[m].top==0)
				      {
				         
				       grid_copy[m].top=1;
				       if(ni!=0)
				       {
				        grid_copy[((ni-1)*5)+nj].bottom=1;
				        grid_copy[((ni-1)*5)+nj].value+=4;
				        grid_copy[((ni-1)*5)+nj].line+=1;
				        }
				       grid_copy[m].line+=1;
				       grid_copy[m].value+=1;
				       m=-1;
			         }
				      else if(grid_copy[m].right==0)
				      { 
				       grid_copy[m].right=1;
				       if(nj!=4)
				       {
				        grid_copy[((ni)*5)+nj+1].left=1;
				        grid_copy[((ni)*5)+nj+1].value+=8;
				        grid_copy[((ni)*5)+nj+1].line+=1;
				        }
				        grid_copy[m].line+=1;
				       grid_copy[m].value+=2;
				       m=-1;
				       }
				      else if(grid_copy[m].bottom==0)
				      {
				        
				       grid_copy[m].bottom=1;
				       if(ni!=4)
				       {
				        grid_copy[((ni+1)*5)+nj].top=1;
				        grid_copy[((ni+1)*5)+nj].value+=1;
				        grid_copy[((ni+1)*5)+nj].line+=1;
				       } 
				       grid_copy[m].line+=1;
				       grid_copy[m].value+=4;
				       m=-1;
				         }
				      else if(grid_copy[m].left==0)
				      {
				        
				        grid_copy[m].left=1;
				        if(nj!=0)
				       {
				        grid_copy[((ni)*5)+nj-1].right=1;
				        grid_copy[((ni)*5)+nj-1].value+=2;
				        grid_copy[((ni)*5)+nj-1].line+=1;
				        }
				       
				       grid_copy[m].line+=1;
				       grid_copy[m].value+=8; 
				       m=-1;
				       }
				               
				           }
				       }
				        ene=find_best_fut(grid_copy);
    //printf("my=%d ene=%d",my,ene);
        if(my==2 && ene>=2 && my+count!=25)
     {
        
         if(smart(x)==-2)//Subprogram print the data
         return -1;
         else 
         return -2;
     }
     else if(my==4 && ene>=4 && my+count!=25)
     {
       
       if(smart_four(x)==-2)//Subprogram print the data
         return -1;
         else 
         return -2;
         
     }
    return -2;
    }
int get_data()
{
	int i=INIT;
	int j=INIT;
	int pl=INIT;
	for(i=INIT;i<MAX_ROW;i++)
	{
		for(j=INIT;j<MAX_COL;j++)
	{
		scanf("%d",&data[i][j]);
	}
	
	}
	scanf("%d",&pl);
	return pl;
}
void fill_data()
{
	int i,j,grid_val,val,bin[4],m,rem;
	int count=0;
	for(i=0;i<MAX_ROW;i++)
	{
		for(j=0;j<MAX_COL;j++)
		{
			grid_val=(i*5)+j;
			grid[grid_val].value=data[i][j];
			val=data[i][j];
			count=0;
			for(m=0;m<4;m++)
			{
				bin[m]=val%2;
				val=val/2;
				if(bin[m]==1)
				count++;
			}
			grid[grid_val].left=bin[3];
			grid[grid_val].bottom=bin[2];
			grid[grid_val].right=bin[1];
			grid[grid_val].top=bin[0];
			grid[grid_val].line=count;
		}
	}
}
int calc_op(struct bot_data temp[25],int x)
{
 int t=100,r=101,b=102,l=103;
 int i,j,t1=0;
 struct bot_data temp_r[25];
 i=x/5;
 j=x%5; 
  int m,ni,nj;
 op=0;
 for(m=0;m<25;m++)//structure copy
 {
     temp_r[m].top=temp[m].top;
     temp_r[m].bottom=temp[m].bottom;
     temp_r[m].left=temp[m].left;
     temp_r[m].right=temp[m].right;
     temp_r[m].line=temp[m].line;
     temp_r[m].value=temp[m].value;
   
 }
//for(m=0;m<25;m++)
// printf("data[%d]=%d\n",m,temp_r[m].value);

 
 	if(temp[x].top==0)
	{
				op=0;
				temp[x].top=1;
				arr_t[op++]=x;
				if(i!=0)
				{
				    temp[((i-1)*5)+j].bottom=1;
				    temp[((i-1)*5)+j].value+=4;
				    temp[((i-1)*5)+j].line+=1;
				    
				}
				temp[x].value+=1;
				temp[x].line+=1;
				t=0;
				t1=0;
				for(m=0;m<25;m++)
				{
				    if(temp[m].value>=15)
				    t++;
				}
				for(m=0;m<25;m++)
				{
				  if(temp[m].line==3)  
				  {
				      ni=m/5;
				      nj=m%5;
				      arr_t[op++]=m;
				      if(temp[m].top==0)
				      {
				       temp[m].top=1;
				       if(ni!=0)
				       {
				        temp[((ni-1)*5)+nj].bottom=1;
				        temp[((ni-1)*5)+nj].value+=4;
				        temp[((ni-1)*5)+nj].line+=1;
				       }
				       temp[m].line+=1;
				       temp[m].value+=1;
				       m=-1;
				      }
				      else if(temp[m].right==0)
				      {
				       temp[m].right=1;
				       if(nj!=4)
				       {
				        temp[((ni)*5)+nj+1].left=1;
				        temp[((ni)*5)+nj+1].value+=8;
				        temp[((ni)*5)+nj+1].line+=1;
				        }
				       
				       temp[m].line+=1;
				       temp[m].value+=2;
				       m=-1;
				      }
				      else if(temp[m].bottom==0)
				      {
				       temp[m].bottom=1;
				       if(ni!=4)
				       {
				        temp[((ni+1)*5)+nj].top=1;
				        temp[((ni+1)*5)+nj].value+=1;
				        temp[((ni+1)*5)+nj].line+=1;
				       }
				       temp[m].line+=1;
				       temp[m].value+=4;
				      m=-1;
				      }
				      else if(temp[m].left==0)
				      {
				        temp[m].left=1;
				        if(nj!=0)
				       {
				        temp[((ni)*5)+nj-1].right=1;
				        temp[((ni)*5)+nj-1].value+=2;
				        temp[((ni)*5)+nj-1].line+=1;
				        }
				       temp[m].line+=1;
				       temp[m].value+=8;  
				      m=-1;
				      }
				  }
				}
				for(m=0;m<25;m++)
				{
				    if(temp[m].value>=15)
				    t1++;
				}
//	for(m=0;m<25;m++)
 //printf("data[%d]=%d line=%d\n",m,temp[m].value,temp[m].line);
 
//			printf("t=%d t1=%d\n",t,t1);
				t=t1-t;
			//arr_t[op]=-1;	
			}
 for(m=0;m<25;m++)//structure copy
 {
     temp[m].top=temp_r[m].top;
     temp[m].bottom=temp_r[m].bottom;
     temp[m].left=temp_r[m].left;
     temp[m].right=temp_r[m].right;
     temp[m].line=temp_r[m].line;
     temp[m].value=temp_r[m].value;
   
 }

	if(temp[x].right==0)
	{           op=0;
	            arr_r[op++]=x;
				temp[x].right=1;
				if(j!=4)
				{
				    temp[((i)*5)+j+1].left=1;
				    temp[((i)*5)+j+1].value+=8;
				    temp[((i)*5)+j+1].line+=1;
				}
				temp[x].value+=2;
				temp[x].line+=1;
				r=0;
				for(m=0;m<25;m++)
				{
				  //  printf("data[%d]=%d\n",m,temp[m].value);
				         if(temp[m].value>=15)
				     r++;
				    
				}
				for(m=0;m<25;m++)
				{
				  if(temp[m].line==3)  
				  {
				      arr_r[op++]=m;
				      ni=m/5;
				      nj=m%5;
				      //printf("m=%d value=%d ",m,temp[m].value);
				      if(temp[m].top==0)
				      {
				         
				       temp[m].top=1;
				       if(ni!=0)
				       {
				        temp[((ni-1)*5)+nj].bottom=1;
				        temp[((ni-1)*5)+nj].value+=4;
				        temp[((ni-1)*5)+nj].line+=1;
				        }
				       temp[m].line+=1;
				       temp[m].value+=1;
				       m=-1;
				      }
				      else if(temp[m].right==0)
				      { 
				       temp[m].right=1;
				       if(nj!=4)
				       {
				        temp[((ni)*5)+nj+1].left=1;
				        temp[((ni)*5)+nj+1].value+=8;
				        temp[((ni)*5)+nj+1].line+=1;
				        }
				        temp[m].line+=1;
				       temp[m].value+=2;
				       m=-1;
				      }
				      else if(temp[m].bottom==0)
				      {
				        
				       temp[m].bottom=1;
				       if(ni!=4)
				       {
				        temp[((ni+1)*5)+nj].top=1;
				        temp[((ni+1)*5)+nj].value+=1;
				        temp[((ni+1)*5)+nj].line+=1;
				       } 
				       temp[m].line+=1;
				       temp[m].value+=4;
				       m=-1;
				      }
				      else if(temp[m].left==0)
				      {
				        
				        temp[m].left=1;
				        if(nj!=0)
				       {
				        temp[((ni)*5)+nj-1].right=1;
				        temp[((ni)*5)+nj-1].value+=2;
				        temp[((ni)*5)+nj-1].line+=1;
				        }
				       
				       temp[m].line+=1;
				       temp[m].value+=8; 
				       m=-1;
				      }
				  }
				}
				for(m=0;m<25;m++)
				{
				    if(temp[m].value>=15)
				    t1++;
				}
			//	printf("r=%d,t=%d",r,t1);
				
				r=t1-r;
			//	arr_r[op]=-1;
			}
for(m=0;m<25;m++)//structure copy
 {
     temp[m].top=temp_r[m].top;
     temp[m].bottom=temp_r[m].bottom;
     temp[m].left=temp_r[m].left;
     temp[m].right=temp_r[m].right;
     temp[m].line=temp_r[m].line;
     temp[m].value=temp_r[m].value;
   
 }			
    if(temp[x].bottom==0)
	{
				op=0;
				arr_b[op++]=x;
				temp[x].bottom=1;
				if(i!=4)
				{
				    temp[((i+1)*5)+j].top=1;
				    temp[((i+1)*5)+j].value+=1;
				    temp[((i+1)*5)+j].line+=1;
				}
				temp[x].value+=4;
				temp[x].line+=1;
				b=0;
				t1=0;
				for(m=0;m<25;m++)
				{
				    if(temp[m].value>=15)
				    b++;
				}
				for(m=0;m<25;m++)
				{
				  if(temp[m].line==3)  
				  {arr_b[op++]=m;
				      ni=m/5;
				      nj=m%5;
				      if(temp[m].top==0)
				      {
				       temp[m].top=1;
				       if(ni!=0)
				       {
				        temp[((ni-1)*5)+nj].bottom=1;
				        temp[((ni-1)*5)+nj].value+=4;
				        temp[((ni-1)*5)+nj].line+=1;
				        }
				       temp[m].line+=1;
				       temp[m].value+=1;
				       m=-1;
				      }
				      else if(temp[m].right==0)
				      {
				       temp[m].right=1;
				       if(nj!=4)
				       {
				        temp[((ni)*5)+nj+1].left=1;
				        temp[((ni)*5)+nj+1].value+=8;
				        temp[((ni)*5)+nj+1].line+=1;
				        }
				       temp[m].line+=1;
				       temp[m].value+=2;
				       m=-1;
				      }
				      else if(temp[m].bottom==0)
				      {
				       temp[m].bottom=1;
				       if(ni!=4)
				       {
				        temp[((ni+1)*5)+nj].top=1;
				        temp[((ni+1)*5)+nj].value+=1;
				        temp[((ni+1)*5)+nj].line+=1;
				        }
				       temp[m].line+=1;
				       temp[m].value+=4;
				       m=-1;
				      }
				      else if(temp[m].left==0)
				      {
				        temp[m].left=1;
				        if(nj!=0)
				       {
				        temp[((ni)*5)+nj-1].right=1;
				        temp[((ni)*5)+nj-1].value+=2;
				        temp[((ni)*5)+nj-1].line+=1;
				       }
				       temp[m].line+=1;
				       temp[m].value+=8;
				       m=-1;
				      }
				  }
				}
				t1=0;
				for(m=0;m<25;m++)
				{
				    if(temp[m].value>=15)
				    t1++;
				}
				b=t1-b;
		//	arr_b[op]=-1;	
			}
for(m=0;m<25;m++)//structure copy
 {
     temp[m].top=temp_r[m].top;
     temp[m].bottom=temp_r[m].bottom;
     temp[m].left=temp_r[m].left;
     temp[m].right=temp_r[m].right;
     temp[m].line=temp_r[m].line;
     temp[m].value=temp_r[m].value;
   
 }	
	if(temp[x].left==0)
	{
				temp[x].left=1;
				op=0;
				arr_l[op++]=x;
				if(j!=0)
				{
				    temp[((i)*5)+j-1].right=1;
				    temp[((i)*5)+j-1].value+=2;
				    temp[((i)*5)+j-1].line+=1;
				}
				temp[x].value+=8;
				temp[x].line+=1;
				l=0;
				t1=0;
				for(m=0;m<25;m++)
				{
				    if(temp[m].value>=15)
				    l++;
				}
				for(m=0;m<25;m++)
				{
				  if(temp[m].line==3)  
				  { arr_l[op++]=m;
				      ni=m/5;
				      nj=m%5;
				      if(temp[m].top==0)
				      {
				       temp[m].top=1;
				       if(ni!=0)
				       {
				        temp[((ni-1)*5)+nj].bottom=1;
				        temp[((ni-1)*5)+nj].value+=4;
				        temp[((ni-1)*5)+nj].line+=1;
    				    }
				       temp[m].line+=1;
				       temp[m].value+=1;
				       m=-1;
				      }
				      else if(temp[m].right==0)
				      {
				       temp[m].right=1;
				       if(nj!=4)
				       {
				        temp[((ni)*5)+nj+1].left=1;
				        temp[((ni)*5)+nj+1].value+=8;
				        temp[((ni)*5)+nj+1].line+=1;
				       } 
				       temp[m].line+=1;
				       temp[m].value+=2;
				       m=-1;
				      }
				      else if(temp[m].bottom==0)
				      {
				       temp[m].bottom=1;
				       if(ni!=4)
				       {
				           //printf("entry");
				        temp[((ni+1)*5)+nj].top=1;
				        temp[((ni+1)*5)+nj].value+=1;
				        temp[((ni+1)*5)+nj].line+=1;
				       }
				       temp[m].line+=1;
				       temp[m].value+=4;
				      m=-1;
				      }
				      else if(temp[m].left==0)
				      {
				        temp[m].left=1;
				        if(nj!=0)
				       {
				        temp[((ni)*5)+nj-1].right=1;
				        temp[((ni)*5)+nj-1].value+=2;
				        temp[((ni)*5)+nj-1].line+=1;
				       }
				       temp[m].line+=1;
				       temp[m].value+=8;
				       m=-1;
				      }
				  }
				}
				for(m=0;m<25;m++)
				{
				    if(temp[m].value>=15)
				    t1++;
				}
			//	printf("FIRST=%d FINAL=%d",t1,l);
		//	for(m=0;m<25;m++)
         //    printf("data[%d]=%d line=%d\n",m,temp[m].value,temp[m].line);
				l=t1-l;
			//	arr_l[op]=-1;
			}			
r_x=0;
l_x=0;
b_x=0;
t_x=0;

 //printf("r=%d b=%d t=%d l=%d m=%d\n",r,b,t,l,x);
 if(t<=r && t<=b && t<=l)
 {t_x=1;
 return t;}
 else if(r<=b && r<=l)
 {r_x=1;
 return r;}
 else if(b<=l)
 {b_x=1;
 return b;}
 else 
 {l_x=1;
 return l;}
}
int find_best_fut(struct bot_data grid1[25])
{
    struct bot_data grid_copy[25];
    struct bot_data grid_copy1[25];
    int i,j,m,min=1000,min_i=0,min_temp;       
 for(m=0;m<25;m++)//structure copy
 {
     grid_copy[m].top=grid1[m].top;
     grid_copy[m].bottom=grid1[m].bottom;
     grid_copy[m].left=grid1[m].left;
     grid_copy[m].right=grid1[m].right;
     grid_copy[m].line=grid1[m].line;
     grid_copy[m].value=grid1[m].value;
   
 }
    for(m=0;m<25;m++)//structure copy
 {
     grid_copy1[m].top=grid1[m].top;
     grid_copy1[m].bottom=grid1[m].bottom;
     grid_copy1[m].left=grid1[m].left;
     grid_copy1[m].right=grid1[m].right;
     grid_copy1[m].line=grid1[m].line;
     grid_copy1[m].value=grid1[m].value;
   
 }
   for(i=0;i<25;i++)
  {
       for(m=0;m<25;m++)//structure copy
        {
     grid_copy1[m].top=grid1[m].top;
     grid_copy1[m].bottom=grid1[m].bottom;
     grid_copy1[m].left=grid1[m].left;
     grid_copy1[m].right=grid1[m].right;
     grid_copy1[m].line=grid1[m].line;
     grid_copy1[m].value=grid1[m].value;
   
 }
    //if(grid_copy1[i].value<15)
  //  printf("%d\n",i);
      min_temp=calc_op(grid_copy1,i); 
      if(min_temp<=min)
      {
         min_i=i;
          min=min_temp;
      }
  }
       return min;
    }
int smart(int x)
    {
      
      int i,j,m;
      i=x/5;
      j=x%5;
      if(grid[x].top==0)
      m=((i-1)*5)+(j);
      else if(grid[x].bottom==0)
      m=((i+1)*5)+(j);
      else if(grid[x].left==0)
      m=((i)*5)+(j-1);
      else if(grid[x].right==0)
      m=((i)*5)+(j+1);
      //printf("M value=%d",m);
      i=m/5;
      j=m%5;
   //   printf("i=%d j=%d ",i,j);
      if(i>=5 || i<0 || j>=5 || j<0)
      {
         // printf("Ennn");
      return -1;
      }
      if(m==x-1)
      {
          if(grid[m].top==0)
          printf("%d %d 0",i,j);
          else if(grid[m].left==0)
          printf("%d %d 3",i,j);
          else if(grid[m].bottom==0)
          printf("%d %d 2",i,j);
          return -2;
      }
      else if (m==x+1)
      {
          if(grid[m].top==0)
          printf("%d %d 0",i,j);
          else if(grid[m].right==0)
          printf("%d %d 1",i,j);
          else if(grid[m].bottom==0)
          printf("%d %d 2",i,j);
          return -2;
      }
      else if (m==x-5)
      {
          if(grid[m].top==0)
          printf("%d %d 0",i,j);
          else if(grid[m].left==0)
          printf("%d %d 3",i,j);
          else if(grid[m].right==0)
          printf("%d %d 1",i,j);
          return -2;
      }
      else if(m==x+5)
      {
           if(grid[m].right==0)
          printf("%d %d 1",i,j);
          else if(grid[m].left==0)
          printf("%d %d 3",i,j);
          else if(grid[m].bottom==0)
          printf("%d %d 2",i,j);
          return -2;
      }
     return -1;
    }
int smart_four(int x)//return -2 means program print something
{
struct bot_data grid_copy[25];
int m,i,mn;
   for(m=0;m<25;m++)//structure copy
    {
     grid_copy[m].top=grid[m].top;
     grid_copy[m].bottom=grid[m].bottom;
     grid_copy[m].left=grid[m].left;
     grid_copy[m].right=grid[m].right;
     grid_copy[m].line=grid[m].line;
     grid_copy[m].value=grid[m].value;
   
 } 
 init();
 calc_op(grid_copy,x);
 asc();
 if(r_x==1)
 { // printf("Right::");
   //  for(i=0;arr_r[i]!=-1;i++)
    // printf("%d ",arr_r[i]);
    if(arr_r[0]+5!=arr_r[2])
    return -1;
    else
    {  
        arr_r[3]=arr_r[1]+5;
        smart_res(arr_r);
        return -2;
    }
 }
 else if(l_x==1)
 {//printf("Left::");
    // for(i=0;arr_l[i]!=-1;i++)
    // printf("%d ",arr_l[i]);
     if(arr_l[0]+5!=arr_l[2])
    return -1;
    else
    {arr_l[3]=arr_l[1]+5;
        smart_res(arr_l);
        return -2;}
 }
  else if(b_x==1)
 {
    // for(i=0;i!=4;i++)
    // printf("%d ",arr_b[i]);
    if(arr_b[0]+5!=arr_b[2])
    return -1;
    else
    {   arr_b[3]=arr_b[1]+5;
        smart_res(arr_b);
        return -2;
    }
 }
  else if(t_x==1)
 {//printf("Top::");
    // for(i=0;arr_t[i]!=-1;i++)
    // printf("%d ",arr_t[i]);
    if(arr_t[0]+5!=arr_t[2])
    return -1;
    else
    {
        arr_t[3]=arr_t[1]+5;
        smart_res(arr_t);
        return -2;
    }
 }
}
void asc()
{
qsort(arr_l,25, sizeof(int), cmp);
qsort(arr_b,25, sizeof(int), cmp);
qsort(arr_t,25, sizeof(int), cmp);
qsort(arr_r,25, sizeof(int), cmp);

}
int smart_res(int *arr)
{

   int ni,i,j,s1=0,s2=0,m,count=0,cn=0,s;
    for(ni=0;ni<4;ni++)
     {
       if(grid[arr[ni]].line==2)
       {
           if(s1==0)
           s1=arr[ni];
           else if(s2==0)
           s2=arr[ni];
       }
   }
   //printf("S1=%d S2=%d\n",s1,s2);
   m=s1;
   i=m/5;
   j=m%5;
  // printf("%d %d",i,j);
   for(ni=0;ni<25;ni++)
  { 
      if(grid[ni].value>=15)
   count++;}
    if(grid[m].left==0)
	{
		  //	printf("Enter in");
		    	grid[m].left=1;
				grid[m].value+=8;
				grid[m].line+=1;
				if(j!=0)
				{
				    grid[((i)*5)+j-1].right=1;
				    grid[((i)*5)+j-1].value+=2;
				    grid[((i)*5)+j-1].line+=1;
				}
			for(ni=0;ni<25;ni++)
                 { 
                if(grid[ni].value>=15)
                  cn++;
                 }
                 s=cn-count;
                  cn=0;
			if(s!=0)
				{
				grid[m].left=0;
				grid[m].value-=8;
				grid[m].line-=1;
				if(j!=0)
				{
				    grid[((i)*5)+j-1].right=0;
				    grid[((i)*5)+j-1].value-=2;
				    grid[((i)*5)+j-1].line-=1;
				}
			
				}
			else
				{
					printf("%d %d %d",i,j,3);
				return -2;
				}
	}
  if(grid[m].top==0)
		{
				grid[m].top=1;
				if(i!=0)
				{
				    grid[((i-1)*5)+j].bottom=1;
				    grid[((i-1)*5)+j].value+=4;
				    grid[((i-1)*5)+j].line+=1;
				}
				grid[m].value+=1;
				grid[m].line+=1;
				for(ni=0;ni<25;ni++)
                 { 
                     if(grid[ni].value>=15)
                  cn++;}
                  s=cn-count;
                  cn=0;
				if(s!=0)
				{
				grid[m].top=0;
				grid[m].value-=1;
				grid[m].line-=1;
				if(i!=0)
				{
				    grid[((i-1)*5)+j].bottom=0;
				    grid[((i-1)*5)+j].value-=4;
				    grid[((i-1)*5)+j].line-=1;
				}
				}
				else
			{
					printf("%d %d %d",i,j,0);
				return -2;
				}
			} 
   if(grid[m].right==0)
	{
				grid[m].right=1;
				grid[m].value+=2;
				grid[m].line+=1;
				if(j!=4)
				{
				    grid[((i)*5)+j+1].left=1;
				    grid[((i)*5)+j+1].value+=8;
				    grid[((i)*5)+j+1].line+=1;
				}
				 for(ni=0;ni<25;ni++)
                 { if(grid[ni].value>=15)
                  cn++;}
                  s=cn-count;
				
				if(s!=0)
				{
				grid[m].right=0;
				grid[m].value-=2;
				grid[m].line-=1;
				if(j!=4)
				{
				    grid[((i)*5)+j+1].left=0;
				    grid[((i)*5)+j+1].value-=8;
				    grid[((i)*5)+j+1].line-=1;
				}
			}
				else
				{   
				    printf("%d %d %d",i,j,1);
					return -2;
					}
					cn=0;
			}
	if(grid[m].bottom==0)
		{
	grid[m].bottom=1;
				grid[m].value+=4;
				grid[m].line+=1;
				if(i!=4)
				{
				    grid[((i+1)*5)+j].top=1;
				    grid[((i+1)*5)+j].value+=1;
				    grid[((i+1)*5)+j].line+=1;
				}
				for(ni=0;ni<25;ni++)
                 { 
                     if(grid[ni].value>=15)
                  cn++;}
                  s=cn-count;
                  cn=0;
				if(s!=0)
				{
				grid[m].bottom=0;
				grid[m].value-=4;
				grid[m].line-=1;
				if(i!=4)
				{
				    grid[((i+1)*5)+j].top=0;
				    grid[((i+1)*5)+j].value-=1;
				    grid[((i+1)*5)+j].line-=1;
				}
				}
				else
				{
					printf("%d %d %d",i,j,2);
					return -2;
					
				}
			}

}