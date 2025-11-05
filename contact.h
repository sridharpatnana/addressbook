#ifndef CONTACT_H
#define CONTACT_H
#define MAX_CONTACTS 100               // Maximum number of contacts that the address book can hold
typedef struct {                       // Structure representing a single contact's information
    char name[50];
    char phone[20];
    char email[50];
} Contact;
typedef struct {                        // Structure representing the address book, which contains a list of contacts
    Contact contacts[100];              // Array to store contacts
    int contactCount;                   // Current number of contacts in the address book
} AddressBook;
void initialize(AddressBook *addressBook);                      // Initializes the address book             // Loads existing contacts into the address book
void createContact(AddressBook *addressBook);                   // Adds a new contact to the address book
void searchContact(AddressBook *addressBook);                   // Searches for a contact in the address book by name or other criteria
void editContact(AddressBook *addressBook);                     // Edits the details of an existing contact
void deleteContact(AddressBook *addressBook);                   // Deletes a contact from the address book
void listContacts(AddressBook *addressBook);                    // Displays all contacts in the address book
void saveContactsToFile(AddressBook *AddressBook);              // Saves all contacts to a file for persistence
#endif
