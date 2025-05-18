#include <iostream>
#include <fstream>
#include <string>

const int MAX_PRODUCTS = 100;

struct Product
{
    int id;
    std::string name;
    int quantity;
    double price;
};

void addProduct(Product products[], int &count)
{
    if (count >= MAX_PRODUCTS)
    {
        std::cout << "Inventory full!\n";
        return;
    }

    std::cout << "Enter product ID: ";
    std::cin >> products[count].id;
    std::cin.ignore();

    std::cout << "Enter product name: ";
    std::getline(std::cin, products[count].name);

    std::cout << "Enter quantity: ";
    std::cin >> products[count].quantity;

    std::cout << "Enter price: ";
    std::cin >> products[count].price;

    count++;
    std::cout << "Product added!\n";
}

void displayInventory(const Product products[], int count)
{
    std::cout << "\nInventory:\n";
    for (int i = 0; i < count; i++)
    {
        std::cout << "ID: " << products[i].id
                  << ", Name: " << products[i].name
                  << ", Quantity: " << products[i].quantity
                  << ", Price: $" << products[i].price << '\n';
    }
}

void saveToFile(const Product products[], int count, const std::string &filename)
{
    std::ofstream outFile(filename);
    for (int i = 0; i < count; i++)
    {
        outFile << products[i].id << '\n'
                << products[i].name << '\n'
                << products[i].quantity << '\n'
                << products[i].price << '\n';
    }
    std::cout << "Data saved to file.\n";
}

void loadFromFile(Product products[], int &count, const std::string &filename)
{
    std::ifstream inFile(filename);
    count = 0;
    while (inFile >> products[count].id)
    {
        inFile.ignore();
        std::getline(inFile, products[count].name);
        inFile >> products[count].quantity >> products[count].price;
        inFile.ignore();
        count++;
        if (count >= MAX_PRODUCTS)
            break;
    }
    std::cout << "Data loaded from file.\n";
}

int main()
{
    Product products[MAX_PRODUCTS];
    int count = 0;
    int choice;
    std::string filename = "inventory.txt";

    do
    {
        std::cout << "\n1. Add product\n2. Show inventory\n3. Save to file\n4. Load from file\n5. Exit\nChoose: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            addProduct(products, count);
        }
        else if (choice == 2)
        {
            displayInventory(products, count);
        }
        else if (choice == 3)
        {
            saveToFile(products, count, filename);
        }
        else if (choice == 4)
        {
            loadFromFile(products, count, filename);
        }
    } while (choice != 5);

    return 0;
}
