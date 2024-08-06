#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color / Reset

FILENAME=log_unit_test
KO_PREFIX='_'
TEMP_STATUS_FILE=$(mktemp)

truncate -s 0 $FILENAME

for file in maps/*; do
    # Run valgrind and store the exit status of cub3d in a temp file
    output=$(timeout 1s valgrind --leak-check=yes --error-exitcode=10 bash -c "./cub3d '$file'; echo $? > $TEMP_STATUS_FILE" 2>&1)
    val_status=$?
    cub_status=$(<"$TEMP_STATUS_FILE")

    echo "$cub_status"


    # Check for Valgrind errors
    if [ "$val_status" -eq 10 ]; then
        echo -e "${RED}KO $file: leaks${NC}"
        printf "\n============ $file ============\n\n" >> $FILENAME
        printf "%s\n" "$output" >> $FILENAME
        printf "\n=================================================\n" >> $FILENAME

    else
        if [[ "$file" =~ ^$KO_PREFIX ]] && [ "$cub_status" -eq 0 ]; then
            echo -e "${RED}KO $file: should not be a valid map${NC}"
        elif [[ "$file" =~ ^$KO_PREFIX ]] && [ "$cub_status" -ne 0 ]; then
            echo -e "${GREEN}OK $file: not a valid map${NC}"
        elif [[ ! "$file" =~ ^$KO_PREFIX ]] && [ "$cub_status" -eq 0 ]; then
            echo -e "${GREEN}OK $file: valid map!${NC}"
        else
            echo -e "${RED}KO $file: should be a valid map${NC}"
        fi
    fi
done

# Cleanup temporary file
rm -f "$TEMP_STATUS_FILE"
