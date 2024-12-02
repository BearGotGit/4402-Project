-- Example file that defines the schema for the database.
-- All relations will be defined here, like the one below.

-- Employee table
CREATE TABLE IF NOT EXISTS Employee (
    EmployeeID INT AUTO_INCREMENT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Department VARCHAR(50),
    Salary DECIMAL(10, 2)
);
/
-- Warehouse table
CREATE TABLE IF NOT EXISTS Warehouse (
    WarehouseID INT AUTO_INCREMENT PRIMARY KEY,
    WarehouseAddress VARCHAR(100)
);

-- Item table
CREATE TABLE IF NOT EXISTS Item (
    ItemID INT AUTO_INCREMENT PRIMARY KEY,
    ItemName VARCHAR(50),
    ItemDescription VARCHAR(100),
    Price DECIMAL(10, 2),
    Count INT,
    WarehouseID INT,
    FOREIGN KEY (WarehouseID) REFERENCES Warehouse(WarehouseID)
        ON DELETE SET NULL -- if warehouse is deleted, item warehouseid is set to null
        ON UPDATE CASCADE -- if warehouseid is updated, item warehouseid is updated
);

-- RECIPE table
CREATE TABLE IF NOT EXISTS RECIPE (
    RecipeID INT AUTO_INCREMENT PRIMARY KEY,
    IngredientID INT,
    Calories INT,
    RecipeName VARCHAR(50),
    RecipeDescription VARCHAR(100),
    Price DECIMAL(10, 2),
    Count INT,
    WarehouseID INT,
    FOREIGN KEY (WarehouseID) REFERENCES Warehouse(WarehouseID)
        ON DELETE SET NULL -- if warehouse is deleted, recipe warehouseid is set to null
        ON UPDATE CASCADE, -- if warehouseid is updated, recipe warehouseid is updated
    FOREIGN KEY (IngredientID) REFERENCES Ingredient(IngredientID)
        ON DELETE CASCADE -- if ingredient is deleted, recipe ingredientid is set to null
        ON UPDATE CASCADE -- if ingredientid is updated, recipe ingredientid is updated
);

-- PLAN table
CREATE TABLE IF NOT EXISTS PLAN (
    PlanID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(50),
    Price DECIMAL(10, 2),
    Calories INT,
    Frequency INT,
    NumberOfMeals INT
);

-- DRIVER table
CREATE TABLE IF NOT EXISTS DRIVER (
    DriverID INT AUTO_INCREMENT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    ZipCode INT,
    RatePerMile DECIMAL(10, 2),
    SumOfTips DECIMAL(10, 2),
    SumOfMiles DECIMAL(10, 2)
);

-- USER table
CREATE TABLE IF NOT EXISTS USER (
    UserID INT AUTO_INCREMENT PRIMARY KEY,
    Phone VARCHAR(20),
    Email VARCHAR(100) UNIQUE,
    Password VARCHAR(100),
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Address VARCHAR(100),
    PlanID INT,
    PaymentInfo VARCHAR(100),
    FOREIGN KEY (PlanID) REFERENCES PLAN(PlanID)
        ON DELETE SET NULL
        ON UPDATE CASCADE
);

-- ADDRESS table
CREATE TABLE IF NOT EXISTS ADDRESS (
    AddressID INT AUTO_INCREMENT PRIMARY KEY,
    Country VARCHAR(50),
    City VARCHAR(50),
    State VARCHAR(50),
    ZipCode INT,
    UserID INT,
    FOREIGN KEY (UserID) REFERENCES USER_TABLE(UserID)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- INGREDIENT table
CREATE TABLE IF NOT EXISTS INGREDIENT (
    IngredientID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(50),
    Description VARCHAR(100),
    Price DECIMAL(10, 2),
    Count INT,
    WarehouseID INT,
    FOREIGN KEY (WarehouseID) REFERENCES Warehouse(WarehouseID)
        ON DELETE SET NULL
        ON UPDATE CASCADE
);

-- Invoice table
CREATE TABLE IF NOT EXISTS Invoice (
    InvoiceID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT,
    DriverID INT,
    RecipeID INT,
    InvoiceDate DATE,
    FOREIGN KEY (UserID) REFERENCES USER_TABLE(UserID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY (DriverID) REFERENCES DRIVER(DriverID)
        ON DELETE SET NULL
        ON UPDATE CASCADE,
    FOREIGN KEY (RecipeID) REFERENCES RECIPE(RecipeID)
        ON DELETE SET NULL
        ON UPDATE CASCADE
);

-- Different feature ideas
-- user sign up 
-- canceled subscription
-- check available driver
-- check test driver 
-- driver signup 