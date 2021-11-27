#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Pass the path to executable as an argument"
    exit 1
fi

python3 generate_file.py -o input.txt -l 10000 -q 25000
sort input.txt --output=sorted.txt --parallel=10
$1

SHA_CORRECT=$(sha256sum output.txt --tag | awk '{print $4}')
SHA_PROG=$(sha256sum sorted.txt --tag | awk '{print $4}')

if [[ $SHA_CORRECT == $SHA_PROG ]]
then
    echo "TEST PASSED CORRECTLY"
else
    echo "TEST FAILED:"
    printf "Expected SHA256:\t$SHA_CORRECT\n"
    printf "Real SHA256:\t\t$SHA_CORRECT\n"
fi

