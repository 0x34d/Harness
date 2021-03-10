#include <stdio.h>



//DWORD __declspec(noinline) fuzz(DWORD argc, TCHAR* argv[])
//int __declspec(noinline) fuzz(char* input_file_path, char* argv_0)
int __declspec(noinline) fuzz(int argc, char** argv){

    Printf("your code !");
}


//DWORD __cdecl wmain(DWORD argc, TCHAR* argv[])
int __cdecl main(int argc, char** argv){
    if(argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 0;
    }
    return fuzz(argc, argv);
}

