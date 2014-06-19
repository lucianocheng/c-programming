#include <stdio.h>
#include <stdlib.h>   /* required for exit() system call     */
#include <string.h>
#include <sys/stat.h> /* required for stat() system call     */

#define BW 0 /* binary write mode */
#define BR 1 /* binary read  mode */
#define TW 2 /* text write   mode */
#define TR 3 /* text read    mode */

/*-------------------------------------------------------------- 
| extract.c starter file
| Programmer: YOUR NAME GOES HERE
| Version: 1.0
| Date: DATE GOES HERE
| History:
-------------------------------------------------------------- */

/* extern function prototypes */
FILE * fopen(const char *, const char *);
int fclose(FILE *);

/* YOU WRITE THIS - at bottom of file */
static void unwatermark();

/* my function prototypes */
static void showusage_and_quit(char * *);
static void showerror_and_quit(char * *);
static void prepread(char *,int,FILE * *,char * *);
static void closefiles();
static void prepwrite(char *,int,FILE * *,char * *);
static int samestring(char *, char *);

/* globals local to this file */
static char * fil_br_nam;       /* string name of binary input file */
static FILE * fil_br_num;       /* file number of binary input file */

static char * fil_tw_nam;       /* string name of binary output file */
static FILE * fil_tw_num;       /* file number of binary output file */



/*-------------------------------------------------------------- 
| main()
|    argv[0] - char * - points to the program name            (from system)
|    argv[1] - char * - points to the binary input file name  (from user)
|    argv[2] - char * - points to the text output file name    (from user)
|    argv[3] - char * - string value of number of bits to extract (from user)
|
| opens two files (binary input and text output)
-------------------------------------------------------------- */

int main(int argc, char * argv[])
{
   int retval;             /* reports stat() success or failure   */

   int text_bitcount;      /* number bits to be extracted */

   if (argc != 4) showusage_and_quit(argv);

   fil_br_nam = argv[1]; /* capture binary input  file name */
   fil_tw_nam = argv[2]; /* capture text   output file name */
   text_bitcount = atoi(argv[3]);

/*
   printf("\n extracting %d bits\n",text_bitcount);
*/

   if (samestring(fil_br_nam,fil_tw_nam)==1) showerror_and_quit(argv);

   prepread(fil_br_nam,BR,&fil_br_num,&argv[0]);
   prepwrite(fil_tw_nam,TW,&fil_tw_num,&argv[0]);

   unwatermark(text_bitcount); /* files are all open now - YOU WRITE THIS */

   closefiles();

   return 0;

} /* end main */



/*-------------------------------------------------------------- 
| prepread()
| opens an existing file for reading
|
| arguments:
|    char *   - points to the filename
|    int      - identifies how the file should be opened
|    FILE * * - sets caller's FILE *
|    char * * - argv (needed in case of errors)
|
| arguments to stat():
|    char *        - points to the file name
|    struct stat * - points to a "stat" struct to be filled
| if stat() returns success, you can access the "stat" struct fields
-------------------------------------------------------------- */
static void prepread(char * filename, int mode,
                     FILE * * filenumber, char * * argv)
{
   struct stat filestruct; /* calling stat() fills this structure */
   int retval;             /* reports stat() success or failure   */

   retval = stat(filename,&filestruct); /* fill stat struct */
   if (retval < 0)
   {
      printf("\ncould not find file %s\n",filename);
      showusage_and_quit(argv);
   }
   else /* file found */
   {
      switch (mode)
      {
         case BR:
            *filenumber = fopen(filename,"rb"); 
	    break;
         case TR:
            *filenumber = fopen(filename,"rt"); 
	    break;
         default:
            printf("\nshould never get here\n");
            showusage_and_quit(argv);
	    break;
      } /* end switch */
      if (filenumber == NULL)
      {
         printf("\ncould not open file %s\n",filename);
         showusage_and_quit(argv);
      }

      /*
         printf("\nopened file %s (%ld bytes) for reading\n",
	         filename,filestruct.st_size);
      */

   } /* else file found */

   return;

} /* end prepread */



/*-------------------------------------------------------------- 
| prepwrite()
| opens a file for writing, and queries user whether to
|     overwrite an existing file
|
| arguments:
|    char *   - points to the filename
|    int      - identifies how the file should be opened
|    FILE * * - sets caller's FILE *
|    char * * - argv (needed in case of errors)
|
| arguments to stat():
|    char *        - points to the file name
|    struct stat * - points to a "stat" struct to be filled
| if stat() returns success, you can access the "stat" struct fields
-------------------------------------------------------------- */
static void prepwrite(char * filename, int mode,
                     FILE * * filenumber, char * * argv)
{

   struct stat filestruct; /* calling stat() fills this structure */
   int retval;             /* reports stat() success or failure   */

   retval = stat(filename,&filestruct); /* fill stat struct */
   if (retval >= 0)
   {
      printf("\noutput filename must not exist, quitting\n");
      showusage_and_quit(argv);
   }

   switch (mode)
   {
      case BW:
         *filenumber = fopen(filename,"wb"); 
         break;
      case TW:
         *filenumber = fopen(filename,"wt"); 
         break;
      default:
         printf("\nshould never get here\n");
         showusage_and_quit(argv);
         break;
   } /* end switch */

   if (filenumber == NULL)
   {
      printf("\ncould not open file %s\n",filename);
      showusage_and_quit(argv);
   }

   /*
      printf("\nopened file %s for writing\n",filename);
   */

   return;
} /* end prepwrite*/




/*-------------------------------------------------------------- 
| samestring()
|     performs a char-by-char string comparison
|
| returns 0 if two strings are NOT identical
| returns 1 if two strings are identical
-------------------------------------------------------------- */
static int samestring(char * str1, char * str2)
{
   int retval=0;
   int i;
   int str1len;
   int str2len;

   str1len = strlen(str1);
   str2len = strlen(str2);
   if (str1len==str2len)
   {
      retval = 1;
      for (i=0;i<str1len;i++)
      {
         if (str1[i]!=str2[i]) retval = 0;
      }
   }
   return retval;
}


/*-------------------------------------------------------------- 
| closefiles()
|     closes any open files, reports success only if files were already open
-------------------------------------------------------------- */
static void closefiles()
{
   if (fil_br_num!=NULL) if (fclose(fil_br_num)==0); /* printf("\n2\n"); */
   if (fil_tw_num!=NULL) if (fclose(fil_tw_num)==0); /* printf("\n3\n"); */
   return;
}


/*-------------------------------------------------------------- 
| showusage_and_quit()
|
| called if user gives two arguments that are identical
|   (obviously an error)
-------------------------------------------------------------- */
static void showerror_and_quit(char * * argv)
{
   printf("\nUsage: %s indirty.bmp output.txt numberOfBitsToExtract\n\n",argv[0]); 
   printf("  (no 2 arguments may be identical)\n\n"); 
   closefiles();
   exit(EXIT_FAILURE);
}


/*-------------------------------------------------------------- 
| showusage_and_quit()
|
| called if user fails to give a filename on the command line
-------------------------------------------------------------- */
static void showusage_and_quit(char * * argv)
{
   printf("\nUsage: %s indirty.bmp output.txt numberOfBitsToExtract\n\n",argv[0]); 
   closefiles();
   exit(EXIT_FAILURE);
}



static void unwatermark(int text_bitcount)
{

   /* YOUR CODE GOES HERE */
   /* REMOVE printf below */
   printf("\nAll files open and ready to go - remove this line!\n");

   return;
} /* end unwatermark */
