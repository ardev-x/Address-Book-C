#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "address_book.h"

/* Function to save all contacts into file */

void saveContacts(AddressBook *myBook)
{
    //Open a file in write mode
    FILE *myFile = fopen(FILENAME, "w");
    if (myFile == NULL)
    {
        printf(ERROR B_WHITE"Could not open file.\n\n" RESET); 
        return;
    }

    //First line of the file contain contact count
    fprintf(myFile, "%d\n", myBook -> contactCount);

    //Store all the details
    for(int i = 0; i < myBook -> contactCount; i++){
        fprintf(myFile, "%s,%s,%s\n",
                    myBook -> contacts[i].name,
                    myBook -> contacts[i].phone,
                    myBook -> contacts[i].mail
               );
    }

    fclose(myFile);
    printf(SUCCESS B_WHITE"Contacts saved to " FILENAME "\n\n" RESET);
    return;
}

/* Function to load all contacts back to structure */
void loadContact(AddressBook * myBook)
{
    //Open file in read mode
    FILE *myFile = fopen(FILENAME, "r");

    //Check if file open is success
    if (myFile == NULL)
    {
        printf(ERROR B_WHITE"Could not open file.\n\n" RESET); 
        myBook -> contactCount = 0; // Initialize contact count as 0 if file not found
        return;
    }
    int contactPos = 0;  // Variable to track contact index
    int totalContact; // Variable to store total contacts from file
    fscanf(myFile, "%d\n", &totalContact);
    myBook -> contactCount = totalContact;

    //Array to store each line from file
    char lines[200];

    // Read file line by line
    while(fgets(lines, sizeof(lines) , myFile))
    {
         // Remove newline character from line
        lines[strcspn(lines, "\n")] = '\0';

        // Split the line using comma delimiter
        char * name = strtok(lines, ",");
        char * phone = strtok(NULL, ",");
        char * mail = strtok(NULL, ",");

        // Copy extracted data into structure
        strcpy(myBook -> contacts[contactPos].name, name);
        strcpy(myBook -> contacts[contactPos].phone, phone);
        strcpy(myBook -> contacts[contactPos].mail, mail);
        
        // Move to next contact position
        if(contactPos < totalContact) contactPos ++;
    }

    //Close the file
    fclose(myFile);
    printf(SUCCESS B_WHITE"Contacts loaded successfully.\n\n" RESET);
    return;
}