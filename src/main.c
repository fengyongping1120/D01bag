#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
int V[1200][1200];//前i个物品装入容量为j的背包中获得的最大价值
int main(){
	int n,temp1,temp2,A[10][3000]={0};
	printf("文件项目：\n");
	printf("idkp1-10.txt\n");
	printf("sdkp1-10.txt\n");
	printf("udkp1-10.txt\n");
	printf("wdkp1-10.txt\n");
	printf("请输入您要打开的文件名称：\n");
	char filename[100];
	gets(filename);   
    FILE * fp1 = fopen(filename, "r");//打开输入文件
    if (fp1==NULL) 
	{//若打开文件失败则退出
        puts("不能打开文件！");
        return 0;
    }
    printf("正在读取文件......\n");
	printf("开始显示信息......\n");
	int i,j,k;
	char file_str[1024];
	int filecount1=100,filecount2=101;
	int location[100],locsum=0;
	int line[100],linesum=0,linenum=0;
	while(fgets(file_str,sizeof(file_str),fp1))//逐行循环读取文件，直到文件结束
	{
		linesum++;
		if(strstr(file_str,"DKP")) //检查字符串是否在该行中，如果在，则输出该行
		{
		    for(i=0;i<strlen(file_str);i++)
		    {
		    	if(file_str[i]=='P')
		    	{
		    		location[locsum]=atoi(&file_str[i+1]);
		    	    locsum++;
		    	    line[linenum]=linesum;
                    linenum++;
				}
			}
		}
	}
	printf("请从%d-10组中输入您要测试的数据：\n",location[0]);
	scanf("%d",&filecount1); 
	int begin; 
	for(i=0;i<100;i++)
	{
		if(location[i]==filecount1)
		{
			printf("该组数据开始的行数为%d，内容如下：\n",line[i]);
			begin=line[i];
			break;
		}
	}
	char buffer[1025];
	SetPositionByLine(fp1, begin);
	fgets(buffer,1024, fp1);
	printf("%s", buffer);
    k=0; 
	int Partsum[100],partsum;//项集个数 
	j=0;
	int Capacity[100],capacity; 
	SetPositionByLine(fp1, begin-1);
	while(fgets(file_str,sizeof(file_str),fp1))//逐行循环读取文件，直到文件结束
	{
		if(strstr(file_str,"3*")) //检查字符串是否在该行中，如果在，则输出该行
		{
		    for(i=0;i<strlen(file_str);i++)
		    {
		    	if(file_str[i]=='*')
		    	{
		    		Partsum[k]=atoi(&file_str[i+1]);
		    		k++;
					break; 
				}
			}
		}
	}
	partsum=Partsum[0];
    printf("该组数据对应的项集数为：%d\n",partsum);
	SetPositionByLine(fp1, begin-1);
	int w,standloc;
	while(fgets(file_str,sizeof(file_str),fp1))//逐行循环读取文件，直到文件结束
	{	
		if(strstr(file_str,"is")) //检查字符串是否在该行中，如果在，则输出该行
		{
		    for(i=0;i<strlen(file_str);i++)
		    {
		    	if(file_str[i]=='.')
		    	{

		    		for(w=i;w>=0;w--)
		    		{
		    			if(file_str[w]==' ')
		    			{
		    				standloc=w;
		    				break;
						}
					}
		    		Capacity[j]=atoi(&file_str[standloc+1]);
		    		j++;
					break; 
				}
			}
		}
	}
	capacity=Capacity[0];
    printf("该组数据对应的背包容量为：%d\n",capacity);
    SetPositionByLine(fp1, begin);
    j=0;
    int end;
	while(fgets(file_str,sizeof(file_str),fp1))//逐行循环读取文件，直到文件结束
	{	
    	j++;
		if(strstr(file_str,"The")) //检查字符串是否在该行中，如果在，则输出该行
		{
			end=begin+j+1;
			break;
		}
	}
	int sub=end-begin;
	SetPositionByLine(fp1,begin);
	char buf[1024];
	char str[1024];
	memset(str,0,sizeof(str));
	memset(buf,0,sizeof(buf));
	int valuecount=0;
	j=0;
    while (fgets(buf,sizeof(buf),fp1))
    {
	 	begin++;
	 	if(begin>end)
	 	{
	 		break; 
		} 
		int y; 
	    while(fscanf(fp1, "%d,", &y ) == 1 )
        {
        	A[3][valuecount]=y;
        	valuecount++;
        }
    } 
 	SetPositionByLine(fp1, begin+sub);
	j=0;
	int weightcount=0;
    while (fgets(str,sizeof(str),fp1))
    {
	 	j++;
	 	if(j-2>sub)
	 	{
	 		break; 
		} 
		int z; 
	    while( fscanf(fp1, "%d,", &z ) == 1 )
        {
        	A[2][weightcount]=z;
        	weightcount++;
        }
    } 
    k=0;
    for(i=0;i<partsum;i++)
    {
        for(j=0;j<3;j++)
        {
    		A[0][i*3+j]=k;		
	    }	
	    k++;
    }
      for(i=0;i<partsum;i++)
    {
        for(j=0;j<3;j++)
        {
    		A[1][i*3+j]=j+1;		
	    }	
    }
    printf("项集编号  物品编号    重量        价值\n"); 
    for(i=0;i<3*partsum;i++)
    {
   	    for(j=0;j<4;j++)
   	    {
   		    printf("%d          ",A[j][i]);
	    }
   	    printf("\n");
    }
	printf("文件读取结束！\n");
	printf("\n------------------------------\n\n");
	printf("散点图如下：\n");
	int C[3000],D[3000],count1=0,count2=0;
	for(i=0;i<3*partsum;i++)
	{
		C[count1]=A[2][i];
		count1++;
	}
	for(i=0;i<3*partsum;i++)
	{
		D[count2]=A[3][i];
		count2++;
	}
	int swap1;
	for(i=0;i<3*partsum;i++)
	{
		for(j=i;j<3*partsum;j++)
		{
			if(C[i]<C[j])
			{
				swap1=C[i];
				C[i]=C[j];
				C[j]=swap1;
			}
		}
	}
	for(i=0;i<3*partsum;i++)
	{
		for(j=i;j<3*partsum;j++)
		{
			if(D[i]<D[j])
			{
				swap1=D[i];
				D[i]=D[j];
				D[j]=swap1;
			}
		}
	}
	int num1=C[0],num2=D[0];//重量和价值的最大值
	num1=num1/10;
	num2=num2/10;
	int B[num1+1][num2+1];
	for(i=0;i<num1;i++)
	{
		for(j=0;j<num2;j++)
		{
			B[i][j]=0;
		}
	}
	for(i=0;i<3*partsum;i++)
	{
		B[A[2][i]/10][A[3][i]/10]=1;
	}
	for(i=0;i<=num1;i++)
	{ 
		for(j=0;j<=num2;j++)
		{
			if(B[i][j]==1)
			{
				printf(".");
				printf("i=%d,j=%d",A[2][i],A[3][i]);
			}
			else
			{
				printf(" ");
			}
		} 
		printf("\n");
    }
	printf("\n------------------------------\n\n");

    int E[3*partsum],F[3*partsum],G[3*partsum],H[3*partsum],count3=0;
    for(i=0;i<3*partsum;i++)
	{
		E[count3]=A[2][i]/A[3][i];
		F[count3]=A[2][i]%A[3][i];
		G[count3]=A[1][i];
		H[count3]=A[0][i];
		count3++;
	}
	int swap2;
	for(i=0;i<3*partsum;i++)
	{
		for(j=i;j<3*partsum;j++)
		{
			if(E[i]<E[j]||((E[i]==E[j])&&(F[i]<F[j])))
			{
				swap2=E[i];
				E[i]=E[j];
				E[j]=swap2;
				swap2=F[i];
				F[i]=F[j];
				F[j]=swap2;
				swap2=G[i];
				G[i]=G[j];
				G[j]=swap2;
				swap2=H[i];
				H[i]=H[j];
				H[j]=swap2;
			}
		}
	}   
	printf("重量比非递增排序如下：\n");
    for(i=0;i<3*partsum;i++)
    {
    	printf("第%d项集-",H[i]);
    	printf("第%d个物品 : ",G[i]);
    	printf("%d.",E[i]);
    	printf("%d",F[i]);
    	printf("\n"); 
	}
	printf("\n------------------------------\n\n");
    int x[2000];
	int s=dynamicprogramming(capacity,A,partsum,x);//动态规划    
	//toflashback(C,A);//回溯 
    printf("最大物品价值为:\n");
    printf("%d\n",s);   
    fclose(fp1);//关闭输入文件
    return 0;
}

