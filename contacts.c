#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "address_book.h"

MailStatus    mailStatus    = MAIL_VALID;
PhoneStatus   phoneStatus   = VALID_PHONE;
NameStatus    nameStatus    = NAME_VALID;

//Clear Buffer
void clearBuffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int original_contatct_pos[MAX_CONTACT] = {0};

void createContact(AddressBook * myBook)
{
    //Check if contact is full
    if(myBook->contactCount == MAX_CONTACT)
    {
        printf(ERROR B_RED"Address book is full! (Max 100)\n\n" RESET);
        return;
    }

    char name[50];
    char phone[15];
    char mail[50];

    printf(B_GREEN"\n==================================================\n"RESET);
    printf(B_GREEN"             NEW CONTACT REGISTRATION             \n"RESET);
    printf(B_GREEN"==================================================\n\n"RESET);

    //Read name till its valid
    do{
        printf("Enter the full name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        nameStatus = is_Valid_Name(name);
        if(nameStatus != NAME_VALID){
            printNameError();
        }

    } while(nameStatus != NAME_VALID);

    //Read Phone till valid
    do{
        printf("Enter the phone number: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = '\0';

        phoneStatus = is_Valid_PhoneNumber(myBook, phone);
        if(phoneStatus != VALID_PHONE){
            printPhoneError();
        }
    }while(phoneStatus != VALID_PHONE);

    //Read Mail till valid
    do{
        printf("Enter the mail ID: ");
        fgets(mail, sizeof(mail), stdin);
        mail[strcspn(mail, "\n")] = '\0';

        mailStatus = is_Valid_Mail(myBook, mail);
        if(mailStatus != MAIL_VALID){
            printMailError();
        }
    }while(mailStatus != MAIL_VALID);  
    
    //Store the name into the structure
    strcpy(myBook -> contacts[myBook -> contactCount].name, name);
    strcpy(myBook -> contacts[myBook -> contactCount].phone, phone);
    strcpy(myBook -> contacts[myBook -> contactCount].mail, mail);

    //Increment the contact count
    myBook -> contactCount ++;
    sortContacts(myBook); 
    printf(SUCCESS B_WHITE"Contact saved successfully!\n\n"RESET);
    return;
}

/* Validation Functions */
NameStatus is_Valid_Name(char * name)
{
    while(*name != '\0'){
        if(!isalpha(*name) && !isspace(*name)){
            return NAME_INVALID_CHAR;
        }
        name ++;
    }
    return NAME_VALID;
}

PhoneStatus is_Valid_PhoneNumber(AddressBook * myBook, char * phone)
{
    //Ensure phone number has 10 digits
    if(strlen(phone) != 10){
        return PHONE_NOT_10_DIGITS;
    }
        

    //Check phone number only contains digits
    for(int i = 0; phone[i] != '\0'; i++){
        if(!isdigit(phone[i])){
            return PHONE_NOT_DIGITS;
        }        
    }

    //Check phone number is unique or not
    for(int i = 0; i < myBook -> contactCount; i++){
        if(strcmp(myBook -> contacts[i].phone, phone) == 0){
            return DUPLICATE_PHONE;
        }          
    }
    return VALID_PHONE;
}

MailStatus is_Valid_Mail(AddressBook * myBook, char * mail)
{
    //A mail should atleast have 7 characters
    if(strlen(mail) < 7){
        return MAIL_TOO_SHORT;
    }

    int at_the_rate_count = 0;
    for(int i = 0; mail[i] != '\0'; i++){
        if(mail[i] == '@')
            at_the_rate_count++;

        if(at_the_rate_count > 1){
            return MAIL_MULTI_CHAR_AT;
        }

        if(!isdigit(mail[i]) && !isalpha(mail[i]) && 
                    mail[i] != '_' && mail[i] != '@' 
                    && mail[i] != '.'){
            return MAIL_INVALID_CHAR;
        }        
    }

    if(at_the_rate_count == 0){
        return MAIL_NO_AT;
    }
        
    //Check if .com present at last
    char *temp = mail;
    if(strcmp(&mail[strlen(mail) - 4], ".com")){
        return MAIL_NO_DOT_COM;
    }
    
    //Check if atleast one character between '@' and ".com"
    while(*mail != '@'){
        mail++;
    }
    if(!isalpha(*(mail + 1))){
        return MAIL_NO_CHAR_AT;
    }
        
    //Check mail is unique or not
    for(int i = 0; i < myBook -> contactCount; i++){
        if(strcmp(myBook -> contacts[i].mail, mail) == 0)
            return MAIL_DUPLICATE;
    }
    return MAIL_VALID;
}

void displayContact(AddressBook * myBook)
{
    //Check for empty contact
    if(myBook -> contactCount == 0){
        printf(MSG_BOOK_EMPTY);
        return;
    }

    printf(B_YELLOW"\n=====================================================================================\n"RESET);
    printf(B_CYAN"                  >>> DISPLAYING ALL REGISTERED CONTACTS <<<\n"RESET);
    printf(YELLOW"=====================================================================================\n"RESET);
    printf(B_WHITE "%-6s %-25s %-15s %-30s\n" RESET, "Sl.No", "Name", " Phone", "  Mail");
    printf(B_YELLOW"-------------------------------------------------------------------------------------\n"RESET);
    
    //Print each contact
    for(int i = 0; i < myBook -> contactCount; i++){
        printf(B_BLUE "%-3d" RESET "    " B_GREEN "%-25s" RESET WHITE"  %-15s  "RESET  WHITE "%-30s" RESET "\n",
        i+1,
        myBook->contacts[i].name,
        myBook->contacts[i].phone,
        myBook->contacts[i].mail
        );
    }
    printf(B_YELLOW "\n============================== %d contact(s) displayed ================================\n\n" RESET, myBook->contactCount);

    return;
}


int searchContact(AddressBook * myBook)
{
    if(myBook -> contactCount == 0)
    {
        printf(MSG_BOOK_EMPTY);
        return 0;
    }

    int slno = 0;
    char key[50];
    printf(B_CYAN "┌─────────────────────────────┐\n" RESET);
    printf(B_CYAN "│        SEARCH CONTACT       │\n" RESET);
    printf(B_CYAN "├─────────────────────────────┤\n" RESET);
    printf(B_CYAN "│ " RESET B_WHITE"1. Search by Name          "RESET CYAN " │\n" RESET);
    printf(B_CYAN "│ " RESET B_WHITE"2. Search by Phone Number  "RESET CYAN " │\n" RESET);
    printf(B_CYAN "│ " RESET B_WHITE"3. Search by Mail ID       "RESET CYAN " │\n" RESET);
    printf(B_CYAN "└─────────────────────────────┘\n" RESET);
    printf("Select the way of search -> ");
    int choice;
    scanf("%d", &choice);
    printf("\n");

    clearBuffer();

    switch(choice){
        case 1:{
            printf("Enter the name to be searched: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0;
            for(int i = 0; i < myBook -> contactCount; i++){
                if(strstr(myBook -> contacts[i].name, key) != NULL){
                    original_contatct_pos[slno] = i;
                    slno++;
                }
            }

            if(slno > 0){
                PRINT_CONTACT_FOUND_MSG();              
                for(int i = 0; i < slno; i++){
                    printf("%d. %-30s %-30s %-35s\n",i+1,
                            myBook -> contacts[original_contatct_pos[i]].name,
                            myBook -> contacts[original_contatct_pos[i]].phone,
                            myBook -> contacts[original_contatct_pos[i]].mail
                    );                     
                }
                printf(B_GREEN"───────────────────────────────────────────────────────────────────────────────────────\n\n" RESET); 
            }
            break;
        }
        case 2:{
            printf("Enter the phone number: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; //Place new line with null
            for(int i = 0; i < myBook -> contactCount; i++){
                if(strcmp(myBook -> contacts[i].phone, key) == 0){
                    PRINT_CONTACT_FOUND_MSG(); 
                    printf("%d. %-30s %-30s %-30s\n",slno+1,
                            myBook -> contacts[i].name,
                            myBook -> contacts[i].phone,
                            myBook -> contacts[i].mail
                    );  
                    printf(B_GREEN"───────────────────────────────────────────────────────────────────────────────────────\n\n" RESET);
                    return slno;
                }
            }
            break;
        }
        case 3:{
            printf("Enter the mail ID: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = 0; //Clear the new line character
            for(int i = 0; i < myBook -> contactCount; i++){
                if(strcmp(myBook -> contacts[i].mail, key) == 0){
                    PRINT_CONTACT_FOUND_MSG(); 

                    printf("%d. %-30s %-30s %-30s\n", slno+1,
                            myBook -> contacts[i].name,
                            myBook -> contacts[i].phone,
                            myBook -> contacts[i].mail
                    );
                   printf(B_GREEN"───────────────────────────────────────────────────────────────────────────────────────\n\n" RESET);  
                   return slno;
                }  
            }
            break;
        }
        default:
            printf(INVALID B_RED"Invalid Choice Entered\n\n" RESET);
            return 0;
    }

    if(slno == 0){
        printf(NOT_FOUND B_WHITE"No matching contact.\n\n" RESET);
    }
    return slno;
}

void editContact(AddressBook * myBook)
{
   //Check if contact is empty
    if(myBook -> contactCount == 0){
        printf(MSG_BOOK_EMPTY);
        return;
    }

    int pos = 1; //Track the index of the original contact array
    int search_result = searchContact(myBook);
    if(search_result == 0){
        return;
    }
    else if(search_result > 1){
        printf("Which of the above contact you want to edit (Type the Sl.No): ");
        scanf("%d", &pos);
        clearBuffer();
        if(pos < 0 && pos > search_result)
        {
            printf(INVALID B_RED"Please enter a valid index.\n\n"RESET);
            return;
        }
    }
    printf("\n================================\n");
    printf("\n");   
    printf("\n");   
    printf(B_CYAN "  ┌─────────────────────────────┐\n" RESET);   
    printf(B_CYAN "  │        EDIT CONTACT         │\n" RESET);  
    printf(B_CYAN "  ├─────────────────────────────┤\n" RESET);   
    printf(B_CYAN "  │ " RESET B_WHITE"1. Name                    "RESET B_CYAN "│\n" RESET);   
    printf(B_CYAN "  │ " RESET B_WHITE"2. Phone Number            "RESET B_CYAN "│\n" RESET);
    printf(B_CYAN "  │ " RESET B_WHITE"3. Mail ID                 "RESET B_CYAN "│\n" RESET);
    printf(B_CYAN "  └─────────────────────────────┘\n" RESET);
    printf("\n  What you need to edit: ")   ;
    int choice;
    scanf("%d",&choice);
    clearBuffer();

    switch(choice){
        case 1:{
            char new_name[50];
            //Ask the user name till its valid name
            do{
                printf("Enter the new name: ");
                fgets(new_name, sizeof(new_name), stdin);
                new_name[strcspn(new_name, "\n")] = 0;

                nameStatus = is_Valid_Name(new_name);
                if(nameStatus != NAME_VALID){
                    printNameError();
                }
            } while(nameStatus != NAME_VALID);

            //Overwrite the old one with new
            strcpy(myBook->contacts[original_contatct_pos[pos-1]].name, new_name);
            break;
        }

        case 2:{
            char new_phone[15];
            do{
                printf("Enter the new phone number: ");
                fgets(new_phone, sizeof(new_phone), stdin);
                new_phone[strcspn(new_phone, "\n")] = 0;

                phoneStatus = is_Valid_PhoneNumber(myBook, new_phone);
                if(phoneStatus != VALID_PHONE){
                    printPhoneError();
                }
            }while(phoneStatus != VALID_PHONE);

            strcpy(myBook->contacts[original_contatct_pos[pos-1]].phone, new_phone);       
            break;
        }
        case 3:{
            char new_mail[50];
            do{
            printf("Enter the new mail ID: ");
            fgets(new_mail, sizeof(new_mail), stdin);
            new_mail[strcspn(new_mail, "\n")] = 0;

            mailStatus = is_Valid_Mail(myBook, new_mail);
            if(mailStatus != MAIL_VALID){
                printMailError();
            }
            } while(mailStatus != 1);

            strcpy(myBook->contacts[original_contatct_pos[pos-1]].mail, new_mail);        
            break;
        }
        
        default:
            return;
    }
    printf(SUCCESS B_WHITE"Contact updated successfully!\n\n" RESET);
    return;
}

void deleteContact(AddressBook * myBook)
{
    if(myBook -> contactCount == 0){
        printf(MSG_BOOK_EMPTY);
        return;
    }

    int pos = 1; //Track the index of the original contact array
    int search_result = searchContact(myBook);
    int delete;
    if(search_result == 0){
        return;
    }
    else if(search_result > 1){
        printf("Which of the above contact you want to delete (Type the Sl.No): ");
        scanf("%d", &pos);
        while(getchar() != '\n');
        if(pos < 0 && pos > search_result){
            printf( INVALID B_RED"Entered index is invalid." RESET);
            return;
        }
    }
    else{
        printf(B_WHITE "Do you want to delete the above contact("RESET B_GREEN"1 for Yes" RESET B_BLUE"0 for No" RESET B_WHITE"): " RESET);
        scanf("%d", &delete);
    }

    if(delete){
        for(int i = original_contatct_pos[pos-1]; i < myBook -> contactCount - 1; i++){
            strcpy(myBook->contacts[i].name, myBook->contacts[i+1].name);
            strcpy(myBook->contacts[i].phone, myBook->contacts[i+1].phone);
            strcpy(myBook->contacts[i].mail, myBook->contacts[i+1].mail);
        }
        myBook -> contactCount --;
        printf(SUCCESS B_WHITE"Contact deleted successfully!\n\n" RESET);
    }
    else{
        printf(ERROR B_WHITE"Contact Not Deleted\n\n" RESET);
    }
    return;
}

// Print Error Functions
void printNameError()
{
    switch(nameStatus){
        case NAME_INVALID_CHAR : printf(INVALID B_WHITE"Name must contain alphabets and space only.\n\n" RESET); break;
    }
}

void printPhoneError(){

    switch(phoneStatus){
        case PHONE_NOT_10_DIGITS:   printf(INVALID B_WHITE"Phone number must be 10 digits only\n\n"RESET);    break;
        case PHONE_NOT_DIGITS:      printf(INVALID B_WHITE"Phone number must be digits only\n\n" RESET);      break;
        case DUPLICATE_PHONE:       printf(INVALID B_WHITE"Phone number already exists.\n\n" RESET);          break;
        default : break;
    }
}

void printMailError()
{
    switch(mailStatus){
        case MAIL_TOO_SHORT:       printf(INVALID B_WHITE"Email too short. Min 7 chars.\n\n"RESET);           break;
        case MAIL_MULTI_CHAR_AT:   printf(INVALID B_WHITE"Only one '@' allowed.\n\n"RESET);                   break;
        case MAIL_NO_AT:           printf(INVALID B_WHITE"Email must contain '@'.\n\n"RESET);                 break;
        case MAIL_NO_DOT_COM:      printf(INVALID B_WHITE"Email must end with '.com'.\n\n"RESET);             break;
        case MAIL_NO_CHAR_AT:      printf(INVALID B_WHITE"Need character between '@' and '.com'.\n\n"RESET);  break;
        case MAIL_DUPLICATE:       printf(INVALID B_WHITE"This email already exists.\n\n"RESET);              break;
        case MAIL_INVALID_CHAR:    printf(INVALID B_WHITE"Email should not contain such character\n\n"RESET); break;
        default : break;
    }
}

/*Sort the contact*/
void sortContacts(AddressBook *myBook){
    for(int i = 0; i < myBook -> contactCount; i++){
        for(int j = i + 1; j < myBook -> contactCount; j++){
            if(strcmp(myBook -> contacts[i].name, myBook -> contacts[j].name) > 0){
                ContactInfo temp = myBook -> contacts[i];
                myBook -> contacts[i] = myBook -> contacts[j];
                myBook -> contacts[j] = temp;
            }
        }
    }
}