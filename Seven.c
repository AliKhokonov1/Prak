#include<stdio.h>
#include<math.h>

double
fx (double y)
{
  return y;
}

double
fy (double x)
{
  return -x;
}

double
Max (double V1, double V2)
{
  if (V1 > V2)
    return V1;
  else
    return V2;
}

double
Min (double V1, double V2)
{
  if (V1 > V2)
    return V2;
  else
    return V1;
}

void
Seven (double tol)
{
  double kx1, kx2, kx3, kx4, kx5, kx6, kx7;
  double ky1, ky2, ky3, ky4, ky5, ky6, ky7;
  double facmin, facmax, fac;
  double t;
  double x0, x, x_d;
  double y0, y, y_d;
  double errx, erry, err;
  double step = 1.0;
  int p = 5;
  fac = 0.9;
  facmax = 1.3;
  facmin = 0.7;
  x0 = 0.0;
  y0 = 1.0;
  x = 0.0;
  y = 1.0;
  t = 0.0;
  double T_t[7][3];
  double T[7];
  T[0] = M_PI;

  for (unsigned int i = 1; i < 7; i++)
    T[i] = T[i - 1] * 10;

  for (unsigned int j = 0; j < 7; j++)
    {
      while (t < T[j])
	{
	  if (t + step > T[j])
	    step = T[j] - t;

	  kx1 = fx (y0);
	  ky1 = fy (x0);

	  kx2 = fx (y0 + step * ((1.0 / 5) * ky1));
	  ky2 = fy (x0 + step * ((1.0 / 5) * kx1));

	  kx3 = fx (y0 + step * ((3.0 / 40) * ky1 + (9. / 40) * ky2));
	  ky3 = fy (x0 + step * ((3.0 / 40) * kx1 + (9. / 40) * kx2));

	  kx4 =
	    fx (y0 +
		step * ((44.0 / 45) * ky1 + (-56.0 / 15) * ky2 +
			(32.0 / 9) * ky3));
	  ky4 =
	    fy (x0 +
		step * ((44.0 / 45) * kx1 + (-56.0 / 15) * kx2 +
			(32.0 / 9) * kx3));

	  kx5 =
	    fx (y0 +
		step * ((19372.0 / 6561) * ky1 + (-25360.0 / 2187) * ky2 +
			(64448.0 / 6561) * ky3 + (-212.0 / 729) * ky4));
	  ky5 =
	    fy (x0 +
		step * ((19372.0 / 6561) * kx1 + (-25360.0 / 2187) * kx2 +
			(64448.0 / 6561) * kx3 + (-212.0 / 729) * kx4));

	  kx6 =
	    fx (y0 +
		step * ((9017.0 / 3168) * ky1 + (-355.0 / 33) * ky2 +
			(46732.0 / 5247) * ky3 + (49.0 / 176) * ky4 +
			(-5103.0 / 18656) * ky5));
	  ky6 =
	    fy (x0 +
		step * ((9017.0 / 3168) * kx1 + (-355.0 / 33) * kx2 +
			(46732.0 / 5247) * kx3 + (49.0 / 176) * kx4 +
			(-5103.0 / 18656) * kx5));

	  kx7 =
	    fx (y0 +
		step * ((35.0 / 384) * ky1 + (500.0 / 1113) * ky3 +
			(125.0 / 192) * ky4 + (-2187.0 / 6784) * ky5 +
			(11.0 / 84) * ky6));
	  ky7 =
	    fy (x0 +
		step * ((35.0 / 384) * kx1 + (500.0 / 1113) * kx3 +
			(125.0 / 192) * kx4 + (-2187.0 / 6784) * kx5 +
			(11.0 / 84) * kx6));

	  x =
	    x0 + step * ((35.0 / 384) * kx1 + (500.0 / 1113) * kx3 +
			 (125.0 / 192) * kx4 + (-2187.0 / 6784) * kx5 +
			 (11.0 / 84) * kx6);
	  y =
	    y0 + step * ((35.0 / 384) * ky1 + (500.0 / 1113) * ky3 +
			 (125.0 / 192) * ky4 + (-2187.0 / 6784) * ky5 +
			 (11.0 / 84) * ky6);

	  x_d =
	    x0 + step * ((5179.0 / 57600) * kx1 + (7571.0 / 16695) * kx3 +
			 (393.0 / 640) * kx4 + (-92097.0 / 339200) * kx5 +
			 (187.0 / 2100) * kx6 + (1.0 / 40) * kx7);
	  y_d =
	    y0 + step * ((5179.0 / 57600) * ky1 + (7571.0 / 16695) * ky3 +
			 (393.0 / 640) * ky4 + (-92097.0 / 339200) * ky5 +
			 (187.0 / 2100) * ky6 + (1.0 / 40) * ky7);

	  errx = fabs (x_d - x);
	  erry = fabs (y_d - y);

	  err = Max (errx, erry);

	  if (err < tol)
	    {
	      x0 = x;
	      y0 = y;
	      t = t + step;
	      printf ("%le %le %le %le", step, t, x, y);
	      printf ("\n");
	    }
	  step =
	    step * Min (facmax,
			Max (facmin, fac * powl (tol / err, 1.0 / (p + 1))));
	}
      T_t[j][0] = T[j];
      T_t[j][1] = x - sin (t);
      T_t[j][2] = y - cos (t);
    }
  printf ("---\n");
  for (unsigned int k = 0; k < 7; k++)
    {
      printf ("%le %le %le %le\n", tol, T_t[k][0], T_t[k][1], T_t[k][2]);
    }
}


int
main ()
{
  double tol = 1e-11;
  Seven (tol);
  return 0;
}