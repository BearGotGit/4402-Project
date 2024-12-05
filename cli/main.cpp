
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cstdlib>
#include <cstdio> // for replacing text input in tests
#include <ctime>

// Callback function to display query results

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{ // callback //
    for (int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << " = "
                  << (argv[i] ? argv[i] : "NULL") << "\t";
    }

    std::cout << std::endl;
    return 0;
} // callback //

// Callback to set exists flag
auto exists_callback = [](void *data, int argc, char **argv, char **azColName) -> int
{
    bool *exists_ptr = static_cast<bool *>(data);
    *exists_ptr = true;
    return 0;
};

// Function to escape single quotes in strings (due to SQL syntax requirements)

std::string EscapeSingleQuotes(const std::string &str)
{ // EscapeSingleQuotes //
    std::string escaped = str;
    size_t pos = 0;
    while ((pos = escaped.find("'", pos)) != std::string::npos)
    {
        escaped.insert(pos, "'");
        pos += 2; // Move past the escaped quote
    }
    return escaped;
} // EscapeSingleQuotes //

int main(int argc, char *argv[])

{ // main //

    // TEST //
    // for your test case, uncomment the line below and enter the name of your case file. Also, run 'rm -rf db.db' before running your test

    // freopen("case1_test.txt", "r", stdin); // replaces input from console with input from test case file
    // freopen("case2_test.txt", "r", stdin);
    // freopen("case3_test.txt", "r", stdin);
    // freopen("case4_test.txt", "r", stdin);
    // freopen("case5_test.txt", "r", stdin);
    // TEST //

    // Initialize sqlite3 db struct, error message, and return code
    sqlite3 *db;
    char *zErrMsg = 0;

    int rc;

    // Seed the random number generator (used for user ID generation)
    srand(static_cast<unsigned int>(time(nullptr)));

    // Database file name - will be created if it doesn't exist
    std::string db_name = "db.db";

    // Execute the setup.sh file (populates the database with the schema/tables and then inserts data)
    std::string setup_command = "sh setup.sh";
    std::cout << "Executing \"" << setup_command << "\" to init the database." << std::endl;
    system(setup_command.c_str());
    std::cout << "Opening database \"" << db_name << "\" (just initialized above)." << std::endl;

    // Open SQLite database / creates one if it doesn't exist
    rc = sqlite3_open(db_name.c_str(), &db);

    if (rc || db == nullptr)

    { // if //
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db); // Close database if open
        return 1;
    } // if //

    else
    {
        std::cout << "Opened database successfully: " << db_name << std::endl;
    }

    while (true)
    { // while //
        // The options to prompt the user with ( Team members: please write whatever you will do and then implement it below )
        std::string prompt =
            R"(
Press 0 to exit the program [done - Zach].
Press 1 to sign up [done - Zach].
Press 2 to delete your account and all your data [done - Zach].
Press 3 to change or cancel your subscription [in progress - Bayla].
Press 4 to sign up to be a driver [done - josh].
Press 5 to [].
Press 6 to enter SQL queries directly [done - Zach].
)";

        std::cout << prompt << std::endl; // Outputs the prompt to the console

        int n = -1;
        std::cin >> n;
        std::cin.ignore(); // Consume leftover newline

        // Initialize the variables you will use to capture your input for your case here:
        // Case 1 Variables //
        std::string u_first, u_last, u_address, u_email, u_card_name, u_card_address, u_card_exp;
        std::string u_phone, u_card_number;
        int u_card_cvv = 0, u_plan_choice = 0;
        std::string u_password, u_password_confirm;
        // Case 1 Variables //

        // Case 2 Variables //
        std::string remove_by_prompt =
            R"(
Press 1 to remove by email.
Press 2 to remove by phone.
Press 3 to remove by address.
Press 4 to remove by your user ID.
)";
        int r = -1, r_id = -1;
        std::string r_email, r_phone, r_address;
        // Case 2 Variables //

        // Case 3 Variables //

        // will use variable u_email and u_password to verify account giving you access to change your subscription/cancel
        std::string edit_subscription =
            R"(
