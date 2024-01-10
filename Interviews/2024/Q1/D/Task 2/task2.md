# TLB Cache Emulator

## Task Description

Your task is to implement an emulator for a Translation Lookaside Buffer (TLB) cache with the following characteristics:

- **Fully Associative**: Any virtual address can be mapped to any entry in the cache.
- **Least Recently Used (LRU) Replacement Policy**: The least recently used entry is replaced when the cache is full and a new entry needs to be added.
- **Cache Misses Tracking**: The emulator must provide the number of cache misses that have occurred since its creation.
- **No Manual Eviction**: Entries are never manually evicted from the cache.

### Interface Function

Implement the following interface function to resolve a virtual memory address:

```cpp
std::optional<PhysicalAddress> translateAddress(VirtualAddress vaddr);
```

Note that PhysicalAddress and VirtualAddress are enums representing physical and virtual memory addresses, respectively. They're enumerated types only for the purpose of distinguishing between the two types of addresses:

```cpp
enum class VirtualAddress : uint64_t {};
enum class PhysicalAddress : uint64_t {};
```

### Assumptions

- `VirtualAddress` and `PhysicalAddress` are enums representing virtual and physical memory addresses, respectively.
- The function `walkPageTables(VirtualAddress vaddr)` is available and performs the actual address translation without caching. This function should be used within your implementation when a cache miss occurs.

### Translator Class

Implement the `Translator` class that provides the `translateAddress` method. The class should internally manage a cache of recently accessed virtual-to-physical address translations.

#### Internal Structure

- `CacheEntry`: A structure to hold individual cache entries, including a history iterator and an optional physical address.
- `cache_`: A map from virtual addresses to cache entries.
- `latest_history_`: A list to track the history of accessed virtual addresses for the LRU policy.
- `cache_size_`: The size of the TLB cache.

### Example Usage

```cpp
Translator translator; // Initialize the translator with a specific cache size
auto physicalAddr = translator.translateAddress(virtualAddr);
```

If the virtual address (`virtualAddr`) is in the cache, the corresponding physical address is returned directly. If it is not in the cache, a cache miss occurs, and `walkPageTables` is used to get the physical address.

## Requirements

- Implement the TLB cache as described, adhering to the fully associative nature and LRU replacement policy.
- Ensure that the number of cache misses is tracked accurately.
- Optimize for efficient lookups and updates in the cache.

## Notes

- Focus on writing clean, efficient, and well-structured code.
- Consider edge cases, such as cache overflow and handling of invalid addresses.
- The LRU replacement policy should be correctly implemented to ensure the most recently used entries are retained in the cache.
