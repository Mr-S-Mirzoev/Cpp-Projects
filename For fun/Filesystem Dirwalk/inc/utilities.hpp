#ifndef UTILITIES_H
#define UTILITIES_H

#define indent_with_t(c) for (int i = 0; i < c; ++i) std::cout << "    "
#define bold_red(s) "\x1B[1;31m" << s << rst
#define bold_blue(s) "\x1B[1;34m" << s << rst

#include <iostream>

/* 
 * \brief Function which resets command line colour and font settings 
*/
std::ostream& rst(std::ostream& os);

#endif // UTILITIES_H