#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H
#define MAX_CONTACT 100
#define INVALID 0
#define VALID 1
#define EMPTY_CONTACT "Contacs are empty. \n"
#define FILE_ERROR "Error: Could not open file.\n"
#define FILENAME "contacts.csv"
#define CONTACT_NOT_FOUND_MSG "The contact with particular details not found\n"
#define CONTACT_FOUND "\t\t\tSUCCESS: Contact Found Successfully!\n"

typedef struct
{
    char name[50];
    char phone[15];
    char mail[50];
}ContactInfo;

typedef struct
{
   int contactCount;
   ContactInfo contacts[MAX_CONTACT];
}AddressBook;

//Array for storing the search result

void createContact(AddressBook *);
int is_Valid_Name(char *);    
int is_Valid_PhoneNumber(AddressBook *, char *);
int is_Valid_Mail(AddressBook *, char *);
void displayContact(AddressBook *);
void saveContacts(AddressBook *);
void loadContact(AddressBook *);
void searchContact(AddressBook *);
#endif