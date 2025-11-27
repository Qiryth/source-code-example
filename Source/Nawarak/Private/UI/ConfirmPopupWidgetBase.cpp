// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ConfirmPopupWidgetBase.h"

void UConfirmPopupWidgetBase::Confirm() const
{
	OnConfirm.ExecuteIfBound();
}

void UConfirmPopupWidgetBase::Cancel() const
{
	OnCancel.ExecuteIfBound();
}
