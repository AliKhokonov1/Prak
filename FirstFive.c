#include <stdio.h>
#include <math.h>
double
func (double x)
{
  return 5 * cos (x) + 6 * sin (x);
}

void
First ()
{
  double eps = 1.0;
  while (eps + 1 > 1)
    eps = eps / 2;
  printf ("eps=%e\n", eps);

  double x = 1.0;
  while (x + 1 > x)
    x = x * 1.1;
  printf ("x=%e\n", x);

  double y = 1.0;
  while (y + pow (10, 20) > y)
    y = y * 1.1;
  printf ("y=%e\n", y);
}

void
Second ()
{
  double I = log (7. / 6.);
  for (int i = 1; i < 32; i++)
    {
      I = 1.0 / I - 6 * I;
    }
  printf ("I_31=%lf\n", I);

  double J = 0.0;
  for (int i = 59; i > 30; i--)
    {
      J = 1.0 / (6 * (J + 1)) - J / 6;
    }
  printf ("J_31=%lf\n", J);

  double i_1000 = 0.0;
  double i_10000 = 0.0;
  for (int i = 0; i < 1000; i++)
    i_1000 +=
      1.0 / 1000 * (pow (i / 1000.0 + 1.0 / 1000, 31) /
		    (6 + 1.0 / 1000 + i / 1000.0));
  for (int i = 0; i < 10000; i++)
    i_10000 +=
      1.0 / 10000 * (pow (i / 10000.0 + 1.0 / 10000, 31) /
		     (6 + 1.0 / 10000 + i / 10000.0));
  printf ("i_1000=%lf\n", i_1000);
  printf ("i_10000=%lf\n", i_10000);

}

void
Third ()
{
  FILE *pFile;
  pFile = fopen ("file3.txt", "w");
  double R;
  double h = 1.0;
  double x_0 = 3.0;
  for (int j = 0; j < 20; j++)
    {
      R =
	fabs (-5 * sin (x_0) + 6 * cos (x_0) -
	      (func (x_0 + h) - func (x_0)) / (h));
      fprintf (pFile, "%lf %lf\n", h, R);
      h = h / 10;
    }
}

void
Fourth ()
{
  int N;
  FILE *pFile;
  pFile = fopen ("file_parabola.txt", "w");
  FILE *ppFile;
  ppFile = fopen ("file_svoja.txt", "w");
  FILE *pppFile;
  pppFile = fopen ("file_tabl.txt", "w");
  double h;
  double y = 0.0;
  double x = 0.0;
  double y0 = 0.0;
  double x0 = 0.0;
  double x1 = 10.0;
  h = 1.0;
  for (int i = 0; i < 3; i++)
    {
      x = x0;
      y = y0;
      N = (x1 - x0) / h;
      fprintf (pFile, "%lf %lf\n", x, y);
      for (int j = 0; j < N; j++, x += h)
	{
	  y = y + h * (x + h);
	  fprintf (pFile, "%lf %lf\n", x, y);
	}
      fprintf (pppFile, "%lf %lf\n", h, fabs ((x1 * x1) / 2 - y));
      fprintf (pFile, "\n\n");
      h = h / 10;
    }
  fprintf (pFile, "\n\n\n\n");
  h = 1.0;
  for (int i = 0; i < 3; i++)
    {
      x = x0;
      y = y0;
      N = (x1 - x0) / h;
      fprintf (ppFile, "%lf %lf\n", x, y);
      for (int j = 0; j < N; j++, x += h)
	{
	  y = y + h * func (x + h);
	  fprintf (ppFile, "%lf %lf\n", x, y);
	}
      fprintf (ppFile, "\n\n");
      h = h / 10;
    }
}

void
Fith ()
{
  int N;
  double x, y;
  double x0 = 0.0;
  double y0 = 1.0;
  double x1 = 0.0;
  double y1 = 0.0;
  double h = 0.1;
  double t = 0.0;
  double t0 = 0.0;
  double T = 3.14;
  FILE *f = fopen ("file5.txt", "w");
  for (int i = 0; i < 5; i++, T *= 10)
    {
      for (int j = 0; j < 3; j++)
	{
	  t = t0;
	  x = x0;
	  y = y0;
	  N = T / h;
	  for (int k = 0; k < N; k++, t += h)
	    {
	      x1 = x + y * h;
	      y1 = y - x * h;
	      x = x1;
	      y = y1;
	    }
	  fprintf (f, "%lf %lf %lf %lf\n", T, h, fabs (sin (T) - x),
		   fabs (cos (T) - y));
	  h /= 10;
	}
      h = 0.1;
    }
}



int
main ()
{
  First ();
  printf ("\n");
  Second ();
  printf ("\n");
  Third ();
  Fourth ();
  Fith ();
  return 0;
}
