#include <dirent.h>
#include <stdio.h>

int DisplayDirectories(const char *name)
{
    //recursive function
    //loop through directories
    //print directory
    //call DisplayDirectories on each directory

    /* now go back to the beginning of the directory ... */
    //rewinddir(dp);

    struct dirent *d;
    DIR *dp;

    if ((dp = opendir(name)) == NULL)
    {
        return (-1);
    }

    while (d = readdir(dp))
    {
        if (d->d_ino != 0 && d->d_name != "." && d->d_name != "..")
        {
            printf("%s\n", d->d_name);
            DisplayDirectories(d->d_name);
        }
    }

    closedir(dp);
    return (0);
}

int main(int argc, char **argv)
{
    int errors;
    errors = 0;

    if (argc == 1)
    {
        char *filename;
        scanf("%s", filename);
        argv[argc++] = filename;
    }

    errors = DisplayDirectories(argv[1]);

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