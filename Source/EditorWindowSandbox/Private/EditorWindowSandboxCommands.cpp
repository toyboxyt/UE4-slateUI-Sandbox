// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorWindowSandboxCommands.h"

#define LOCTEXT_NAMESPACE "FEditorWindowSandboxModule"

void FEditorWindowSandboxCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "EditorWindowSandbox", "Bring up EditorWindowSandbox window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
