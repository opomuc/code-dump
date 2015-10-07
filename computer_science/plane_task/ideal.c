#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int sqrtt(long L);

int main()
{
    //######initialization#####
    printf("Hello world!\n");

	FILE *in; in = fopen("in.txt", "r");

	FILE *inq; inq = fopen("inq.txt", "r");
	FILE *out; out = fopen("out.txt", "w");

    int x1, y1, xx = 0, yy = 0,x[20],y[20],xq[20],yq[20], tq[20],lq;
    int vx, vy, v = 20, time=0;
    int k = 0, z = 0, i = 0, t, kq;
    int oil = 150;

    //######reading from in.txt#####
    do
    {
        i++;
        fscanf (in, "%d %d", &x[i], &y[i]);
        x[i] = x[i]*10;
        y[i] = y[i]*10;
        printf ("%d %d\n", x[i], y[i]);
    }while (!feof(in));
    int l = i;

     i = 0;
     do
    {
        i++;
        fscanf (inq, "%d %d %d", &xq[i], &yq[i], &tq[i]);
        xq[i] = xq[i]*10;
        yq[i] = yq[i]*10;
       // printf ("%d %d %d q\n", xq[i], yq[i], tq[i]);
    }while (!feof(inq));  lq = i;


    long d = 10000;
    long p = 0;  int flag,a,b;

    for (z = 1; z<=l;z++)
    {
        d = 9000;
        for (i = 1;i<=l;i++)
        {
            if (x[i] != 11111 && sqrtt((x[i]-xx)*(x[i]-xx)+(y[i]-yy)*(y[i]-yy))<d)
                {
                    d = sqrtt((x[i]-xx)*(x[i]-xx)+(y[i]-yy)*(y[i]-yy));
                    k=i;
                }
        }

        x1=x[k]; y1=y[k];

        flag = 0;  kq=0;
        b = 9000;
        for (i = 1;i<=lq;i++)
        {
            //printf ("\n! %d", i);
            if (xq[i] != 11111 && sqrtt((xq[i]-xx)*(xq[i]-xx)+(yq[i]-yy)*(yq[i]-yy))<b && time>tq[i])
                {

                    b = sqrtt((xq[i]-xx)*(xq[i]-xx)+(yq[i]-yy)*(yq[i]-yy));
                  //  printf ("#%d %d %d ",xq[i], yq[i], d);
                    kq=i;
                }
        }
       // printf ("%d^[%d %d(%d) = %d %d %d(%d) = %d]",time, xq[1], yq[1],tq[1],sqrtt((xq[1]-xx)*(xq[1]-xx)+(yq[1]-yy)*(yq[1]-yy)),xq[2], yq[2],tq[2],sqrtt((xq[2]-xx)*(xq[2]-xx)+(yq[2]-yy)*(yq[2]-yy)));

        a = sqrtt((x[k]-xx)*(x[k]-xx)+(y[k]-yy)*(y[k]-yy));
      if (kq!=0) b = sqrtt((xq[kq]-xx)*(xq[kq]-xx)+(yq[kq]-yy)*(yq[kq]-yy));
      else b = 9000;

      //printf ("Yes %d ", b);
      //printf ("\n!alternative %d %d\n", a, b);

  if (a > b)
    {
      printf ("\n### %d:: New Point: (%d;%d), appeared at %d, it is closer to this point (%d) than to the next(%d;%d) (%d)\n",time, xq[kq],yq[kq],tq[kq], b, x[k], y[k], a);
      x1 = xq[kq]; y1 = yq[kq];  flag = 1;
    }
        p = sqrtt((x1-0)*(x1-0)+(y1-0)*(y1-0)) ;

        if ((p+d)/v > oil-time) {
                if (t != 1) {printf ("\n return to the base\n");
                printf ("\n Point that the airplane did not reach: \n");  }

                t = 1;
        }


        while (sqrtt((xx-x1)*(xx-x1)+(yy-y1)*(yy-y1))>20)
        {
            vx = ((x1-xx)*v/sqrtt((xx-x1)*(xx-x1)+(yy-y1)*(yy-y1)));
            vy = ((y1-yy)*v/sqrtt((xx-x1)*(xx-x1)+(yy-y1)*(yy-y1)));
            xx=xx+vx;
            yy=yy+vy;

            time++;
        }
        printf ("time: %3d, position: (%3d;%3d), destination (%3d;%3d), vx = %3d, vy = %3d\n",time, xx, yy,x1,y1,vx,vy);
                    fprintf (out, "%d\n", x1);

        if (flag == 0) x[k] = 11111; else xq[kq] = 11111;
        }

        fclose(in);
        fclose(inq);
        fclose(out);
        return 0;
}



int sqrtt(long L)
	{
	    int div = 1, rslt = 0;
		while (L > 0)
		{
		    L -= div,  div += 2;
			rslt += L < 0 ? 0 : 1;
		}
		return rslt;
	}
