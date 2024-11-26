```mermaid
erDiagram
    EMPLOYEE {
        INT EmployeeID PK
        VARCHAR FirstName
        VARCHAR LastName
        VARCHAR Department
        DECIMAL Salary
    }

    WAREHOUSE {
        INT WarehouseID PK
        VARCHAR WarehouseAddress
        INT ItemID
    }

    ITEM {
        INT ItemID PK
        VARCHAR ItemName
        VARCHAR ItemDescription
        DECIMAL Price
        INT Count
        INT WarehouseID FK
    }

    RECIPE {
        INT RecipeID PK
        INT IngredientID
        INT Calories
        VARCHAR RecipeName
        VARCHAR RecipeDescription
        DECIMAL Price
        INT Count
        INT WarehouseID FK
    }

    USER {
        INT UserID PK
        VARCHAR PhoneNumber
        VARCHAR Email
        PASSWORD Password
        VARCHAR FirstName
        VARCHAR LastName
        VARCHAR Address
        INT PlanID FK
        VARCHAR PaymentInfo
    }

    ADDRESS {
        INT AddressID PK
        VARCHAR Country
        VARCHAR City
        VARCHAR State
        INT ZipCode
        INT UserID FK
    }

    DRIVER {
        INT DriverID PK
        VARCHAR FirstName
        VARCHAR LastName
        INT ZipCode
        DECIMAL RatePerMile
        DECIMAL SumOfTips
        DECIMAL SumOfMiles
    }

    INVOICE {
        INT InvoiceID PK
        INT UserID FK
        INT DriverID FK
        INT RecipeID FK
        DATE InvoiceDate
    }

    EMPLOYEE ||--o{ WAREHOUSE : manages
    WAREHOUSE ||--o{ ITEM : stores
    WAREHOUSE ||--o{ RECIPE : contains
    ITEM ||--o{ RECIPE : used_in
    RECIPE ||--o{ ADDRESS : includes
    USER ||--o{ ADDRESS : resides_at
    USER ||--o{ INVOICE : makes
    DRIVER ||--o{ INVOICE : delivers
    INVOICE ||--|| RECIPE : details
