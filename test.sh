#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Pass the path to executable as an argument"
    exit 1
fi

mkdir -p ${TEST_DIR}
python3 generate_file.py -o ${TEST_DIR}/input.txt -l 10000 -q 25000
sort ${TEST_DIR}/input.txt --output=${TEST_DIR}/sorted.txt --parallel=10
$1
mv output.txt ${TEST_DIR}

SHA_CORRECT=$(sha256sum ${TEST_DIR}/output.txt --tag | awk '{print $4}')
SHA_PROG=$(sha256sum ${TEST_DIR}/sorted.txt --tag | awk '{print $4}')

if [[ $SHA_CORRECT == $SHA_PROG ]]
then
    echo "TEST PASSED CORRECTLY"
    exit 0
else
    echo "TEST FAILED:"
    printf "Expected SHA256:\t$SHA_CORRECT\n"
    printf "Real SHA256:\t\t$SHA_PROG\n"
    exit 1
fi

