#ifndef BIGNUM_H
#define BIGNUM_H
#include "gmp.h"
#include <iostream>

class BigNum;
void avoid_memory_leak(BigNum&b);
class BigNum
{
	public:
		char resultat;
		//don't do something like (x+y).x or it would cause memory leak
		mpz_t x;
		// So that = will behave the same way in all cases
		BigNum(BigNum &b){mpz_init(x);resultat=0;*this=b;};
		BigNum(mpz_t &y){mpz_init_set(x,y);resultat=0;};
		BigNum(){mpz_init_set_ui(x,0);resultat=0;};
		BigNum(const char * c){mpz_init_set_str(x,c,10);resultat=0;};
		virtual ~BigNum(){mpz_clear(this->x);resultat=0;};
		long size(){long size=mpz_sizeinbase(this->x,2);avoid_memory_leak(*this);return size;}
		unsigned long get_ui(){long value=mpz_get_ui(this->x);avoid_memory_leak(*this);return value;}
		BigNum &operator >>(long b)
		{
			mpz_t res;
		  mpz_init(res);
		  mpz_div_2exp(res,this->x,b);
		  BigNum* r=new BigNum(res);
		  mpz_clear(res);
		  r->resultat=1;
		  avoid_memory_leak(*this);
		  return *r;
		};
		BigNum &operator <<(long b)
		{
			mpz_t res;
		  mpz_init(res);
		  mpz_mul_2exp(res,this->x,b);
		  BigNum* r=new BigNum(res);
		  mpz_clear(res);
		  r->resultat=1;
		  avoid_memory_leak(*this);
		  return *r;
		};
		BigNum &operator +(BigNum &b)
		{
		  mpz_t res;
		  mpz_init(res);
		  mpz_add(res,this->x,b.x);
		  BigNum* r=new BigNum(res);
		  mpz_clear(res);
		  r->resultat=1;
		  avoid_memory_leak(b);
		  avoid_memory_leak(*this);
		  return *r;
			  //allocation dynamique pour éviter la suppression au sortir de la fonction
		};
		BigNum &operator -(BigNum &b)
		{
		  mpz_t res;
		  mpz_init(res);
		  mpz_sub(res,this->x,b.x);
		  BigNum* r=new BigNum(res);
		  r->resultat=1;
		  mpz_clear(res);
		  avoid_memory_leak(b);
		  avoid_memory_leak(*this);
		  return *r;
			  //allocation dynamique pour éviter la suppression au sortir de la fonction
		};
		BigNum &operator +(int b)
		{
		  mpz_t res;
		  mpz_init(res);
		  mpz_add_ui(res,this->x,b);
		  BigNum* r=new BigNum(res);
		  mpz_clear(res);
		  r->resultat=1;
		  avoid_memory_leak(*this);
		  return *r;
			  //allocation dynamique pour éviter la suppression au sortir de la fonction
		};
		BigNum &operator -(int b)
		{
		  mpz_t res;
		  mpz_init(res);
		  mpz_sub_ui(res,this->x,b);
		  BigNum* r=new BigNum(res);
		  mpz_clear(res);
		  r->resultat=1;
		  avoid_memory_leak(*this);
		  return *r;
			  //allocation dynamique pour éviter la suppression au sortir de la fonction
		};


