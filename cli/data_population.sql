-- This script populates the database with sample data to test all features.
-- Ensure that `schema_setup.sql` has been executed before running this script.

-- Insert into PLAN table
INSERT INTO PLAN (PlanID, Name, Price, Calories, Frequency, NumberOfMeals)
VALUES 
    (1, 'Basic Plan', 29.99, 2000, 3, 15),
    (2, 'Premium Plan', 59.99, 2500, 5, 25);

-- Insert into DRIVER table
INSERT INTO DRIVER (FirstName, LastName, ZipCode, RatePerMile, SumOfTips, SumOfMiles)
VALUES 
    ('Alice', 'Smith', 12345, 0.85, 200.50, 1500),
    ('Bob', 'Johnson', 67890, 0.90, 150.75, 1200);

-- Insert into Warehouse table
INSERT INTO Warehouse (WarehouseAddress)
VALUES 
    ('100 Warehouse Ave'),
    ('200 Storage Blvd');

-- Insert into Ingredient table
INSERT INTO INGREDIENT (Name, Description, Price, Count, WarehouseID)
VALUES 
    ('Tomato', 'Fresh ripe tomatoes', 0.50, 500, 1),
    ('Cheese', 'Organic cheddar cheese', 2.50, 200, 1),
    ('Basil', 'Fresh basil leaves', 0.20, 300, 2);

-- Insert into Employee table
INSERT INTO Employee (FirstName, LastName, Department, Salary)
VALUES 
    ('John', 'Doe', 'Sales', 55000.00),
    ('Jane', 'Williams', 'Marketing', 60000.00);

-- Insert into USER_TABLE
INSERT INTO USER_TABLE (Phone, Email, Password, FirstName, LastName, Address, PlanID, PaymentInfo)
VALUES 
    ('1234567890', 'user1@example.com', 'hashedpassword1', 'Michael', 'Brown', '123 Elm Street', 1, 'Visa **** 1111'),
    ('1112223333', 'user2@example.com', 'hashedpassword2', 'Sarah', 'Davis', '456 Oak Avenue', 2, 'Mastercard **** 2222');

-- Insert into ADDRESS table
INSERT INTO ADDRESS (Country, City, State, ZipCode, UserID)
VALUES 
    ('USA', 'New York', 'NY', 10001, 1),
    ('USA', 'Los Angeles', 'CA', 90001, 2);

-- Insert into Item table
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID)
VALUES 
    ('Spaghetti', 'Long pasta noodles', 1.99, 100, 1),
    ('Marinara Sauce', 'Tomato-based sauce', 3.49, 150, 1),
    ('Pesto', 'Basil pesto sauce', 4.99, 80, 2);

-- Insert into RECIPE table
INSERT INTO RECIPE (IngredientID, Calories, RecipeName, RecipeDescription, Price, Count, WarehouseID)
VALUES 
    (1, 500, 'Tomato Soup', 'Classic tomato soup', 5.99, 50, 1),
    (2, 300, 'Cheese Pizza', 'Delicious cheese pizza', 8.99, 30, 1),
    (3, 250, 'Pesto Pasta', 'Pasta with basil pesto', 7.99, 40, 2);

-- Insert into Invoice table
INSERT INTO Invoice (UserID, DriverID, RecipeID, InvoiceDate)
VALUES 
    (1, 1, 1, '2023-10-01'),
    (2, 2, 3, '2023-10-02');