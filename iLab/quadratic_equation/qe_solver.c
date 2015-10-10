/** **********************************************************************************
 * @file    qe_solver.c
 * @date    2013-09-23 23:10
 * @author  Roman Proskin <roman.proskin@frtk.ru>
 *
 * Solve a quadratic equation considering particular cases
 *
 * @par     Task.
 *          The program gets 3 coefficients of a quadratic equation
 *
 * @warning Do not enter invalid set of coefficients! The program will close!
**************************************************************************************/

#include <stdio.h>
#include <math.h>
#include <assert.h>

int solve_square(double a, double b, double c, double* x1, double* x2);

int main()
{
    double a=0, b=0, c=0, x1=0, x2=0;

    printf("Quadratic equation solver\nVersion 1.0.0\nProskin Roman\n\nPlease type three coefficients a, b, c:");
    scanf("%lg %lg %lg", &a,&b,&c);

    int roots=solve_square(a,b,c,&x1,&x2);

    if (roots==-1) {printf("This is not a quadratic equation! :)"); return 0;};
    if (roots==0)
        printf("First root: %lgi\nSecond root: %lgi",x1,x2);
        else if (roots==1)
                printf("One root, x=%lg",x1);
                else printf("First root: %lg\nSecond root: %lg",x1,x2);
    return 0;

}

int solve_square(double a, double b, double c, double* x1, double* x2)
{
    assert(x1!=NULL);
    assert(x2);
    assert(x1!=x2);

    if (a==0) return -1;
    if (b*b-4*a*c < 0)
    {
       *x1=(-b+(sqrt(-(b*b-4*a*c))))/(2*a);
       *x2=(-b-(sqrt(-(b*b-4*a*c))))/(2*a);
       return 0;
    }

        else if (b*b-4*a*c > 0)
             {
                *x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
                *x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
                return 2;
             }

                else {*x1 = (-b/(2*a)); return 1;}

}