		void operator =(BigNum & b)
		{
		  mpz_set(this->x,b.x);
		  avoid_memory_leak(b);
		  avoid_memory_leak(*this);
		};
		void operator =(int  b)
		{
		  mpz_set_ui(this->x,b);
		  avoid_memory_leak(*this);

		};
		bool operator ==(int b)
		{
		  int k =mpz_cmp_ui(this->x,b);
		  if(k==0){
		  avoid_memory_leak(*this);
		  return true;}
		  else {
		  avoid_memory_leak(*this);
		  return false;}
		};
		bool operator ==(BigNum& b)
		{
		  int k =mpz_cmp(this->x,b.x);
			avoid_memory_leak(*this);
			avoid_memory_leak(b);
		  if(k==0){
		  return true;}
		  else {
		  return false;}
		};
		bool operator !=(int b)
		{   
			int k =mpz_cmp_ui(this->x,b);
		  if(k!=0){
		  avoid_memory_leak(*this);
		  return true;}
		  else {
		  avoid_memory_leak(*this);
		  return false;}

		};
		bool operator !=(BigNum& b)
		{   
			int k =mpz_cmp(this->x,b.x);
			avoid_memory_leak(*this);
			avoid_memory_leak(b);
		  if(k!=0){
		  return true;}
		  else {
		  return false;}
		};
		bool operator >(BigNum & b)
		{
		  int k = mpz_cmp(this->x,b.x);

		  avoid_memory_leak(b);
		  avoid_memory_leak(*this);
		  if(k>0){return true;}
		  else{return false;}

		};
		bool operator <(BigNum & b)
		{
		  int k = mpz_cmp(this->x,b.x);

		  avoid_memory_leak(b);
		  avoid_memory_leak(*this);
		  if(k<0){return true;}
		  else{return false;}

		};
		bool operator >(int b)
		{
		  int k = mpz_cmp_ui(this->x,b);
		  avoid_memory_leak(*this);
		  if(k>0){return true;}
		  else{return false;}
		};
		bool operator <(int b)
		{
			int k = mpz_cmp_ui(this->x,b);
			avoid_memory_leak(*this);
			if(k<0){return true;}
			else{return false;}
		};
		BigNum & operator*(BigNum &b)
		{
			mpz_t res;
			mpz_init(res);
			mpz_mul(res,this->x,b.x);
			BigNum*r=new BigNum(res);
			r->resultat=1;
			mpz_clear(res);
			avoid_memory_leak(b);
			avoid_memory_leak(*this);
			return *r;
		};
		BigNum & operator*(int b)
		{
			mpz_t res;
			mpz_init(res);
			mpz_mul_ui(res,this->x,b);
			BigNum*r=new BigNum(res);
			r->resultat=1;
			mpz_clear(res);

			avoid_memory_leak(*this);
			return *r;
		};
		BigNum & operator %(BigNum & b )
		{
			mpz_t res;
			mpz_init(res);

			mpz_mod(res,this->x,b.x);
			BigNum* r=new BigNum(res);
			r->resultat=1;
			mpz_clear(res);
			avoid_memory_leak(b);
			avoid_memory_leak(*this);
			return *r;

		};
		BigNum & operator %(int b)
		{
			mpz_t res;
			mpz_init(res);
			mpz_mod_ui(res,this->x,b);
			BigNum* r=new BigNum(res);
			r->resultat=1;
			mpz_clear(res);
			avoid_memory_leak(*this);
			return *r;

		};
		BigNum & operator /(BigNum & b)
		{
		  mpz_t res;
		  mpz_init(res);
		  mpz_div(res,this->x,b.x);
		  BigNum* r=new BigNum(res);
		  r->resultat=1;
		  mpz_clear(res);
		  avoid_memory_leak(b);
		  avoid_memory_leak(*this);
		  return *r;
		};
		BigNum & operator /(int b)
		{
		  mpz_t res;
		  mpz_init(res);
		  mpz_div_ui(res,this->x,b);
		  BigNum* r=new BigNum(res);
		  mpz_clear(res);
		  r->resultat=1;
		  avoid_memory_leak(*this);
		  return *r;
		};
		BigNum & operator ^(int n)
		{
		  BigNum *r=new BigNum("1");
		  BigNum q(this->x);
		  int i =n;

		  while(i>0)
		  {
	      if(i%2==0)
	      {
          q=q*q;
          i=i/2;
	      }
	      else
	      {
          *r=*r*q;
          i=i-1;
	      }

		  }
			r->resultat=1;
			avoid_memory_leak(*this);
		  return *r;

		};

		BigNum * operator &(){this->resultat=0;return this; };
		void afficher()
		{
		  gmp_printf("%Zd",this->x);

		  avoid_memory_leak(*this);
		};
		int inverse(BigNum& modn)
		{
		  return mpz_invert(this->x,this->x,modn.x);


		};
		void next_prime()
		{
		  mpz_nextprime(this->x,this->x);
		};
		BigNum& next_p()
		{   
			BigNum *res=new BigNum("0");
			mpz_nextprime(res->x,this->x);
			return *res;
		};
		friend BigNum& gcd(BigNum & a, BigNum &b);
		friend BigNum& exp_rap_mod(BigNum& entier,BigNum& n,BigNum& mod);
	protected:
	private:
};
BigNum& exp_rap_mod(BigNum& entier,BigNum& n,BigNum& mod)
{
    BigNum *res=new BigNum("1");
    BigNum tmp;
    BigNum k;
    k=n;
    tmp=entier;
    while(k>0)
    {
        if((k%2)==0)
        {
            k=k/2;
            tmp=(tmp*tmp)%mod;

        }
        else
        {
            k=k-1;
            *res=(*res*tmp)%mod;
        }
    }
    avoid_memory_leak(entier);
	avoid_memory_leak(n);
    avoid_memory_leak(mod);
	res->resultat=1;
    return *res;
};
BigNum& gcd(BigNum & a, BigNum &b)
{
    mpz_t pgcd;
    mpz_init(pgcd);
    mpz_gcd(pgcd,a.x,b.x);
    BigNum *r = new BigNum(pgcd);
    mpz_clear(pgcd);
    avoid_memory_leak(a);
    avoid_memory_leak(b);
	r->resultat=1;
    return *r;
};
//allows to combine operators without taking care of memory management
void avoid_memory_leak(BigNum&b)
{
    if(b.resultat==1)
    {
        delete(&b);
    }
}

#endif // BIGNUM_H
