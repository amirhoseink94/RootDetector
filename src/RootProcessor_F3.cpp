#include "RootProcessor.h"
using namespace std;

vector<double> RootProcessor::poly_detect(vector<Point2f> points,int n)
{
	int m=points.size();
	double *temp=new double[n*m];
	double** mat=new double*[m];
	for(int i=0;i<m;i++)
		mat[i]=temp+i*n;
	vector<double> ls;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			mat[i][j]=pow((points[i].x-m/2),j)/10000000000;
		}
		ls.push_back(points[i].y/10000000000);
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<mat[i][j]<<" ";
		}
		cout<<"|"<<ls[i]<<endl;
	}
	int mm;
	cin>>mm;
	for(int i=0;i<m;i++)
	{
		if(mat[i][i]!=0)
		{
			for(int j=i+1;j<m;j++)
			{
				double Z=-mat[j][i]/mat[i][i];
				for(int k=0;k<n;k++)
				{
					mat[j][k]=mat[j][k]+mat[i][k]*Z;
				}
				ls[j]=ls[j]+ls[i]*Z;
			}
		}
	}
	
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<mat[i][j]<<" ";
		}
		cout<<"|"<<ls[i]<<endl;
	}
}

void RootProcessor::rotate(Mat& src,int angle,Mat& dst)
{
	Point2f pt(src.cols/2,src.rows/2);
	int sr=src.rows;
	int sc=src.cols;
	switch(angle)
	{
		case 1:
		{
			transpose(src, src);  
    		flip(src, src,1);
			break;
		}
		case 2:
		{
			flip(src, src,-1);
			break;
		}
		case 3:
		{
			transpose(src, src);  
    		flip(src, src,0);;
			break;
		}
	}
}

Point2f* RootProcessor::root_detection(Mat src_m,Point2f pt,int last_edge,int back_t)
{
	Mat src;
	src_m.copyTo(src);
	Mat src_res;
	src_m.copyTo(src_res);
	Mat src_fill;
	src_m.copyTo(src_fill);
	Point2f resl;
	
	bool lf=false,rf=false;
	int y=pt.y-back_t,li,ri;
	int max=0;
	do
	{
		lf=false;
		rf=false;
		int max_t;
		for(int i=pt.x;i<src_fill.cols;i++)
		{
			if(src_fill.at<uchar>(y,i)==255)
			{
				ri=i;
				rf=true;
				break;
			}
		}
		for(int i=pt.x;i>0;i--)
		{
			if(src_fill.at<uchar>(y,i)==255)
			{
				li=i;
				lf=true;
				break;
			}
		}
		if(lf&&rf)
		{
			pt.y=y;
			pt.x=(li+ri)/2;
			y++;
			max_t=abs(li-ri);
			if(max<max_t)
				max=max_t;
		}
	}while(lf&&rf);
	
	
	
	Point2f resl2;
	for(int i=last_edge;i<src.rows;i++)
	{
		bool l=false,r=false;
		int l_index=-1,r_index=-1;
		for(int j=0;j<src.cols&&l==false;j++)
		{
			if(src.at<uchar>(i,j)>0)
			{
				l_index=j;
				l=true;
				break;
			}
		}
		for(int j=src.cols-1;j>=0&&r==false;j--)
		{
			if(src.at<uchar>(i,j)>0)
			{
				r_index=j;
				r=true;
				break;
			}
		}
		if(l&&r)
		{
			if(l_index!=r_index&&l_index!=-1&&r_index!=-1)
			{
				int m=((l_index+r_index)/2);
				src.at<uchar>(i,l_index)=0;
				src.at<uchar>(i,r_index)=0;
				src.at<uchar>(i,m)=255;
				resl2.x=m;
				resl2.y=i;
				i--;
			}
		}
	} 
	
	Point2f* res_a=new Point2f[3];
	res_a[0]=pt;
	res_a[1]=resl2;
	Point2f temp(max,0);
	res_a[2]=temp;
	return res_a;
}
