# C_Database
This is an small SQLite clone project that I explored to further my knowledge of C and Storage Systems. The database uses a B-Tree system to store the information. There are only three columns: ID, USERNAME, EMAIL.

# Running the Program
Go to the directory that houses the executable. Running this command will compile and run the program, along with creating a data.db file.
  `if ($?) { gcc Database.c -o Database } ; if ($?) { .\Database data.db}`

# Implemented Commands
This SQLite clone implements three meta-commands along with two SQL statements.
- .exit: exits the program gracefully
- .btree: lists out the tree and structure of the data stored
- .constants: lists sizes of rows, common nodes, leaf nodes, etc.
- SELECT: prints all the entries of the table
- INSERT: inserts a new entry into the table using the format
  `INSERT ID USERNAME EMAIL`
