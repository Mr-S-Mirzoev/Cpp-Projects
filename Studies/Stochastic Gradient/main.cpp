#include <iostream>
#include "blaze/Math.h"

using blaze::StaticVector;
using blaze::DynamicVector;

int main()
{
   // Instantiation of a static 3D column vector. The vector is directly initialized as
   //    ( 4 -2  5 )
   StaticVector<int,3UL> a{ 4, -2, 5 };

   // Instantiation of a dynamic 3D column vector. Via the subscript operator the values are set to
   //    ( 2  5 -3 )
   DynamicVector<int> b( 3UL );
   b[0] = 2;
   b[1] = 5;
   b[2] = -3;

   // Adding the vectors a and b
   DynamicVector<int> c = a + b;

   // Printing the result of the vector addition
   std::cout << "c =\n" << c << "\n";

   blaze::DynamicVector<double, blaze::columnVector> weights (4UL);
   blaze::DynamicVector<double, blaze::columnVector> x (4UL);
   weights[0] = 1;
   weights[1] = 2;
   weights[2] = 3;
   weights[3] = 4;

   x[0] = x[1] = x[2] = x[3] = 1;

   std::cout << blaze::trans(x) * weights << std::endl; 
}