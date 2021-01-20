#ifndef UTILITIES_H
#define UTILITIES_H

template <class T>
T thread_safe_rand(T low, T high);

template<> float thread_safe_rand<float>(float low, float high);

template<> double thread_safe_rand<double>(double low, double high);

#endif //UTILITIES_H
