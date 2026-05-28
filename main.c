#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "address_book.h"

int main()
{
    AddressBook myBook;
    myBook.contactCount = 0;

    int choice;
    loadContact(&myBook);
    do
    {
        printf("\n1. Create\n2. List\n3. Search\n4. Edit\n5. Delete\n6. Save & Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice)
        {
            case 1:
            createContact(&myBook);
            break;

            case 2:
            displayContact(&myBook);
            break;

            case 3:
            searchContact(&myBook);
            break;

            case 6:
            saveContacts(&myBook);
            break;

            default:
            printf("Invalid Choice\n");
            break;
    }

    } while(choice != 6);
    
    return 0;
}



