#!/bin/bash

# Function to validate UUID v4
validate_uuid_v4() {
    local uuid=$1
    # UUID v4 regex pattern
    local uuid_pattern='^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-4[0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$'

    if [[ $uuid =~ $uuid_pattern ]]; then
        return 0  # Valid UUID v4
    else
        return 1  # Invalid UUID v4
    fi
}

# Test cases
declare -a tests=(
    $(./build/uuid)
    $(./build/uuid)
    $(./build/uuid)
    $(./build/uuid)
    $(./build/uuid)
    $(./build/uuid)
    $(./build/uuid)
    $(./build/uuid)
    $(./build/uuid)
)

expected_exit_code=0  # Expected for valid UUID v4
failed_tests=()

for uuid in "${tests[@]}"; do
    description="Checking UUID: $uuid"
    validate_uuid_v4 "$uuid"
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
done

# Summary
if [ ${#failed_tests[@]} -eq 0 ]; then
    echo "All tests passed!"
else
    echo "Some tests failed:"
    for test in "${failed_tests[@]}"; do
        echo "$test"
    done
fi
