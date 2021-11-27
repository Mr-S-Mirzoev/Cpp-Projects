# External_Sort
External sort with C++

## Building

```
cmake -B build

make -C build -j2
```

## Testing

```
./test.sh ./build/external_sort
```

## RAM Usage check

```
valgrind --tool=massif  ./build/external_sort
ms_print ms_print massif.out.*
```
