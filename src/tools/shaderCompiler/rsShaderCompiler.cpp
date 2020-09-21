/*

RSEngine Shader Compiler
Copyright (c) 2020 Mason Lee Back

File name: rsShaderCompiler.cpp

*/

#include <stdio.h>
#include <vector>

const char* fileName = "";
const char* outputFile = "";

enum shaderType {
    VERTEX_SHADER,
    PIXEL_SHADER,
    COMPUTE_SHADER,
    UNDEFINED_SHADER
};

shaderType currentShaderType = UNDEFINED_SHADER;

void PrintUsage()
{
    printf("RSEngine Shader Compiler\n"
        "Copyright (c) 2020 Mason Lee Back\n"
        "USAGE:\n"
        "-i <InputFile>   Name of input file.\n"
        "-o <OutputFile>  Name of output file.\n"
        "-t <Type>        Type of shader to compile.\n"
        "Types:\n    1: VERTEX_SHADER,\n    2: PIXEL_SHADER,\n    3: COMPUTE_SHADER\n\n");
}

void CompileShader()
{

}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        PrintUsage();
        return 1;
    }

    if (argc != 7) {
        printf("Invalid usage!\n");
        PrintUsage();
        return 1;
    }

    printf("%s, %s, %s, %s, %s, %s\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);

    return 0;
}
