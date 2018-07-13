// Fill out your copyright notice in the Description page of Project Settings.

#include "SMainWidgetWindow.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWidgetWindow::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()											
		[											
			// selector combo box										
			SAssignNew(SelectorComboBox, SComboBox<TSharedPtr<FString> >)										
				.OptionsSource(&SelectorComboBoxOptions)									
				.OnSelectionChanged(this, &SMainWidgetWindow::HandleSelectorComboBoxSelectionChanged)
				.OnGenerateWidget(this, &SMainWidgetWindow::HandleComboBoxGenerateWidget)
				[
					SNew(STextBlock)
						.Text(this, &SMainWidgetWindow::HandleSelectorComboBoxText)
				]
		]								
		// second
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(SecondComboBox, SComboBox<TSharedPtr<FString> >)
				.OptionsSource(&SecondComboBoxOptions)
				.OnSelectionChanged(this, &SMainWidgetWindow::HandleSecondComboBoxSelectionChanged)
				.OnGenerateWidget(this, &SMainWidgetWindow::HandleComboBoxGenerateWidget)
				[
					SNew(STextBlock)
						.Text(this, &SMainWidgetWindow::HandleSecondComboBoxText)
				]
		]
	];


	// initialize SComboBox
	{
		TSharedPtr<FString> SelectedItem = MakeShareable(new FString(TEXT("Options List A")));
		SelectorComboBoxOptions.Add(SelectedItem);
		SelectorComboBoxOptions.Add(MakeShareable(new FString(TEXT("Options List B"))));
		SelectorComboBoxSelectedItem = SelectedItem;

		SelectorComboBox->RefreshOptions();
		SelectorComboBox->SetSelectedItem(SelectedItem);

	}
	{
		SecondComboBoxOptions.Empty();

		for (int32 ItemIndex = 0; ItemIndex < 500; ++ItemIndex)
		{
			SecondComboBoxOptions.Add(MakeShareable(new FString(FString::Printf(TEXT("Item A %3d"), ItemIndex))));
		}

		SecondComboBox->RefreshOptions();
		SecondComboBox->SetSelectedItem(SecondComboBoxOptions[0]);

	}
	
}

// Callback for generating a widget in the SComboBox example.
TSharedRef<SWidget> SMainWidgetWindow::HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock)
		.Text(FText::FromString(*InItem));
}

// Callback for changing the selector combo box's selection in SComboBox example.
void SMainWidgetWindow::HandleSelectorComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
	//if (SelectorComboBoxOptions[0] == NewSelection)
	//{
	//	SwitchSecondComboToOptionSetA();
	//}
	//else
	//{
	//	SwitchSecondComboToOptionSetB();
	//}


	SelectorComboBoxSelectedItem = NewSelection;
}

// Callback for getting the text of the selector combo box in the SComboBox example.
FText SMainWidgetWindow::HandleSelectorComboBoxText() const
{
	return SelectorComboBoxSelectedItem.IsValid() ? FText::FromString(*SelectorComboBoxSelectedItem) : FText::GetEmpty();
}

void SMainWidgetWindow::HandleSecondComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboString = NewSelection;
}
FText SMainWidgetWindow::HandleSecondComboBoxText() const
{
	return ComboString.IsValid() ? FText::FromString(*ComboString) : FText::GetEmpty();
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
