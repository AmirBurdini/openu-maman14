

/*
##########################################################################################################
############################################## exportFiles.c #############################################
##########################################################################################################
This document is utilized to produce the necessary output files for the assembler.
##########################################################################################################
*/

/*  void exportFilesMainHandler()
This function invokes other functions responsible for generating the .ob file, 
.ent file (if there are any entry labels), and .ext file (if there are any external labels).*/
void exportFilesMainHandler();

/* void generateObFile()
This function creates the .ob files by writing the memory image. 
If the file cannot be generated, it raises an error.*/
void generateObFile();

/* void createEntriesFile()
This function generates the .ent files (provided there are entry labels) by writing them into the file. 
If the file cannot be generated, it raises an error.*/
void createEntriesFile();

/* createExternalsFile()
This function generates the .ext files (assuming there are external labels) by writing them into the file. 
If the file cannot be generated, it raises an error.*/
void createExternalsFile();