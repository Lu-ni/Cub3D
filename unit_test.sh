#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

FILENAME=log_unit_test
KO_PREFIX='_'

TEST_PASSED=0
NBR_TESTS=0

args=("$@")

touch $FILENAME
truncate -s 0 $FILENAME

test_leaks() {
    echo "Testing leaks"
    for file in maps/*/*; do
        NBR_TESTS=$((NBR_TESTS+1))
        output=$(timeout 0.5s valgrind --leak-check=yes --error-exitcode=10 ./cub3d "$file" >> $FILENAME 2>&1)
        val_status=$?

        if [ "$val_status" -eq 10 ]; then
            echo -e "${RED}KO $file: leaks${NC}"
            printf "\n============ $file ============\n\n" >> $FILENAME
            printf "\n=================================================\n" >> $FILENAME
        else
            TEST_PASSED=$((TEST_PASSED+1))
            echo -e "${GREEN}OK $file${NC}"
        fi
    done
}

test_valid_maps() {
    echo "Testing valid maps"
    for file in maps/valid/*; do
        NBR_TESTS=$((NBR_TESTS+1))
        output=$(timeout 0.2s ./cub3d "$file" 2>&1)
        cub_status=$?
        if [[ "$cub_status" -eq 124 ]]; then
            echo -e "${GREEN}OK $file${NC}"
            TEST_PASSED=$((TEST_PASSED+1))
        else
            echo -e "${RED}KO $file should be a valid map${NC}"
        fi
    done
}

test_invalid_maps() {
    echo "Testing invalid maps"
    for file in maps/invalid/*; do
        NBR_TESTS=$((NBR_TESTS+1))
        output=$(timeout 0.2s ./cub3d "$file" 2>&1)
        cub_status=$?
        if [[ "$cub_status" -ne 124   ]]; then
            TEST_PASSED=$((TEST_PASSED+1))
            echo -e "${GREEN}OK $file${NC}"
        else
            SUCCESS=false
            echo -e "${RED}KO $file should not be a valid map${NC}"
        fi
    done
}


run_all() {
    test_leaks
    test_valid_maps
    test_invalid_maps
}


if [ -z "$1" ]; then
        run_all
        exit 0
fi

case "$1" in
    leaks)
        test_leaks
        ;;
    valid)
        test_valid_maps
        ;;
    invalid)
        test_invalid_maps
        ;;
    all)
        run_all
        ;;
    *)
        echo "Usage: $0 { all | leaks | valid | invalid }"
        ;;
esac

echo Test passed: $TEST_PASSED / $NBR_TESTS


if [ "$TEST_PASSED" -eq "$NBR_TESTS" ]; then
    echo -e "${GREEN}SUCCESS${NC}"
    exit 0
else
    echo -e "${RED}FAILURE${NC}"
    exit 1
fi
