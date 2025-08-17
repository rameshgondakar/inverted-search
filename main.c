/*
Documenation
Name: Ramesh Gondakar
Date: 3/04/2025
Project Name : Inverted Search
input : gcc *.c
        ./a.out f1.txt f2.txt f.txt f3.txt

[ f.txt ] => FILE NOT EXIST arg[3]

[ f3.txt ] => File is Empty file  arg[4]

File validation successful

The valid files are f1.txt -> f2.txt
1. Create database
2. Display
3. Search
4. Update
5. Save
6. Exit
Enter an option:
*/
#include<stdio.h>
#include<string.h>
#include"main.h"
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char *argv[]) 
{
    int opt = 0;
    
    fn_node *head = NULL;
    main_node *hashtable[27] = {NULL};  // Hash table to store words
    int ret, count = 0;
    fn_node *temp;

    // Validate files
    if ((ret = file_validate(argc, argv)) == SUCCESS) 
    {
        printf("File validation successful\n");
    } else {
        printf("File validation failed\n");
        return FAILURE;
    }

    // Insert each file name into the linked list
    for (int i = 1; i < argc; i++) 
    {
        if (argv[i] != NULL) 
        {
            if ((ret = insert_at_last(&head, argv[i])) == DUPLICATE_FOUND) 
            {
                printf("DUPLICATE: '%s' arg[%d]\n", argv[i], i);      
            }
        }
    }

    // Print the list of files
    printf("\n");
    print_list(head);

    // Main menu loop
    while (opt != 6) {
        printf("1. Create database\n2. Display\n3. Search\n4. Update\n5. Save\n6. Exit\n");
        printf("Enter an option: ");
        scanf("%d", &opt);
        printf("---------------------------------------------------------------------\n");

        switch (opt) {
            case 1:  // Create database
                temp = head;
                FILE *fptr;
                char buff[30];
                int index = 0, j = 0;
                while (temp) {
                    fptr = fopen(temp->file_name, "r");
                    if (fptr == NULL) 
                    {
                        printf("Error: Could not open file %s\n", temp->file_name);
                        return FAILURE;
                    }

                    while (fscanf(fptr, "%s", buff) != EOF) 
                    {
                        // Handle punctuation by mapping it to index 26
                        if ((buff[0] >= 33 && buff[0] <= 47) || (buff[0] >= 58 && buff[0] <= 63)) 
                        {
                            index = 26;
                        } 
                        else 
                        {
                            index = (tolower(buff[0])) % 97;
                        }
                        
                        // Create or update the database
                        if (create_data_base(&hashtable[index], buff, temp->file_name) != SUCCESS) {
                            printf("Error creating database\n");
                            return FAILURE;
                        }
                    }
                    fclose(fptr);
                    temp = temp->link;
                }
                printf("DATABASE CREATED SUCCESSFULLY\n");
                break;

            case 2:  // Display database
                count = 0;
                printf("Index    Word   File Count    Filename      Word Count\n");
                for (int i = 0; i < 27; i++) {
                    count += display_data(hashtable[i], i);
                }
                if (count == 0) {
                    printf("DATABASE IS EMPTY\n");
                }
                break;

            case 3:  // Search for a word
                {
                    char word[20];
                    int index;
                    printf("Enter a word to search: ");
                    scanf("%s", word);
                    index = (tolower(word[0])) % 97;
                    printf("Index\tWord\tFile Count\tFilename\tWord Count\n");
                    if (search_data(hashtable[index], index, word) != SUCCESS) {
                        printf("WORD NOT FOUND\n");
                    }
                }
                break;

                case 4:  
                {
                    char file[256];  // Increased buffer size
                    printf("\nEnter the file name for update: ");
                    scanf("%255s", file);  // Prevent buffer overflow
            
                    FILE *test = fopen(file, "r");
                    if (test == NULL) 
                    {
                        perror("ERROR");
                        fprintf(stderr, "ERROR: Unable to open file '%s'. Please check if the file exists.\n", file);
                    } 
                    else 
                    {
                        fclose(test);
                        if (update_validation(file, hashtable) == SUCCESS) 
                        {
                            printf("\nINFO: Updation Successful !!\n");
                        }
                    }
                    break;
                }            
            case 5:  // Save the database to a file
                ret = save(hashtable);
                if (ret == FAILURE) {
                    printf("\tDATABASE IS EMPTY\n");
                } else {
                    printf("\tDATA SAVED SUCCESSFULLY\n");
                }
                break;

            case 6:  // Exit
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return SUCCESS;
}
