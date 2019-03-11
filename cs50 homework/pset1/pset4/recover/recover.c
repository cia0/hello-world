#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
BYTE buffer[512]; //makes the buffer

int main(int argc, char *argv[])
{
    int found = 0;//keep track of how many jpegs have been found
    
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }
    char *infile = argv[1];
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL){
        fprintf(stderr, "Could not open %s\n", infile);
        return 2; 
    }
    
    FILE* outptr = NULL;
    
    while (fread(buffer, 1, 512, inptr) == 512)
    {

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            {   
                //close outptr if open
                if (outptr != NULL){
                    fclose(outptr);
                }
                
            // Determine name of new file
            char filename[8];
            sprintf(filename, "%03d.jpg", found);
            
            //open new jpeg for writing
            outptr = fopen(filename, "w");
            
            found++;
            }
        //writes 512 bytes to outptr    
        if (outptr != NULL){
            fwrite(buffer, 512, 1, outptr);
        }
    }
    if (outptr != NULL){
        fclose(outptr);
    }
    fclose(inptr);
    
    return 0;
}