#include <dirent.h>
#include <stdio.h>

int my_double_ls(const char *name)
{
    struct dirent *d;
    DIR *dp;

    /* open the directory and check for failure */
    if ((dp = opendir(name)) == NULL)
    {
        return (-1);
    }

    /* continue looping through the directory
     * printing out the directory entry name as long
     * as the inode number is valid
     */
    while (d = readdir(dp))
    {
        if (d->d_ino != 0)
        {
            printf("%s\n", d->d_name);
        }
    }

    /* now go back to the beginning of the directory ... */
    rewinddir(dp);

    /* ... and print out the directory again */
    while (d = readdir(dp))
    {
        if (d->d_ino != 0)
        {
            printf("%s\n", d->d_name);
        }
    }

    closedir(dp);
    return (0);
}

void DisplayDirectories()
{
    //recursive function
    //loop through directories
    //print directory
    //call DisplayDirectories on each directory
}



int main(int argc, char **argv)
{
    int errors;
    errors = 0;

    //call DisplayDirectories

    if (errors)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}