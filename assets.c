#include <stdio.h>
#include "asset.h"

#ifndef NAME_LEN
#define NAME_LEN 50
#endif

#ifndef DEPT_LEN
#define DEPT_LEN 50
#endif

int assetID[MAX_ASSETS];
char assetName[MAX_ASSETS][NAME_LEN];
char assetType[MAX_ASSETS][TYPE_LEN];
float purchaseValue[MAX_ASSETS];
char department[MAX_ASSETS][DEPT_LEN];
char condition[MAX_ASSETS][CONDITION_LEN];

int count = 0;

void addAsset(void)
{
   printf("\n----Add Asset----\n");

   printf("Enter Asset ID:");
   scanf("%d", &assetID[count]);

   printf("Enter Asset Name:");
   scanf(" %[^\n]", assetName[count]);

   printf("Enter Asset Type");
   scanf(" %[^\n]", assetType[count]);

   printf("Enter Purchace Value");
   scanf(" %f", &purchaseValue[count]);

   printf("Enter Department");
   scanf(" %[^\n]", department[count]);

   printf("Enter condition");
   scanf(" %[^\n]", condition[count]);

   count++;

   printf("\n Asset successfully added.\n");

}



void assetDisplay(void)
{
    int i;

    printf("\n------ASSETS-------\n");

    if (count == 0)
    {
        printf("No Assets Available");

        return;

    }
    printf("%-8d %-20s %-15s %-15.2f %-20s %-15s\n",
       "assetID",
       "assetName",
       "assetType",
       "purchaseValue",
       "department",
       "condition");

       printf("------------------------------------------------------------------------\n");

       for (i =0; i < count;i++)
       {
        printf("%-8d %-20.20s %-15.15s %-11.2f %-20.20s %-15.15s\n",
        assetID[i], 
        assetName[i], 
        assetType[i], 
        purchaseValue[i], 
        department[i], 
        condition[i]);


       }

       printf("\nAssets: %d\n",count);
    }

       void searchAsset(void)
       {
        int search;
        int search_results =0;
        int i;

        printf("\n------SEARCH ASSETS-------\n");

        printf("enter Asset ID");
        scanf("%d", &search);

        for (i = 0; i < count; i++)
        {
            if(assetID[i] ==search)
            {
                printf("\n------Search Results------\n");

                printf("Asset ID : %d\n", assetID[i]); 
                printf("Asset Name : %s\n", assetName[i]); 
                printf("Asset Type : %s\n", assetType[i]); 
                printf("Purchase Value : N$ %.2f\n", purchaseValue[i]); 
                printf("Department : %s\n", department[i]); 
                printf("Condition : %s\n", condition[i]);

                search_results =1;
                break;
            }

        }

        if (search_results == 0)
        {
            printf("\nAsset was not found\n");

        }
    }

        void choice(void){

        int choice;

        do 
        {
        
            printf("\n------ ASSET MANAGEMENT ------\n"); 
            printf("1.Add Asset");
            printf("2. Display Assets\n"); 
            printf("3. Search Assets\n"); 
            printf("4. Exit\n"); 
            printf("Enter your choice: "); 
            scanf("%d", &choice);
            if(choice==1)
            {
                addAsset();
            }


            else if (choice ==2)
            {
                assetDisplay();

            }
            else if (choice ==3)
            {
                searchAsset();
            
            }
            else if(choice == 4)
            {
                printf("\nExiting ASSET MANAGEMENT\n");
            }
            else 
            {
                printf("\nInvalid choice.\n");
            }
        
        }while (choice !=4);

        
    
        
    }       

    

       
    
