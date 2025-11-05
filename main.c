#include <stdio.h>
#include "contact.h"                     // Include header file containing function and structure declarations for contact management     
int main()                               // Main function - Entry point of the address book program
{
    char choice;                         // Variable to store user menu choice
    AddressBook addressBook;            // Declare an AddressBook structure variable
    initialize(&addressBook);           // Initialize the address book
    do 
    {         // Loop until the user chooses to exit
        printf("\nADDRESS BOOK MENU:\n");                  
        printf("1. CREATE CONTACT\n");                    // Add a new contact
        printf("2. SEARCH CONTACT\n");                    // Search for an existing contact
        printf("3. EDIT CONTACT\n");                      // Edit details of an existing contact
        printf("4. DELETE CONTACT\n");                    // Delete a contact from the address book
        printf("5. LIST ALL CONTACTS\n");                 // Display all contacts
    	printf("6. SAVE CONTACT\n");
        printf("7.EXIT\n");		
        printf("ENTER YOUR CHOICE: ");
        scanf(" %c", &choice);
        switch (choice) 
        {
            case 49:
                createContact(&addressBook);
                break;
            case 50:
                searchContact(&addressBook);
                break;
            case 51:
                editContact(&addressBook);
                break;
            case 52:
                deleteContact(&addressBook);
                break;
            case 53:          
                listContacts(&addressBook);
                break;
            case 54:
                printf("SAVING \n");
                saveContactsToFile(&addressBook);
                break;
            case 55:
                printf("EXITING..\n");
            default:
                printf("INVALID CHOICE. PLEASE TRY AGAIN.\n");
        }
    } while (choice != '7');
    return 0;
}
