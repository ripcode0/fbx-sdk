#include "fbxsdk.h"
#include <iostream>




int main(int args, char* argv[])
{
    fbxsdk::FbxImporter* importer;

    //FBXSDK_printf("hello world\n");
    
    //FbxImporter::Create()
    fbxsdk::FbxManager* manager = fbxsdk::FbxManager::Create();
    
    FbxImporter* im;
    //im->AddListener();

    //manager->AddLocalization(,);  

    system("pause");
    return 0;
}