-- This file will populate the database with sample data.
-- You will need to create a sufficient amount of sample data (many INSERT statements) for your tables.

INSERT INTO Employee (FirstName, LastName, Department, Salary)
VALUES ('John', 'Doe', 'Sales', 50000.00);

INSERT INTO Warehouse (WarehouseAddress, ItemID) VALUES ('789 Main St', NULL);
INSERT INTO Warehouse (WarehouseAddress, ItemID) VALUES ('456 Elm St', NULL);
INSERT INTO Warehouse (WarehouseAddress, ItemID) VALUES ('123 Oak St', NULL);

INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Gadget', 'Electronic gadget', 29.99, 150, 1);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Widget', 'Small widget', 5.99, 300, 2);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Gizmo', 'Gizmo', 15.99, 100, 3);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Doohickey', 'Doohickey', 8.99, 200, 1);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Thingamajig', 'Thingamajig', 12.99, 75, 2);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Doodad', 'Doodad', 7.99, 250, 3);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Whatchamacallit', 'Whatchamacallit', 9.99, 125, 1);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Wobble', 'Wobble', 6.99, 175, 2);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Gadgetron', 'Gadgetron', 14.99, 80, 3);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Widgetron', 'Widgetron', 10.99, 120, 1);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Gizmor', 'Gizmor', 18.99, 90, 2);
INSERT INTO Item (ItemName, ItemDescription, Price, Count, WarehouseID) VALUES ('Doohickron', 'Doohickron', 11.99, 150, 3);

INSERT INTO RECIPE (IngredientID, Calories, RecipeName, RecipeDescription, Price, Count, WarehouseID) VALUES (1, 500, 'Pasta Primavera', 'A fresh vegetable pasta', 9.99, 50, 1);
INSERT INTO RECIPE (IngredientID, Calories, RecipeName, RecipeDescription, Price, Count, WarehouseID) VALUES (1, 300, 'Spaghetti Bolognese', 'Italian pasta dish', 12.99, 500, 1);

-- INSERT INTO PLAN (Price, Calories, Frequency, NumberOfMeals) VALUES (299.99, 2000, 3, 20);

-- INSERT INTO DRIVER (FirstName, LastName, ZipCode, RatePerMile, SumOfTips, SumOfMiles) VALUES ('Alex', 'Johnson', 70810, 0.75, 150.50, 300);

-- INSERT INTO USER (PhoneNumber, Email, Password, FirstName, LastName, Address, PlanID, PaymentInfo) 
-- VALUES ('123-456-7890', 'sampleemail@example.com', 'securepassword', 'Liam', 'Brown', '456 Elm St', 1, 'Credit Card');

-- INSERT INTO ADDRESS (Country, CITY, State, ZipCode, UserID) 
-- VALUES ('United States', 'New York', 'NY', 10001, 1);

-- INSERT INTO INGREDIENT (Name, Description, Price, Count, WarehouseID) 
-- VALUES ('Tomato', 'Fresh tomatoes', 0.50, 200, 1);