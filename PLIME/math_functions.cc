#include <math.h>
#include "utils.h"
#include "math_functions.h"

/***********************************************************************/
/* Dot product of two float vectors				       */
/***********************************************************************/
float qprod_scal(float *v1, float *v2, int dim)
{ 
   int i;
   float result = 0;
   for (i = 0; i < dim; i++)
      result += v1[i] * v2[i];
   return result;
}

/***********************************************************************/
/* Euclidian norm						       */
/***********************************************************************/
float norm_euclid(float x,float y)
{
  return sqrt(x*x + y*y);
}

double norm_euclid(double *x, int size)
{
  float norm = 0;
  for (int i=0; i<size; i++) norm += x[i]*x[i];
  return sqrt(norm);
}

float sq_norm_euclid(float x,float y)
{
  return (x*x + y*y);
}

/***********************************************************************/
/* Round a float to an int					       */
/***********************************************************************/
int round_to_int(float x)
{
  if (x-floor(x) >= 0.5) return (int)ceil(x);
  else return (int)floor(x);
}

/***********************************************************************/
/* Max value in a float vector					       */
/***********************************************************************/
int index_max_value(int *V, int size)
{
  int index = 0;
  for (int i=1; i<size; i++)
    if (V[i] > V[index]) index = i;
  return index;
}

/***********************************************************************/
/* Sort two numbers					               */
/***********************************************************************/
void sort_value(float *v1, float *v2)
{
  float aux;
  if (*v1 > *v2) {
    aux = *v1;
    *v1 = *v2;
    *v2 = aux;
  }
}

void sort_value(int *v1, int *v2)
{
  int aux;
  if (*v1 > *v2) {
    aux = *v1;
    *v1 = *v2;
    *v2 = aux;
  }
}

/***********************************************************************/
/* Min & max search of 2 float numbers				       */
/***********************************************************************/
float max_value(float v1, float v2)
{
  if (v1>v2) return v1;
  else return v2;
}

int max_value(int v1, int v2)
{
  if (v1>v2) return v1;
  else return v2;
}

float min_value(float v1, float v2)
{
  if (v2>v1) return v1;
  else return v2;
}

int min_value(int v1, int v2)
{
  if (v2>v1) return v1;
  else return v2;
}

float min_abs_value(float v1, float v2)
{
  if (((v2>0)? v2 : -v2)>((v1>0)? v1 : -v1)) return v1;
  else return v2;
}

/***********************************************************************/
/* Gaussian distibuted number generator				       */
/***********************************************************************/
#define M1 259200
#define IA1 7141
#define IC1 54773
#define RM1 (1.0/M1)
#define M2 134456
#define IA2 8121
#define IC2 28411
#define RM2 (1.0/M2)
#define M3 243000
#define IA3 4561
#define IC3 51349
 
float ran1(int *idum)
{
  static long ix1,ix2,ix3;
  static float r[98];
  float temp;
  static int iff=0;
  int j;
 
  if (*idum < 0 || iff == 0) {
    iff=1;
    ix1=(IC1-(*idum)) % M1;
    ix1=(IA1*ix1+IC1) % M1;
    ix2=ix1 % M2;
    ix1=(IA1*ix1+IC1) % M1;
    ix3=ix1 % M3;
    for (j=1;j<=97;j++) {
      ix1=(IA1*ix1+IC1) % M1;
      ix2=(IA2*ix2+IC2) % M2;
      r[j]=(ix1+ix2*RM2)*RM1;
    }
    *idum=1;
  }
  ix1=(IA1*ix1+IC1) % M1;
  ix2=(IA2*ix2+IC2) % M2;
  ix3=(IA3*ix3+IC3) % M3;
  j=1 + ((97*ix3)/M3);
  if (j > 97 || j < 1) exit_with_error("RAN1: This cannot happen.");
  temp=r[j];
  r[j]=(ix1+ix2*RM2)*RM1;
  return temp;
}

 
#undef M1
#undef IA1
#undef IC1
#undef RM1
#undef M2
#undef IA2
#undef IC2
#undef RM2
#undef M3
#undef IA3
#undef IC3

