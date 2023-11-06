#!/bin/bash

# string
out1=$(echo -n "OKOKOKOKO" | sha1sum | cut -f 1 -d " ")
tmp2=$(echo -n "SHA1 \"OKOKOKOKO" | ./rhasher)
line_count=$(echo "$tmp2" | wc -l)
if [ "$line_count" -eq 3 ]; then
    out2=$(echo "$tmp2" | awk 'NR==2 {split($0, arr, " "); print arr[length(arr)]}')
else
    out2=$(echo "$tmp2" | awk 'NR==1 {split($0, arr, " "); print arr[length(arr)]}')
fi
[ "echo $out1" = "echo $out2" ] && echo "Test 1 (SHA1): OK" || echo "Test 1 (SHA1): FAIL"

# file
out1=$(sha1sum ./rhasher.c | cut -f 1 -d " ")
tmp2=$(echo -n "SHA1 ./rhasher.c" | ./rhasher)
line_count=$(echo "$tmp2" | wc -l)
if [ "$line_count" -eq 3 ]; then
    out2=$(echo "$tmp2" | awk 'NR==2 {split($0, arr, " "); print arr[length(arr)]}')
else
    out2=$(echo "$tmp2" | awk 'NR==1 {split($0, arr, " "); print arr[length(arr)]}')
fi
[ "echo $out1" = "echo $out2" ] && echo "Test 2 (SHA1): OK" || echo "Test 2 (SHA1): FAIL"

# string
out1=$(echo -n "OKOKOKOKO" | md5sum | cut -f 1 -d " ")
tmp2=$(echo -n "MD5 \"OKOKOKOKO" | ./rhasher)
line_count=$(echo "$tmp2" | wc -l)
if [ "$line_count" -eq 3 ]; then
    out2=$(echo "$tmp2" | awk 'NR==2 {split($0, arr, " "); print arr[length(arr)]}')
else
    out2=$(echo "$tmp2" | awk 'NR==1 {split($0, arr, " "); print arr[length(arr)]}')
fi
[ "echo $out1" = "echo $out2" ] && echo "Test 3 (MD5): OK" || echo "Test 3 (MD5): FAIL"

# file
out1=$(md5sum ./rhasher.c | cut -f 1 -d " ")
tmp2=$(echo -n "MD5 ./rhasher.c" | ./rhasher)
line_count=$(echo "$tmp2" | wc -l)
if [ "$line_count" -eq 3 ]; then
    out2=$(echo "$tmp2" | awk 'NR==2 {split($0, arr, " "); print arr[length(arr)]}')
else
    out2=$(echo "$tmp2" | awk 'NR==1 {split($0, arr, " "); print arr[length(arr)]}')
fi
[ "echo $out1" = "echo $out2" ] && echo "Test 4 (MD5): OK" || echo "Test 4 (MD5): FAIL"
