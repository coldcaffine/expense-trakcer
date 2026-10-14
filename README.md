# 💰 Personal Expense Tracker in C

A simple, menu-driven expense tracking application built using the C programming language. This project helps users record expenses, view transaction history, calculate total spending, and search expenses by category.

## ✨ Features

- ➕ Add new expenses
- 📋 View all recorded expenses
- 💵 Calculate total expenses
- 🔍 Search expenses by category
- 💾 Save expense records using file handling
- 🔄 Load saved expenses when the program starts
- ✅ Validate numeric input

## 🛠️ Technologies Used

- **Language:** C
- **Compiler:** GCC
- **Concepts:** Structures, arrays, functions, loops, conditional statements, string handling, and file handling

## 📂 Project Structure

```text
c-personal-expense-tracker/
├── expense_tracker.c
└── README.md
```

The program creates `expenses.txt` locally to store expense records.

## 🚀 Getting Started

### Prerequisites

Install GCC or another C compiler that supports C99.

### Compile the program

```bash
gcc -std=c99 -Wall -Wextra expense_tracker.c -o expense_tracker
```

### Run the program

```bash
./expense_tracker
```

## 📖 How to Use

1. Run the application.
2. Choose an option from the menu.
3. Enter the expense amount, category, and description when prompted.
4. View your expenses or calculate your total spending.
5. Search for expenses using their category.
6. Choose Exit when you're done.

## 📚 Concepts Practiced

- User-defined structures using `struct`
- Arrays and variables
- Functions and modular programming
- `switch`, `do-while`, and `for` loops
- String manipulation and comparison
- File operations using `fopen()`, `fprintf()`, `fscanf()`-related parsing, and `fclose()`
- Input validation and error handling

## 🔮 Future Improvements

- Edit and delete expenses
- Add dates to transactions
- Set monthly budgets
- Generate category-wise spending reports
- Improve input validation and data storage

## 🎯 Purpose

Built as a C programming practice project to strengthen my understanding of structured programming, problem-solving, and file handling.

---

**Author:** Aditi Dharme
