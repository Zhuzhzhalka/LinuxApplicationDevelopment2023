#!/bin/bash

if [ "$#" -eq "0" ]; then
    DELAY=0.0
else
    if [ "$#" -eq "1" ]; then
        DELAY=$1
    else
        echo "Usage: LC_ALL=C ./randomize.sh [DELAY optional]"
        exit 1
    fi
fi

MAX_LINE=0
STDIN=$(cat -)
tput clear
RANDOMS=$(shuf -i 0-"${#STDIN}")

while IFS= read POS; do
    if [ "${STDIN:$POS:1}" != " " ] && [ "${STDIN:$POS:1}" != $'\n' ]; then
        LINE=$(echo $(echo "$STDIN" | cat -A | grep -o -n . | head -n $(($POS + 1)) | tail -n 1 | cut -d: -f1))
        COL=$(($POS - $(echo "$STDIN" | head -n $(($LINE - 1)) | wc -c)))
        if [ "$LINE" -ge "$MAX_LINE" ]; then
            MAX_LINE=$LINE
        fi
        LINE=$(($LINE - 1))
        tput cup $LINE $COL
        echo "${STDIN:$POS:1}"
        tput cup $LINE $COL
        sleep $DELAY
    fi
done <<< "$RANDOMS"

tput cup $(($MAX_LINE)) 0
