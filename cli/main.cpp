#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cstdlib>
#include <ctime>

// Callback function to display query results
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{ // callback //
    for(int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << " = " 
                  << (argv[i] ? argv[i] : "NULL") << "\t";
    }

    std::cout << std::endl;
    return 0;
} // callback //

// Function to escape single quotes in strings (due to SQL syntax requirements)
std::string EscapeSingleQuotes(const std::string& str)
{ // EscapeSingleQuotes //
    std::string escaped = str;
    size_t pos = 0;
    while((pos = escaped.find("'", pos)) != std::string::npos)
    {
        escaped.insert(pos, "'");
        pos += 2; // Move past the escaped quote
    }
    return escaped;
} // EscapeSingleQuotes //

int main(int argc, char* argv[])
{ // main //
    // init sqlite3 db struct, error message, and return code
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // Seed the random number generator (used for user ID generation)
    srand(static_cast<unsigned int>(time(nullptr)));

    // Database file name - will be created if it doesn't exist
    std::string db_name = "mydatabase.db";

    // Execute the setup.sh file (populates the database with the schema / tables and then inserts data)
    std::string setup_command = "sh setup.sh";
    std::cout << "Executing \"" << setup_command << "\" to init the database." << std::endl;
    system(setup_command.c_str());
    std::cout << "Opening database \"" << db_name << "\" (just initialized above)." << std::endl;
    
    // Open SQLite database / creates one if it doesn't exist
    rc = sqlite3_open(db_name.c_str(), &db);

    if(rc || db == nullptr)
    { // i // 
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db); // Close database if open
        return 1;
    } // i //
    else { std::cout << "Opened database successfully: " << db_name << std::endl; }

    // The options to prompt the user with ( Team members: please write whatever you will do and then implement it below )
    std::string prompt = R"(
    Press 1 to sign up.
    Press 2 to delete your account and all your data.
    Press 3 to [].
    Press 4 to [].
    Press 5 to [].
    Press 6 to enter SQL queries directly.
    )";

    std::cout << prompt << std::endl; // outputs the prompt to the console

    // Grab the choice from user 
    int n = 0;
    std::cin >> n;
    std::cin.ignore(); // Consume leftover newline

    // init the variables you will use to capture your input for your case here:
    // Case 1 Variables // 
    std::string u_first, u_last, u_address, u_email, u_card_name, u_card_address, u_card_exp;
    std::string u_phone, u_card_number;
    int u_card_cvv = 0, u_plan_choice = 0;
    // Case 1 Variables //

    // Case 2 Variables //

    // Case 2 Variables //

    // Case 3 Variables //

    // Case 3 Variables //

    // Case 4 Variables //

    // Case 4 Variables //

    // Case 5 Variables // 

    // Case 5 Variables //


    switch(n)
    { // switch //
        case 1:
        { // case 1 //
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
            std::cout << "\nYou wbackend4402/src/main/resources/schema.sqlill now enter your payment info:\n";
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

            // Combine payment info
            std::string u_payment_info = u_card_number + "," + u_card_name + "," + u_card_address + "," + u_card_exp + "," + std::to_string(u_card_cvv);

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

            // Generate a unique random User ID
            int user_id;
            bool is_unique = false;
            int attempts = 0;
            const int MAX_ATTEMPTS = 1000;

            while(!is_unique && attempts < MAX_ATTEMPTS)
            {
                user_id = rand() % 9000 + 1000; // Generates a number between 1000 and 9999
                std::string check_query = "SELECT 1 FROM USER_TABLE WHERE UserID = " + std::to_string(user_id) + " LIMIT 1;";
                
                bool exists = false;

                // Callback to set exists flag
                auto exists_callback = [](void* data, int argc, char** argv, char** azColName) -> int {
                    bool* exists_ptr = static_cast<bool*>(data);
                    *exists_ptr = true;
                    return 0;
                };

                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);
                if(rc != SQLITE_OK)
                {
                    std::cerr << "SQL error during UserID check: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                    break;
                }

                if(!exists)
                {
                    is_unique = true;
                }

                attempts++;
            }

            if(!is_unique)
            {
                std::cerr << "Failed to generate a unique User ID after " << MAX_ATTEMPTS << " attempts." << std::endl;
                sqlite3_close(db);
                return 1;
            }

            std::cout << "Assigned User ID: " << user_id << std::endl;

            // Build the SQL INSERT statement using sqlite3_mprintf to prevent SQL injection
            char* sql_insert_user = sqlite3_mprintf(
                "INSERT INTO USER_TABLE (UserID, FirstName, LastName, Address, Email, PhoneNumber, PaymentInfo, PlanID) "
                "VALUES (%d, '%q', '%q', '%q', '%q', '%q', '%q', %d);",
                user_id,
                u_first.c_str(), u_last.c_str(), u_address.c_str(), u_email.c_str(), u_phone.c_str(),
                u_payment_info.c_str(),
                u_plan_choice
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
                std::cout << "New user added successfully with User ID: " << user_id << ".\n";
            }

            // Free the memory allocated by sqlite3_mprintf
            sqlite3_free(sql_insert_user);
            break;
        } // case 1 //
        case 2:
        { // case 2 //
            // Implementation for deleting account and data
            std::cout << "Feature not implemented yet.\n";
            break;
        } // case 2 //
        case 3:
        { // case 3 //
            // Implementation for option 3
            std::cout << "Feature not implemented yet.\n";
            break;
        } // case 3 //
        case 4:
        { // case 4 //
            // Implementation for option 4
            std::cout << "Feature not implemented yet.\n";
            break;
        } // case 4 //
        case 5:
        { // case 5 //
            // Implementation for option 5
            std::cout << "Feature not implemented yet.\n";
            break;
        } // case 5 //
        case 6:
        { // case 6 //
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
        } // case 6 //
        default:
        { // default //
            std::cout << "You entered an invalid choice. Please rerun and try again.\n";
            sqlite3_close(db);
            return 1;
        } // default //
    }

    // Close SQLite database
    sqlite3_close(db);
    return 0;
}
