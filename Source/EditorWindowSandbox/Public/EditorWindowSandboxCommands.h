// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorWindowSandboxStyle.h"

class FEditorWindowSandboxCommands : public TCommands<FEditorWindowSandboxCommands>
{
public:

	FEditorWindowSandboxCommands()
		: TCommands<FEditorWindowSandboxCommands>(TEXT("EditorWindowSandbox"), NSLOCTEXT("Contexts", "EditorWindowSandbox", "EditorWindowSandbox Plugin"), NAME_None, FEditorWindowSandboxStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};