#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int DisplayDirectories(const char *name, int level)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return -1;
    if (!(entry = readdir(dir)))
        return -1;

    do
    {
        if (entry->d_type == DT_DIR)
        {
            char path[PATH_MAX + 1];
            int len = snprintf(path, sizeof(path) - 1, "%s/%s", name, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            printf("%*s[%s]\n", level * 2, "", entry->d_name);
            DisplayDirectories(path, level + 1);
        }
    } while (entry = readdir(dir));
    closedir(dir);
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

    errors = DisplayDirectories(argv[1], 0);

    if (errors)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}