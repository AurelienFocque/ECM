#ifndef POINTEDWARDS_H
#define POINTEDWARDS_H
#include "gmp.h"
#include "CourbeEdwards.h"
#include "BigNum.h"
class PointEdwards;
void avoid_memory_leak(PointEdwards&P);
class PointEdwards
{
  public:
		char resultat;
    CourbeEdwards c;
    BigNum x;
    BigNum y;
    BigNum erreur;
    PointEdwards(){x=0;y=1;erreur=1;resultat=0;};
    PointEdwards(CourbeEdwards & c){x=0;y=1;erreur=1;c=c;resultat=0;};
    PointEdwards(BigNum &u,BigNum &v){x=u;y=v;erreur=1;resultat=0;};
    PointEdwards(PointEdwards&P){*this=P;resultat=0;}
		~PointEdwards(){}
    friend PointEdwards & operator +(PointEdwards & Q,PointEdwards & P);
    //friend void operator +=(PointEdwards & P);
    void operator =(PointEdwards & P)
    {
      this->x=P.x;
      this->y=P.y;
      this->c=P.c;
      this->erreur=P.erreur;
    	avoid_memory_leak(P);
    };
		bool operator ==(PointEdwards & P)
    {
			bool ret=this->x==P.x && this->y==P.y && this->erreur==P.erreur;
			avoid_memory_leak(*this);		      	
    	avoid_memory_leak(P);
			return ret;
    };
    friend PointEdwards & operator *(int k,PointEdwards& P);
    void operator +=(PointEdwards & P)
    {
        if(this->erreur!=1)
        {   
					avoid_memory_leak(P);
					return;
        }
        if(P.erreur!=1)
        {   
        	this->erreur=P.erreur;
					avoid_memory_leak(P);
          return ;
        }
		
        BigNum b1;
        b1=1;
        BigNum x_res;
        BigNum y_res;
        BigNum tmp;
        BigNum tmp1;
        BigNum tmp2;
        x_res=(this->x)*P.y;
        x_res=x_res + (this->y)*P.x;
        tmp= ((this->c.d)*(P.x)*(P.y)*(this->x)*(this->y));
        tmp1=tmp+1;
        tmp1=tmp1%this->c.Modulo;
        tmp2=b1-tmp;
        tmp2=tmp2%this->c.Modulo;
        if(gcd(tmp1,this->c.Modulo)==1&&gcd(tmp2,this->c.Modulo)==1){
        tmp1.inverse(this->c.Modulo);
        tmp2.inverse(this->c.Modulo);
        }
        else
        {
          if(gcd(tmp1,this->c.Modulo)==1)
          {
          	this->erreur=gcd(tmp2,this->c.Modulo);
          	this->erreur=(this->erreur)%(this->c.Modulo);

          }
          if(gcd(tmp2,this->c.Modulo)==1)
          {
          	this->erreur=gcd(tmp1,this->c.Modulo);
          	this->erreur=(this->erreur)%(this->c.Modulo);
          }
        }
        x_res= x_res * tmp1;
        y_res= y_res * tmp2;
        x_res= x_res % this->c.Modulo;
        y_res=(this->y)*(P.y);
        y_res=y_res-(P.x)*(this->x);
        y_res=y_res*tmp2;
        y_res=y_res % this->c.Modulo;
        this->x=x_res;
        this->y=y_res;
				avoid_memory_leak(P);
        return ;
    };
    void afficher()
    {
			gmp_printf("Point ( %Zd , %Zd ) erreur %Zd\n",this->x.x,this->y.x,this->erreur.x);
    };
    protected:
    private:
};

