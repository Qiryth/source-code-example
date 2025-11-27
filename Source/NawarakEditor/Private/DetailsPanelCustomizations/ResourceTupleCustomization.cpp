#include "DetailsPanelCustomizations/ResourceTupleCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Resources/ResourceBase.h"

TSharedRef<IPropertyTypeCustomization> FResourceTupleCustomization::MakeInstance()
{
	return MakeShareable(new FResourceTupleCustomization);
}

void FResourceTupleCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
	FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	const TSharedPtr<IPropertyHandle> ResourceTypeHandle =
		PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FResourceTuple, Type));
	const TSharedPtr<IPropertyHandle> ResourceAmountHandle =
		PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FResourceTuple, Amount));

	HeaderRow.NameContent().HAlign(HAlign_Fill)[
		SNew(SHorizontalBox) +
		SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(FText::FromString("Resource")).Font(IDetailLayoutBuilder::GetDetailFont())
		] +
		SHorizontalBox::Slot().FillWidth(1)[SNew(SSpacer)] +
		SHorizontalBox::Slot().AutoWidth().Padding(2,0).VAlign(VAlign_Center)
		[
			ResourceTypeHandle->CreatePropertyValueWidget()
		]
	]
	.ValueContent()
	[
		SNew(SHorizontalBox) +
		SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(FText::FromString("Amount")).Font(IDetailLayoutBuilder::GetDetailFont())
		] +
		SHorizontalBox::Slot().FillWidth(1)[SNew(SSpacer)] +
		SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ResourceAmountHandle->CreatePropertyValueWidget()]
	];
}

void FResourceTupleCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder,
	IPropertyTypeCustomizationUtils& CustomizationUtils)
{
}
