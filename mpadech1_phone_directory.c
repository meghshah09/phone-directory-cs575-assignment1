#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include<time.h>
#include <stdbool.h>
#include<unistd.h>


// Telephone directory Struct
typedef struct Directory
{
    char *fname;
    char *lname;
    char *phone;
} DirectoryStruct;

// Create Telephone Directory by reading input file and tokenizing it using strtok
DirectoryStruct * Create(char * fileName)
{
    char buff[255];
    DirectoryStruct * array = malloc(sizeof(DirectoryStruct)*100);
    char *token;
    int j=0;
    FILE *fptr;

    fptr = fopen (fileName,"r");

    while(fgets(buff,sizeof(buff),fptr))
    {
        token = strtok(buff, " ") ;
        array[j].fname = strdup(token);

        token = strtok(NULL,", ");
        array[j].lname = strdup(token);

        token = strtok(NULL," ");
        array[j].phone = strdup(token);

        j++;

    }
    array[j].fname = NULL;
    fclose(fptr);
    return array;
}


// A generic method to get the directory length, returns integer.
int directoryLength(DirectoryStruct * dir)
{
    int cnt=0;
    while(dir[cnt].fname !=NULL)
    {

        cnt++;
    }
    return cnt;
}

// Display all records from Directory.
// It is called when you pass option 4 through the command prompt.
void showDirectory(DirectoryStruct * dir)
{

    int j  = 0 ;
    printf("Number of contacts found : %d\n",directoryLength(dir));
    while(dir[j].fname !=NULL)
    {
        printf("\n");
        printf("%s\n", dir[j].fname);
        printf("%s\n", dir[j].lname);
        printf("%s\n", dir[j].phone);

        j++;
    }
}


// Conquering logic for merge Sort
void merge(DirectoryStruct * dir, int s, int m, int e)
{

    int ind1 = m-s+1;
    int ind2 = e-m;
    DirectoryStruct *t1= malloc(sizeof(DirectoryStruct)*100);
    DirectoryStruct *t2 = malloc(sizeof(DirectoryStruct)*100);

    for(int i =0; i<ind1; i++)
    {
        t1[i].lname=strdup(dir[s+i].lname);
        t1[i].fname=strdup(dir[s+i].fname);
        t1[i].phone=strdup(dir[s+i].phone);
    }

    for(int j =0; j<ind2; j++)
    {
        t2[j].lname=strdup(dir[m+1+j].lname);
        t2[j].fname=strdup(dir[m+1+j].fname);
        t2[j].phone=strdup(dir[m+1+j].phone);
    }

    int i=0,j=0;
    int k=s;
    while(i<ind1 && j<ind2)
    {

        if(strcmp(t1[i].lname,t2[j].lname)>0)
        {
            //string1 is greater than string 2.
            dir[k].fname = t2[j].fname;
            dir[k].lname = t2[j].lname;
            dir[k].phone = t2[j].phone;
            j++;

        }
        else if(strcmp(t1[i].lname,t2[j].lname)==0)
        {

            //both string are equal.
            if(strcmp(t1[i].fname,t2[j].fname)>0)  // Now Comparing first Name.
            {
                // String1 fname is greater than String2 fname.
                dir[k].fname = t2[j].fname;
                dir[k].lname = t2[j].lname;
                dir[k].phone = t2[j].phone;
                j++;
            }

            else
            {
                // String2 fname is greater than String1 fname.
                dir[k].fname = t1[i].fname;
                dir[k].lname = t1[i].lname;
                dir[k].phone = t1[i].phone;
                i++;
            }

        }
        else
        {
            // String2 lname is greater than string1 lname
            dir[k].fname= t1[i].fname;
            dir[k].lname= t1[i].lname;
            dir[k].phone= t1[i].phone;
            i++;
        }
        k++;

    }

    while(i<ind1)
    {
        dir[k].fname = t1[i].fname;
        dir[k].lname = t1[i].lname;
        dir[k].phone = t1[i].phone;
        i++;
        k++;
    }

    while(j<ind2)
    {
        dir[k].fname = t2[j].fname;
        dir[k].lname = t2[j].lname;
        dir[k].phone = t2[j].phone;
        j++;
        k++;
    }

}

