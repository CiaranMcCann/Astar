/*!
*  \brief Removes junk from a string
*
*  \param C-style string
*/
const char *trim(char *s) {
    char *ptr;
    if (!s)
        return NULL;   // handle NULL string
    if (!*s)
        return s;      // handle empty string
    for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
    ptr[1] = '\0';
    return s;
}

/*!
*  \brief Random function
*
*/
unsigned int randr(unsigned int min, unsigned int max)
{
       double scaled = (double)rand()/RAND_MAX;

       return (max - min +1)*scaled + min;
}

/*!
*  \brief Splits a string into as many substring as you want
* 
*  \param The buffer to split
*  \param Number of substrings to split it into
*  \param Pionters to places to store the substrings
*/
void split(char * buffer, int num, ...)
{
     char* string;
     char* tofree;
     string = strdup(trim(buffer));

     if (string != NULL)
     {
        tofree = string;

        va_list arguments; 

        //Initializing arguments to store all values after num 
        va_start ( arguments, num );           

        int i = 0;
        for (i = 0; i < num; i++ )        
        {
           //Item is the final store place of the split substring
           char ** arg = va_arg ( arguments, char *);

           //Split the strings, delimiter is space
           char * splitBuffer = strsep(&string, " ");

           //Allocate the buffer memory to store the splitBuffer
           *arg  =  malloc(sizeof(char*)*strlen(splitBuffer));

           strcpy(*arg ,splitBuffer);
           //printf("Buffer [%s] -- [%s]\n", buffer, *arg);
        }
        va_end ( arguments ); // Cleans up the list

        free(tofree);
     }
 }