Press 1 to change subscription.
Press 2 to cancel subscription.
)";
        std::string identify_user_for_subscription = R"(
Press 1 to indentify by your email.
Press 2 to indentify by your phone number.
Press 3 to indentify by your User ID.
)";

        std::string remove_or_update_subscription_prompt = R"(
Press 0 to remove your subscription.
Or press the subscription number you would like to change to.
)";

        std::string u_plan; // the user plan they chose when they signed up
        int u_plan_id, u_plan_subscription_choice;

        // Case 3 Variables //

        // Case 4 Variables //

        std::string d_first, d_last;
        int d_zip;
        float d_rate, d_tips, d_miles;

        // Case 4 Variables //
        // Case 4 Variables //

        // Case 5 Variables //
        // Case 5 Variables //

        switch (n)
        {       // switch //
        case 0: // EXIT PROGRAM
        {       // case 0 //
            std::cout << "Exiting program." << std::endl;
            sqlite3_close(db);
            return 0;
        } // case 0 //

        case 1: // SIGN UP USER
        {       // case 1 //
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

            std::cout << "\nPassword: ";
            std::cin >> u_password;
            std::cin.ignore();
            std::cout << "\nConfirm password: ";
            std::cin >> u_password_confirm;
            std::cin.ignore();

            if (u_password != u_password_confirm)
            { // if //
                std::cout << "Passwords do not match. Please rerun and try again.\n";
                break;
            } // if //

            // manually free / delete u_password_confim for security reasons
            u_password_confirm.clear();
            u_password_confirm.shrink_to_fit();

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

            // Combine payment info
            std::string u_payment_info = u_card_number + "," + u_card_name + "," + u_card_address + "," + u_card_exp + "," + std::to_string(u_card_cvv);

            // Display available plans
            std::cout << "\nHere are the following plan options:\n";
            rc = sqlite3_exec(db, "SELECT PlanID, Name, Price, Calories, Frequency, NumberOfMeals FROM PLAN;", callback, 0, &zErrMsg);

            if (rc != SQLITE_OK)
            { // if //
                std::cerr << "SQL error: " << zErrMsg << std::endl;
                sqlite3_free(zErrMsg);
                sqlite3_close(db);
                return 1;
            } // if //
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

            while (!is_unique && attempts < MAX_ATTEMPTS)
            {                                   // while //
                user_id = rand() % 9000 + 1000; // Generates a number between 1000 and 9999
                std::string check_query = "SELECT 1 FROM USER WHERE UserID = " + std::to_string(user_id) + " LIMIT 1;";

                bool exists = false;

                // Callback to set exists flag
                auto exists_callback = [](void *data, int argc, char **argv, char **azColName) -> int
                {
                    bool *exists_ptr = static_cast<bool *>(data);
                    *exists_ptr = true;
                    return 0;
                };

                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);
                if (rc != SQLITE_OK)
                { // if //
                    std::cerr << "SQL error during UserID check: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                    break;
                } // if //

                if (!exists)
                {
                    is_unique = true;
                }

                attempts++;
            } // while //

            if (!is_unique)
            { // if //
                std::cerr << "Failed to generate a unique User ID after " << MAX_ATTEMPTS << " attempts." << std::endl;
                sqlite3_close(db);
                return 1;
            } // if //

            std::cout << "Assigned User ID: " << user_id << std::endl;

            // Build the SQL INSERT statement using sqlite3_mprintf to prevent SQL injection
            char *sql_insert_user = sqlite3_mprintf(
                "INSERT INTO USER (UserID, FirstName, LastName, Address, Email, Phone, PaymentInfo, PlanID, Password) "
                "VALUES (%d, '%q', '%q', '%q', '%q', '%q', '%q', %d, '%q');",
                user_id,
                u_first.c_str(), u_last.c_str(), u_address.c_str(), u_email.c_str(), u_phone.c_str(),
                u_payment_info.c_str(),
                u_plan_choice,
                u_password.c_str());

            // Execute the SQL statement
            rc = sqlite3_exec(db, sql_insert_user, nullptr, 0, &zErrMsg);
            if (rc != SQLITE_OK)
            { // if //
                std::cerr << "SQL error: " << zErrMsg << std::endl;
                sqlite3_free(zErrMsg);
            } // if //
            else
            {
                std::cout << "New user added successfully with User ID: " << user_id << ".\n";
            }

            // Free the memory allocated by sqlite3_mprintf
            sqlite3_free(sql_insert_user);
            break;
        } // case 1 //

        case 2: // REMOVE A USER
        {       // case 2 //
            // prompt and get the choice
            std::cout << remove_by_prompt << std::endl;
            std::cin >> r;
            std::cin.ignore();

            switch (r)
            { // s //
            case 1:
            { // case 1 //
                std::cout << "Enter the email of the user you wish to remove: ";
                std::cin >> r_email;
                std::cin.ignore();

                // Escape single quotes in user inputs
                r_email = EscapeSingleQuotes(r_email);

                // Check if the email even exists
                std::string check_query = "SELECT 1 FROM USER WHERE Email = '" + r_email + "' LIMIT 1;";
                bool exists = false;

                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);

                if (!exists)
                {
                    std::cout << "Email does not exist. Please rerun and try again.\n";
                    break;
                }

                rc = sqlite3_exec(db, ("DELETE FROM USER WHERE Email = '" + r_email + "';").c_str(), callback, 0, &zErrMsg);
                if (rc != SQLITE_OK)
                { // i //
                    std::cerr << "SQL error: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                } // i //
                else
                {
                    std::cout << "User removed successfully.\n";
                }
                break;
            } // case 1 //
            case 2:
            { // case 2 //
                std::cout << "Enter the phone number of the user you wish to remove: ";
                std::cin >> r_phone;
                std::cin.ignore();

                // Escape single quotes in user inputs
                r_phone = EscapeSingleQuotes(r_phone);

                // Check if the phone even exists
                std::string check_query = "SELECT 1 FROM USER WHERE Phone = '" + r_phone + "' LIMIT 1;";
                bool exists = false;

                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);

                if (!exists)
                {
                    std::cout << "Phone does not exist. Please rerun and try again.\n";
                    break;
                }

                rc = sqlite3_exec(db, ("DELETE FROM USER WHERE Phone = '" + r_phone + "';").c_str(), callback, 0, &zErrMsg);
                if (rc != SQLITE_OK)
                { // i //
                    std::cerr << "SQL error: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                } // i //
                else
                {
                    std::cout << "User removed successfully.\n";
                }
                break;
            } // case 2 //
            case 3:
            { // case 3 //
                std::cout << "Enter the address of the user you wish to remove: ";
                std::cin >> r_address;
                std::cin.ignore();

                // Escape single quotes in user inputs
                r_address = EscapeSingleQuotes(r_address);

                // Check if the address even exists
                std::string check_query = "SELECT 1 FROM USER WHERE Address = '" + r_address + "' LIMIT 1;";
                bool exists = false;
                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);

                if (!exists)
                {
                    std::cout << "Address does not exist. Please rerun and try again.\n";
                    break;
                }

                // Assuming address exists, now delete the user
                rc = sqlite3_exec(db, ("DELETE FROM USER WHERE Address = '" + r_address + "';").c_str(), callback, 0, &zErrMsg);
                if (rc != SQLITE_OK)
                { // if //
                    std::cerr << "SQL error: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                } // i //
                else
                {
                    std::cout << "User removed successfully.\n";
                }
                break;
            } // case 3 //
            case 4:
            { // case 4 //
                std::cout << "Enter the User ID of the user you wish to remove: ";
                std::cin >> r_id;
                std::cin.ignore();

                // Check if the User ID even exists
                std::string check_query = "SELECT 1 FROM USER WHERE UserID = " + std::to_string(r_id) + " LIMIT 1;";
                bool exists = false;
                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);

                if (!exists)
                {
                    std::cout << "User ID does not exist. Please rerun and try again.\n";
                    break;
                }

                // Assuming the user ID does exist...
                rc = sqlite3_exec(db, ("DELETE FROM USER WHERE UserID = " + std::to_string(r_id) + ";").c_str(), callback, 0, &zErrMsg);
                if (rc != SQLITE_OK)
                { // if //
                    std::cerr << "SQL error: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                } // i //
                else
                {
                    std::cout << "User removed successfully.\n";
                }
                break;
            } // case 4 //
            default:
            { // default //
                std::cout << "You entered an invalid choice. Please rerun and try again.\n";
                break;
            } // default //
            } // s //
            break;
        } // case 2 //
        case 3: // CHANGE OR EDIT THE SUBSCRIPTION
        {       // case 3 //
            // prompt user to choose first how to idenntify themselves
            std::cout << identify_user_for_subscription << std::endl;
            std::cin >> r;
            std::cin.ignore();

            // Identify the user
            switch (r)
            {       // s //
            case 1: // BY EMAIL
            {       // case 1 //
                std::cout << "Enter the email of the user you wish to change or edit the subscription for: ";
                std::cin >> u_email;
                std::cin.ignore(); // ignore / consume the leftover newline character

                // Escape single quotes in user inputs
                u_email = EscapeSingleQuotes(u_email);

                // Check if the email even exists
                std::string check_query = "SELECT 1 FROM USER WHERE Email = '" + u_email + "' LIMIT 1;";
                bool exists = false;
                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);

                if (!exists)
                {
                    std::cout << "Email does not exist. Please rerun and try again.\n";
                    break;
                }

                // output all the plans
                std::cout << "Here are the following plan options:\n";
                rc = sqlite3_exec(db, "SELECT PlanID, Name, Price, Calories, Frequency, NumberOfMeals FROM PLAN;", callback, 0, &zErrMsg);
                std::cout << "\nYour current plan is: \n";

                // Get the users current plan
                std::string get_plan_query = "SELECT PlanID FROM PLAN WHERE PlanID = (SELECT PlanID FROM USER WHERE Email = '" + u_email + "');";
                rc = sqlite3_exec(db, get_plan_query.c_str(), callback, 0, &zErrMsg);

                // Prompt user
                std::cout << remove_or_update_subscription_prompt << std::endl;

                std::cin >> u_plan_subscription_choice;

                if (u_plan_subscription_choice == 0)
                {
                    std::string remove_query = "DELETE FROM USER WHERE Email = '" + u_email + "';";
                    rc = sqlite3_exec(db, remove_query.c_str(), callback, 0, &zErrMsg);
                    if (rc != SQLITE_OK)
                    {
                        std::cerr << "SQL error: " << zErrMsg << std::endl;
                        sqlite3_free(zErrMsg);
                    }
                    else
                    {
                        std::cout << "Subscription removed successfully.\n";
                    }
                }
                else
                {
                    // update the subscription
                    std::string update_query = "UPDATE USER SET PlanID = " + std::to_string(u_plan_subscription_choice) + " WHERE Email = '" + u_email + "';";
                    rc = sqlite3_exec(db, update_query.c_str(), callback, 0, &zErrMsg);
                    if (rc != SQLITE_OK)
                    {
                        std::cerr << "SQL error: " << zErrMsg << std::endl;
                        sqlite3_free(zErrMsg);
                    }
                    else
                    {
                        std::cout << "Subscription updated successfully.\n";
                    }
                }

                break;
            } // case 1 //
            case 2: // IDENTIFY USER BY PHONE NUMBER
            {       // case 2 //

                break;
            } // case 2 //
            case 3: // IDENTIFY USER BY USER ID
            {       // case 4 //
                break;
            } // case 4 //
            default:
            { // default //
                std::cout << "You entered an invalid choice. Please rerun and try again.\n";
                break;
            } // default //
            } // s //

            break;
        } // case 3 //
        case 4:
        { // case 4 //
            // Implementation for option 4
            std::cout << "First and last name ([FirstName] [LastName]): ";
            std::cin >> d_first >> d_last;
            std::cin.ignore();

            std::cout << "Zipcode: ";
            std::cin >> d_zip;

            std::cout << "Enter starting rate per mile: ";
            std::cin >> d_rate;

            d_tips = 0.00; // initialize starting tips and miles to zero
            d_miles = 0.00;

            // Escape single quotes in user inputs
            d_first = EscapeSingleQuotes(d_first);
            d_last = EscapeSingleQuotes(d_last);

            // Generate a unique random User ID
            int driver_id;
            bool is_unique = false;
            int attempts = 0;
            const int MAX_ATTEMPTS = 1000;

            while (!is_unique && attempts < MAX_ATTEMPTS)
            {                                     // while //
                driver_id = rand() % 9000 + 1000; // Generates a number between 1000 and 9999
                std::string check_query = "SELECT 1 FROM DRIVER WHERE DriverID = " + std::to_string(driver_id) + " LIMIT 1;";

                bool exists = false;

                // Callback to set exists flag
                auto exists_callback = [](void *data, int argc, char **argv, char **azColName) -> int
                {
                    bool *exists_ptr = static_cast<bool *>(data);
                    *exists_ptr = true;
                    return 0;
                };

                rc = sqlite3_exec(db, check_query.c_str(), exists_callback, &exists, &zErrMsg);
                if (rc != SQLITE_OK)
                { // if //
                    std::cerr << "SQL error during DriverID check: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                    break;
                } // if //

                if (!exists)
                {
                    is_unique = true;
                }

                attempts++;
            } // while //

            if (!is_unique)
            { // if //
                std::cerr << "Failed to generate a unique Driver ID after " << MAX_ATTEMPTS << " attempts." << std::endl;
                sqlite3_close(db);
                return 1;
            } // if //

            std::cout << "Assigned Driver ID: " << driver_id << std::endl;

            // Build the SQL INSERT statement using sqlite3_mprintf to prevent SQL injection
            char *sql_insert_driver = sqlite3_mprintf(
                "INSERT INTO DRIVER (DriverID, FirstName, LastName, ZipCode, RatePerMile, SumOfTips, SumOfMiles) "
                "VALUES (%d, '%q', '%q', %d, %.2f, %.2f, %.2f);",
                driver_id,
                d_first.c_str(), d_last.c_str(),
                d_zip, d_rate, d_tips, d_miles);

            // Execute the SQL statement
            rc = sqlite3_exec(db, sql_insert_driver, nullptr, 0, &zErrMsg);
            if (rc != SQLITE_OK)
            { // if //
                std::cerr << "SQL error: " << zErrMsg << std::endl;
                sqlite3_free(zErrMsg);
            } // if //
            else
            {
                std::cout << "Congrats on joining our team! Your Driver ID is: " << driver_id << ".\n";
            }

            // Free the memory allocated by sqlite3_mprintf
            sqlite3_free(sql_insert_driver);

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
            std::cout << "Enter SQL queries to execute. Type 'exit' to return to the main menu or Ctrl+C to end program abruptly.\n";
            while (true)
            { // w //
                std::cout << "SQL> ";
                std::string sql;
                std::getline(std::cin, sql);

                if (sql.empty())
                {
                    continue;
                }

                if (sql == "exit")
                {
                    break;
                }

                // Execute SQL statement
                rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
                if (rc != SQLITE_OK)
                { // i //
                    std::cerr << "SQL error: " << zErrMsg << std::endl;
                    sqlite3_free(zErrMsg);
                } // i //
                else
                {
                    std::cout << "Operation executed successfully.\n";
                }
            } // w //
            break;
        } // case 6 //
        default:
        { // default //
            std::cout << "You entered an invalid choice. Please rerun and try again.\n";
            sqlite3_close(db);
            return 1;
        } // default //

        } // switch //
    } // while //

    // Close SQLite database
    sqlite3_close(db);
    return 0;
} // main //
