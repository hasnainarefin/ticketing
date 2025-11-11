#include <stdio.h>

struct User
{
    char username[50];
    char password[50];
};

int registerUser()
{
    FILE *fp = fopen("data/users.txt", "ab");
    struct User u;
    if (fp == NULL)
    {
        printf("Error opening user file!\n");
        return 0;
    }
    printf("Enter Username: ");
    fgets(u.username, sizeof(u.username), stdin);
    u.username[strcspn(u.username, "\n")] = '\0';
    printf("Enter Password: ");
    fgets(u.password, sizeof(u.password), stdin);
    u.password[strcspn(u.password, "\n")] = '\0';

    fwrite(&u, sizeof(struct User), 1, fp);
    fclose(fp);
    printf("\nUser registered successfully!\n");
    return 1;
}

int loginUser(char currentUser[])
{
    FILE *fp = fopen("data/users.txt", "rb");
    struct User u;
    char uname[50], pass[50];
    int found = 0;

    if (fp == NULL)
    {
        printf("No users registered yet!\n");
        return 0;
    }

    printf("Enter Username: ");
    fgets(uname, sizeof(uname), stdin);
    uname[strcspn(uname, "\n")] = '\0';
    printf("Enter Password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    while (fread(&u, sizeof(struct User), 1, fp) == 1)
    {
        if (strcmp(u.username, uname) == 0 && strcmp(u.password, pass) == 0)
        {
            found = 1;
            strcpy(currentUser, uname);
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("\nLogin successful! Welcome, %s.\n", uname);
    else
        printf("\nInvalid username or password!\n");

    return found;
}
