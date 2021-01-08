#include "RootProcessor.h"
using namespace std;
vector<Point2f> RootProcessor::
									cornerDetection(Mat src,double qualityLevel,double minDistance,int blockSize,bool useHarrisDetector,double k,int max)
{
	vector<Point2f> corners;
	goodFeaturesToTrack(src,corners,max,qualityLevel,minDistance,Mat(),blockSize,useHarrisDetector,k);
	return corners;
}

double* RootProcessor::make_ready(vector<Point2f> d)
{
	double median[3]={0},SIGMA[3]={0},sigma[3]={0},Sxy=0,Sxx=0;
	int n=d.size();
	for(int i=0;i<n;i++)
	{
		SIGMA[0]+=i+1;
		SIGMA[1]+=d.at(i).x;
		SIGMA[2]+=d.at(i).y;
	}
	for(int i=0;i<3;i++)
		median[i]=SIGMA[i]/n;
	for(int i=0;i<n;i++)
	{
		sigma[0]+=(i+1-median[0])*(i+1-median[0]);
		sigma[1]+=(d.at(i).x-median[1])*(i+1-median[1]);
		sigma[2]+=(d.at(i).y-median[2])*(i+1-median[2]);
		Sxy+=(d.at(i).x-median[1])*(d.at(i).y-median[2]);
		Sxx+=(d.at(i).x-median[1])*(d.at(i).x-median[1]);
	}
	double* res=new double[7];
	res[0]=(sigma[1]/sigma[0]);
	res[1]=(sigma[2]/sigma[0]);
	res[2]=Sxy/((Sxx==0)?1:Sxx);									//B1
	res[3]=median[2]-res[2]*median[1];			//B0
	res[4]=median[1];
	res[5]=median[2];
	res[6]=median[0];
	return res;
}

