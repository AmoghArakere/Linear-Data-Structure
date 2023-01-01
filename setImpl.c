/*
  Filters are a great way of optimizing search. This program demonstrates basic filtration by using a set (linear data structure)
  to return elements that satisfy both the inclusion and exclusion conditions.

  Program that takes divisibility and non-divisibility conditions from user 
  and filters the pre-defined set of natural numbers 1-25 to give the required results.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//structure which holds a set - program ensures elements are unique and ordered (ascending)
typedef struct 
{
    int num[25];
    int size;
} set;
set S, divisibleSet, nonDivisibleSet, resultSet;

// structure which holds elements and size
typedef struct 
{
    int arr[20];
    int size;
} list;

list includeList, excludeList;

char operation;

// Bubble sort
set sortSet(set s)
{
    int i, j;
    for (i = 0; i < s.size - 1; i++) 
    {
        for (j = 0; j < s.size - i - 1; j++) 
        {
            if (s.num[j] > s.num[j + 1]) 
            {
                int temp = s.num[j];
                s.num[j] = s.num[j + 1];
                s.num[j + 1] = temp;
            }
        }
    }

    return s;
}

// Removes duplicates (works only on sorted array)
set removeDuplicates(set s)
{
    int sSize = s.size;

    int p = 1;
    for (int i = 1; i < sSize; i++) 
    {
        if (s.num[i] == s.num[i - 1]) 
        {
            s.size--;
            continue;
        }

        s.num[p] = s.num[i];
        p++;
    }

    return s;
}

// Returns true or false depending on whether element is found
bool foundInBinarySearch(int item, set s) 
{
    int l = 0, r = s.size - 1, mid;
    while (l <= r) 
    {
        mid = (int)((l + r) / 2);
        if (item == s.num[mid]) 
        {
            return true;
        } 
        else if (item < s.num[mid]) 
        {
            r = mid - 1;
        } 
        else 
        {
            l = mid + 1;
        }
    }
    
    return false;
}

// Searches for each element of divSet in nonDivSet and if present adds them to the result set
set intersect(set setA, set setB) 
{    
    for (int i = 0; i < setA.size; i++) 
    {
        if (foundInBinarySearch(setA.num[i], setB)) 
        {
            resultSet.num[resultSet.size] = setA.num[i];
            resultSet.size++;
        }
    }
    
    return resultSet;
}

// Merges in order div set and non div set without duplicates <similar to polynomial addition logic>
set conjoin(set setA, set setB) 
{
    int i, j, k;
    for (i = 0, j = 0, k = 0; i < setA.size && j < setB.size; k++) 
    {
        if (setA.num[i] < setB.num[j]) 
        {
            resultSet.num[k] = setA.num[i];
            i++;
        }
        else if (setA.num[i] == setB.num[j]) 
        {
            resultSet.num[k] = setA.num[i];
            i++;
            j++;
        }
        else {
            resultSet.num[k] = setB.num[j];
            j++;
        }
        
        resultSet.size++;
    }
    
    while (i < setA.size) 
    {
        resultSet.num[k] = setA.num[i];
        i++;
        k++;
        resultSet.size++;
    }

    while (j < setB.size) 
    {
        resultSet.num[k] = setB.num[j];
        j++;
        k++;
        resultSet.size++;
    }

    return resultSet;
}

// This function orchestrates the logic and calls all other functions
set filter(list includeList, list excludeList, char operation) 
{
    int i, j;
    // Makes div set (can contain duplicates and improper order)
    for (i = 0; i < includeList.size; i++) 
    {
        for (j = 0; j < S.size; j++) 
        {
            if (includeList.arr[i] > 0 && S.num[j] % includeList.arr[i] == 0) 
            {
                divisibleSet.num[divisibleSet.size] = S.num[j];
                divisibleSet.size++;
            }
        }
    }
    // Sort and remove duplicates
    divisibleSet = sortSet(divisibleSet);
    divisibleSet = removeDuplicates(divisibleSet);

    printf("Div Set Size: %d\n", divisibleSet.size);
    printf("Div Set Elements:\n");
    for (i = 0; i < divisibleSet.size; i++) 
    {
        printf("%d ", divisibleSet.num[i]);
    }
    printf("\n----\n");
    
    // Makes non div set (can contain duplicates and improper order)
    for (i = 0; i < S.size; i++) 
    {
        int currCount = 0;
        for (j = 0; j < excludeList.size; j++) 
        {
            if (excludeList.arr[j] > 0 && S.num[i] % excludeList.arr[j] != 0) 
            {
                currCount++;
            }
        }

        if (currCount == excludeList.size) 
        {
            nonDivisibleSet.num[nonDivisibleSet.size] = S.num[i];
            nonDivisibleSet.size++;
        }
    }
    
    // Sort and remove duplicates
    nonDivisibleSet = sortSet(nonDivisibleSet);
    nonDivisibleSet = removeDuplicates(nonDivisibleSet);

    printf("Non Div Set Size: %d\n", nonDivisibleSet.size);
    printf("Non Div Set Elements:\n");
    for (i = 0; i < nonDivisibleSet.size; i++) 
    {
        printf("%d ", nonDivisibleSet.num[i]);
    }
    printf("\n----\n");

    switch (operation)
    {
    case 'i':
        return intersect(divisibleSet, nonDivisibleSet);
    case 'c':
        return conjoin(divisibleSet, nonDivisibleSet);
    default:
        printf("Invalid option, try again");
        exit(1);
    }
}

int main() 
{

    int i;
    // Populates pre-defined set with 1-25
    for (i = 0; i < 25; i++) 
    {
        S.num[i] = i + 1;
        S.size++;
    }

    printf("Enter the wanted divisibilities and -1 to end list:\n");
    for (i = 0;; i++)
    {
        scanf("%d", &includeList.arr[i]);
        if (includeList.arr[i] == -1)
            break;
        includeList.size++;
    }

    
    printf("Enter the unwanted divisibilities and -1 to end list:\n");
    for (i = 0;; i++)
    {
        scanf("%d", &excludeList.arr[i]);
        if (excludeList.arr[i] == -1)
            break;
        excludeList.size++;
    }

    printf("Enter c/i (conjunction/intersection):");
    scanf(" %c", &operation);

    set res = filter(includeList, excludeList, operation);

    printf("Result Set Size: %d\n", res.size);
    printf("Result Set Elements:\n");
    for (i = 0; i < res.size; i++) 
    {
        printf("%d ", res.num[i]);
    }
    printf("\n----\n");

    return 0;
}