# CampusBites Cafeteria Management System

## Project Overview
CampusBites is a comprehensive cafeteria management system designed for a college campus environment. The system helps manage menu items, customer orders, loyalty programs, and generates daily sales reports.

## Features

### 1. Menu Management
- Organized menu categories:
  - Vegetarian
  - Vegan
  - Gluten-Free
  - Specialty
  - Drinks
- Each item includes:
  - Name
  - Price
  - Category
  - Dietary restrictions
  - Availability tracking

### 2. Customer Management
- Customer registration with:
  - Name
  - Contact information
  - Dietary preferences
- Loyalty program
  - 1 point for every $50 spent
  - Points can be redeemed for discounts

### 3. Order Processing
- Interactive order placement
- Multiple items per order
- Real-time inventory tracking
- Loyalty points integration
- Payment processing

### 4. Reporting
- Daily sales reports
- Order history
- Total revenue tracking
- Number of orders processed

## Technical Requirements
- C++ compiler (Dev-C++ recommended)
- Standard C++ libraries
- Minimum 512MB RAM
- Terminal/Console support

## Installation & Setup
1. Create a new C++ project in your IDE
2. Copy the entire code into a single file named `coms.cpp`
3. Compile and run the program

## Usage Instructions

### 1. Starting the Program
- Run the compiled executable
- Main menu will display available options

### 2. Customer Registration
- Select Option 1
- Enter customer details:
  - Name
  - Contact number
  - Dietary preferences

### 3. Viewing Menu
- Select Option 2
- Displays all available items with:
  - ID
  - Name
  - Price
  - Availability

### 4. Placing Orders
- Select Option 3
- Enter item ID and quantity
- Add multiple items
- Apply loyalty points if available
- Process payment

### 5. Generating Reports
- Select Option 4
- View daily sales summary
- Total revenue
- Number of orders

## Menu Structure
```
=== CampusBites Menu ===
Vegetarian:
1. Veggie Burger - $8.99
2. Veggie Wrap - $7.49
3. Grilled Cheese Sandwich - $5.99
4. Vegetable Stir Fry - $9.49

Vegan:
5. Vegan Buddha Bowl - $10.99
6. Vegan Tacos - $8.49
7. Vegan Quinoa Salad - $9.29
8. Vegan Chili - $7.99

[...additional categories...]
```

## System Limitations
- Maximum 20 menu items
- Maximum 100 customers
- Maximum 100 orders
- Maximum 10 items per order
- Maximum 5 customizations per item

## Error Handling
- Invalid menu selections
- Insufficient inventory
- Invalid loyalty points usage
- Order capacity limits

## Best Practices
1. Register customer before placing orders
2. Check item availability before ordering
3. Review order details before payment
4. Generate daily reports at end of day

## Note
This system is designed for educational purposes and demonstrates the implementation of Object-Oriented Programming concepts in C++.
