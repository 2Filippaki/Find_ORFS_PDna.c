#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ValidDseq (char* dseq);
void FindORF (char* dseq);
void reverse_dseq (char* dseq, char* rdseq);
void rm_spaces (char* dseq);


int main ()
{
	int c,len,value,t;
	char dseq[1000],rdseq[1000],a[6];

	printf("Hello,\nThis program is going to find the ORF's in a Prokaryotic Dna sequence.\n");
	printf("The only valid characters are (A,T,G,C),if you need to exit the program please type 'exit'\nΑny empty character within the sequence will be deleted so that we have a sequence without gaps.\n");

	while (1)
	{
		printf("_______________________________________________\n");
		printf("Please insert a Prokaryotic Dna sequence:\n");

		fgets(dseq,sizeof(dseq),stdin);
		dseq[strcspn(dseq,"\n")] = 0;

			if(strcmp(dseq,"exit")==0)
			{
				printf("You are exiting the program,I hope it was usefull! :D\n");
				break;
			}

			if (strlen(dseq) <= 6 )
			{
				printf("I am expecting a Prokaryotic sequence!Please insert a sequence larger than 6 characters.\n");
				continue;
			}

		rm_spaces(dseq);



		len = strlen(dseq);
		value = 1;

		printf("Keep in mind that the numbering starts from 0.\n");

			for (t = 0; t < len ; t++)
			{

				dseq[t] = toupper(dseq[t]);
			}

			printf("\n                     ---->\n");
			printf("The sequence is : 5'~> %s ~>3'\n",dseq);
			printf("Assuming that the sequence is 5' ----> 3'.\n\n");

			if (!ValidDseq(dseq))
			{
				printf("Error: Invalid character detected! Please try again.\n");
				value = 0;
			}
			if (value == 1)
			{
				FindORF(dseq);

				printf("\nIn case you are not sure if the direction of the sequence is 5' -> 3',\nwould you like to reverse the sequence and look for ORF's in the reversed sequence?\nType 'y' for YES or 'n' for NO:\n");

					while (1)
					{

						fgets(a, sizeof(a), stdin);
						a[strcspn(a, "\n")] = 0;

 							if (strcmp(a, "y") == 0 || strcmp(a, "n") == 0 || strcmp(a,"exit") == 0)
							{
								break;
							}
							else
							{
								printf("Please type 'y' for YES or 'n' for NO.\n");
							}

					}

					if(strcmp(a,"exit") == 0)

					{
						printf("You are exiting the program,I hope it was usefull! :D\n");
						break;
					}


					if (strcmp(a,"y") == 0)
					{
						printf(" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n");
						 printf("|Now Finding ORF's in opposite direction!|\n");
						printf(" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n");

						reverse_dseq (dseq, rdseq);

						FindORF(rdseq);
					}
			}
	}
	return 0;
}


int ValidDseq (char* dseq)

{
	int c;
	c = 0;
		for(c = 0; c < strlen(dseq) ; c++)

		{

			if (dseq[c] != 'A' && dseq[c] != 'T' && dseq[c] != 'G' && dseq[c] != 'C')

			{
				return 0;
			}
		}

	return 1;
}

void FindORF(char * dseq)

{

	int len, startpoint, stoppoint, foundORF, stopCcount, neareststop, c, j, e;

	char *startcodon = "ATG";
	char *stopcodon[] = {"TAA","TAG","TGA"};
	char orf[1000];

	len = strlen(dseq);
	foundORF = 0;
	stopCcount = 3;
	neareststop = -1;
	startpoint = -1;

		for(c = 0 ; c < len - 2 ; c++)

		{

			if (strncmp(&dseq[c], startcodon , 3) == 0)

			{
				startpoint = c;

				printf("A start codon found in position %d\n", startpoint);

				neareststop = -1;

					for (j = startpoint ; j < len -2 ; j += 3)

					{

						for(e = 0 ; e  < stopCcount ; e++)

						{

							if(strncmp(&dseq[j] , stopcodon[e] , 3) == 0)

							{
								neareststop = j + 3;
								stoppoint = j;

								printf("A stop codon found in position %d\n",stoppoint);

								break;

							}
						}

						if (neareststop != -1)

						{
							break;
						}
					}

					if(neareststop == -1)
					{
						printf("No stop codon found!\n");
					}

					if (neareststop != -1)

					{
						strncpy(orf , &dseq[startpoint] , neareststop - startpoint);
						orf[neareststop - startpoint] = '\0';

						printf("An ORF found: %s,\nfrom position %d to position %d!\n\n", orf, startpoint, stoppoint + 2);

						foundORF++;
					}

			}

		}

		if (startpoint == -1)

		{
			printf("\nNo start codon found!\n");
		}

	printf("The total amount of ORFs found in this DNA sequence are %d\n", foundORF);

}


void reverse_dseq (char* dseq, char* rdseq)

{

	int len, i, k;

	k = 0;
	i = 0;

	len = strlen(dseq);

		for (i = len - 1 ; i >= 0 ; i--)

		{
			rdseq[k] = dseq[i];
			k++;
		}

	rdseq[len] = '\0';

	printf("The sequence starting from the opposite direction: '3<~ %s <~'5\n", dseq);
	printf("\n5'~> %s ~> 3'\n", rdseq);
	printf("        -------->\n\n");

}

void rm_spaces(char* dseq)
{
	int c, j;
	char nsp [1000];

	j=0;
	c=0;
		for (c = 0; dseq[c] != '\0'; c++)
		{
			if (dseq[c] != ' ')
			{
				nsp[j] = dseq[c];
				j++;
			}
		}
	nsp[j] = '\0';
	strcpy(dseq, nsp);
}
