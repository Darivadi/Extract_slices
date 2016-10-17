
/*******************************************************************
                       HEADERS
*******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/***************************************************************                                                
               DEFINITIONS AND PREPROCESOR DIRECTIVES                                                           
 ***************************************************************/
#define X 0
#define Y 1
#define Z 2

#define POW2(x) ((x)*(x))
#define POW3(x) ((x)*(x)*(x))
#define INDEX_C(i,j,k) (k)+(NCELLS)*((j)+(NCELLS)*(i)) //Index in C-order 

int main( int argc, char *argv[] )
{
  int m, i, j, k, l, n, nread;
  int NCELLS, counter, Size_int;
  unsigned long NTOTALCELLS;
  char *infile=NULL;
  double dummy, *PotDot=NULL, *PotDot_read=NULL;
  int up_lim, down_lim;
  double SliceSize, BoxSize, CellSize;
  int NCells_Slice, dummy_int;
  unsigned long int dummy_uli;
  char buffer[100], dummy_c;
  FILE *pf=NULL;
  
  /*+++++ Reading data +++++*/
  down_lim  = atoi(argv[1]);
  up_lim    = atoi(argv[2]);
  SliceSize = atof(argv[3]);
  
  printf("Let's read data\n");
  //pf = fopen("./../../Processed_data/Potential.bin", "r");
  pf = fopen("./../../Data/NGrid1024/CIC/out/snap_130_NGRID_1024_CIC.dens", "r");
  //pf = fopen("./../../Processed_data/PotDot_app2.bin", "r");

  nread = fread(&dummy, sizeof(double), 1, pf);  // Matter density parameter
  nread = fread(&dummy, sizeof(double), 1, pf);  // Matter density parameter
  nread = fread(&dummy, sizeof(double), 1, pf);  // Matter density parameter
  nread = fread(&dummy, sizeof(double), 1, pf);  // Matter density parameter
  
  nread = fread(&NCELLS,    sizeof(int),    1, pf);  // Hubble parameter
  nread = fread(&dummy_int, sizeof(int), 1, pf);  // Matter density parameter
  
  nread = fread(&BoxSize,   sizeof(double), 1, pf);  // Box Size
  nread = fread(&dummy_uli, sizeof(unsigned long), 1, pf);  // Matter density parameter
  nread = fread(&dummy,     sizeof(double), 1, pf);  // Cosmological constant density parameter
  nread = fread(&dummy,     sizeof(double), 1, pf);  // Redshift
  nread = fread(&dummy,     sizeof(double), 1, pf);  // Hubble parameter
  nread = fread(&dummy,     sizeof(double), 1, pf);  // Hubble parameter
  nread = fread(&dummy_c,   sizeof(char), 1, pf);  // Hubble parameter
  nread = fread(&dummy_c,   sizeof(char), 1, pf);  // Hubble parameter
  nread = fread(&dummy_c,   sizeof(char), 1, pf);  // Hubble parameter
  
  NTOTALCELLS = POW3(NCELLS);

  printf("Allocating memory\n");
  PotDot_read = (double *) calloc( NTOTALCELLS, sizeof(double) );

  for(m=0; m < NTOTALCELLS; m++)
    {
      nread = fread(&PotDot_read[m], sizeof(double), 1, pf);
    }//for m  
  
  fclose(pf);

  printf("Data read!\n");
  
  CellSize = BoxSize / (1.0 * NCELLS);
  NCells_Slice = floor( SliceSize /  CellSize);
  NCells_Slice *= NCELLS*NCELLS;

  Size_int = floor(SliceSize);
  
  printf("%d\n", Size_int);

  
  printf("Saving data\n");
  for(n = down_lim; n < up_lim; n += Size_int ) //For in slices. 3 slices
    {
      
      snprintf(buffer, sizeof(char)*100, "./../../Processed_data/DenCon_z%dto%d.txt", n, n+Size_int );
      printf("n=%d\n", n);
      pf = fopen(buffer, "w");
      
      //counter = 0;
      for(i=0; i<NCELLS; i++)
	{
	  for(j=0; j<NCELLS; j++)
	    {	      	      
	      for(k=n; k<(n+Size_int); k++)
		{
		  m = INDEX_C(i,j,k);
		  //counter++;
		  //l = INDEX_C(i,j,counter);
		  //PotDot[l] = PotDot_read[m];
		  
		  fprintf(pf, "%16.8lf\n", PotDot_read[m]);
		}
	    }//for j
	}//for i
      
      fclose(pf);

    }//for m

  printf("Code finished\n");

}//main
