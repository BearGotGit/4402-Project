-- Example file that defines the schema for the database.
-- All relations will be defined here, like the one below.

-- Example: I don't think I've changed it since the fork
CREATE TABLE Employee (
    EmployeeID INT AUTO_INCREMENT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Department VARCHAR(50),
    Salary DECIMAL(10, 2)
);

CREATE TABLE Warehouse (
    WarehouseID INT AUTO_INCREMENT PRIMARY KEY,
    WarehouseAddress VARCHAR(100),
    -- TODO: composite type for ITEM
    ItemID INT
);

CREATE TABLE Item (
    ItemID INT AUTO_INCREMENT PRIMARY KEY,
    ItemName VARCHAR(50),
    ItemDescription VARCHAR(100),
    Price DECIMAL(10, 2),
    Count INT,
    WarehouseID INT 
    -- TODO: Idk how
    -- FOREIGN KEY ,
    -- FOREIGN KEY (WarehouseID) REFERENCES Warehouse(WarehouseID)
);

CREATE TABLE RECIPE (
    RecipeID INT AUTO_INCREMENT PRIMARY KEY,
    IngredientID INT,
    Calories INT,
    RecipeName VARCHAR(50),
    RecipeDescription VARCHAR(100),
    Price DECIMAL(10, 2),
    Count INT,
    WarehouseID INT
    -- FOREIGN KEY (WarehouseID) REFERENCES WAREHOUSE(WarehouseID)
);

-- CREATE TABLE PLAN (
--     PlanID INT AUTO_INCREMENT PRIMARY KEY,
--     Price DECIMAL(10, 2),
--     Calories INT,
--     Frequency INT,
--     NumberOfMeals INT, 
-- )

-- CREATE TABLE DRIVER (
--     -- TODO: Put more
--     RANGE ZipCodes {70810, 70811, 70812, 70813}
--     DriverID INT AUTO_INCREMENT PRIMARY KEY,
--     FirstName VARCHAR(50),
--     LastName VARCHAR(50),
--     ZipCode INT,
--     RatePerMile DECIMAL(10, 2),
--     SumOfTips DECIMAL(10, 2),
--     SumOfMiles DECIMAL(10, 2),
-- )

-- CREATE TABLE USER (
--     UserID INT AUTO_INCREMENT PRIMARY KEY,
--     PhoneNumber VARCHAR(20),
--     Email VARCHAR(100),
--     Password PASSWORD VARCHAR(100),
--     FirstName VARCHAR(50),
--     LastName VARCHAR(50),
--     Address VARCHAR(100),
--     PlanID INT FOREIGN KEY,
--     -- TODO: Make a table or get rid of specify better
--     PaymentInfo VARCHAR(100),
--     FOREIGN KEY (PlanID) REFERENCES PLAN(PlanID)
-- )

-- CREATE TABLE ADDRESS (
--     AddressID INT AUTO_INCREMENT PRIMARY KEY,
--     Country VARCHAR(50),
--     CITY VARCHAR(50),
--     State VARCHAR(50),
--     ZipCode INT,
--     UserID INT FOREIGN KEY,
--     FOREIGN KEY (UserID) REFERENCES USER(UserID)
-- )

-- CREATE TABLE INGREDIENT (
--     IngredientID INT AUTO_INCREMENT PRIMARY KEY,
--     Name VARCHAR(50),
--     Description VARCHAR(100),
--     Price DECIMAL(10, 2),
--     Count INT,
--     WarehouseID INT FOREIGN KEY,
--     FOREIGN KEY (WarehouseID) REFERENCES WAREHOUSE(WarehouseID)
-- )

-- -- Callin Invoice instead of Order because I'm scared it conflicts with language keywords
-- CREATE TABLE Invoice (
--     InvoiceID INT AUTO_INCREMENT PRIMARY KEY,
--     UserID INT FOREIGN KEY,
--     DriverID INT FOREIGN KEY,
--     RecipeID INT FOREIGN KEY,
--     InvoiceDate DATE,
--     -- TODO: IDK If useful:
--     -- FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
--     -- FOREIGN KEY (ItemID) REFERENCES Item(ItemID)
-- )