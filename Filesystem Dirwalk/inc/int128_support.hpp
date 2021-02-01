#ifndef INT128_H
#define INT128_H

#include <iostream>
#include <inttypes.h>

/* 
 * \brief Representation of int128 value
*/
std::ostream& operator<<(std::ostream& dest, __int128_t value);

#endif // INT128_H