float gasdev(int *idum)
{
  static int iset=0;
  static float gset;
  float fac,r,v1,v2;
 
  if  (iset == 0) {
    do {
      v1=2.0*ran1(idum)-1.0;
      v2=2.0*ran1(idum)-1.0;
      r=v1*v1+v2*v2;
    } while (r >= 1.0);
    fac=sqrt(-2.0*log(r)/r);
    gset=v1*fac;
    iset=1;
    return v2*fac;
  }
  else {
    iset=0;
    return gset;
  }
}

/***********************************************************************/
/* Elliptic integral of second kind				       */
/* ellipse_length_norm returns the length of the ellipse:      	       */
/* x^2 + y^2/b^2 = 1; b < 1					       */
/***********************************************************************/

#define a1 .44325141463
#define a2 .06260601220
#define a3 .04757383546
#define a4 .01736506451

#define b1 .24998368310
#define b2 .09200180037
#define b3 .04069697526
#define b4 .00526449639

float ellipse_length_norm(float b)
{
  float k;
  float m;
  
  k = 1 - (b*b);
  m = 1-k;
  return 4*((1 + m*(a1 + m*(a2 + m*(a3 + m*a4)))) +
	    m*(b1 + m *(b2 + m*(b3 + m*b4)))*log(1/m));
}

#undef a1
#undef a2
#undef a3
#undef a4

#undef b1
#undef b2
#undef b3
#undef b4

/***********************************************************************/
/* Perimeter of an ellipse given by its two foyers and a	       */
/***********************************************************************/
#define X1 coeff[0]
#define Y1 coeff[1]
#define X2 coeff[2]
#define Y2 coeff[3]
#define AA coeff[4]
float ellipse_length(float *coeff)
{
  float a2,c2,a,b;
  c2 = ((X2-X1)*(X2-X1)+(Y2-Y1)*(Y2-Y1))/4;
  a2 = AA*AA/4;
  if (a2-c2 > a2) {
    a = sqrt(a2-c2);
    b = sqrt(a2);
  }
  else {
    b = sqrt(a2-c2);
    a = sqrt(a2);
  }
  if (a==b) return 2*M_PI*a; /* ellipse is a circle */

  return (a*ellipse_length_norm(b/a));
}
#undef X1
#undef Y1
#undef X2
#undef Y2
#undef AA

