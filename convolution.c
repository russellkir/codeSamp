
typedef struct pgm {
  int w;
  int h;
  int max;
  int* pData;
} pgm;

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/* 
   This LoadPGM function is an updated version that will deal with 
   comments in file headers and do at least some basic checking if the 
   file can be opened or is the correct format. It does assume the file 
   is actually a valid length once the header has been read. 
*/

void LoadPGM( char* filename, pgm* pPgm ) {
  FILE* ifp;
  int word;
  int nRead = 0;
  char readChars[256];

  //open the file, check if successful
  ifp = fopen( filename, "r" );
  if (!ifp) {
    printf("Error: Unable to open file %s.\n\n", filename);
    exit(1);
  }

  //read headers from file
  printf ("Reading PGM file: %s...\n", filename);
  fscanf (ifp, "%s", readChars);

  if (strcmp(readChars, "P2") == 0) {
    //valid file type
    //get a word from the file
    fscanf (ifp, "%s", readChars);
    while (readChars[0] == '#') {
      //if a comment, get the rest of the line and a new word
      fgets (readChars, 255, ifp);
      fscanf (ifp, "%s", readChars);
    }
    
    //ok, comments are gone
    //get width, height, color depth
    sscanf (readChars, "%d", &pPgm->w);
    fscanf (ifp, "%d", &pPgm->h);
    fscanf (ifp, "%d", &pPgm->max);

    // allocate some memory, note that on the HandyBoard you want to 
    // use constant memory and NOT use calloc/malloc
    pPgm->pData = (int*)malloc(sizeof(int) * pPgm->w * pPgm->h);
    
    // now read in the image data itself    
    for (nRead = 0; nRead < pPgm->w * pPgm->h; nRead++) {
      fscanf(ifp, "%d" ,&word);
      pPgm->pData[nRead] = word;
      // printf("nRead = %d %d\n",nRead,pPgm->pData[nRead]);
    }

    printf ("Loaded PGM. Size: %dx%d, Greyscale: %d \n", 
	    pPgm->w, pPgm->h, pPgm->max + 1);
  }
  else {
    printf ("Error: Read file type %s. Format unsupported.\n\n", readChars);
    exit(1);
  }
  fclose(ifp);
}

int find_max(int x, int y)
{
  if (x > y)
    return x;
  return y;
}

int find_min(int x, int y)
{
  if (x < y)
    return(x);
  return(y);
}

/* Simply saves the PGM file to a file whose name is in filename */

void WritePGM( char* filename, pgm* pPgm ) {
  FILE* ofp;
  int w, h, max, temp;
  int nWrite = 0;
  int i,j;

  strcat(filename, ".out.pgm");
  ofp = fopen(filename, "w");
  if (!ofp) {
    printf("Error: Unable to open file %s.\n\n", filename);
    exit(1);
  }

  printf ("Writing ouput PGM: %s\n\n", filename);

  //write the header
  fprintf( ofp, "P2\n" );
  fprintf( ofp, "%d %d\n", pPgm->w, pPgm->h );
  fprintf( ofp, "%d\n", pPgm->max );

  //write the image data
  for (i = 0; i < pPgm->h;i++) {
    for (j = 0; j < pPgm->w; j++)
    {
      temp = find_max(0, *(pPgm->pData + i * pPgm->w + j));
      temp = find_min(temp, pPgm->max);
      fprintf(ofp,"%d ", temp);
    }
    fprintf(ofp,"\n");
  }
  fclose(ofp);	
}


/* Possibly useful in debugging...prints the data portion of the pgm
 * to the screen.
 */
void PrintPGM(pgm * my_pgm)
{
  int count;
  for (count = 0; count < my_pgm->w*my_pgm->h; count++)
  {
    if (count % my_pgm->w == 0)
      printf("\n");
    printf("%d ", (my_pgm->pData)[count]);
  }
}

/* don't forget that you need to flip the mask
 * in convolution.
 */
void FlipMask(pgm * mask)
{
  int * mBuff;
  int * temp;
  int i;

  mBuff = mask->pData;
  temp = (int *) malloc((sizeof(int)) * (mask->w) * (mask->h));

  for (i = 0; i < (mask->h * mask->w); i++)
  {
    temp[i] = (mask->pData)[(mask->w) * (mask->h) - i -1];
  }

  memcpy(mBuff, temp, (sizeof(int)) * (mask->w) * (mask->h));
  free(temp);
}

