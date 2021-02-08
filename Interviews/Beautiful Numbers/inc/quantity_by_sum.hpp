#ifndef QUANTITY_BY_SUM_H
#define QUANTITY_BY_SUM_H

#include <inttypes.h>

/*!
    \brief Quantity of 6-digit numbers in the 13-digit system 
        of calculation with given sum
    
    \param sum the given sum
*/
int64_t quantity_of_numbers_with_sum(short sum);

#endif // QUANTITY_BY_SUM_H