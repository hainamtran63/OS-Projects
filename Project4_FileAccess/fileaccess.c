/*** fileaccess.c ***/
/*** Ryan Scopio ***/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <dirent.h>

/* fileaccess file ... 		*/
/* print info on access modes 	*/

// [Permissions][# of hardlinks][file owner][file group][file size]
// [modification time][filename]

// [file type][owner permissions][group permissions][everyone permissions]

void DisplayInfo(struct stat);

int main(int argc, char **argv)
{
    int errors, k;
    struct stat fileStat;
    struct dirent *dp;
    DIR *dfd;
    errors = 0;

    //if multiple files, print total blocks
    if (argc == 1)
    {
		//choose current directory
		printf("Usage: %s dirname\n", argv[0]);
		return 0;
    }

    for (k = 1; k < argc; k++)
    {
		/* fetch inode information */
		//char filename[100];
		//sprintf(filename, "%s/%s", argv[k], dp->d_name);
		//printf("filename: %s", filename);
		if (stat(argv[k], &fileStat) == (-1))
		{
			fprintf(stderr, "%s: cannot access %s\n", argv[0], argv[k]);
			errors++;
			continue;
		}

		/* print file info */
		DisplayInfo(fileStat);
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
    //owner permissions
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    //group permissions
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    //everyone permissions
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

    printf("."); //I don't know what this part represents

    /* # of hardlinks */
    printf(" %d", fileStat.st_nlink);

    /* file owner */
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
    {
		printf(" %s", pwd->pw_name);
    }
    else
    {
		printf(" d", fileStat.st_uid);
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
    printf(" %d", fileStat.st_size);

    /* modification time */
    time = localtime(&fileStat.st_mtime);
    char datestring[256];
    strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), time);
    printf(" %s", datestring);
}
