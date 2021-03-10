#include <stdio.h>
#include <io.h>
#include <Windows.h>

int main(int argc, char** argv){

    FILE * File_input = NULL;
    HANDLE Contd_handle = NULL; //InSz

    File_input = fopen(argv[1], "r");   //Open

    if(File_input == NULL){
        printf("Fail ! \n");
    }
    else{
        Contd_handle = (HANDLE)_get_osfhandle(fileno(File_input));  //Convert
    }

    //DO Somthing 

    if(File_input == NULL){
        printf("Fail ! \n");
    }
    else{
        fclose(File_input); //Close 
    }
    //Note : User Do not Need to Close the Handle (Contd_handle)
}