Point2f RootProcessor::detector_M(vector<Point2f> candidate,Point2f p,double minD)
{
	cerr<<"middle detected"<<endl;
	Point2f res(p);
	bool det=true;
	for(int u=0;u<2;u++)
	{
		for(int i=0;i<candidate.size();i++)
		{
			double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
			if(dist==0)
				return candidate.at(i);
			if(res.y<=candidate.at(i).y&&dist<=minD)
			{
				res=candidate.at(i);
				det=false;
			}
		}
		minD+=1;
	}
	if(det)
	{
		minD-=2;
		for(int u=0;u<2;u++,minD+=1)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				if(floor(dist)<minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		minD-=2;
		res.y-=5;
		for(int u=0;u<2;u++,minD+=1)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				if(res.y<=candidate.at(i).y&&floor(dist)<minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		//res.y-=5;
		minD-=2;
		for(int u=0;u<3;u++,minD+=1.0)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				//cerr<<"~~~~~"<<dist<<"^"<<minD<<" "<<(res.x>=candidate.at(i).x)<<endl;
				if(floor(dist)<=minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		cerr<<"WARNING!\nthe root doesn't detected"<<endl;
		/*res.x=l.x+((int(resi[0])==0)?1:int(resi[0]));
		res.y=l.y+((int(resi[1])==0)?1:int(resi[1]));*/
		res.x=p.x;
		res.y=p.y+2;
		return res;
	}
	return res;
	/*Point2f res(p);
	bool det=true;
	for(int i=1;i<candidate.size();i++)
	{
		if(res.y<candidate.at(i).y)
		{
			res=candidate.at(i);
			det=false;
		}
	}
	if(det)
	{
		res.y-=5;
		for(int i=1;i<candidate.size();i++)
		{
			if(res.y<candidate.at(i).y)
			{
				res=candidate.at(i);
				det=false;
			}
		}
	}
	if(det)
	{
		res.x=-1;
		return res;
	}
	return res;*/
}

Point2f RootProcessor::detector_R(vector<Point2f> candidate,Point2f p,double minD)
{
	/*Point2f res(p);
	bool det=true;
	for(int i=1;i<candidate.size();i++)
	{
		if(res.y<candidate.at(i).y&&res.x<=candidate.at(i).x)
		{
			res=candidate.at(i);
			det=false;
		}
	}
	if(det)
	{
		for(int i=1;i<candidate.size();i++)
		{
			if(res.y<candidate.at(i).y)
			{
				res=candidate.at(i);
				det=false;
			}
		}
	}
	if(det)
	{
		res.y-=5;
		for(int i=1;i<candidate.size();i++)
		{
			if(res.y<candidate.at(i).y&&res.x<=candidate.at(i).x)
			{
				res=candidate.at(i);
				det=false;
			}
		}
	}
	if(det)
	{
		res.y-=5;
		for(int i=1;i<candidate.size();i++)
		{
			if(res.y<candidate.at(i).y)
			{
				res=candidate.at(i);
				det=false;
			}
		}
	}
	if(det)
	{
		res.x=-1;
		return res;
	}
	return res;*/
	cerr<<"right detected"<<endl;
	Point2f res(p);
	bool det=true;
	for(int u=0;u<2;u++)
	{
		for(int i=0;i<candidate.size();i++)
		{
			double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
			if(dist==0)
				return candidate.at(i);
			if(res.y<=candidate.at(i).y&&res.x<=candidate.at(i).x&&dist<=minD)
			{
				res=candidate.at(i);
				det=false;
			}
		}
		minD+=1;
	}
	if(det)
	{
		minD-=2;
		for(int u=0;u<2;u++,minD+=1)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				if(res.x<candidate.at(i).x&&floor(dist)<minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		minD-=2;
		res.y-=5;
		for(int u=0;u<2;u++,minD+=1)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				if(res.y<=candidate.at(i).y&&res.x<candidate.at(i).x&&floor(dist)<minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		//res.y-=5;
		minD-=2;
		for(int u=0;u<3;u++,minD+=1.0)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				//cerr<<"~~~~~"<<dist<<"^"<<minD<<" "<<(res.x>=candidate.at(i).x)<<endl;
				if(res.x<=candidate.at(i).x&&floor(dist)<=minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		cerr<<"WARNING!\nthe root doesn't detected"<<endl;
		/*res.x=l.x+((int(resi[0])==0)?1:int(resi[0]));
		res.y=l.y+((int(resi[1])==0)?1:int(resi[1]));*/
		res.x=p.x;
		res.y=p.y+1;
		return res;
	}
	return res;
}

Point2f RootProcessor::detector_L(vector<Point2f> candidate,Point2f p,double minD)
{
	cerr<<"left detected"<<endl;
	Point2f res(p);
	bool det=true;
	for(int u=0;u<2;u++)
	{
		for(int i=0;i<candidate.size();i++)
		{
			double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
			if(dist==0)
				return candidate.at(i);
			if(res.y<=candidate.at(i).y&&res.x>=candidate.at(i).x&&dist<=minD)
			{
				res=candidate.at(i);
				det=false;
			}
		}
		minD+=1;
	}
	if(det)
	{
		minD-=2;
		for(int u=0;u<2;u++,minD+=1)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				if(res.x>candidate.at(i).x&&floor(dist)<minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		minD-=2;
		res.y-=5;
		for(int u=0;u<2;u++,minD+=1)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				if(res.y<=candidate.at(i).y&&res.x>candidate.at(i).x&&floor(dist)<minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		//res.y-=5;
		minD-=2;
		for(int u=0;u<3;u++,minD+=1.0)
			for(int i=0;i<candidate.size();i++)
			{
				double dist=sqrt((p.x-candidate.at(i).x)*(p.x-candidate.at(i).x)+(p.y-candidate.at(i).y)*(p.y-candidate.at(i).y));
				//cerr<<"~~~~~"<<dist<<"^"<<minD<<" "<<(res.x>=candidate.at(i).x)<<endl;
				if(res.x>=candidate.at(i).x&&floor(dist)<=minD)
				{
					res=candidate.at(i);
					det=false;
				}
			}
	}
	if(det)
	{
		cerr<<"WARNING!\nthe root doesn't detected"<<endl;
		/*res.x=l.x+((int(resi[0])==0)?1:int(resi[0]));
		res.y=l.y+((int(resi[1])==0)?1:int(resi[1]));*/
		res.x=p.x;
		res.y=p.y+1;
		return res;
	}
	return res;
}

Point2f RootProcessor::sp_detector(vector<Point2f> candidate,Point2f p,double grade,double radius)
{
	Point2f a(0,0);
	double defGr=1000000000000;
	Point2f b(candidate.at(0).x,candidate.at(0).y);
	//distanceCl(a,a);
	double minDis=distanceCl(p,candidate.at(0));
	for(int i=1;i<candidate.size();i++)
	{
		double dis=distanceCl(candidate.at(i),p);
		double ge=gradient(p,candidate.at(i));
		if(dis<=minDis&&abs(ge-grade)<defGr&&candidate[i].y>=p.y)
		{
			minDis=dis;
			defGr=abs(ge-grade);
			a=candidate.at(i);
		}
	}
	return a;	
}

double RootProcessor::gradient(Point2f s,Point2f e)
{
	return (e.y-s.y)/(e.x-s.x);
	//return (e.y-s.y)/(((e.x-s.x)==0)?1:(e.x-s.x));	
}

double RootProcessor::distanceCl(Point2f a,Point2f b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
