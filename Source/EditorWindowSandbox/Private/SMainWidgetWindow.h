// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SComboBox.h"




/**
 * 
 */
class SMainWidgetWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainWidgetWindow)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	// common 
	TSharedRef<SWidget> HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem);


	//first
	void HandleSelectorComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
	FText HandleSelectorComboBoxText() const;

	TSharedPtr<SComboBox<TSharedPtr<FString> > > SelectorComboBox;
	TArray<TSharedPtr<FString> > SelectorComboBoxOptions;
	TSharedPtr<FString>	SelectorComboBoxSelectedItem;


	//seconds
	void HandleSecondComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
	FText HandleSecondComboBoxText() const;

	TSharedPtr<SComboBox<TSharedPtr<FString> > > SecondComboBox;
	TArray<TSharedPtr<FString> > SecondComboBoxOptions;
	TSharedPtr<FString> ComboString;

};
