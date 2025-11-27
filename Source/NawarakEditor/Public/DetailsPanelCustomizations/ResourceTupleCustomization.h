#pragma once

#include "CoreMinimal.h"
#include "IPropertyTypeCustomization.h"
 
class FResourceTupleCustomization : public IPropertyTypeCustomization
{
// Static
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();


// Lifecycle
public:
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
 
};
