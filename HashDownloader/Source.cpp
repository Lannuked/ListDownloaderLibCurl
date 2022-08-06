#include "pch.h"
#include "Globals.h"
#include "msclr\marshal_cppstd.h"

std::string TextToString(System::String^ managedString)
{
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(managedString);
    return standardString;
}

System::String^ StringToText(std::string managedString)
{
    msclr::interop::marshal_context context;
    System::String^ standardString = context.marshal_as<System::String^>(managedString);
    return standardString;
}