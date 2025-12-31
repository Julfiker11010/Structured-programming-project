#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *file;

struct GroceryItem{
    int id;
    char name[50];
    int price;
    int quantity;
};

struct GroceryItem groceryItems[100];
int itemCount = 0;

char adminUsername[] = "a";
char adminPassword[] = "p";

void loadItemsFromFile() {
    file = fopen("grocery_file.txt", "r");

    while (fscanf(file, "%d %s %d %d", &groceryItems[itemCount].id, groceryItems[itemCount].name,
                                          &groceryItems[itemCount].price, &groceryItems[itemCount].quantity) == 4) {
        itemCount++;
    }

    fclose(file);
}

void saveItemsToFile() {
    file = fopen("grocery_file.txt", "w");

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%d %s %d %d\n", groceryItems[i].id, groceryItems[i].name,
                                        groceryItems[i].price, groceryItems[i].quantity);
    }

    fclose(file);
}


int adminLogin() {
    char username[20], password[20];

    printf("Enter admin username: ");
    scanf("%s", username);

    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0) {
        return 1;
    }

    else {
        printf("Invalid credentials. Access denied!\n");
        return adminLogin();
    }
}


void addItem() {
    if (itemCount < 100) {
        struct GroceryItem newItem;

        newItem.id = itemCount + 1;

        printf("Enter item name: ");
        scanf("%s",newItem.name);

        printf("Enter item price: ");
        scanf("%d",&newItem.price);

        printf("Enter item quantity: ");
        scanf("%d",&newItem.quantity);

        file = fopen("grocery_file.txt", "a");

        fprintf(file, "%d\t%s\t%d\t%d\n", newItem.id, newItem.name, newItem.price, newItem.quantity);
        fclose(file);

        groceryItems[itemCount++] = newItem;
        saveItemsToFile();

        printf("Item added successfully!\n");
    }

    else {
        printf("No space to add more items.\n");
    }
}

void displayItems() {

    struct GroceryItem newItem;
    char ch;

        file = fopen("grocery_file.txt","r");
        ch = fgetc(file);
        while(ch != EOF){
          printf("%c",ch);
          ch = fgetc(file);
        }
        printf("\n");

        fclose(file);

}

void removeItem(int itemId) {
    struct GroceryItem newItem;
    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (groceryItems[i].id == itemId) {
            found = 1;
            for (int j = i; j < itemCount - 1; j++) {
                groceryItems[j] = groceryItems[j + 1];
            }
            itemCount--;
            saveItemsToFile();
            printf("Item removed successfully!\n");
            break;
        }
    }
    if (found == 0) {
        printf("Item not found.\n");
    }
}

void updateItem(int itemId) {
    struct GroceryItem newItem;
    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (groceryItems[i].id == itemId) {
            found = 1;

            printf("Enter updated item name: ");
            scanf("%s", groceryItems[i].name);

            printf("Enter updated item price: ");
            scanf("%d", &groceryItems[i].price);

            printf("Enter updated item quantity: ");
            scanf("%d", &groceryItems[i].quantity);

            saveItemsToFile();

            printf("Item updated successfully!\n");
            break;
        }

    }
    if (found == 0) {
        printf("Item not found.\n");
    }
}

void buyItem() {
    printf("Available Items:\n");
    displayItems();

    int itemId, quantity;
    printf("Enter the ID of the item you want to buy: ");
    scanf("%d", &itemId);

    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (groceryItems[i].id == itemId) {
            found = 1;

            printf("Enter the quantity to buy: ");
            scanf("%d", &quantity);

            if (groceryItems[i].quantity >= quantity) {
                groceryItems[i].quantity -= quantity;
                saveItemsToFile();
                printf("You purchased %d %s.\n", quantity, groceryItems[i].name);
            } else {
                printf("Insufficient stock for the purchase.\n");
            }
            break;
        }
    }
    if (found == 0) {
        printf("Item not found.\n");
    }
}

int main() {
    loadItemsFromFile();

    int choice;
    int itemId;

    printf("\n\\\\\\\\Welcome to Grocery Management System\\\\\\\\\\ \n\n");

    int preference;
    printf("1. Admin login\n2. Customer\nEnter preference:\n");
    scanf("%d",&preference);

    if(preference == 1)
    {

     adminLogin();

    do {
        printf("\nGrocery Management System\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Remove Item\n");
        printf("4. Update Item\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayItems();
                break;
            case 3:
                printf("Enter the ID of the item to remove: ");
                scanf("%d", &itemId);
                removeItem(itemId);
                break;
            case 4:
                printf("Enter the ID of the item to update: ");
                scanf("%d", &itemId);
                updateItem(itemId);
                break;
            case 5:
                printf("Exiting........\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 5);
    }

    else if(preference==2)
    {
        buyItem();
    }
    else {
        printf("Invalid choice\n\n");
        main();
    }

    return 0;
}
