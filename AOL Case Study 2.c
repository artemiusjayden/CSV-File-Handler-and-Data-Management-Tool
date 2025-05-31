#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Struct used to store all the data in separate and manageable chunks
typedef struct {
    char loc[101];
    char city[101];
    int price;
    int rooms;
    int bath;
    int carp;
    char type[101];
    char furn[101];
} Data;

//Prints all the data with correct spacing
void PrintAll(Data p) {
    printf("%-25s %-18s %-10d %-7d %-10d %-10d %-12s %-12s\n", p.loc, p.city, p.price, p.rooms, p.bath, p.carp, p.type, p.furn);
}

//Checks each data, and compares them to user's inputs. If the user's search and data matches, it prints the entire line.
void searchPrint(Data properties[], int *count, char find[50], int *found, char *col) {
    int i;
    *found = 0;
    for (i = 0; i < *count; i++) {
        int match = 0;

        if (strcmp(col, "Location") == 0 && strcmp(find, properties[i].loc) == 0) {
            match = 1;
        } else if (strcmp(col, "City") == 0 && strcmp(find, properties[i].city) == 0) {
            match = 1;
        } else if (strcmp(col, "Price") == 0 && atoi(find) == properties[i].price) {
            match = 1;
        } else if (strcmp(col, "Rooms") == 0 && atoi(find) == properties[i].rooms) {
            match = 1;
        } else if (strcmp(col, "Bath") == 0 && atoi(find) == properties[i].bath) {
            match = 1;
        } else if (strcmp(col, "Carpark") == 0 && atoi(find) == properties[i].carp) {
            match = 1;
        } else if (strcmp(col, "Type") == 0 && strcmp(find, properties[i].type) == 0) {
            match = 1;
        } else if (strcmp(col, "Furnish") == 0 && strcmp(find, properties[i].furn) == 0) {
            match = 1;
        }

        if (match == 1) {
            if (*found == 0) {
                printf("Data found. Detail of data:\n");
                printf("Location     	          City               Price      Rooms   Bathroom   Carpark    Type         Furnish\n");
            }
            *found = 1;
            PrintAll(properties[i]);
        }
    }
    if (*found == 0) {
        printf("Data not found!\n");
    }
}

//Swaps two chosen lines
void swap(Data *a, Data *b) {
    Data temp = *a;
    *a = *b;
    *b = temp;
}

//Sorts the data according to user's input, then prints the first ten lines
void sortPrint(Data properties[], char col[1001], char order[1001], int *count, int *found) {
    int i, j;
    *found = 0;

    for (i = 0; i < *count - 1; i++) {
        for (j = 0; j < *count - 1 - i; j++) {
            int diff = 0;

            if (strcmp(col, "Rooms") == 0) {
                diff = properties[j + 1].rooms - properties[j].rooms;
            } else if (strcmp(col, "Price") == 0) {
                diff = properties[j + 1].price - properties[j].price;
            } else if (strcmp(col, "Bath") == 0) {
                diff = properties[j + 1].bath - properties[j].bath;
            } else if (strcmp(col, "Carpark") == 0) {
                diff = properties[j + 1].carp - properties[j].carp;
            } else if (strcmp(col, "Location") == 0) {
                diff = strcmp(properties[j + 1].loc, properties[j].loc);
            } else if (strcmp(col, "City") == 0) {
                diff = strcmp(properties[j + 1].city, properties[j].city);
            } else if (strcmp(col, "Type") == 0) {
                diff = strcmp(properties[j + 1].type, properties[j].type);
            } else if (strcmp(col, "Furnish") == 0) {
                diff = strcmp(properties[j + 1].furn, properties[j].furn);
            }

            if ((strcmp(order, "asc") == 0 && diff < 0) || (strcmp(order, "dsc") == 0 && diff > 0)) {
                swap(&properties[j], &properties[j + 1]);
                *found = 1;
            }
        }
    }
    if (*found == 1) {
        printf("Data found. Detail of data:\n");
        printf("Location     	          City               Price      Rooms   Bathroom   Carpark    Type         Furnish\n");
        for (i = 0; i < 10; i++) {
            PrintAll(properties[i]);
        }
    } else {
        printf("Data not found!\n");
    }
}

//Creates a buffer after each process
void waitForButton() {
	printf("\nClick enter to continue...\n");
    getchar();
}

