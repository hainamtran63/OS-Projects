#include <stdio.h>
#include <stdlib.h>
//Ryan Scopio
//Prints lines with  line numbers, left adjusted, with a tab spacing

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printf("Error: no input file\n");
		return 1;
	}

	FILE *fileRead = fopen(argv[1],"r"); //open file as read

	if(fileRead == NULL)
	{
		printf("Error opening input file\n");
		return 1;
	}
	char buffer[10000];
	int index = 0;
	while(!feof(fileRead)) //while not end of file
	{
		buffer[index] = fgetc(fileRead); //get char from fileRead
		index++;
	}
	fclose(fileRead);

	if(buffer[0] == EOF)
	{
		return 0;
	}

	int lines = 0;
	printf("%d	", lines + 1);
	int i;
	for(i = 0; i < index - 2; i++)
	{
		printf("%c", buffer[i]);
		if(buffer[i] == '\n')
		{
			lines++;
			printf("%d	", lines + 1);
		}
	}
	printf("\n");
	return 0;
}
