#include <iostream>
#include "BigNum.h"
#include "PointEdwards.h"
#include "CourbeEdwards.h"
#include <math.h>
using namespace std;
int puissance_max(BigNum& a, BigNum& b)
{
    int i = 0;
    BigNum c("1");
    while (c < b) {
        c = c * a;
        i++;
    }
    return i - 1; // highest power of a < b
}
void Lenstra(BigNum& entier)
{
    if (entier % 2 == 0) {
        printf("divisor found 2");
        return;
    }
    if (entier % 3 == 0) {
        printf("divisor found 3");
        return;
    }
    BigNum B("10000");
    int t = mpz_sizeinbase(B.x, 2);
    BigNum B2;
    B2 = B * t;
    int taille = mpz_sizeinbase(B2.x, 2);
    BigNum primes[B2.get_ui()];
    taille *= taille;
    PointEdwards* tab;
    int k = 0;
    BigNum tp("2");
    while (B2 > tp) {
        primes[k] = tp;
        tp.next_prime();
        k++;
    }
    int fini = 0;
    int puis;
    BigNum p, pr;
    while (fini == 0) {

        CourbeEdwards C(entier);

        PointEdwards P(C.x_point, C.y_point);
        P.c = C;
        C.afficher();
        k = 0;
        p = primes[k];

        while (p < B) {
            puis = puissance_max(p, B);
            pr = p ^ puis;
            P = pr * P;

            if (P.erreur > 1) {

                gmp_printf("divisor found %Zd\n", P.erreur.x);
                fini = 1;
                return;
            }
            if (P.x == 0) {
                printf("\nabort this curve\n");
                p = p + B2;
                break;
            }
            if (gcd(P.x, entier) != 1 && gcd(P.x, entier) != entier) {
                printf("divisor found ");
                (gcd(P.x, entier)).afficher();
                printf("\n");
                fini = 1;
                return;
            }
            if (gcd(P.x, entier) == 0) {
                printf("\nabort this curve\n");
                p = p + B2;
            }
            if (P.erreur == 0) {
                printf("\nabort this curve\n");
                p = p + B2;
            }
            k++;
            p = primes[k];
        }
        //stage 2

        mpz_t tmp;
        mpz_init(tmp);
        mpz_sqrt(tmp, B2.x);
        mpz_add_ui(tmp, tmp, 1);
        taille = mpz_get_ui(tmp);
        PointEdwards tab[taille];
        PointEdwards Q;
        Q.c = C;
        P = p * P;
        p = taille;
        Q = p * P;
        int k = 1;
        tab[0] = Q;
        while (k < taille) {
            tab[k] = tab[k - 1] + Q;
            k++;
        }

        P.x = entier - P.x;
        k = 1;
        int j;
        Q.x = 0;
        Q.y = 1;
        mpz_t tp;
        mpz_init_set_ui(tp, 2);
        //BabyStepGiantStep missing fast algorithm to compute the big product in sqrt(B2)
        //TODO Implement Fast Polynomial arithmetic To compute it faster
        while (k < taille) {
            j = 0;
            while (j < taille) {
                mpz_set_ui(tp, (k + 1) - (j + 1) * taille);
                if (mpz_probab_prime_p(tp, 1) > 0) {
                    BigNum temp = ((Q.x) - (tab[j].x));
                    mpz_mul(tmp, tmp, temp.x);
                    mpz_mod(tmp, tmp, entier.x);
                }
                j = j + 1;
            }
            Q = P + Q;
            k = k + 1;
        }
        mpz_set(p.x, tmp);
        if (gcd(p, entier) != 1 && gcd(p, entier) != entier) {
            gmp_printf("divisor found\n");
            gcd(p, entier).afficher();
            return;
        }
        mpz_clear(tmp);
        mpz_clear(tp);
    }
}
void TestScalarMul(BigNum& entier)
{
    CourbeEdwards C(entier);
    PointEdwards P(C.x_point, C.y_point);
    P.c = C;
    for (long y = 1; y < 100; y++) {
        char by[6] = { 0 };
        sprintf(by, "%d", y);
        BigNum b(by);
        PointEdwards M;
        PointEdwards A;
        A.c = C;
        M.c = C;
        M = b * P;
        for (long yo = 0; yo < y; yo++) {
            A += P;
        }
        if (!(A == M)) {
            gmp_printf("error");
            return;
        }
    }
    gmp_printf("success");
}
int main()
{
    BigNum n("340282366920938463463374607431768211457");
    Lenstra(n);
    //TestScalarMul(n);
    return 0;
}
