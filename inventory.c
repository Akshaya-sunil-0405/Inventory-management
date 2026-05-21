#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "inventory.txt"
#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    int quantity;
    float price;
} Product;

// ─── Utility ───────────────────────────────────────────────────────────────

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnter() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void printLine() {
    printf("------------------------------------------------------------\n");
}

// ─── File Operations ────────────────────────────────────────────────────────

int getNextID() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return 1;
    Product p;
    int maxID = 0;
    while (fscanf(fp, "%d|%49[^|]|%d|%f\n", &p.id, p.name, &p.quantity, &p.price) == 4) {
        if (p.id > maxID) maxID = p.id;
    }
    fclose(fp);
    return maxID + 1;
}

void addProduct() {
    clearScreen();
    printLine();
    printf("         ADD NEW PRODUCT\n");
    printLine();

    Product p;
    p.id = getNextID();

    printf("Enter Product Name   : ");
    scanf(" %49[^\n]", p.name);
    printf("Enter Quantity       : ");
    scanf("%d", &p.quantity);
    printf("Enter Price (Rs.)    : ");
    scanf("%f", &p.price);

    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) { printf("Error opening file!\n"); return; }
    fprintf(fp, "%d|%s|%d|%.2f\n", p.id, p.name, p.quantity, p.price);
    fclose(fp);

    printf("\n✔ Product added successfully! (ID: %d)\n", p.id);
    pressEnter();
}

void displayAll() {
    clearScreen();
    printLine();
    printf("%-6s %-25s %-12s %-12s\n", "ID", "Product Name", "Quantity", "Price (Rs.)");
    printLine();

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) { printf("No inventory records found.\n"); pressEnter(); return; }

    Product p;
    int count = 0;
    while (fscanf(fp, "%d|%49[^|]|%d|%f\n", &p.id, p.name, &p.quantity, &p.price) == 4) {
        printf("%-6d %-25s %-12d %-12.2f\n", p.id, p.name, p.quantity, p.price);
        count++;
    }
    fclose(fp);

    if (count == 0) printf("Inventory is empty.\n");
    else { printLine(); printf("Total Products: %d\n", count); }
    pressEnter();
}

void searchProduct() {
    clearScreen();
    printLine();
    printf("         SEARCH PRODUCT\n");
    printLine();

    int id;
    printf("Enter Product ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) { printf("No inventory records found.\n"); pressEnter(); return; }

    Product p;
    int found = 0;
    while (fscanf(fp, "%d|%49[^|]|%d|%f\n", &p.id, p.name, &p.quantity, &p.price) == 4) {
        if (p.id == id) {
            printLine();
            printf("ID       : %d\n", p.id);
            printf("Name     : %s\n", p.name);
            printf("Quantity : %d\n", p.quantity);
            printf("Price    : Rs. %.2f\n", p.price);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) printf("Product with ID %d not found.\n", id);
    pressEnter();
}

void updateProduct() {
    clearScreen();
    printLine();
    printf("         UPDATE PRODUCT\n");
    printLine();

    int id;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) { printf("No inventory records found.\n"); pressEnter(); return; }

    FILE *temp = fopen("temp.txt", "w");
    Product p;
    int found = 0;

    while (fscanf(fp, "%d|%49[^|]|%d|%f\n", &p.id, p.name, &p.quantity, &p.price) == 4) {
        if (p.id == id) {
            found = 1;
            printf("Current Name     : %s\n", p.name);
            printf("Current Quantity : %d\n", p.quantity);
            printf("Current Price    : Rs. %.2f\n\n", p.price);
            printf("Enter New Name     : ");
            scanf(" %49[^\n]", p.name);
            printf("Enter New Quantity : ");
            scanf("%d", &p.quantity);
            printf("Enter New Price    : ");
            scanf("%f", &p.price);
        }
        fprintf(temp, "%d|%s|%d|%.2f\n", p.id, p.name, p.quantity, p.price);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) printf("\n✔ Product updated successfully!\n");
    else printf("Product with ID %d not found.\n", id);
    pressEnter();
}

void deleteProduct() {
    clearScreen();
    printLine();
    printf("         DELETE PRODUCT\n");
    printLine();

    int id;
    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) { printf("No inventory records found.\n"); pressEnter(); return; }

    FILE *temp = fopen("temp.txt", "w");
    Product p;
    int found = 0;

    while (fscanf(fp, "%d|%49[^|]|%d|%f\n", &p.id, p.name, &p.quantity, &p.price) == 4) {
        if (p.id == id) { found = 1; continue; }
        fprintf(temp, "%d|%s|%d|%.2f\n", p.id, p.name, p.quantity, p.price);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) printf("\n✔ Product deleted successfully!\n");
    else printf("Product with ID %d not found.\n", id);
    pressEnter();
}

void lowStockAlert() {
    clearScreen();
    printLine();
    printf("         LOW STOCK ALERT (Quantity < 5)\n");
    printLine();

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) { printf("No inventory records found.\n"); pressEnter(); return; }

    Product p;
    int found = 0;
    printf("%-6s %-25s %-12s\n", "ID", "Product Name", "Quantity");
    printLine();

    while (fscanf(fp, "%d|%49[^|]|%d|%f\n", &p.id, p.name, &p.quantity, &p.price) == 4) {
        if (p.quantity < 5) {
            printf("%-6d %-25s %-12d ⚠\n", p.id, p.name, p.quantity);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) printf("All products are well stocked!\n");
    pressEnter();
}

// ─── Main Menu ──────────────────────────────────────────────────────────────

int main() {
    int choice;
    do {
        clearScreen();
        printLine();
        printf("       INVENTORY MANAGEMENT SYSTEM\n");
        printLine();
        printf("  1. Add Product\n");
        printf("  2. Display All Products\n");
        printf("  3. Search Product by ID\n");
        printf("  4. Update Product\n");
        printf("  5. Delete Product\n");
        printf("  6. Low Stock Alert\n");
        printf("  0. Exit\n");
        printLine();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct();     break;
            case 2: displayAll();     break;
            case 3: searchProduct();  break;
            case 4: updateProduct();  break;
            case 5: deleteProduct();  break;
            case 6: lowStockAlert();  break;
            case 0: printf("\nExiting... Goodbye!\n\n"); break;
            default: printf("Invalid choice! Try again.\n"); pressEnter();
        }
    } while (choice != 0);

    return 0;
}
