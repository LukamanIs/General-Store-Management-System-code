# 🛒 General Store Management System (C++ Console App)

This is a simple console-based inventory and sales management system built in C++. It allows users to add products, view inventory, buy items, generate receipts, and clear stored data. All data is handled via text files (`data.txt` and `temp.txt`) for simplicity.

---

## 🔧 Features

- **Add Product**: Enter product ID, name, quantity, and price. Supports multi-word product names.
- **View Products**: Displays all products stored in `data.txt`.
- **Buy Products**:
  - User selects a product by ID and chooses quantity.
  - Quantity is subtracted from inventory if available.
  - A payment summary is shown after each purchase.
  - A final receipt is saved to `temp.txt`.
- **Clear All Data**:
  - Clears both `data.txt` (inventory) and `temp.txt` (receipt).
- **Receipts**:
  - Stored in `temp.txt` for each shopping session.
  - Shows item details, quantities, individual totals, and total bill.
- **User Input Handling**:
  - Only accepts `Y/N` for "continue" prompts.
  - Input is validated to avoid crashing on bad data.

---

## 💾 File Structure

| File        | Purpose                            |
|-------------|------------------------------------|
| `data.txt`  | Stores product inventory            |
| `temp.txt`  | Stores purchase receipt             |
| `.cpp` file | Main C++ source code               |

---

## 🧪 Sample Flow

```text
======= Welcome to the Shop =======
A - Add Product
1 - Start Shopping
C - Clear All Data
0 - Exit
Enter your choice: 1

=== Product List ===
Product ID: 101
Product Name: Lays
Quantity: 40
Product Price: $2.5

Enter Product ID to buy: 101
Enter Quantity: 2

--- Payment Summary ---
You bought 2 of Lays
Amount for this item: $5
Total so far: $5

Do you want to continue shopping? (Y/N): n

Thank you for shopping.
Total Purchase Amount: $5
A receipt has been saved to 'temp.txt'.
