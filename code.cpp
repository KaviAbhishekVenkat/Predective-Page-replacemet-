#include<iostream>
#include<algorithm>
using namespace std;
int pg[10000],n,fr,pre[10][10][4];
void set_predict(int,int);
int* predict(int);
void calibrate();
//void calibrate(int);
main()
{
    int fault=0;
    cout<<"Enter the no. of pages:";
    cin>>n;
    cout<<"\nEnter the size of the frame:";
    cin>>fr;
    cout<<"\n";
    cout<<"enter the page sequence -\n";
    for(int k=0;k<n;k++)
        cin>>pg[k];
    calibrate();
    int frame[fr];
    for(int i=0;i<fr;i++)
        {

                frame[i]=pg[i];

                if(i!=0)
                    set_predict(pg[i-1],pg[i]);
                fault++;
        }
    for(int t=fr;t<n;t++)
    {
       int temp=pg[t],found=0;
       set_predict(pg[t-1],temp);
       for(int i=0;i<fr;i++)
        if(frame[i]==temp)
            found++;
       if(found==0)
       {
           int loc[3];
           loc[0]=0;
           loc[1]=0;
           loc[2]=0;
           int *a=predict(temp);
           for(int i=0;i<fr;i++)
            if(a[0]==frame[i] || a[1]==frame[i])
            {
                loc[i]=1;
            }
           int mini=0;
           for(int i=0;i<fr;i++)
            if(loc[i]==0)
                mini=i;
           frame[mini]=temp;
           fault++;

       }


    }
    cout<<endl<<"The predicted page that is replaced";
for(int k=0;k<n;k++)
{
    cout<<endl<<frame[k];
}

cout<<endl<<"total faults are-"<<fault;


}

void calibrate()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            {
                pre[i][j][0]=i+1;
                pre[i][j][1]=j+1;
                pre[i][j][2]=0;
            }

}
void set_predict(int a,int b)
{
    int temp1,temp2;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            {
                if(pre[i][j][0]==a && pre[i][j][1]==b)
                {
                    temp1=i;
                    temp2=j;
                    break;
                }

            }
    pre[temp1][temp2][2]+=1;

}

int* predict(int a)
{
    int loc[2];
    int temp1[9][3],temp2[9];
        for(int j=0;j<9;j++)
            {
                temp1[j][1]=pre[a][j][1];
                temp1[j][2]=pre[a][j][2];

                temp2[j]=pre[a][j][2];

            }
        sort(temp2,temp2+9);
        for(int j=0;j<9;j++)
        {
            if(temp2[8]==temp1[j][2])
                loc[0]=j;
            if(temp2[7]==temp1[j][2])
                loc[1]=j;
        }
    return loc;

}
