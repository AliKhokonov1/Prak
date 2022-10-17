#include <stdio.h>
#include <math.h>

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

void
Six (void)
{
  //FILE* file=fopen("file_6","w");
  double kx1, kx2, kx3, kx4, kx5, kx6;
  double ky1, ky2, ky3, ky4, ky5, ky6;
  double t, x0, x, y0, y;
  double RKstep[4];
  double step_const[4];
  double T[7];
  double T_t[7][3];

  RKstep[0] = 0.1;
  step_const[0] = 0.1;
  T[0] = M_PI;

  for (unsigned int i = 1; i < 4; i++)
    RKstep[i] = RKstep[i - 1] / 10;

  for (unsigned int i = 1; i < 4; i++)
    step_const[i] = step_const[i - 1] / 10;

  for (unsigned int i = 1; i < 7; i++)
    T[i] = T[i - 1] * 10;

  for (unsigned int l = 0; l < 4; l++)
    {
      x0 = 0.0;
      y0 = 1.0;
      x = 0.0;
      y = 1.0;
      t = 0.0;

      for (unsigned int j = 0; j < 7; j++)
	{
	  RKstep[l] = step_const[l];
	  while (t < T[j])
	    {
	      if (t + RKstep[l] > T[j])
		RKstep[l] = T[j] - t;

	      kx1 = fx (y0);
	      ky1 = fy (x0);

	      kx2 = fx (y0 + RKstep[l] * ((1.0 / 5) * ky1));
	      ky2 = fy (x0 + RKstep[l] * ((1.0 / 5) * kx1));

	      kx3 =
		fx (y0 + RKstep[l] * ((3.0 / 40) * ky1 + (9.0 / 40) * ky2));
	      ky3 =
		fy (x0 + RKstep[l] * ((3.0 / 40) * kx1 + (9.0 / 40) * kx2));

	      kx4 =
		fx (y0 +
		    RKstep[l] * ((44.0 / 45) * ky1 + (-56.0 / 15) * ky2 +
				 (32.0 / 9) * ky3));
	      ky4 =
		fy (x0 +
		    RKstep[l] * ((44.0 / 45) * kx1 + (-56.0 / 15) * kx2 +
				 (32.0 / 9) * kx3));

	      kx5 =
		fx (y0 +
		    RKstep[l] * ((19372.0 / 6561) * ky1 +
				 (-25360.0 / 2187) * ky2 +
				 (64448.0 / 6561) * ky3 +
				 (-212.0 / 729) * ky4));
	      ky5 =
		fy (x0 +
		    RKstep[l] * ((19372.0 / 6561) * kx1 +
				 (-25360.0 / 2187) * kx2 +
				 (64448.0 / 6561) * kx3 +
				 (-212.0 / 729) * kx4));

	      kx6 =
		fx (y0 +
		    RKstep[l] * ((9017.0 / 3168) * ky1 + (-355.0 / 33) * ky2 +
				 (46732.0 / 5247) * ky3 + (49.0 / 176) * ky4 +
				 (-5103.0 / 18656) * ky5));
	      ky6 =
		fy (x0 +
		    RKstep[l] * ((9017.0 / 3168) * kx1 + (-355.0 / 33) * kx2 +
				 (46732.0 / 5247) * kx3 + (49.0 / 176) * kx4 +
				 (-5103.0 / 18656) * kx5));

	      x =
		x0 + RKstep[l] * ((35.0 / 384) * kx1 + (500.0 / 1113) * kx3 +
				  (125.0 / 192) * kx4 +
				  (-2187.0 / 6784) * kx5 + (11.0 / 84) * kx6);
	      y =
		y0 + RKstep[l] * ((35.0 / 384) * ky1 + (500.0 / 1113) * ky3 +
				  (125.0 / 192) * ky4 +
				  (-2187.0 / 6784) * ky5 + (11.0 / 84) * ky6);

	      x0 = x;
	      y0 = y;
	      t = t + RKstep[l];
	    }
	  T_t[j][0] = T[j];
	  T_t[j][1] = x - sin (t);
	  T_t[j][2] = y - cos (t);
	}
      printf ("---\n");
      for (unsigned int k = 0; k < 7; k++)
	{
	  printf ("%e %e %e %e\n", RKstep[l], T_t[k][0], T_t[k][1],
		  T_t[k][2]);
	}
    }
}

int
main ()
{
  Six ();
  return 0;
}

