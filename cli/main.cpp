#include <iostream>
#include <sqlite3.h>
#include <string>

// Callback function to display query results
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for(int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << " = " 
                  << (argv[i] ? argv[i] : "NULL") << "\t";
    }

    std::cout << std::endl;
    return 0;
}

// Function to escape single quotes in strings
std::string EscapeSingleQuotes(const std::string& str)
{
    std::string escaped = str;
    size_t pos = 0;
    while((pos = escaped.find("'", pos)) != std::string::npos)
    {
        escaped.insert(pos, "'");
        pos += 2; // Move past the escaped quote
    }
    return escaped;
}

int main(int argc, char* argv[])
{
    // Initialize database variable 
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // Database name
    std::string db_name = "mydatabase.db";

    // Open SQLite database / creates one if it doesn't exist
    rc = sqlite3_open(db_name.c_str(), &db);

    if(rc || db == nullptr)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db); // Close database if open
        return 1;
    }
    else
    {
        std::cout << "Opened database successfully: " << db_name << std::endl;
    }

    std::string prompt = R"(
    Press 1 to sign up.
    Press 2 to delete your account and all your data.
    Press 3 to [].
    Press 4 to [].
    Press 5 to [].
    Press 6 to enter SQL queries directly.
    )";

    std::cout << prompt << std::endl;

    // Grab the input 
    int n = 0;
    std::cin >> n;
    std::cin.ignore(); // Consume leftover newline

    // Declare variables
    std::string u_first, u_last, u_address, u_email, u_card_name, u_card_address, u_card_exp;
    std::string u_phone, u_card_number;
    int u_card_cvv = 0, u_plan_choice = 0;

    switch(n)
    {
        case 1:
        {
            std::cout << "Thanks for signing up! Please enter the following info as prompted:\n";

            // User info
            std::cout << "First and last name ([FirstName] [LastName]): ";
            std::cin >> u_first >> u_last;
            std::cin.ignore(); // Consume leftover newline

            std::cout << "\nUS address ([Street Address or P.O. Box], [City], [State] [ZIP Code]):\n";
            std::getline(std::cin, u_address);

            std::cout << "\nEmail: ";
            std::cin >> u_email;
            std::cin.ignore();

            std::cout << "\nPhone (no spaces or parentheses - ex: 1234567890): ";
            std::cin >> u_phone;
            std::cin.ignore();

            // User payment info
            std::cout << "\nYou will now enter your payment info:\n";
            std::cout << "\nPlease enter your card # (no spaces or symbols between numbers): ";
            std::cin >> u_card_number;
            std::cin.ignore();

            std::cout << "\nPlease enter the name on the card:\n";
            std::getline(std::cin, u_card_name);

            std::cout << "\nUS billing address ([Street Address or P.O. Box], [City], [State] [ZIP Code]):\n";
            std::getline(std::cin, u_card_address);

            std::cout << "\nExpiration date ([Month]/[Year - 4 digits] - ex: 10/2024): ";
            std::cin >> u_card_exp;
            std::cin.ignore();

            std::cout << "\nCVV: ";
            std::cin >> u_card_cvv;
            std::cin.ignore();

            // Display available plans
            std::cout << "\nHere are the following plan options:\n";
            rc = sqlite3_exec(db, "SELECT PlanID, Name, Price, Calories, Frequency, NumberOfMeals FROM PLAN;", callback, 0, &zErrMsg);

            if(rc != SQLITE_OK)
            {
                std::cerr << "SQL error: " << zErrMsg << std::endl;
                sqlite3_free(zErrMsg);
                sqlite3_close(db);
                return 1;
            }
            else
            {
                std::cout << "Available plans displayed above.\n";
            }

            std::cout << "Enter the Plan ID you choose: ";
            std::cin >> u_plan_choice;
            std::cin.ignore();

            // Escape single quotes in user inputs
            u_first = EscapeSingleQuotes(u_first);
            u_last = EscapeSingleQuotes(u_last);
            u_address = EscapeSingleQuotes(u_address);
            u_email = EscapeSingleQuotes(u_email);
            u_card_name = EscapeSingleQuotes(u_card_name);
            u_card_address = EscapeSingleQuotes(u_card_address);
            u_card_exp = EscapeSingleQuotes(u_card_exp);

            // Build the SQL INSERT statement using sqlite3_mprintf to prevent SQL injection
            char* sql_insert_user = sqlite3_mprintf(
                "INSERT INTO User (FirstName, LastName, Address, Email, Phone, CardNumber, CardName, CardAddress, CardExp, CardCVV, PlanID) "
                "VALUES ('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', %d, %d);",
                u_first.c_str(), u_last.c_str(), u_address.c_str(), u_email.c_str(), u_phone.c_str(),
                u_card_number.c_str(), u_card_name.c_str(), u_card_address.c_str(), u_card_exp.c_str(),
                u_card_cvv, u_plan_choice
            );

            // Execute the SQL statement
            rc = sqlite3_exec(db, sql_insert_user, nullptr, 0, &zErrMsg);
            if(rc != SQLITE_OK)
            {
                std::cerr << "SQL error: " << zErrMsg << std::endl;
                sqlite3_free(zErrMsg);
            }
            else
            {
                std::cout << "New user added successfully.\n";
            }

            // Free the memory allocated by sqlite3_mprintf
            sqlite3_free(sql_insert_user);
            break;
        }
        case 2:
            // Implementation for deleting account and data
            std::cout << "Feature not implemented yet.\n";
            break;
        case 3:
            // Implementation for option 3
            std::cout << "Feature not implemented yet.\n";
            break;
        case 4:
            // Implementation for option 4
            std::cout << "Feature not implemented yet.\n";
            break;
        case 5:
            // Implementation for option 5
            std::cout << "Feature not implemented yet.\n";
            break;
        case 6:
        {
            std::cout << "Enter SQL queries to execute. Type 'exit' to quit.\n";
            while(true)
            {
                std::cout << "SQL> ";
                std::string sql;
                std::getline(std::cin, sql);

                if(sql.empty()) { continue; }

                if(sql == "exit") { break; }

                // Execute SQL statement
                rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
                if(rc != SQLITE_OK)
                {
                    std::cerr << "SQL error: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                }
                else
                {
                    std::cout << "Operation executed successfully.\n";
                }
            }
            break;
        }
        default:
            std::cout << "You entered an invalid choice. Please rerun and try again.\n";
            sqlite3_close(db);
            return 1;
    }

    // Close SQLite database
    sqlite3_close(db);
    return 0;
}
