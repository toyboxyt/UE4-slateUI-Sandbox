// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorWindowSandbox.h"
#include "EditorWindowSandboxStyle.h"
#include "EditorWindowSandboxCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "SMainWidgetWindow.h"

static const FName EditorWindowSandboxTabName("EditorWindowSandbox");

#define LOCTEXT_NAMESPACE "FEditorWindowSandboxModule"

void FEditorWindowSandboxModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEditorWindowSandboxStyle::Initialize();
	FEditorWindowSandboxStyle::ReloadTextures();

	FEditorWindowSandboxCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorWindowSandboxCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FEditorWindowSandboxModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FEditorWindowSandboxModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FEditorWindowSandboxModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(EditorWindowSandboxTabName, FOnSpawnTab::CreateRaw(this, &FEditorWindowSandboxModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FEditorWindowSandboxTabTitle", "EditorWindowSandbox"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FEditorWindowSandboxModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorWindowSandboxStyle::Shutdown();

	FEditorWindowSandboxCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EditorWindowSandboxTabName);
}

TSharedRef<SDockTab> FEditorWindowSandboxModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{

	const TSharedRef<SDockTab> DockTab = SNew(SDockTab)
		.TabRole(ETabRole::MajorTab);
		//.TabRole(ETabRole::NomadTab);

	// main window
	TSharedRef<SMainWidgetWindow> Window = SNew(SMainWidgetWindow);

	DockTab->SetContent(Window);

	return DockTab;

	//FText WidgetText = FText::Format(
	//	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	//	FText::FromString(TEXT("FEditorWindowSandboxModule::OnSpawnPluginTab")),
	//	FText::FromString(TEXT("EditorWindowSandbox.cpp"))
	//	);

	//return SNew(SDockTab)
	//	.TabRole(ETabRole::NomadTab)
	//	[
	//		// Put your tab content here!
	//		SNew(SBox)
	//		.HAlign(HAlign_Center)
	//		.VAlign(VAlign_Center)
	//		[
	//			SNew(STextBlock)
	//			.Text(WidgetText)
	//		]
	//	];
}



void FEditorWindowSandboxModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(EditorWindowSandboxTabName);
}

void FEditorWindowSandboxModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FEditorWindowSandboxCommands::Get().OpenPluginWindow);
}

void FEditorWindowSandboxModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FEditorWindowSandboxCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorWindowSandboxModule, EditorWindowSandbox)