#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "address_book.h"

void saveContacts(AddressBook *myBook)
{
    //Open a file in write mode
    FILE *myFile = fopen(FILENAME, "w");
    if (myFile == NULL)
    {
        printf(FILE_ERROR);
        return;
    }

    //First line of the file contain contact count
    fprintf(myFile, "%d\n", myBook -> contactCount);

    //Store all the details
    for(int i = 0; i < myBook -> contactCount; i++)
    {
        fprintf(myFile, "%s,%s,%s\n",

                    myBook -> contacts[i].name,
                    myBook -> contacts[i].phone,
                    myBook -> contacts[i].mail
               );
    }

    //Close the file
    fclose(myFile);

    return;
}

void loadContact(AddressBook * myBook)
{
    //Open file in read mode
    FILE *myFile = fopen(FILENAME, "r");
    //Check if file open is success
    if (myFile == NULL)
    {
        myBook -> contactCount = 0;
        return;
    }
    int contactPos = 0;
    int totalContact;
    fscanf(myFile, "%d\n", &totalContact);
    myBook -> contactCount = totalContact;

    char lines[300];

    while(fgets(lines, sizeof(lines) , myFile))
    {
        lines[strcspn(lines, "\n")] = '\0';

        char * name = strtok(lines, ",");
        char * phone = strtok(NULL, ",");
        char * mail = strtok(NULL, ",");

        strcpy(myBook -> contacts[contactPos].name, name);
        strcpy(myBook -> contacts[contactPos].phone, phone);
        strcpy(myBook -> contacts[contactPos].mail, mail);
        
        if(contactPos < totalContact)contactPos ++;
    }
    //Close the file
    fclose(myFile);

    return;
}