/***********************************************************************/
/* Initialisation of the array for exponential calculation	       */
/***********************************************************************/
void init_exp_array(float **array_ptr)
{
//  static float array_exp[MAX_EXP_NEG];
//  for (int i=0; i<MAX_EXP_NEG; i++) array_exp[i] = exp(i-MAX_EXP_NEG+1);

  static float array_exp[301] = {5.148200e-131,1.399426e-130,3.804034e-130,1.034044e-129,2.810822e-129,7.640607e-129,2.076932e-128,5.645687e-128,1.534657e-127,4.171630e-127,1.133967e-126,3.082441e-126,8.378943e-126,2.277633e-125,6.191248e-125,1.682956e-124,4.574748e-124,1.243545e-123,3.380307e-123,9.188626e-123,2.497728e-122,6.789527e-122,1.845585e-121,5.016820e-121,1.363713e-120,3.706956e-120,1.007655e-119,2.739091e-119,7.445621e-119,2.023930e-118,5.501611e-118,1.495493e-117,4.065171e-117,1.105028e-116,3.003778e-116,8.165115e-116,2.219508e-115,6.033249e-115,1.640007e-114,4.458002e-114,1.211810e-113,3.294042e-113,8.954136e-113,2.433986e-112,6.616261e-112,1.798486e-111,4.888792e-111,1.328912e-110,3.612356e-110,9.819402e-110,2.669190e-109,7.255611e-109,1.972280e-108,5.361212e-108,1.457328e-107,3.961430e-107,1.076828e-106,2.927122e-106,7.956744e-106,2.162867e-105,5.879283e-105,1.598155e-104,4.344235e-104,1.180885e-103,3.209980e-103,8.725629e-103,2.371872e-102,6.447416e-102,1.752589e-101,4.764032e-101,1.294998e-100,3.520170e-100,9.568814e-100,2.601073e-99,7.070451e-99,1.921948e-98,5.224396e-98,1.420138e-97,3.860335e-97,1.049348e-96,2.852423e-96,7.753691e-96,2.107672e-95,5.729245e-95,1.557370e-94,4.233372e-94,1.150750e-93,3.128062e-93,8.502954e-93,2.311343e-92,6.282881e-92,1.707864e-91,4.642456e-91,1.261950e-90,3.430337e-90,9.324621e-90,2.534695e-89,6.890015e-89,1.872900e-88,5.091071e-88,1.383897e-87,3.761821e-87,1.022569e-86,2.779630e-86,7.555819e-86,2.053885e-85,5.583037e-85,1.517627e-84,4.125337e-84,1.121383e-83,3.048235e-83,8.285962e-83,2.252358e-82,6.122544e-82,1.664280e-81,4.523982e-81,1.229746e-80,3.342796e-80,9.086660e-80,2.470010e-79,6.714184e-79,1.825105e-78,4.961148e-78,1.348580e-77,3.665820e-77,9.964733e-77,2.708695e-76,7.362997e-76,2.001470e-75,5.440560e-75,1.478898e-74,4.020060e-74,1.092766e-73,2.970445e-73,8.074507e-73,2.194879e-72,5.966298e-72,1.621808e-71,4.408531e-71,1.198363e-70,3.257489e-70,8.854772e-70,2.406977e-69,6.542841e-69,1.778528e-68,4.834542e-68,1.314165e-67,3.572270e-67,9.710436e-67,2.639570e-66,7.175096e-66,1.950393e-65,5.301719e-65,1.441157e-64,3.917470e-64,1.064879e-63,2.894640e-63,7.868448e-63,2.138866e-62,5.814040e-62,1.580420e-61,4.296027e-61,1.167781e-60,3.174359e-60,8.628801e-60,2.345551e-59,6.375870e-59,1.733141e-58,4.711166e-58,1.280628e-57,3.481107e-57,9.462629e-57,2.572209e-56,6.991990e-56,1.900620e-55,5.166421e-55,1.404379e-54,3.817497e-54,1.037703e-53,2.820770e-53,7.667648e-53,2.084283e-52,5.665668e-52,1.540088e-51,4.186394e-51,1.137980e-50,3.093350e-50,8.408597e-50,2.285694e-49,6.213160e-49,1.688912e-48,4.590938e-48,1.247946e-47,3.392270e-47,9.221146e-47,2.506567e-46,6.813557e-46,1.852117e-45,5.034575e-45,1.368539e-44,3.720076e-44,1.011221e-43,2.748785e-43,7.471972e-43,2.031093e-42,5.521082e-42,1.500786e-41,4.079559e-41,1.108939e-40,3.014409e-40,8.194013e-40,2.227364e-39,6.054602e-39,1.645811e-38,4.473779e-38,1.216099e-37,3.305701e-37,8.985826e-37,2.442601e-36,6.639677e-36,1.804851e-35,4.906095e-35,1.333615e-34,3.625141e-34,9.854155e-34,2.678637e-33,7.281290e-33,1.979260e-32,5.380186e-32,1.462486e-31,3.975450e-31,1.080639e-30,2.937482e-30,7.984904e-30,2.170522e-29,5.900091e-29,1.603811e-28,4.359610e-28,1.185065e-27,3.221340e-27,8.756511e-27,2.380266e-26,6.470235e-26,1.758792e-25,4.780893e-25,1.299581e-24,3.532629e-24,9.602680e-24,2.610279e-23,7.095474e-23,1.928750e-22,5.242886e-22,1.425164e-21,3.873998e-21,1.053062e-20,2.862519e-20,7.781132e-20,2.115131e-19,5.749522e-19,1.562882e-18,4.248354e-18,1.154822e-17,3.139133e-17,8.533048e-17,2.319523e-16,6.305117e-16,1.713908e-15,4.658886e-15,1.266417e-14,3.442477e-14,9.357623e-14,2.543666e-13,6.914400e-13,1.879529e-12,5.109089e-12,1.388794e-11,3.775135e-11,1.026188e-10,2.789468e-10,7.582560e-10,2.061154e-09,5.602796e-09,1.522998e-08,4.139938e-08,1.125352e-07,3.059023e-07,8.315287e-07,2.260329e-06,6.144212e-06,1.670170e-05,4.539993e-05,1.234098e-04,3.354626e-04,9.118820e-04,2.478752e-03,6.737947e-03,1.831564e-02,4.978707e-02,1.353353e-01,3.678794e-01,1.000000e+00};

  *array_ptr = (float*)&array_exp;

}





