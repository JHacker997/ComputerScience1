
// Header for the Assignment 1 problem stamp
#include <stdio.h>
#include <stdlib.h>

// A structure for holding a stamp or paper
typedef struct
{
  // The size of the contents of this stamp.
  int num_rows;
  int num_columns;
  
  // For type 2 stamps only, the offset values from the top-left corner of the stamp
  int offset_rows;
  int offset_columns;

  // A 2D array of characters for a stamp.
  char ** grid;
} stamp_t;


// This structure is a dynamically allocated array of stamps.
typedef struct
{
    
  // The amount of stamps in the database
  int num_stamps;
   
  // An array of stamp_t pointers
  stamp_t ** stamp_array;
} stamp_database_t;


// Functions for creating and maintaining a database of stamps
stamp_database_t * read_database(FILE * fptr);
void destroy_database(stamp_database_t * database);

// Helper functions for reading/destroying/testing stamps
void read_stamp(FILE * fptr, int stamp_id, stamp_database_t * database);
stamp_t * read_stamp_type1(FILE * fptr);
stamp_t * read_stamp_type2(FILE * fptr, stamp_database_t * database);

// Function for creating and applying a stamp to a page
stamp_t * create_stamp(int num_rows, int num_cols);
void apply_stamp(stamp_t * paper, stamp_t * stamp, int offset_row, int offset_column);
void destroy_stamp(stamp_t * stamp);
void print_stamp(stamp_t * stamp);