// Core logic for Merge Sort
void merge_sort(DirectoryStruct * dir, int start, int end)
{

    if(start<end)
    {
        int mid = (start+end)/2;
        merge_sort(dir, start, mid);
        merge_sort(dir, mid+1, end);
        merge(dir, start, mid, end);

    }

}

// Randomize method for Randomized Quick Sort.
void randomize(DirectoryStruct * dir, int len)
{
    int j = rand()%(len);
    DirectoryStruct * temp = malloc(sizeof(DirectoryStruct)*100);
    temp[0].fname = dir[0].fname;
    temp[0].lname = dir[0].lname;
    temp[0].phone = dir[0].phone;
    dir[0].fname = dir[j].fname;
    dir[0].lname = dir[j].lname;
    dir[0].phone = dir[j].phone;
    dir[j].fname = temp[0].fname;
    dir[j].lname = temp[0].lname;
    dir[j].phone = temp[0].phone;


}

// Dividing algorithm for Quick sort.
// It will get a randomized pivot and than start swapping the numbers accordingly.(numbers lesser than pivot goes towards left and remaining towards right)
int partition(DirectoryStruct * dir, int s, int e)
{
    int randomPivotIndex = s+rand()%(e-s+1);
    DirectoryStruct pivot = dir[randomPivotIndex];
    int i = s-1;
    DirectoryStruct temp;

    temp = dir[randomPivotIndex];
    dir[randomPivotIndex]=dir[e];
    dir[e] = temp;

    for(int j=s; j<e; j++)
    {

        if(strcmp(dir[j].lname,pivot.lname)<0)
        {
            //String2 is greater than String1.
            i++;

            temp = dir[i];
            dir[i]=dir[j];
            dir[j] = temp;

        }
        else if(strcmp(dir[j].lname,pivot.lname)==0 && strcmp(dir[j].fname,pivot.fname)<0)
        {
            //String 2 is greater than String1
            i++;

            temp = dir[i];
            dir[i]=dir[j];
            dir[j] = temp;
        }
        else if(strcmp(dir[j].lname,pivot.lname)==0 && strcmp(dir[j].fname,pivot.fname)==0 && strcmp(dir[j].phone,pivot.phone)<=0)
        {
            //String2 is greater than string1
            i++;

            temp = dir[i];
            dir[i]=dir[j];
            dir[j] = temp;
        }

    }

    temp = dir[i+1];
    dir[i+1]=dir[e];
    dir[e] = temp;
    return i+1;
}

// Core Quick sort logic.
void quick_sort(DirectoryStruct * dir, int start, int end)
{

    int j;

    if(start<end)
    {
        j = partition(dir,start,end);
        quick_sort(dir,start,j-1);
        quick_sort(dir,j+1,end);
    }

}

// Returns a boolean indicating whether the Quick Sort to be implemented or not.
int findingMatch(DirectoryStruct * dir)
{

    for( int i =0; i<directoryLength(dir); i++)
    {

        for(int j=i+1; j<directoryLength(dir); j++)
        {

            if(strcmp(dir[i].fname,dir[j].fname)==0 && strcmp(dir[i].lname,dir[j].lname)==0)
            {

                return 1;

            }
        }

    }
    return 0;
}

// Calling Merge Sort on the Directory, after Merge sorted, calling Randomized Quick Sort.
void sortDirectory(DirectoryStruct * dir)
{

    int l = directoryLength(dir);

    merge_sort(dir,0,l-1);

    int matchFlag = findingMatch(dir);

    if(matchFlag == 1)
    {
        randomize(dir,l-1); // Randomizing the directory first.
        quick_sort(dir,0,l-1);
    }
}

