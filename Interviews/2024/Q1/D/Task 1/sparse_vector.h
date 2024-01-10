#pragma once

#include <map>
#include <vector>

enum class ImplementationType
{
    MapBased,
    VectorBased
};

template <typename T, ImplementationType Impl>
class SparseVector
{
};

#include "sparse_vector_m.impl.h"
#include "sparse_vector_v.impl.h"