//Opens the file, making sure it handles the header and checks if it is NULL or not. 
//If it detects an empty file it shows an error.
//It also scans each line and stores it in the struct with respective identities.
int main() {
    FILE *file = fopen("file.csv", "r");

    if (file == NULL) {
        printf("Invalid File\n");
        return 1;
    }

    char end;
    int count = 0;
	char header[1001];
    fscanf(file, "%[^\n]", header);
    fgetc(file);
                    
	while ((end = fgetc(file)) != EOF) {
        if (end == '\n') {
            count++;
        }
    }

    if (count == 0) {
        fclose(file);
        printf("Invalid, file is empty\n");
        return 1;
    }
    fclose(file);

    file = fopen("file.csv", "r");
    if (file == NULL) {
        printf("Invalid File\n");
        return 1;
    }
    Data properties[count];

    fscanf(file, "%[^\n]", header);
    fgetc(file);

	int i=0;
    for ( i = 0; i < count; i++) {
        fscanf(file, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s", properties[i].loc, properties[i].city, &properties[i].price, &properties[i].rooms, &properties[i].bath, &properties[i].carp, properties[i].type, properties[i].furn);
		fgetc(file);               
	}                           
    fclose(file);      
                       
    int choice;
    do {
        printf("What do you want to do?\n");
        printf("1. Display data\n");
        printf("2. Search Data\n");
        printf("3. Sort Data\n");
        printf("4. Export Data\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
        	while (getchar() != '\n'); 
        	printf("Invalid input. Please enter a number between 1 and 5.\n");
        	waitForButton();
    	}
    //Displays number of rows depending on the user's input, and handles invalid inputs.
        if (choice == 1) {
            int rows, i;
            do {
                printf("Number of rows: ");
                if (scanf("%d", &rows) != 1 || rows < 1) {
                    printf("Invalid input. Please enter a number between 1 and %d.\n", count);
                    while (getchar() != '\n');
                }else {
                	if (rows > count){
                		rows = count;
					}
                    break;
                }
            } while (1);
            printf("Location     	          City               Price      Rooms   Bathroom   Carpark    Type         Furnish\n");
            for (i = 0; i < rows && i < count; i++) {
                PrintAll(properties[i]);
            }
            while (getchar() != '\n');
            waitForButton();
    //User inputs column and query, and prints every line that matches.
        } else if (choice == 2) {
            char chooseCol[1001], dataFind[1001];
            int valid = 0, i;
    		const char *validCols[8] = {"Location", "City", "Price", "Rooms", "Bath", "Carpark", "Type", "Furnish"};
            int numCol = 8;
			
			do {	
				printf("Choose column: ");
        		scanf("%s", chooseCol);
        		getchar(); 
        		for (i = 0; i < numCol; i++) {
            		if (strcmp(chooseCol, validCols[i]) == 0) {
                		valid = 1;
                		break;
            		}
        		}
        		if (!valid) {
            		printf("Invalid column. Please choose: Location, City, Price, Rooms, Bath, Carpark, Type, Furnish.\n");
        		}
    		} while (!valid);
            
			printf("What data do you want to find? ");
            scanf("%s", dataFind);
            getchar();

            int found = 0;
            searchPrint(properties, &count, dataFind, &found, chooseCol);
            waitForButton();
    //Sorts the data according to user's input, and displays the first 10 data.
        } else if (choice == 3) {
            char chooseCol[1001], ascdsc[1001];
        	int valid = 0;
    		const char *validCols[8] = {"Location", "City", "Price", "Rooms", "Bath", "Carpark", "Type", "Furnish"};
            int numCol = 8;
            
            do{
            	printf("Choose column: ");
            	scanf("%s", chooseCol);
            	getchar();
            	valid=0;
            	int i = 0;
            	for (i = 0; i < numCol; i++) {
            		if (strcmp(chooseCol, validCols[i]) == 0) {
                	valid = 1;
                	break;
            	}
			}
            	if (!valid) {
            		printf("Invalid column. Please choose from the following: Location, City, Price, Rooms, Bath, Carpark, Type, Furnish.\n");
        		}
    		} while (!valid);
    		do {
        		printf("Sort ascending or descending? ");
        		scanf("%s", ascdsc);
        		getchar();
        		
				if (strcmp(ascdsc, "asc") != 0 && strcmp(ascdsc, "dsc") != 0) {
            		printf("Invalid. Please choose from the following: asc, dsc.\n");
        		}
    		} while (strcmp(ascdsc, "asc") != 0 && strcmp(ascdsc, "dsc") != 0); 

            int found = 0;

            sortPrint(properties, chooseCol, ascdsc, &count, &found);
            waitForButton();
    //Writes the modified data into a .csv file that the user specifies.
        } else if (choice == 4) {
            char fileName[1001];
            
			printf("File name: ");
            scanf("%s", fileName);
            getchar();
            strcat(fileName, ".csv");

            FILE *newFile = fopen(fileName, "w");

            if (newFile == NULL) {
                printf("Error, cannot access %s file\n", fileName);
            } else {
                fprintf(newFile, "%s\n", header);
                int i = 0;
                for (i = 0; i < count; i++) {
					fprintf(newFile, "%s,%s,%d,%d,%d,%d,%s,%s\n",
                            properties[i].loc, properties[i].city, properties[i].price,
                            properties[i].rooms, properties[i].bath, properties[i].carp,
                            properties[i].type, properties[i].furn);
                }
                printf("Data successfully written to file %s!\n", fileName);
                fclose(newFile);
            }
            waitForButton();
        } else if (choice != 5) {
            printf("Invalid input. Please enter a number from 1 to 5.\n");
        }
    //Closes the program and says thank you
    } while (choice != 5);

    printf("Thank you for using the program!\n");
    return 0;
}
