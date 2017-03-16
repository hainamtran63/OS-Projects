/*** fileaccess.c ***/
/*** Ryan Scopio ***/

// [Permissions][# of hardlinks][file owner][file group][file size]
// [modification time][filename]

// [file type][owner permissions][group permissions][everyone permissions]

#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

void DisplayInfo(struct stat);

int main(int argc, char **argv)
{
  int errors, k;
  struct stat fileStat;
  DIR *dir;
  struct dirent *dent;
  errors = 0;

  //get home directory
  const char *homedir;
  if ((homedir = getenv("HOME")) == NULL)
  {
    homedir = getpwuid(getuid())->pw_dir;
  }

  //if no arguments, read file from terminal
  if (argc == 1)
  {
    char *filename;
    scanf("%s", filename);
    argv[argc++] = filename;
  }

  for (k = 1; k < argc; k++)
  {
    //create relative file path
    char *filepath = argv[k];
    if (argv[k][0] != '/')
    {
      filepath = (char *)malloc(2 + strlen(homedir) + strlen(argv[k]));
      strcpy(filepath, homedir);
      strcat(filepath, "/");
      strcat(filepath, argv[k]);
    }

    //check if file can be accessed
    if (stat(filepath, &fileStat) == (-1))
    {
      fprintf(stderr, "%s: cannot access %s\n", argv[0], argv[k]);
      errors++;
      continue;
    }

    /* print file info */
    struct passwd *pwd;
    struct group *grp;
    struct tm *time;

    /* print file permissions */
    dir = opendir(filepath);
    if (dir != NULL && dent = readdir(dir))
    {
      //file type
      printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
      //user permissions
      printf(
          ((dent->st_uid == getuid() && dent->st_mode & S_IRUSR) || (dent->st_gid == getgid() && dent->st_mode & S_IRGRP) || (dent->st_mode && S_IROTH))
              ? "r"
              : "-");
      printf(
          ((dent->st_uid == getuid() && dent->st_mode & S_IWUSR) || (dent->st_gid == getgid() && dent->st_mode & S_IWGRP) || (dent->st_mode && S_IWOTH))
              ? "w"
              : "-");
      printf(
          ((dent->st_uid == getuid() && dent->st_mode & S_IXUSR) || (dent->st_gid == getgid() && dent->st_mode & S_IXGRP) || (dent->st_mode && S_IXOTH))
              ? "x"
              : "-");
    }

    /* seperation just for looks */
    printf(".");

    /* # of hardlinks */
    printf(" %d", (int)fileStat.st_nlink);

    /* file owner */
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
    {
      printf(" %s", pwd->pw_name);
    }
    else
    {
      printf(" %d", fileStat.st_uid);
    }

    /* file group */
    if ((grp = getgrgid(fileStat.st_gid)) != NULL)
    {
      printf(" %s", grp->gr_name);
    }
    else
    {
      printf(" %d", fileStat.st_gid);
    }

    /* file size */
    printf(" %d", (int)fileStat.st_size);

    /* modification time */
    time = localtime(&fileStat.st_mtime);
    char datestring[256];
    strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), time);
    printf(" %s", datestring);

    /* file name */
    printf(" %s\n", argv[k]);
  }
  if (errors)
  {
    return (1);
  }
  else
  {
    return (0);
  }
}

void DisplayInfo(struct stat fileStat)
{
  struct passwd *pwd;
  struct group *grp;
  struct tm *time;
  /* print file permissions */
  //file type
  printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  //user permissions
  printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
  printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
  printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
  /*
  //group permissions
  printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
  printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
  printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
  //other permissions
  printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
  printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
  printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
  */
  printf("."); //I don't know what this part represents

  /* # of hardlinks */
  printf(" %d", (int)fileStat.st_nlink);

  /* file owner */
  if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
  {
    printf(" %s", pwd->pw_name);
  }
  else
  {
    printf(" %d", fileStat.st_uid);
  }

  /* file group */
  if ((grp = getgrgid(fileStat.st_gid)) != NULL)
  {
    printf(" %s", grp->gr_name);
  }
  else
  {
    printf(" %d", fileStat.st_gid);
  }

  /* file size */
  printf(" %d", (int)fileStat.st_size);

  /* modification time */
  time = localtime(&fileStat.st_mtime);
  char datestring[256];
  strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), time);
  printf(" %s", datestring);
}
