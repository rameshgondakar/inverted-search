#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// Function to update the database from the backup file
int update_database(FILE *fptr, main_node *hash_t[27]);

// Function to validate the backup file
int update_validation(char file[50], main_node **hash_t) 
{
    FILE *fptr = fopen(file, "r");                   
    if (fptr == NULL) 
    {
        perror("fopen");					
        fprintf(stderr, "ERROR: Unable to open file %s\n", file);
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);					
    if (ftell(fptr) == 0)  // Check if file is empty
    {
        fprintf(stderr, "ERROR : %s File is empty\n", file);
        printf("Hence we cannot update database\n");
        fclose(fptr);
        return FAILURE;
    }
    
    rewind(fptr);
    
    char *ext = strrchr(file, '.');  
    if (!ext || strcmp(ext, ".txt") != 0)  
    {
        printf("FAILURE in %s: Pass .txt file\n", file);
        fclose(fptr);
        return FAILURE;
    }
    
    if (update_database(fptr, hash_t) != SUCCESS)   
    {
        fclose(fptr);
        return FAILURE;
    }
    
    fclose(fptr);
    return SUCCESS;
}

int update_database(FILE *fptr, main_node *hash_t[27])
{
    char arr[50];					
    int index;
    char word[50];
    int file_count;
    char file_name[50];
    int word_count;					
    
    while (fscanf(fptr, "%49s", arr) != EOF)
    {
        if (arr[0] == '#')				
        {
            // Tokenizing the line
            char *token = strtok(&arr[1], ";");
            if (!token) return FAILURE;
            index = atoi(token);

            token = strtok(NULL, ";");
            if (!token) return FAILURE;
            strcpy(word, token);

            token = strtok(NULL, ";");
            if (!token) return FAILURE;
            file_count = atoi(token);

            int i = file_count;

            if (hash_t[index] == NULL)   // Create a new main node if the index is empty
            {
                main_node *main_n = malloc(sizeof(main_node));
                if (!main_n) return FAILURE;

                main_n->file_count = file_count;
                strcpy(main_n->word, word);
                main_n->m_link = NULL;
                main_n->s_link = NULL;

                token = strtok(NULL, ";");
                if (!token) return FAILURE;
                strcpy(file_name, token);

                token = strtok(NULL, ";");
                if (!token) return FAILURE;
                word_count = atoi(token);

                sub_node *sub = malloc(sizeof(sub_node));
                if (!sub) return FAILURE;

                strcpy(sub->file_name, file_name);
                sub->word_count = word_count;
                sub->link = NULL;
                main_n->s_link = sub;

                sub_node *temp = sub;
                while (--i)				
                {
                    sub_node *sub = malloc(sizeof(sub_node));
                    if (!sub) return FAILURE;

                    token = strtok(NULL, ";");
                    if (!token) return FAILURE;
                    strcpy(file_name, token);

                    token = strtok(NULL, ";");
                    if (!token) return FAILURE;
                    word_count = atoi(token);

                    strcpy(sub->file_name, file_name);
                    sub->word_count = word_count;
                    sub->link = NULL;
                    temp->link = sub;
                    temp = sub;
                }

                hash_t[index] = main_n;				
            }
            else // If index is not empty, append to the linked list
            {
                main_node *tempt = hash_t[index], *prev = NULL;
                while (tempt != NULL)				
                {
                    prev = tempt;					
                    tempt = tempt->m_link; 
                }

                main_node *main_n = malloc(sizeof(main_node));
                if (!main_n) return FAILURE;

                main_n->file_count = file_count;
                strcpy(main_n->word, word);
                main_n->m_link = NULL;
                main_n->s_link = NULL;

                token = strtok(NULL, ";");
                if (!token) return FAILURE;
                strcpy(file_name, token);

                token = strtok(NULL, ";");
                if (!token) return FAILURE;
                word_count = atoi(token);

                sub_node *sub = malloc(sizeof(sub_node));
                if (!sub) return FAILURE;

                strcpy(sub->file_name, file_name);
                sub->word_count = word_count;
                sub->link = NULL;
                main_n->s_link = sub;

                sub_node *temp = sub;
                while (--i)				
                {
                    sub_node *sub = malloc(sizeof(sub_node));
                    if (!sub) return FAILURE;

                    token = strtok(NULL, ";");
                    if (!token) return FAILURE;
                    strcpy(file_name, token);

                    token = strtok(NULL, ";");
                    if (!token) return FAILURE;
                    word_count = atoi(token);

                    strcpy(sub->file_name, file_name);
                    sub->word_count = word_count;
                    sub->link = NULL;
                    temp->link = sub;
                    temp = sub;
                }

                prev->m_link = main_n;				
            }
        }
        else								
        {
            printf("Invalid file format\n");
            return FAILURE;
        }
    }
    return SUCCESS;
}
