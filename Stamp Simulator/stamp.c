//Declare header
#include "stamp.h"
    
int main(void){

  //File handle to the stamp.txt file
  FILE * ifp = NULL;
  
  //The structs and variables to save file data and output with
  stamp_database_t * stampDatabase = malloc(sizeof(stamp_database_t));   
  stamp_t * paper = malloc(sizeof(stamp_t));
  int commands = 0, rows = 0, columns = 0, stamp_num = 0;
  
  ifp = fopen("stamp.txt", "r");
  
  //Functions to create and fill the stamp database and paper
  stampDatabase = read_database(ifp);
  
  //Allocate space for and create the paer to be stamped on
  fscanf(ifp, "%d %d %d", &commands, &paper->num_rows, &paper->num_columns);
  paper = create_stamp(paper->num_rows, paper->num_columns);
  
  //Apply stamps to paper
  for (int i = 0; i < commands; i++){
    fscanf(ifp, "%d %d %d", &stamp_num, &rows, &columns);
    apply_stamp(paper, stampDatabase->stamp_array[stamp_num - 1], rows, columns);
  }
  
  //Print final paper with all stamps applied
  print_stamp(paper);
  
  //Plug memory leaks
  fclose(ifp);
  destroy_database(stampDatabase);
  destroy_stamp(paper);
  
  return 0;
}
  
  
  // Functions for creating and maintaining a database of stamps.
  stamp_database_t * read_database(FILE *fptr){
  
    //Allocate memory for the database
    stamp_database_t * myDatabase = malloc(sizeof(stamp_database_t));   
    fscanf(fptr, "%d", &myDatabase->num_stamps);
    
    //Allocate memory for the array of stamps
    myDatabase->stamp_array = malloc(sizeof(stamp_t *)*myDatabase->num_stamps);
    
    //Process every stamp
    for (int i = 0; i < myDatabase->num_stamps; i++){
      read_stamp(fptr, i, myDatabase);
    }
    
    return myDatabase;
  }
  
  
  // Frees allocated memory to the stamp database
  void destroy_database(stamp_database_t * database){
    //Free stamps individually, then the array of stamps, then the database as a whole
    for (int i = 0; i < database->num_stamps; i++)
    
      //Check to make sure the stamp was not already freed to avoid corruption
      if(database->stamp_array[i] != NULL)
        destroy_stamp(database->stamp_array[i]);
    free(database->stamp_array);
    free(database);
  }
  
  
  // Reads the type of stamp then calls appropriate stamp reading function
  void read_stamp(FILE * fptr, int stamp_id, stamp_database_t * database){
    int stamp_type = 0;
    fscanf(fptr, "%d", &stamp_type);
    
    //Check for type of stamp and call appropriate function
    if (stamp_type == 1)
      database->stamp_array[stamp_id] = read_stamp_type1(fptr);
    else
      database->stamp_array[stamp_id] = read_stamp_type2(fptr, database);
  }
  
  
  // Function to create a stamp with appropriate symbols
  stamp_t * read_stamp_type1(FILE * fptr){
  
    //Allocate memory for the stamp
    stamp_t * stamp = malloc(sizeof(stamp_t));
  
    //Find the size of the stamp
    fscanf(fptr, "%d %d", &stamp->num_rows, &stamp->num_columns);
    
    stamp = create_stamp(stamp->num_rows, stamp->num_columns);
    
    //Find the symbols on the stamp
    for (int r = 0; r < stamp->num_rows; r++)
      for (int c = 0; c < stamp->num_columns; c++){
        fscanf(fptr, "%c", &stamp->grid[r][c]);
        while (stamp->grid[r][c] == '\n' || stamp->grid[r][c] == '\r')
          fscanf(fptr, "%c", &stamp->grid[r][c]);
      }
      
    return stamp;
  }
  
  
  // Function to create an aggregate stamp with appropriate symbols
  stamp_t * read_stamp_type2(FILE * fptr, stamp_database_t * database){

    //Declare and allocate memory for the aggregate stamp and a temporary stamp database
    stamp_database_t * stamp2_database = malloc(sizeof(stamp_database_t));  
    stamp_t * stamp2;
    stamp_t * temp;
    int num_stamps = 0, stamp_index = 0, max_rows = 0, max_columns = 0;
    
    //Create an array of all the stamps a part of the aggregate stamp and find the size of the aggregate stamp
    fscanf(fptr, "%d", &num_stamps);
    stamp2_database->stamp_array = malloc(sizeof(stamp_t *)*num_stamps);
    
    //Create an array of all the stamps to be applied to the aggregate stamp
    for (int i = 0; i < num_stamps; i++){
      stamp2_database->stamp_array[i] = malloc(sizeof(stamp_t));
      fscanf(fptr, "%d", &stamp_index);
      
      //Decrease by 1 to fit numbering of array
      stamp_index --;
      temp = create_stamp(database->stamp_array[stamp_index]->num_rows, database->stamp_array[stamp_index]->num_columns);
      fscanf(fptr, "%d %d", &temp->offset_rows, &temp->offset_columns);
      
      //Check for the farthest in either direction that an applied stamp will reach
      if (temp->offset_rows + database->stamp_array[stamp_index]->num_rows > max_rows)
        max_rows = temp->offset_rows + database->stamp_array[stamp_index]->num_rows;
      if (temp->offset_columns + database->stamp_array[stamp_index]->num_columns > max_columns)
        max_columns = temp->offset_columns + database->stamp_array[stamp_index]->num_columns;
        
      //Copy the characters of stamp into the temporary stamp/database
      temp->grid = database->stamp_array[stamp_index]->grid;
      stamp2_database->stamp_array[i] = temp;
    }   
    
    //Allocate memory to the aggregate stamp
    stamp2 = create_stamp(max_rows, max_columns);
    
    //Apply the stamps to the aggregate stamp
    for (int i = 0; i < num_stamps; i++)
      apply_stamp(stamp2, stamp2_database->stamp_array[i], stamp2_database->stamp_array[i]->offset_rows, stamp2_database->stamp_array[i]->offset_columns);
    
    //Free memory allocated to temporary database and stamp
    free(stamp2_database->stamp_array);
    free(stamp2_database);
    destroy_stamp(temp);
    
    return stamp2;
  }
  
  
  // Tool for creating blank a stamp/paper
  stamp_t * create_stamp(int num_rows, int num_cols){

    //Allocate memory for the stamp/paper
    stamp_t * page = malloc(sizeof(stamp_t));
    
    //Save the size of the stamp so that it can be used outside of this function
    page->num_rows = num_rows;
    page->num_columns = num_cols;
    
    //Allocate memory for the grid on the stamp/paper
    page->grid = malloc(sizeof(char *)*num_rows);
    for (int r = 0; r < num_rows; r++)
      page->grid[r] = malloc(sizeof(char)*(num_cols + 1));
  
    //Initialize the grid full of "." and put an '\0' at the end of each row
    for (int r = 0; r < num_rows; r++)
      for (int c = 0; c <= num_cols; c++){
        if (c == num_cols)
          page->grid[r][c] = '\0';
        else
          page->grid[r][c] = '.';
      }
    
    return page;
  }
  
  
  // Function for applying a stamp to a page
  void apply_stamp(stamp_t * destination, stamp_t * stamp, int offset_row, int offset_column){

    //Apply the non-"." characters that make contact with the paper
    for (int r = 0; r < stamp->num_rows; r++)
      for (int c = 0; c < stamp->num_columns; c++)
      
        //Check if the stamp went off the paper and that the character is not "."
        if (r + offset_row < destination->num_rows && r + offset_row >= 0 && c + offset_column < destination->num_columns && c + offset_column >= 0 && stamp->grid[r][c] != '.')
          
          //Apply the character that hits the paper/type2 stamp
          destination->grid[r + offset_row][c + offset_column] = stamp->grid[r][c];
  }
  
  
  // Frees allocated memory to stamps/paper
  void destroy_stamp(stamp_t * stamp){

    //Free are characters in the grid, the grid, and the stamp itself
    for (int r = 0; r > stamp->num_rows; r++)
      free(stamp->grid[r]);
    free(stamp->grid);
    free(stamp);
  }
  
  
  // Prints to screen the contents of a stamp or page
  void print_stamp(stamp_t * paper){
    //Print every character in 2D array with a new line at the end of every row
    for (int r = 0; r < paper->num_rows; r++){
      for (int c = 0; c < paper->num_columns; c++){
        printf("%c", paper->grid[r][c]);
//printf("r = %d, c = %d\n", r, c);
//fflush(stdout);
      }
      printf("\n");
    }
  }