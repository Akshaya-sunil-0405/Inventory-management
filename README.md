# 📦 Inventory Management System

A console-based inventory management program built in C using structures and file handling.

---

## 📌 Project Description

The Inventory Management System helps small shop owners manage their product records efficiently through a menu-driven console interface. All data is stored persistently in a `.txt` file using C file handling. Built as part of a B.Sc. Computer Science portfolio project.

---

## 🛠️ Tech Stack

| Technology | Purpose |
|-----------|---------|
| C Language | Core programming language |
| File Handling (.txt) | Persistent data storage |
| Structures (struct) | Organize product data |
| Standard I/O (stdio.h) | Input/output operations |

---

## ✨ Features

- ➕ Add new products (ID auto-generated)
- 📋 Display all products in a formatted table
- 🔍 Search product by ID
- ✏️ Update product details (name, quantity, price)
- 🗑️ Delete product by ID
- ⚠️ Low Stock Alert (flags products with quantity < 5)
- 💾 All data saved to `inventory.txt` automatically

---

## 📁 Project Structure

```
inventory_system/
│
├── inventory.c        # Main source code file
├── inventory.txt      # Auto-generated data storage file
└── README.md          # Project documentation
```

---

## ⚙️ Installation & Setup

### Prerequisites
- GCC Compiler (MinGW for Windows / GCC for Linux/Mac)
- Any C IDE: Dev C++, Code::Blocks, or VS Code

### Step 1 — Clone or Download
```bash
git clone https://github.com/yourusername/inventory-management.git
cd inventory-management
```

### Step 2 — Compile the Program

**Using GCC (Terminal):**
```bash
gcc inventory.c -o inventory
```

**Using Dev C++ / Code::Blocks:**
- Open `inventory.c` in the IDE
- Click Build & Run (F9 in Dev C++ / F9 in Code::Blocks)

### Step 3 — Run the Program
```bash
./inventory          # Linux / Mac
inventory.exe        # Windows
```

---

## 🖥️ Menu Options

```
------------------------------------------------------------
       INVENTORY MANAGEMENT SYSTEM
------------------------------------------------------------
  1. Add Product
  2. Display All Products
  3. Search Product by ID
  4. Update Product
  5. Delete Product
  6. Low Stock Alert
  0. Exit
------------------------------------------------------------
```

---

## 💾 Data Storage Format

Products are stored in `inventory.txt` in pipe-separated format:

```
ID|Product Name|Quantity|Price
1|Rice Bag|50|450.00
2|Sugar|3|55.00
3|Cooking Oil|20|180.00
```

---

## 📸 Screenshots

> Run the program and capture the terminal output to add here.

---

## 🔮 Future Improvements

- Add category-wise product grouping
- Generate sales report with total inventory value
- Add date of entry for each product
- Implement search by product name

---

## 👩‍💻 Author

**Akshaya S**  
B.Sc. Computer Science — Nirmala College for Women, Coimbatore  
📧 achusunil0405@gmail.com

---

## 📄 License

This project is for educational and portfolio purposes.
