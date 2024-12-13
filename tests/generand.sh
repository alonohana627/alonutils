#!/bin/bash

run_test() {
    description=$1
    command=$2
    expected_exit_code=$3
    echo "Running test: $description"
    eval $command &> /dev/null
    actual_exit_code=$?
    if [ $actual_exit_code -eq $expected_exit_code ]; then
        echo "================"
        echo "PASS: $description"
        echo "================"
    else
        echo "================"
        echo "FAIL: $description (Expected: $expected_exit_code, Got: $actual_exit_code)"
        echo "================"
        failed_tests+=("$description")
    fi
}

declare -a failed_tests=()

run_test "Test 1: Successful execution" "$(pwd)/build/generand --min 1 --max 10" 0
run_test "Test 2: No parameters provided" "$(pwd)/build/generand" 0
run_test "Test 3: Unknown argument" "$(pwd)/build/generand --unknown" 1
run_test "Test 4: Error min >= max" "$(pwd)/build/generand --min 10 --max 5" 3
run_test "Test 5: Checking help flag" "$(pwd)/build/generand --help" 2

if [ ${#failed_tests[@]} -ne 0 ]; then
    echo "Failed tests:"
    for test in "${failed_tests[@]}"; do
        echo "- $test"
    done
    echo "Number of failed tests: ${#failed_tests[@]}"
else
    echo "All tests passed!"
fi

exit ${#failed_tests[@]}