PointEdwards &operator +(PointEdwards & Q,PointEdwards & P)
{
  if(Q.erreur!=1)
  {   
  	PointEdwards *res =new PointEdwards();
    res->erreur=Q.erreur;
		avoid_memory_leak(P);
		avoid_memory_leak(Q);
		res->resultat=1;
    return *res;
  }
  if(P.erreur!=1)
  {   
  	PointEdwards *res =new PointEdwards();
    res->erreur=P.erreur;
		avoid_memory_leak(P);
		avoid_memory_leak(Q);
		res->resultat=1;
    return *res;
  }
  BigNum b1;
  b1=1;
  BigNum x_res;
  BigNum y_res;
  BigNum tmp;
  BigNum tmp1;
  BigNum tmp2;
  x_res=(Q.x)*P.y;
  x_res=x_res + (Q.y)*P.x;
  tmp= ((Q.c.d)*(P.x)*(P.y)*(Q.x)*(Q.y));
  tmp1=tmp+1;
  tmp1=tmp1%Q.c.Modulo;
  tmp2=b1-tmp;
  tmp2=tmp2%Q.c.Modulo;
  if(gcd(tmp1,Q.c.Modulo)==1&&gcd(tmp2,Q.c.Modulo)==1)
  {
  	tmp1.inverse(Q.c.Modulo);
  	tmp2.inverse(Q.c.Modulo);
  }
  else
  {   
  	PointEdwards *res= new PointEdwards(x_res,y_res);
    if(gcd(tmp1,Q.c.Modulo)==1)
    {
    	res->erreur=gcd(tmp2,Q.c.Modulo);
    	res->erreur=(res->erreur)%(Q.c.Modulo);
    	res->c=Q.c;
    }
    if(gcd(tmp2,Q.c.Modulo)==1)
    {
    	res->erreur=gcd(tmp1,Q.c.Modulo);
    	res->erreur=(res->erreur)%(Q.c.Modulo);
    	res->c=Q.c;}
		avoid_memory_leak(P);
		avoid_memory_leak(Q);
		res->resultat=1;
    return *res;
  }
  x_res= x_res * tmp1;
  x_res= x_res % Q.c.Modulo;
  y_res=(Q.y)*(P.y);
  y_res=y_res-(P.x)*(Q.x);
  y_res=y_res*tmp2;
  y_res=y_res % Q.c.Modulo;
  PointEdwards *res= new PointEdwards(x_res,y_res);
  res->c=Q.c;
  res->erreur=(res->erreur)%(Q.c.Modulo);
	avoid_memory_leak(P);
	avoid_memory_leak(Q);
	res->resultat=1;
  return *res;
};
//#define SWi
#ifndef SWi
//Classic exponentiation
PointEdwards & operator *(BigNum &k,PointEdwards & P)
{   
	PointEdwards Tmp;
  PointEdwards* Q=new PointEdwards();
  Q->c=P.c;
  BigNum c;
  Tmp=P;
  c=k;
  while(c>0&&Q->erreur==1)
  {   
		if(c%2==0)
    {
      Tmp+=Tmp;
      c=c/2;
    }
    else
		{
      *Q+=Tmp;
      c=c-1;
    }
  }
  avoid_memory_leak(P);
	avoid_memory_leak(k);
  Q->resultat=1;
  return *Q;
};
#endif SWi
#ifdef SWi
//Sliding window
PointEdwards & operator *(BigNum &k,PointEdwards & P)
{   
    //Compute sliding window
	long size=k.size();
	//TODO compute the optimal value according to k
	long swblocsize=3;
  long swlen=(1<<swblocsize)-1;
  PointEdwards SW[swlen];
	SW[0]=P;
	for (long l =1;l<swlen;l++)
	{
		SW[l]=SW[l-1]+P;
	}
  PointEdwards Tmp;
  PointEdwards* Q=new PointEdwards();
  Q->c=P.c;
  BigNum c;
  Tmp=P;
  c=k;
	long index=size;
	long lastindex=size;
	long realblocsize;
	long indexor0;
	while(index>0)
	{
		index-=swblocsize;
		if(Q->erreur==0){break;}
		indexor0=index;
		if(index<0)
		{indexor0=0;}
		long overflow=(index<0)*(swblocsize+index)+(index>=0)*swblocsize;
		long blocvalue=((k>>indexor0).get_ui())%(1<<overflow);
		//while High Significant Bit is 0, slide the window. Shouldn't go here at first time.
		while((blocvalue>>(swblocsize-1)==0) && index>0)
		{
			index--;
			blocvalue=((k>>index).get_ui())%(swlen+1);
			if(Q->erreur==1)
			{
				*Q=*Q+*Q;
			}
		}
		//we get here if the last bloc is filled with zeros
		if(blocvalue!=0)
		{
			*Q+=SW[blocvalue-1];
		}
		swblocsize>index?realblocsize=index:realblocsize=swblocsize;
		if(index>0)//No shift for the last time
		{
			for(long u=0;u<realblocsize;u++)
			{
				if(Q->erreur==1)
				{
					*Q=*Q+*Q;
				}
			}
		}
		
	}
	avoid_memory_leak(P);
	avoid_memory_leak(k);
  Q->resultat=1;
  return *Q;
};
#endif SWi
//allows to combine operators without taking care of memory management
void avoid_memory_leak(PointEdwards&P)
{
  if(P.resultat==1)
  {
    delete(&P);
  }
}


#endif // POINTEDWARDS_H
