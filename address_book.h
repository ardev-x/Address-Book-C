#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H
#define MAX_CONTACT 100
#define FILENAME "contacts.csv"

//Adding Text Color (BOLD)
#define B_CYAN    "\033[1;36m"
#define B_GREEN   "\033[1;32m"
#define B_YELLOW  "\033[1;33m"
#define B_BLUE    "\033[1;34m"
#define B_RED     "\033[1;31m"
#define B_WHITE   "\033[1;37m"

//Adding Text Color (Normal)
#define CYAN    "\033[0;36m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define RED     "\033[0;31m"
#define WHITE   "\033[0;37m"
#define RESET   "\033[0m"

#define SUCCESS  "\n\033[1;32m[SUCCESS]\033[0m "
#define ERROR    "\n\033[1;31m[ERROR]\033[0m "
#define INVALID  "\n\033[1;33m[INVALID]\033[0m "
#define FOUND    "\n\033[1;36m[FOUND]\033[0m "
#define NOT_FOUND "\n\033[1;31m[NOT FOUND]\033[0m "

#define MSG_BOOK_EMPTY  ERROR"No contacts found. Add one first!\n\n"
#define PRINT_CONTACT_FOUND_MSG() \
    printf(B_GREEN"\n═══════════════════════════════════════════════════════════════════════════════════════\n" RESET); \
    printf(B_GREEN"\t\t\t[✓] SUCCESS: CONTACT FOUND IN ADDRESS BOOK\n" RESET); \
    printf(B_GREEN"═══════════════════════════════════════════════════════════════════════════════════════\n" RESET); \
    printf(B_BLUE"#  %-30s %-30s %-30s\033[0m\n", "Name", "Phone Number", "Mail ID" RESET); \
    printf(B_GREEN"═══════════════════════════════════════════════════════════════════════════════════════\n" RESET);

typedef struct{
    char name[50];
    char phone[15];
    char mail[50];
}ContactInfo;

typedef struct{
   int contactCount;
   ContactInfo contacts[MAX_CONTACT];
}AddressBook;

typedef enum{
    VALID_PHONE = 1,
    PHONE_NOT_10_DIGITS,
    PHONE_NOT_DIGITS,
    DUPLICATE_PHONE
}PhoneStatus;
extern PhoneStatus phoneStatus;

typedef enum{
    NAME_VALID = 1,
    NAME_INVALID_CHAR
}NameStatus;
extern NameStatus nameStatus;

typedef enum{
    MAIL_VALID = 1,
    MAIL_TOO_SHORT,
    MAIL_NO_DOT_COM,
    MAIL_NO_AT,
    MAIL_NO_CHAR_AT,
    MAIL_INVALID_CHAR,
    MAIL_MULTI_CHAR_AT,
    MAIL_DUPLICATE,
}MailStatus;
extern MailStatus mailStatus;

// function prototypes
NameStatus is_Valid_Name(char *);    
PhoneStatus is_Valid_PhoneNumber(AddressBook *, char *);
MailStatus is_Valid_Mail(AddressBook *, char *);
void createContact(AddressBook *);
void displayContact(AddressBook *);
void saveContacts(AddressBook *);
void loadContact(AddressBook *);
int searchContact(AddressBook *);
void editContact(AddressBook *);
void deleteContact(AddressBook *);
void sortContacts(AddressBook *);
void printMailError();
void printNameError();
void printPhoneError();
void clearBuffer();
#endif