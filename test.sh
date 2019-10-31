#!/usr/bin/bash

TEST_DIR=./tests/

clean () {
	rm -rf gnl.res gnl expected.res
}

print_test_type () {
	echo -e "\e[94m==== \e[45m$1\e[49m \e[49m====\e[39m"
}

compile_test () {
	# $1 ~> name of test c source file
	# $2 ~> buffer size
	echo -e "\e[91mBUFFER_SIZE = $2\e[39m"
	gcc get_next_line.c get_next_line_utils.c $TEST_DIR/src/$1 -D BUFFER_SIZE=$2 -o gnl
}

basic_tester () {
	printf "$1: "
	./gnl $TEST_DIR/files/$1 > gnl.res
	diff $TEST_DIR/files/$1 gnl.res 2>/dev/null > /dev/null
	if [[ $? -eq 0 ]];
	then
		echo -e "\e[32mOK\e[39m"
	else
		echo  -e "\e[31mFAIL\e[39m"
		clean
		exit
	fi
}

basic_test () {
	basic_tester one_line
	basic_tester medium_file
	basic_tester medium_plus_file
	basic_tester one_new_line
	basic_tester lot_of_new_line
	basic_tester one_char_per_line
	basic_tester one_char
	basic_tester one_huge_line
}

few_lines_tester () {
	printf "$1: "
	./gnl $TEST_DIR/files/$1 > gnl.res
	head -n 3 $TEST_DIR/files/$1 > expected.res
	diff gnl.res expected.res 2>/dev/null > /dev/null
	if [[ $? -eq 0 ]];
	then
		echo -e "\e[32mOK\e[39m"
	else
		echo  -e "\e[31mFAIL\e[39m"
		clean
		exit
	fi
}

few_lines_test () {
	few_lines_tester medium_file
	few_lines_tester medium_plus_file
	few_lines_tester lot_of_new_line
	few_lines_tester one_char_per_line
}

#########
# BASIC #
#########
print_test_type "BASICS"

# 32
compile_test basic_tests.c 32
basic_test
# 42
compile_test basic_tests.c 42
basic_test
# 1
compile_test basic_tests.c 1
basic_test
# 10000
compile_test basic_tests.c 10000
basic_test
# 9999999
compile_test basic_tests.c 9999999
basic_test

#############
# FEW LINES #
#############
print_test_type "Few Lines"
# 32
compile_test few_lines.c 32
few_lines_test
# 42
compile_test few_lines.c 42
few_lines_test
# 1
compile_test few_lines.c 1
few_lines_test
# 10000
compile_test few_lines.c 10000
few_lines_test
# 9999999
compile_test few_lines.c 9999999
few_lines_test

# CLEAN
clean
