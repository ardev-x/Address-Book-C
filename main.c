#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
    char name[50];
    char ph_num[11];
    char email[50];

}Contacts;

typedef struct
{
    Contacts contact[100];
    int contactCount;
    
}AddressBook;

//------------------ VALIDATING FUNCTIONS ------------------//
int validateName(char *); //Name validation function
int validatePhoneNum(char *, AddressBook *); //Validate Phone Number
int validateMail(char * mail,  AddressBook *);
//Creating a contact
void createContact(AddressBook * myBook);
void listContact(AddressBook * myBook);
int main()
{
    AddressBook myBook;
    myBook.contactCount = 0;
    createContact(&myBook);
    listContact(&myBook);
    return 0;
}


void listContact(AddressBook * myBook)
{
    printf("%-20s %-20s %-20s\n", "Name", "Phone Number", "Mail ID");
    for(int i = 0; i < (myBook -> contactCount); i++)
    {
        printf("%-20s %-20s %-20s\n",myBook ->contact[i].name, myBook -> contact[i].ph_num, myBook->contact[i].email);
    }
    return;
}






void createContact(AddressBook * myBook)
{
    char name[50];
    char phone_num[11];
    char mailID[50];
    //Reading the name
    do
    {
        //Reading the name
        printf("Enter the name: ");
        scanf(" %[^\n]", name);
    }
    while(validateName(name) != 1); //Loop till name is valid

    //Reading the phone number
    do
    {
        printf("Enter the phone number: ");
        scanf(" %[^\n]", phone_num);
    }
    while(validatePhoneNum(phone_num, myBook) != 1); //Loop till phone number is valid

    //Reading the mail id from user
    do
    {
        printf("Enter the email: ");
        scanf(" %[^\n]", mailID);
    }
    while(validateMail(mailID, myBook) != 1);

    strcpy(myBook -> contact[myBook -> contactCount].name, name);
    strcpy(myBook -> contact[myBook -> contactCount].ph_num, phone_num);
    strcpy(myBook -> contact[myBook -> contactCount].email, mailID);
    myBook -> contactCount++;
}



int validateName(char * name)
{
    /*
    This fucntion will check weather the name is valid or not.
    If the name contains any characters other than alphabet it is said to be invalid.
    Input  : char * str 
    Output :  0 -> INVALID || 1 -> VALID 
    */

    while(*name != '\0')
    {
        //Checking for other characters except space and alphabets
        if(!isalpha(*name) && !isspace(*name))
        {
            return 0; //Return 0 if name is invalid
        }
        name++;
    }
    return 1;
}




int validatePhoneNum(char *phoneNum, AddressBook* myBook)
{
    /*
    The goal of the fucntion is to check weather the Phone numbe is valid or not
    Key Features:
    -> Check if there is more than 10 digits
    -> Check phone number contains only digits
    -> Check it is unique or not
    */

    //Validating the total digits
    if(strlen(phoneNum) != 10)
    {
        return 0;
    }

    //Checking if there is anyhting other than  0 - 9
    char * start = phoneNum;
    while(*start != '\0')
    {
        if(!isdigit(*start))
        {
            return 0;
        }
        start++;
    }

    //Checking phone number is unique
    for(int i = 0; i < (myBook -> contactCount); i++)
    {
        if(strcmp(myBook -> contact[i].ph_num, phoneNum) == 0)
        {
            return 0;
        }
    }
    return 1;
} 

int validateMail(char * mail, AddressBook * myBook)
{
    /*
    The duty of the function is to valdiate the mail id from user
    It takes starting address of the mailId
    
    Key Feature
    -> Check the mail contain '@'
    -> Check if .com is present or not
    -> Check if there is atleast one character between '@' and '.com';
    -> Look for user who used same mail.

    Inputs:
    -> Starting address of the mail

    Output:
    -> Return's: 1 for Validate
    -> Return's: 0 for INVALID
    */

    //Checking it has valid length
    if(strlen(mail) < 6)
    {
        return 0;
    }

    //checking if @ is present or not
    char * temp = mail;
    int count = 0;
    while(*temp != '\0')
    {
        if(*temp =='@')
        {
            count++;
        }
        temp ++;
    }
    if(count < 0 || count > 1)
    {
        return 0;
    }
    else
    {
        if(!isalpha(*(temp + 1)))
        {
            return 0;
        }
    }

    // Checking if the .com is present at the end
    //strlen(mail) - 4 -> gives the starting address of .com if it is present
    if(strcmp(mail + strlen(mail) - 4, ".com") != 0)
    {
        return 0;
    }

    //Checking if any person contains the same mail id
    for(int i = 0; i < myBook -> contactCount; i++)
    {
        if(strcmp(myBook->contact[i].email, mail) == 0)
        {
            return 0;
        }
    }

    return 1;
}