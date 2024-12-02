#!/bin/bash

cd "$(dirname "${BASH_SOURCE[0]}")" || { echo "Failed to change directory"; exit 1; }

DB_FILE="./db.db"
SCHEMA_FILE="./schema_setup.sql"
DATA_FILE="./data_population.sql"

REQUIRED_TABLES=("PLAN" "DRIVER" "EMPLOYEE" "WAREHOUSE" "INGREDIENT" "RECIPE" "USER" "ADDRESS" "INVOICE")

initialize_database() {
    echo "Creating database schema..."
    sqlite3 "$DB_FILE" < "$SCHEMA_FILE"
    if [ $? -ne 0 ]; then
        echo "Failed to set up the database schema."
        exit 1
    fi

    echo "Populating database with initial data..."
    sqlite3 "$DB_FILE" < "$DATA_FILE"
    if [ $? -ne 0 ]; then
        echo "Failed to populate the database with data."
        exit 1
    fi

    echo "Database initialized successfully with schema and data."
}

if [ ! -f "$DB_FILE" ]; then
    echo "Database file $DB_FILE does not exist. Creating it..."
    initialize_database
else
    # Check for required tables
    missing_tables=()
    for table in "${REQUIRED_TABLES[@]}"; do
        result=$(sqlite3 "$DB_FILE" "SELECT name FROM sqlite_master WHERE type='table' AND name='$table';")
        if [ -z "$result" ]; then
            missing_tables+=("$table")
        fi
    done

    if [ ${#missing_tables[@]} -ne 0 ]; then
        echo "Missing tables detected: ${missing_tables[@]}"
        echo "Re-initializing the database..."
        initialize_database
    else
        echo "All required tables exist. Skipping initialization."
    fi
fi