// Calling Search directory method  by passing 2 from command prompt.
// Binary search have been used for searching record in the directory.
// If records exist, than displays record, else , record not found displayed.
int searchDirectory(DirectoryStruct* dirStr,int start,int end,char *fname,char*lname,bool isToPrint)
{

    int lowerBound = start;
    int upperBound = end;
    bool setPrintVar = isToPrint;
    if(end >=start)
    {
        int mid = start + (end - start)/2;

        int upCounter = 0;
        int upperlevel = mid - 1;
        int downCounter = 0;
        int lowerlevel = mid + 1;
        int totalCounter = 0;

        if(strcmp(dirStr[mid].fname,fname) == 0 && strcmp(dirStr[mid].lname,lname)== 0)
        {

            while(upperlevel >= lowerBound && strcmp(dirStr[upperlevel].fname,fname) == 0 && strcmp(dirStr[upperlevel].lname,lname)== 0)
            {
                upCounter++;
                upperlevel = upperlevel - 1;
            }
            while(lowerlevel <= upperBound && strcmp(dirStr[lowerlevel].fname,fname) == 0 && strcmp(dirStr[lowerlevel].lname,lname)== 0)
            {
                downCounter++;
                lowerlevel = lowerlevel + 1;
            }
            totalCounter = upCounter + downCounter;
            if(upCounter > 0)
            {
                mid =  mid - upCounter;
                while(totalCounter >= 0)
                {
                    if(setPrintVar)
                    {
                        printf("Location: %d\n Firstname :%s\n Secondname:%s\n PhoneNumber:%s\n",mid,dirStr[mid].fname,dirStr[mid].lname,dirStr[mid].phone);
                    }
                    totalCounter--;
                    mid++;
                }

                return mid-1;
            }
            else if(downCounter > 0)
            {
                while(totalCounter >= 0)
                {
                    if(setPrintVar)
                    {
                        printf("Location: %d\n Firstname :%s\n Secondname:%s\n PhoneNumber:%s\n",mid,dirStr[mid].fname,dirStr[mid].lname,dirStr[mid].phone);
                    }
                    totalCounter--;
                    mid++;
                }

                return mid-1;
            }

            if(setPrintVar)
            {
                printf("Location: %d\n Firstname :%s\n Secondname:%s\n PhoneNumber:%s\n",mid,dirStr[mid].fname,dirStr[mid].lname,dirStr[mid].phone);
            }

            return mid;

        }


        if(strcmp(dirStr[mid].lname,lname) == 0)
        {
            if(strcmp(dirStr[mid].fname,fname) > 0)
            {
                return searchDirectory(dirStr,start,mid-1,fname,lname,setPrintVar);
            }
            else
            {
                return searchDirectory(dirStr,mid+1,end,fname,lname,setPrintVar);
            }
        }

        if(strcmp(dirStr[mid].fname,fname) == 0)
        {

            if(strcmp(dirStr[mid].lname,lname) > 0)
            {
                return searchDirectory(dirStr,start,mid-1,fname,lname,setPrintVar);
            }
            else
            {
                return searchDirectory(dirStr,mid+1,end,fname,lname,setPrintVar);
            }
        }

        if(strcmp(dirStr[mid].lname,lname) > 0)
        {
            return searchDirectory(dirStr,start,mid-1,fname,lname,setPrintVar);
        }

        return searchDirectory(dirStr,mid+1,end,fname,lname,setPrintVar);
    }

    if(setPrintVar)
    {
        printf("NAME NOT FOUND\n\n");
        printf("Please re-check the input entered, it could have following errors:\n");
        printf("1.First name's or last name's alphabet not entered in Capital\n");
        printf("2.Spell errors\n");
        printf("3.if not any of above, record doesn't exist in directory \n");
    }

    return -1;
}

// Delete record entered by user.
// If record found, deleted from Dir struct, else display message of record not found
void deleteEntry(DirectoryStruct* dirStr,int start,int end,char *fname,char*lname)
{
    int index = searchDirectory(dirStr,start,end-1,fname,lname,false);

    if(index < 0)
    {
        printf("Unable to delete as entry not found\n");
        printf("Please re-check the input entered, it could have following errors:\n");
        printf("1.First name's or last name's alphabet not entered in Capital\n");
        printf("2.Spell errors\n");
        printf("3.if not any of above, record actually doesn't exist in directory \n");
    }
    else
    {
        for(int i = index; i < end; i++)
        {
            dirStr[i] = dirStr[i + 1];
        }

        dirStr[end-1].fname = NULL;
        printf("Record deleted successfully \n");
    }
}

