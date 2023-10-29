TEST_COUNTER=1

echo "Starting tests..."

# Test 1
echo "something${TEST_COUNTER}" > infile
strace -e trace=openat -e fault=openat:error=EACCESS:when=3 ./move infile outfile > /dev/null 2>&1
test $? -eq 1 && test -f infile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 2
echo "something${TEST_COUNTER}" > infile
strace -e trace=openat -e fault=openat:error=EROFS:when=4 ./move infile outfile > /dev/null 2>&1
test $? -eq 1 && test -f infile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 3
cat move.c > infile
strace -e trace=read -e fault=read:error=EIO:when=4 ./move infile outfile > /dev/null 2>&1
test $? -eq 1 && test -f infile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 4
echo "something${TEST_COUNTER}" > infile
strace -e trace=read -e fault=read:error=EINTR:when=2 ./move infile outfile > /dev/null 2>&1
test $? -eq 1 && test -f infile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 5
echo "something${TEST_COUNTER}" > infile
strace -e trace=write -e fault=write:error=EACCESS:when=1 ./move infile outfile > /dev/null 2>&1
test $? -eq 1 && test -f infile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 6
echo "something${TEST_COUNTER}" > infile
strace -e trace=close -e fault=close:error=EINTR:when=3,4 ./move infile outfile > /dev/null 2>&1
test $? -eq 1 && test -f infile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 7 (all is OK)
echo "something${TEST_COUNTER}" > infile
./move infile outfile > /dev/null 2>&1
test $? -eq 0 && test ! -f infile && test -f outfile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 8 (dynlib - PROTECT)
echo "something${TEST_COUNTER}" > infilePROTECT
LD_PRELOAD=`pwd`/lib_remove.so ./move infilePROTECT outfile > /dev/null 2>&1
test $? -eq 0 && test -f infilePROTECT && test -f outfile || echo "Test ${TEST_COUNTER} failed."
rm -f infilePROTECT outfile
TEST_COUNTER=$((TEST_COUNTER + 1))

# Test 9 (dynlib - no PROTECT)
echo "something${TEST_COUNTER}" > infile
LD_PRELOAD=`pwd`/lib_remove.so ./move infile outfile > /dev/null 2>&1
test $? -eq 0 && test ! -f infile && test -f outfile || echo "Test ${TEST_COUNTER} failed."
rm -f infile outfile

echo "Completed ${TEST_COUNTER} tests"
