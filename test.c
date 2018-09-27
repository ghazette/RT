#include <math.h>
#include <stdio.h>
#include "libalgebra/includes/libalgebra.h"
# define DEGTORAD(DEG) (DEG * M_PI / 180)
# define RADTODEG(RAD) (RAD * 180 / M_PI)
# define PYREX 1.474
# define AIR 1.0

int main()
{
	t_vec3 n;
	t_vec3 r;
	double n1 = AIR;
	double n2 = PYREX;
	vector3d(&n, 0, 1, 0);
	vector3d(&r, 1, 1, 0);

	// calcul de l'angle incident
	// cos (theta) = ( r DOT n)  (||r|| * ||n||)
	double top = vec3_dotproduct(&r, &n);
	double down = vec3_magnitude(&n) * vec3_magnitude(&r);
	double theta1 = top / down;
	theta1 = acos(theta1);
	// theta1 est deja en radian
	// on convertie le resultat en degres pour plus de lisibilite


	// calcul de l'angle refracter
	// n1 * sin(theta1) = n2 * sin(theta2) theta2 est l'inconnu
	double theta2 = asin((n1 * sin(theta1)) / n2);


	// maitenant il faut calculer le nouveau vecteur directeur
	// le nouveau point de vue (la view) sera le point d'intersection
	t_vec3 nr;
	t_vec3 nv;

	vec3_scale(&n, theta2, MULT, &nr);
	vec3_add(&r, &nr, &nv);
	vec3_normalize(&nv);
	printf("angle incident : %f\nangle refracter : %f\nnouveau vecteur directeur (nr) : %f %f %f\n", RADTODEG(theta1), RADTODEG(theta2), nv.x, nv.y, nv.z);
}