void imageShift(pgm *in, pgm* out,int size, int* p_data, int min, int difference)
{
  double scaling_ratio = 256.0 / difference;
  int i = 0;

  for(i = 0; i < size; i ++)
    {
      out->pData[i] = p_data[i] - min;
      out->pData[i] *= scaling_ratio;
    }
}

//function that rescales the values such that the minimum pixel value            
//is 0 and the highest pixel value is 255                                       
void Contrast (pgm *in, pgm *out)
{

  //min and max will be the minimum and maximum pixel values that will be        
  //found and then used to perform the rescaling                                 
  int min = 255;
  int max = 0;

  //details from PGM                                                             
  int width = in -> w;
  int height = in -> h;
  int size = width * height;
  int* p_data = in -> pData;
  
  //loop that will go through and find max and min                               
  int i = 0;
  for(i = 0; i < size; i++)
    {
      //reset min/max to current pixel value                                     
      if(p_data[i] < min)
        {
          min = p_data[i];
        }
      if(p_data[i] > max)
        {
          max = p_data[i];
        }
    }
//perform the actual image shift.  This is accomplished by moving all the pixels
//down to zero and then multiplying by a scaling factor, which is the difference 
//of max and min divided into the global max + 1                                 
  double difference = max - min + 1;
  imageShift(in, out, size, p_data, min, difference);

  return;
}

/* Perform the convolution */
pgm * Convolve(pgm * image, pgm * mask)
{
  int i,j;
  int * pBuff;
  pgm * result;

  int image_size = image -> w * image -> h;

  result = (pgm *) malloc(sizeof(pgm));
  result->w = image->w;
  result->h = image->h;
  result->max = 255;
  result->pData = (int *) malloc(sizeof(int)*(image->w) * (image->h));
  FlipMask(mask);

  //loop through image

  //i goes down each row while k goes across
  //each column in the ith row
  for(int i = 0; i < image -> h; i++)
    {
      for(int k = 0; k < image -> w; k++)
	{
	 
	  //index of pixel being convolved
	  int img_ind = image -> w * i + k;
	  
	  //convolution is now performed.  The mask is applied
	  //where the upper left corner of the mask is on the
	  //current pixel, and the result of the masking is put
	  //into the outputs down-diagonal pixel location (where 
	  //the center of the mask is)
	  	  
	  int sum = 0;
	  //loop through the mask
	  for(int l = 0; l < mask -> h; l++)
	    {
	      for(int m = 0; m < mask -> w; m++)
		{
		  int mask_ind = mask -> w * l + m;
		 
		  //check to see if off board
		  if(img_ind + mask_ind < image_size
		     && img_ind+image->w*l+m <image_size)
		    {
		      sum += (mask->pData[mask_ind]*
			      image->pData[img_ind+image->w*l + m]) % INT_MAX;
		    }
		}
	    }
	  
	  int res_ind = img_ind + (image->w * (mask->h/2))
	    + mask->w/2;
	  if(res_ind < image_size)
	    {
	      result->pData[res_ind] = sum;
	    }
	}
    }

   return(result);
}

int main(int argc, char * argv[]) {
  pgm* conv_img;
  pgm* mask;
  pgm* image;
  char filename[256];
  char maskname[256];
  int val;
  int errchk;

  //check if an image filename was given, if not, ask for one
  if (argc > 1) {
    strcpy(filename, argv[1]);
    printf("Image filename is %s\n", filename);
  }
  else {
    printf ("Enter image filename: ");
    scanf ("%s", filename);
  }

  //check if a mask filename was given, if not, ask for one
  if (argc > 2) {
    strcpy(maskname, argv[2]);
    printf("Mask filename is %s\n", maskname);
  }
  else {
    printf ("Enter mask filename:  ");
    scanf ("%s", maskname);
  }

  //allocate memory for the pgm struct
  image = (pgm *) malloc (sizeof(pgm));
  mask  = (pgm *) malloc (sizeof(pgm));

  //read the file
  LoadPGM(filename, image);
  LoadPGM(maskname, mask);

  //Perform the convolution
  conv_img = Convolve(image, mask); 

  pgm* contrasted = (pgm *) malloc (sizeof(pgm));
  contrasted->max=image->max;
  contrasted->w=image->w;
  contrasted->h=image->h;
  contrasted->pData=malloc(sizeof(int)*contrasted->w*contrasted->h);

  // run contrasting                                                             
  Contrast(conv_img,contrasted);

  //finally write the new file
  WritePGM(filename, contrasted);

  free(image->pData);
  free(image);
  free(mask->pData);  
  free(mask);
  free(conv_img->pData);
  free(conv_img);
 
  //all done
  printf("Done. Have a nice day...\n\n");
}
