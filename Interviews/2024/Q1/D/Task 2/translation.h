#pragma once

#include "types.h"

#include <optional>

/**
 * @brief Convert virtual address to physical address (without caching)
 *
 * @param vaddr Virtual address to convert
 * @return std::optional<PhysicalAddress> a physical address if the page maps to a physical address,
 * std::nullopt if offloaded to disk
 */
std::optional<PhysicalAddress> walkPageTables(VirtualAddress vaddr);
