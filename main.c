/*
Author : Aromal K S
Date : 24/05/2026
Project Theme: A robust, modular console application built in C for managing personal contacts, 
               featuring input validation, modular function design, and data persistence via a CSV database.

*/

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
        printf(B_CYAN "╔══════════════════════════════════════════════╗\n");
        printf(B_CYAN "║              " B_CYAN "ADDRESS BOOK SYSTEM" B_CYAN "             ║\n");
        printf(B_CYAN "╠══════════════════════════════════════════════╣\n");
        printf(B_CYAN "║  " B_BLUE "[1]" B_WHITE " Create New Contact                      " B_CYAN "║\n");
        printf(B_CYAN "║  " B_BLUE "[2]" B_WHITE " List All Contacts                       " B_CYAN "║\n");
        printf(B_CYAN "║  " B_BLUE "[3]" B_WHITE " Search Contact                          " B_CYAN "║\n");
        printf(B_CYAN "║  " B_BLUE "[4]" B_WHITE " Edit Existing Contact                   " B_CYAN "║\n");
        printf(B_CYAN "║  " B_BLUE "[5]" B_WHITE " Delete Contact                          " B_CYAN "║\n");
        printf(B_CYAN "║  " B_RED "[6] Save & Exit                             " B_CYAN "║\n");
        printf(B_CYAN "╚══════════════════════════════════════════════╝\n");
        
        printf(B_GREEN "\nEnter your choice : " RESET);
        scanf("%d", &choice);
        printf("\n");
        clearBuffer();

        switch(choice){
            case 1:  createContact(&myBook);     break;
            case 2:  displayContact(&myBook);    break;
            case 3:  searchContact(&myBook);     break;
            case 4:  editContact(&myBook);       break;
            case 5:  deleteContact(&myBook);     break;           
            case 6:  saveContacts(&myBook);      break;
            default: printf(INVALID"Please enter a valid choice (1 - 6).\n\n"); break;
        }
    } while(choice != 6);
    return 0;
}



