#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char task[100][100];
char date[100][11];
char status[100][15];
int indx = 0;

void add();
void show(char[100][11], char[100][100], int);
void del(int);
void complete(int);
void open(int);
void load();
void save();

int main()
{
    int op, option, flag = 1;

    load();

    while (flag == 1)
    {
        printf("1. Add a task\n2. Show\n3. Delete\n4. Mark completed\n5. Mark open\n6. quit\n");
        printf("Choose an option:\n");
        scanf("%d", &op);
        printf("\n");

        switch (op)
        {
        case 1:
            add();
            break;
        case 2:
            show(date, task, indx);
            break;
        case 3:
            show(date, task, indx);
            printf("Enter the task number to be deleted: \n");
            scanf("%d", &option);
            printf("\n");
            del(option);
            break;
        case 4:
            show(date, task, indx);
            printf("Enter the task number to be marked as completed: \n");
            scanf("%d", &option);
            printf("\n");
            complete(option);
            break;
        case 5:
            show(date, task, indx);
            printf("Enter the task number to be marked as opened: \n");
            scanf("%d", &option);
            printf("\n");
            open(option);
            break;
        case 6:
            flag = 0;
            break;
        default:
            printf("Invalid option. Try again");
            break;
        }
    }

    return 0;
}

void add()
{
    printf("Add a task: \n");
    scanf(" %[^\n]", task[indx]);
    printf("Enter due date for the task (yyyy-mm-dd): \n");
    scanf("%s", date[indx]);
    printf("\nTask has been added successfully\n\n");
    strcpy(status[indx], "open");
    indx++;
    save();
}

void show(char date[100][11], char task[100][100], int indx)
{
    int i, j;
    char store_date[11], store_task[100];

    for (i = 0; i < indx - 1; i++)
    {
        for (j = 0; j < indx - i - 1; j++)
        {
            if (strcmp(date[j], date[j + 1]) > 0)
            {
                strcpy(store_date, date[j]);
                strcpy(date[j], date[j + 1]);
                strcpy(date[j + 1], store_date);

                strcpy(store_task, task[j]);
                strcpy(task[j], task[j + 1]);
                strcpy(task[j + 1], store_task);
            }
        }
    }    
    struct tm *local;
    time_t t;
    char day[4];
    t = time(NULL);
    local = localtime(&t);
    strftime(day, sizeof(day), "%a", local);

    printf("Your To-Do List\n");
    
    printf("Last modified on, %s %d at %d:%02d ", day, local->tm_mday, local->tm_hour, local->tm_min);

    if (local->tm_hour > 12)
        printf("PM\n\n");
    else
        printf("AM\n\n");

    for (i = 0; i < indx; i++)
    {
        printf("%d. %s, Due Date: %s, Status: %s\n", i + 1, task[i], date[i], status[i]);
    }
    printf("\n\n");
    save();
}

void del(int line_num)
{
    if (line_num < 1 || line_num > indx)
    {
        printf("Invalid task number.\n");
        return;
    }

    int i;
    for (i = line_num - 1; i < indx - 1; i++)
    {
        strcpy(task[i], task[i + 1]);
        strcpy(date[i], date[i + 1]);
        strcpy(status[i], status[i + 1]);
    }
    indx--;
    printf("Task %d has been deleted successfully.\n\n", line_num);
    save();
}

void complete(int line_num)
{
        if (line_num < 1 || line_num > indx)
    {
        printf("Invalid task number.\n");
        return;
    }

    if (strcmp(status[line_num-1], "open") == 0)
    strcpy(status[line_num-1], "completed");


    printf("Task %d has been marked as completed successfully.\n\n", line_num);

    save();
}

void open(int line_num)
{
        if (line_num < 1 || line_num > indx)
    {
        printf("Invalid task number.\n");
        return;
    }

    if (strcmp(status[line_num-1], "completed") == 0)
    strcpy(status[line_num-1], "open");


    printf("Task %d has been marked as open successfully.\n\n", line_num);

    save();
}

void load()
{
    FILE *fp;
    fp = fopen("Your To-Do List.txt", "r");
    if (fp == NULL)
    {
        printf("Failed to execute the task");
        exit(1);
    }
    else
    {
        int i = 0;
        while (fscanf(fp, "%[^,], %[^,], %[^\n]\n", task[i], date[i], status[i]) == 3)
        {
            i++;
        }
        indx = i;
        fclose(fp);
    }
}



void save()
{
    FILE *fp;
    fp = fopen("Your To-Do List.txt", "w");
    if (fp == NULL)
    {
        printf("Failed to execute the task");
        exit(1);
    }
    
    else
    {
        for (int i = 0; i < indx; i++)
        {
            fprintf(fp, "%s, %s, %s\n", task[i], date[i], status[i]);
        }
        fclose(fp);
    }
}

