#include "translation.h"

#include <unordered_map>

static constexpr auto PAGE_SIZE_BITS = 12;
static constexpr auto PAGE_SIZE = 1 << PAGE_SIZE_BITS;

// Mock implementation of the translation function
std::optional<PhysicalAddress> walkPageTables(VirtualAddress vaddr)
{
    // Mock implementation that simply returns an incremented value or std::nullopt
    static std::unordered_map<VirtualAddress, PhysicalAddress> pageTable;
    auto it = pageTable.find(vaddr);
    if (it != pageTable.end())
    {
        return it->second;
    }

    // Example transformation: simply cast the virtual address to physical address
    // For testing, let's say if the virtual address's pageId is a multiple of 3, it's offloaded to
    // disk
    auto address_to_transform = static_cast<uint64_t>(vaddr);

    auto pageOffset = address_to_transform % PAGE_SIZE;
    auto pageId = address_to_transform >> PAGE_SIZE_BITS;

    // Return nullopt for some predefined virtual addresses to simulate offloaded pages
    if (pageId % 3 == 0)
    {
        return std::nullopt;
    }

    // Mock translation
    std::uint64_t paddr_val = (pageId + 3) * PAGE_SIZE + pageOffset;
    PhysicalAddress paddr{paddr_val};
    pageTable[vaddr] = paddr;
    return paddr;
}