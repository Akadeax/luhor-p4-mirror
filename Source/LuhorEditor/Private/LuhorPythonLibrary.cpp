// Fill out your copyright notice in the Description page of Project Settings.


#include "LuhorPythonLibrary.h"
#include "PythonScriptPlugin/Public/IPythonScriptPlugin.h"

FString ULuhorPythonLibrary::RunPythonFile(FString FileName, TArray<FString> Args)
{
    FStringBuilderBase builder;

    builder.Append("\"");
    builder.Append(FPaths::ProjectDir());
    builder.Append("Python/");
    builder.Append(FileName);
    builder.Append("\"");

    for (const FString& arg : Args)
    {
        builder.Append(" ");
        builder.Append("\"");
        builder.Append(arg);
        builder.Append("\"");
    }
    
    FPythonCommandEx command{};
    command.Command = builder.ToString();
    IPythonScriptPlugin::Get()->ExecPythonCommandEx(command);

    builder.Reset();
    for (FPythonLogOutputEntry& output : command.LogOutput)
    {
        builder.Append(output.Output);
        builder.Append("\n");
    }

    // Remove \n suffix if last
    if (command.LogOutput.Num() != 0) { builder.RemoveSuffix(2); }

    return FString(builder);
}
