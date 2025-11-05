#include <stdio.h>
#include "file.h"
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contact.txt","w");
    if(fp == NULL) 
    {
        printf("Failed to save contacts.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    printf("Contacts saved successfully.\n");
}
   

// void loadContactsFromFile(AddressBook *addressBook)
// {

// }