// This method will Insert the records entered by user.
void insert(DirectoryStruct * dir, char * fname, char * lname, char * phone)
{

    int len = directoryLength(dir);
    dir[len].fname = fname;
    dir[len].lname = lname;
    dir[len].phone = phone;

    dir[len+1].fname = NULL;


}

// Helper function to avoid duplicate records to be entered in the directory.
int compare(DirectoryStruct * dir, char * fname, char * lname, char * phone)
{

    for( int i =0; i<directoryLength(dir); i++)
    {

        if(strcmp(dir[i].fname,fname)==0 && strcmp(dir[i].lname,lname)==0 && strcmp(dir[i].phone,phone)==0)
        {
            return 1;
        }
    }
    return 0;

}

// Driver program
int main (int argc, char * argv[])
{
    printf("========Welcome to Phone Directory ========\n");
    if(argv[1] != NULL && argc >1 && argc <=2)
    {
        if(access(argv[1],F_OK) != -1)
        {
            int a;
            printf("Creating phone Directory with the given input file : %s\n", argv[1]);
            printf("\n");

            DirectoryStruct *dir = Create(argv[1]);

            printf("\n");

            printf("Phone Directory Created...\n");
            char * fname = malloc(100);
            char * lname = malloc(100);
            char * phone = malloc(100);
            printf("Applying Sorting Technique on Directory...\n");
            sortDirectory(dir);
            printf("Phone Directory Sorted...\n");
            do
            {
                printf("Please Provide the Below Option :\n");
                printf(" 1.Insert             (press 1)\n 2.Search             (press 2)\n 3.Delete             (press 3)\n 4.Show Directory     (press 4)\n 5.Exit               (press 5)\n");
                scanf("%d",&a);

                switch(a)
                {

                case 1 :

                    printf("Enter the First Name and Last Name separated by space : \n");
                    scanf("%s", fname);
                    scanf("%s",lname);
                    printf("Enter 10 digit Phone Number without space in the following format : \n");
                    printf("EXAMPLE : (xxx)xxx-xxxx\n");
                    scanf("%s", phone);
                    printf("Inserting....\n");
                    //check if the entry already exists.
                    if(compare(dir,fname,lname,phone)==0)
                    {
                        insert(dir,fname,lname,phone);
                        printf("Inserted.....\n");
                        printf("Now Re-Sorting the Directory.....\n");
                        sortDirectory(dir);
                        printf("Re-Sorted the Directory....\n");
                    }
                    else
                    {
                        printf("Sorry we tried inserting the data but we think the data already exists in the Directory\n");
                    }
                    a=6;
                    break;
                case 2:
                    printf ("Please enter name to be searched\n");

                    char *fname = malloc(100);
                    char *lname = malloc(100);

                    scanf("%s",fname);
                    scanf("%s",lname);
                    printf("Searching....\n\n");
                    int end = directoryLength(dir);
                    bool isPrint = true;

                    searchDirectory(dir,0,end-1,fname,lname,isPrint);
                    a=6;
                    break;
                case 3:
                    printf ("Please enter name to be deleted\n");
                    char *fnameDel = malloc(100);
                    char *lnameDel = malloc(100);
                    scanf("%s",fnameDel);
                    scanf("%s",lnameDel);
                    printf("Deleting....\n");
                    int endDel = directoryLength(dir);
                    deleteEntry(dir,0,endDel,fnameDel,lnameDel);
                    a=6;
                    break;
                case 4:
                    printf("Phone directory :\n");
                    showDirectory(dir);
                    a=6;
                    break;
                case 5:
                    printf("Exiting....\n");
                    exit(0);
                    break;

                default:
                    printf("Not the Correct Option\n Please re-run the program.\n");
                    printf("Exiting....\n");
                    exit(0);

                    break;

                }

            }
            while(1);
        }
        else
        {
            printf("Input file not found.\n");
            return 0;
        }
    }
    else
    {
        printf("No input file found. Please re-run the program with correct input file.\n");
        return 0;
    }
    return 0;
}

