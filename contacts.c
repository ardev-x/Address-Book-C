#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "address_book.h"

int original_contatct_pos[MAX_CONTACT] = {0};

void createContact(AddressBook * myBook)
{
    if(myBook->contactCount == MAX_CONTACT)
    {
        printf("Contact Full\n");
        return;
    }
    char name[50];
    char phone[11];
    char mail[50];

    printf("==================================================\n");
    printf("             NEW CONTACT REGISTRATION             \n");
    printf("==================================================\n");

    do
    {
        printf("Enter your full name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

    } while(is_Valid_Name(name) != 1);

    do
    {
        printf("Enter your phone number: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = '\0';

    }while(is_Valid_PhoneNumber(myBook, phone) != 1);

    do
    {
        printf("Enter your mail ID: ");
        fgets(mail, sizeof(mail), stdin);
        mail[strcspn(mail, "\n")] = '\0';

    }while(is_Valid_Mail(myBook, mail) != 1);  
    
    //Store the name into the structure
    strcpy(myBook -> contacts[myBook -> contactCount].name, name);
    strcpy(myBook -> contacts[myBook -> contactCount].phone, phone);
    strcpy(myBook -> contacts[myBook -> contactCount].mail, mail);
    myBook -> contactCount ++;
}

int is_Valid_Name(char * name)
{
    //Validate name contains only space and alphabets
    while(*name != '\0')
    {
        if(!isalpha(*name) && !isspace(*name))
            return INVALID;

        name ++;
    }
    return VALID;
}

int is_Valid_PhoneNumber(AddressBook * myBook, char * phone)
{
    //Ensure phone number has 10 digits
    if(strlen(phone) != 10)
        return INVALID;

    //Check phone number only contains digits
    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
            return INVALID;
    }

    //Check phone number is unique or not
    for(int i = 0; i < myBook -> contactCount; i++)
    {
        if(strcmp(myBook -> contacts[i].phone, phone) == 0)
            return INVALID;
    }

    return VALID;
}

int is_Valid_Mail(AddressBook * myBook, char * mail)
{
    //A mail should atleast have 7 characters
    if(strlen(mail) < 7)
        return INVALID;

    int at_the_rate_count = 0;
    for(int i = 0; mail[i] != '\0'; i++)
    {
        if(mail[i] == '@')
            at_the_rate_count++;

        if(at_the_rate_count > 1)
            return INVALID;

        if(!isdigit(mail[i]) && !isalpha(mail[i]) && 
                    mail[i] != '_' && mail[i] != '@' 
                    && mail[i] != '.')
            return INVALID;
    }

    //Check if only one @ present on the given mail
    if(at_the_rate_count == 0)
        return INVALID;

    //Check if .com present at last
    char *temp = mail;
    if(strcmp(&mail[strlen(mail) - 4], ".com"))
        return INVALID;

    //Check if atleast one character between '@' and ".com"
    while(*mail != '@')
    {
        mail++;
    }
    if(!isalpha(*(mail + 1)))
        return INVALID;

    //Check mail is unique or not
    for(int i = 0; i < myBook -> contactCount; i++)
    {
        if(strcmp(myBook -> contacts[i].mail, mail) == 0)
            return INVALID;
    }

    return VALID;
}

void displayContact(AddressBook * myBook)
{
    if(myBook -> contactCount == 0)
    {
        printf(EMPTY_CONTACT);
        return;
    }
    printf("\n============================================================================================\n");
    printf(" >>>                DISPLAYING ALL REGISTERED CONTACTS (%d total) <<<\n", myBook -> contactCount);
    printf("============================================================================================\n");
    printf("%-30s %-30s %-30s\n", "Name", "Phone Number", "Mail ID");
    printf("---------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < myBook -> contactCount; i++)
    {
        printf("%-30s %-30s %-30s\n",
                myBook -> contacts[i].name,
                myBook -> contacts[i].phone,
                myBook -> contacts[i].mail
        );
    }
    printf("---------------------------------------------------------------------------------------------\n\n");

    return;
}


void searchContact(AddressBook * myBook)
{
    if(myBook -> contactCount == 0)
    {
        printf(EMPTY_CONTACT);
        return;
    }

    int slno = 0;
    char key[50];
    printf("\n");
    printf("1. Search by name\n2. Search by Phone Number\n3. Search by Mail ID\n\n");
    int choice;
    printf("Select the way of search: ");
    scanf("%d", &choice);
    printf("\n");
    int c;
    while((c = getchar()) != '\n' && c != EOF);

    switch(choice)
    {
        case 1:
        {
            printf("Enter the name to be searched: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = '\0';
            for(int i = 0; i < myBook -> contactCount; i++)
            {
                if(strcmp(myBook -> contacts[i].name, key) == 0)
                {
                    original_contatct_pos[slno] = i;
                    slno++;
                }
            }

            if(slno > 0)
            {
                printf("\n=======================================================================================\n");
                printf(CONTACT_FOUND);
                printf("=======================================================================================\n");               
                for(int i = 0; i < slno; i++)
                {
                    printf("%d. %-30s %-30s %-30s\n",i+1,
                            myBook -> contacts[original_contatct_pos[i]].name,
                            myBook -> contacts[original_contatct_pos[i]].phone,
                            myBook -> contacts[original_contatct_pos[i]].mail
                    );                     
                }
                printf("=======================================================================================\n"); 
            }
            else
            {
                printf(CONTACT_NOT_FOUND_MSG);
            }
            break;
        }
        case 2:
        {
            printf("Enter the phone number: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = '\0'; //Place new line with null
            for(int i = 0; i < myBook -> contactCount; i++)
            {
                if(strcmp(myBook -> contacts[i].phone, key) == 0)
                {
                    printf("\n=======================================================================================\n");
                    printf(CONTACT_FOUND);
                    printf("=======================================================================================\n");
                    printf("%d. %-30s %-30s %-30s\n",slno+1,
                            myBook -> contacts[i].name,
                            myBook -> contacts[i].phone,
                            myBook -> contacts[i].mail
                    );  
                    printf("=======================================================================================\n");

                    printf("Contact position : %d", original_contatct_pos[slno]);
                    return;
                }
            }
            break;
        }

        case 3:
        {
            printf("Enter the mail ID: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; //Clear the new line character
            for(int i = 0; i < myBook -> contactCount; i++)
            {
                if(strcmp(myBook -> contacts[i].mail, key) == 0)
                {
                    printf("\n=======================================================================================\n");
                    printf(CONTACT_FOUND);
                    printf("=======================================================================================\n");
                    printf("%d. %-30s %-30s %-30s\n", slno+1,
                            myBook -> contacts[i].name,
                            myBook -> contacts[i].phone,
                            myBook -> contacts[i].mail
                    );
                   printf("=======================================================================================\n");  
                    return;
                }
            }
            break;
        }

        default:
            printf("Invalid Choice\n");
            break;
    }
}