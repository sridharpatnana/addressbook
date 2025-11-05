#include <stdio.h>
#include <stdlib.h>                 
#include <string.h>                 
#include <ctype.h>                                
#include "file.h"
#include "contact.h" 
void listContacts(AddressBook *addressBook) 
{
    printf("\n%-5s %-20s %-15s %-30s\n","SL.NO. ","NAME", "PHONE NUMBER", "Email");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i <addressBook->contactCount&& addressBook->contactCount< 100; i++)     // Loop through contacts and print each one
    {
        printf("%-5d %-20s %-15s %-30s\n", i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook) 
{
    Contact contact;
    addressBook->contactCount = 0;
    FILE *fp=NULL;
    fp=fopen("contact.txt","r");
    if(fp==NULL)
    {
        printf("No file exist");
        return;
    }
    while(!feof(fp))
    {
        if(fscanf(fp,"%[^,],%[^,],%[^\n]\n",contact.name,contact.phone,contact.email)==3)
        addressBook->contacts[addressBook->contactCount]=contact;
        addressBook->contactCount++;
        if(addressBook->contactCount>=MAX_CONTACTS)
        return;
            
    }
    fclose(fp);
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

//*****check with phone number function***** 
int checkphone(AddressBook*addressBook,char*phone)
{
    int count=0;
    for(int i=0;phone[i]!='\0';i++)
    {
        count++;
        if(!isdigit(phone[i]))      //checking for all characters are digits or not
        {
            return 0;
        }
    }
    if(count!=10)                   //condition for phone number contain 10 digits or not
    {
        return 0;
    }
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (!strcmp(addressBook->contacts[i].phone, phone)) //comparing the phone number with previous data
        {
            return 0;
        }
    }
    return 1;
}
//***check with email function***** 
int checkmail(AddressBook*addressBook,char*email)            
{
    int count=0,j;
    int len=strlen(email);
    for(int i=0;email[i]!='\0';i++)
    {
        if(isupper(email[i]))            //ccondition for any character is upper case is there or not
        {
            return 0;
        }
        if(email[i]=='@')                //condition for @ character is present in email or not  for 1 time only
        {
            j=i;
            count++;
        }
    }
    if(len<4||count!=1)                     
    {
        return 0;
    }
    for (int i=j+1; i < len - 4; i++)          
    {
        if ((!islower(email[i])))              //all characters are lower case or not for confirmation
        {
            return 0;                           
        }
    }
    if (strcmp(email + len - 4, ".com"))        //condition for .com is there in email or not
    {
        return 0;
    }
    for (int i = 0; i < addressBook->contactCount; i++)            
    {
        if (!strcmp(addressBook->contacts[i].email, email))   //comparing the email number with previous data      
        {
            return 0;                                               
        }
    }
    return 1;        
}
//*******Create contact******** 
void createContact(AddressBook *addressBook)
{
	Contact newcontact;
    int limit=0;
    while(1)
    {
    printf("Enter the name:\n");
    scanf(" %[^\n]",newcontact.name);
    if(isalpha(newcontact.name[0]))
    {
        break;
    }
    else
    {
        printf("enter a valid name\n");
        limit++;
        if(limit>=3)
        {
            printf("Too many invalid inputs\n");
            return;
        }
    }
    }
    limit=0;
    while(1)
    {
    printf("Enter the phone:\n");
    scanf(" %s",newcontact.phone);
    if(checkphone(addressBook,newcontact.phone))
    {
        break;        
    }
    else
    {
        printf("Enter a valid phone\n");
        limit++;
        if(limit>=3)
        {
            printf("Too many invalid inputs\n");
            return;
        }
    }
    }
    limit=0;
    while(1)
    {
    printf("Enter the Email:\n");
    scanf(" %s",newcontact.email);
    if(checkmail(addressBook,newcontact.email))
    {
        break;
    }
    else
    {
        printf("Enter valid mail\n");
        limit++;
        if(limit>=3)
        {
            printf("Too many invalid inputs\n");
            return;
        }
    }
    }
    int option;
    printf("Choose one option:\n 1.confirm to create 2.Not confirm to create\n");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        addressBook->contacts[addressBook->contactCount]=newcontact;
        addressBook->contactCount++;
        printf("contact saved successfully.");
        break;
        case 2:
        printf("contact not saved.");
        break;
        default:
        printf("Enter a valid option.");                  
    }       
}
//***search for name function definition****** 
int searchwithname(AddressBook *addressBook,char *name)
{
    int index=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(!strcmp(addressBook->contacts[i].name,name))
        {
            printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            index++;
        }
    }
    if(index==0)
    {
        printf("contact is not found\n");
    }
    return index;
}
//****search for phone function definition ******* 
int searchwithphone(AddressBook *addressBook,char *phone)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(!strcmp(addressBook->contacts[i].phone,phone))
        {
            printf("Contact is found\n");
            printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }
    printf("contact is not found\n");
    return -1;
}
//*******search for email function definition  ******* 
int searchwithemail(AddressBook *addressBook,char *email)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(!strcmp(addressBook->contacts[i].email,email))
        {
            printf("Contact is found\n");
            printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }
    printf("contact is not found\n");
    return -1;

}
//********main search contact function*******
void searchContact(AddressBook *addressBook) 
{
   Contact searchcontact;
   int option,index;
   int limit=0;
   while(limit<3)
   {
   printf("Choose the option\n1.Name\n2.Phone\n3.Email\n");
   scanf("%d",&option);
   switch(option)
   {
    case 1:
    printf("Enter the name:");
    scanf(" %[^\n]",searchcontact.name);
    index=searchwithname(addressBook,searchcontact.name); //function call for searchwith name function
    printf("Showing data successfully!\n");
    break;
    case 2:
    printf("Enter the phone:");
    scanf("%s",searchcontact.phone);
    searchwithphone(addressBook,searchcontact.phone);     //function call for searchwith phone function
    printf("Showing data successfully!\n");
    break;
    case 3:
    printf("Enter the Email:\n");
    scanf("%s",searchcontact.email);
    searchwithemail(addressBook,searchcontact.email);      //function call for searchwith email function
    printf("Showing data successfully!\n");
    break;
    default:
    printf("Invalid option\n");
    limit++;
    if(limit>=3)
    {
        printf("Too many invalid inputs\n");
        return;
    }
    break;
   }
   }
}
//********main delete contact function********
void deleteContact(AddressBook *addressBook)
{
   Contact deletecontact;
   int option,index=-1;
   printf("Enter the option:\n1.name\n2.phone\n3.email\n");
   scanf("%d",&option);
   switch(option)
   {
    case 1:
    printf("Enter the name:");
    scanf(" %[^\n]",deletecontact.name);
    int count=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(!strcmp(addressBook->contacts[i].name,deletecontact.name))
        {
            count++;
        }
    }
    if(count==0)
    {
        printf("No contact is found\n");
        return;
    }
    else if(count==1)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(!strcmp(addressBook->contacts[i].name,deletecontact.name))
            {
                index=i;
            }
        }
    }
    else
    {
        printf("Multiple contacts detected with same name\n"); 
        printf("Enter phone or email to identify:\n");
        printf("Phone: ");
        scanf("%s",deletecontact.phone); 
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(!strcmp(addressBook->contacts[i].name,deletecontact.name)&&!strcmp(addressBook->contacts[i].phone,deletecontact.phone))
            {
                index=i;
                break;
            }
        }
        if(index==-1)
        {
            printf("No contact found with phone verify with email:\n");
            printf("Email:");
            scanf("%s",deletecontact.email);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(!strcmp(addressBook->contacts[i].name,deletecontact.name)&&!strcmp(addressBook->contacts[i].email,deletecontact.email))
                {
                    index=i;
                    break;
                }
            }
            if(index==-1)
            {
                printf("No contact is found with both phone and email\n");
                return;
            }                
        }    
    }  
    break;
    case 2:
    printf("Enter the phone number:");
    scanf("%s",deletecontact.phone);
    index=searchwithphone(addressBook,deletecontact.phone);
    break;
    case 3:
    printf("Enter the mail:");
    scanf("%s",deletecontact.email);
    index=searchwithemail(addressBook,deletecontact.email);
    break;
    default:
    printf("Invalid option");
    return;
    } 
    printf("Enter option:\n1.Confirm to Delete contact 2.cancel to Delete contact\n");
    int deleteoption;
    scanf("%d",&deleteoption);    
    switch(deleteoption)
    {
        case 1:
        for(int j=index;j<addressBook->contactCount;j++)
        {
            addressBook->contacts[j]=addressBook->contacts[j+1];                
        }
        addressBook->contactCount--;                
        printf("contact deleted successfully."); 
        break;
        case 2:
        printf("contact not deleted.");
        break;
        default:
        printf("Enter a valid option.");
    }    
}
//****edit contact*****
void editContact(AddressBook *addressBook)
{
    Contact searchContact;
    int option,index=-1;
    char edit_name[50],edit_phone[50],edit_email[50];
    printf("search contact to edit by:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d",&option);
    switch(option)
    {
    case 1:
    printf("Enter the name:\n");
    scanf(" %[^\n]",searchContact.name);
    int count=0;
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(!strcmp(addressBook->contacts[i].name,searchContact.name))
        {
            printf("%d %s %s %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            count++;
        }
    }
    if(count==0)
    {
        printf("No contacts found\n");
        return;
    }
    else if(count==1)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(!strcmp(addressBook->contacts[i].name,searchContact.name))
            {
                index=i;
                break;
            }
        }
    }
    else
    {
        printf("Multiple contacts detected with same name\n"); 
        printf("Enter phone or email to identify:\n");
        printf("Phone: ");
        scanf("%s",searchContact.phone); 
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(!strcmp(addressBook->contacts[i].name,searchContact.name)&&!strcmp(addressBook->contacts[i].phone,searchContact.phone))
            {
                index=i;
                break;
            }
        }
        if(index==-1)
        {
            printf("No contact found with phone verify with email:\n");
            printf("Email:");
            scanf("%s",searchContact.email);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(!strcmp(addressBook->contacts[i].name,searchContact.name)&&!strcmp(addressBook->contacts[i].email,searchContact.email))
                {
                    index=i;
                    break;
                }
            }
            if(index==-1)
            {
                printf("No contact is found with both phone and email\n");
                return;
            }                
        }    
    }
    break;
    case 2:
    printf("Enter the phone:\n");
    scanf("%s",searchContact.phone);
    index=searchwithphone(addressBook,searchContact.phone);
    if(index==-1)
    {
        return;
    }
    break;
    case 3:
    printf("Enter the Email:\n");
    scanf("%s",searchContact.email);
    index=searchwithemail(addressBook,searchContact.email);
    if(index==-1)
    {
        return;
    }
    break;
    default:
    printf("Invalid option\n");
    }
    //new editing data updating area//
    printf("Menu of the option to data:\n");
    printf("1.I want Edit name:\n");
    printf("2.I want Edit phone:\n");
    printf("3.I want Edit email:\n");
    printf("4.Exit from the edit function\n");
    printf("Enter the option:\n");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        printf("Enter new name:\n");
        scanf("%s",edit_name);            
        strcpy(addressBook->contacts[index].name,edit_name);
        printf("Edit name successfully\n");
        break;
        case 2:
        printf("Enter new phone:\n");
        scanf("%s",edit_phone);
        strcpy(addressBook->contacts[index].phone,edit_phone);
        printf("Edit number successfully\n");
        break;
        case 3:
        printf("Enter new email:\n");
        scanf("%s",edit_email);
        strcpy(addressBook->contacts[index].email,edit_email);
        printf("Edit email successfully\n");
        break;
        default:
        printf("Invalid choice\n");
    }   
}