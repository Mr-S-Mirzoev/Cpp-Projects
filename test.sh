#!/bin/bash -e

QUANTITY=25000
LINE_Q=10000

while getopts q:d:l:e:h option
do
    case "${option}"
    in
        q) QUANTITY=${OPTARG};;
        d) DIR=${OPTARG};;
        l) LINE_Q=${OPTARG};;
        e) EXECUTABLE=${OPTARG};;
        h) SHOW_HELP=1;;
    esac
done

HELP_EXIT_STATUS=0
if [[ "$DIR" == "" || "$EXECUTABLE" == "" ]]; then
    SHOW_HELP="1"
    HELP_EXIT_STATUS=1
fi

if [[ "$SHOW_HELP" == "1" ]]; then
    echo "Usage ./test.sh [ARGS]"
    printf "\t-h\t\t\tshow help\n"
    printf "\t-e\t[MANDATORY]\texecutable which implements external sorting\n"
    printf "\t-d\t[MANDATORY]\ttest directory path\n"
    printf "\t-q\t[OPTIONAL]\tquantity of lines in generated file\n"
    printf "\t-l\t[OPTIONAL]\tmax length\n"
    exit ${HELP_EXIT_STATUS}
fi

DIR=$(echo ${DIR} | sed 's:/*$::')
export TEST_DIR=${DIR}

mkdir -p ${TEST_DIR}
python3 generate_file.py -o ${TEST_DIR}/input.txt -q "$QUANTITY" -l "$LINE_Q"
echo "Sorting $(du -sh ./output_dir/input.txt)"
sort ${TEST_DIR}/input.txt --output=${TEST_DIR}/sorted.txt --parallel=10
${EXECUTABLE}

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