int SetPositionByLine(FILE *fp, int nLine)
{
	int i = 0;
	char buffer[1025];
	fpos_t pos;
 
	rewind(fp);
	for (; i < nLine; i++)
		fgets(buffer, 1024, fp);
	fgetpos(fp, &pos);
	return 0;
} 

int max(int a,int b)
{
   if(a>=b)
       return a;
   else return b;
}
int dynamicprogramming(int capacity,int A[10][1000],int n,int x[100])
{
	clock_t start, finish;
    start = clock();
    int i,j; 
	//填表,其中第一行和第一列全为0
    for(i=0;i<=3*n;i++)
        V[i][0]=0;
    for(j=0;j<=capacity;j++)
        V[0][j]=0;
    for(i=1;i<=3*n;i++)
	{
        for(j=1;j<=capacity;j++)
		{
            if(j<A[2][i-1])
			{
				V[i][j]=V[i-1][j];
			}			
            else
			{
                V[i][j]=max(V[i-1][j],V[i-1][j-A[2][i-1]]+A[3][i-1]);
			}
		}
	}
	//判断哪些物品被选中
    j=capacity;
    for(i=3*n;i>=1;i--)
    {
        if(V[i][j]>V[i-1][j])
        {
			x[i]=1;
			j=j-A[2][i-1];
        }
        else
            x[i]=0;
    }
    FILE * fp2 = fopen("output.txt", "w");//打开输出文件
    char c[ ]={"maxvalue:"};
    fputs(c,fp2);
    fprintf(fp2,"%d",V[3*n][capacity]);
    fputc('\n', fp2);
    finish = clock();
    int duration = finish - start;
    double durationS = (double)duration / CLOCKS_PER_SEC;//如果需要换算成秒
    char e[ ]={"time:"};
    fputs(e,fp2);
    fprintf(fp2,"%f",durationS);
    char d='s';
    fputc(d,fp2); 
    fputc('\n',fp2);
    printf("选中的物品是:\n");
    char b='-';
    for(i=1;i<=3*n;i++)
    {
    	if(x[i]==1)
    	{
    		printf("%d %d %d \n",A[0][i-1],A[1][i-1],x[i]);
    		fprintf(fp2,"%d",A[0][i-1]);//向输出文件写入一个整数
    		fputc(b,fp2);
            fprintf(fp2,"%d",A[1][i-1]);
            fputc('\n', fp2);
		}
	}
    return V[3*n][capacity];         
    fclose(fp2);//关闭输出文件，相当于保存  
}


