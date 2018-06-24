#ifndef COURBEEDWARDS_H
#define COURBEEDWARDS_H
#include "gmp.h"
#include "PointEdwards.h"
#include "BigNum.h"


class CourbeEdwards
{
    public:
        BigNum d;
        BigNum Modulo;
        BigNum x_point;
        BigNum y_point;
        CourbeEdwards(){d=0;Modulo=0;x_point=0;y_point=0;};
        CourbeEdwards(BigNum & Modulo)
        {   bool fini = false;
            BigNum tmp1;
            BigNum tmp2;
            while (fini == false){
            this->Modulo=Modulo;
            mpz_t a,b;
            mpz_init (a);
            mpz_init (b);
            mpz_random(a,mpz_sizeinbase(Modulo.x,2));
            mpz_random(b,mpz_sizeinbase(Modulo.x,2));
            BigNum e(a);
            BigNum f(b);
            x_point=e%Modulo;
            y_point=f%Modulo;
            e=(e)*(e);
            f=(f)*(f);
            tmp1=e+f;
            tmp1=tmp1-1;
            tmp2=e*f;
            tmp2=tmp2%Modulo;


            if(gcd(Modulo,tmp2)==1&&tmp2!=0)
            {
                tmp2.inverse(Modulo);

                this->d=tmp2*tmp1;
                this->d=this->d%Modulo;
                fini=true;

            }
			mpz_clear(a);
			mpz_clear(b);
            }
            return;


        };
        CourbeEdwards(BigNum & d,BigNum &Modulo){this->d=d;this->Modulo=Modulo;} ;
        void operator = (CourbeEdwards & c)
        {
            this->d=c.d;
            this->Modulo=c.Modulo;
            this->x_point=c.x_point;
            this->y_point=c.y_point;
        };
        void afficher()
        {
           	gmp_printf("Modulo=%Zd,d=%Zd,x=%Zd,y=%Zd\n",Modulo.x,d.x,x_point.x,y_point.x);
        };
    protected:
    private:
};

#endif // COURBEEDWARDS_H
