#include "NawarakEditor.h"

#include "DetailsPanelCustomizations/ResourceTupleCustomization.h"
#include "Resources/ResourceBase.h"

IMPLEMENT_MODULE(FNawarakEditorModule, NawarakEditor)

void FNawarakEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(FResourceTuple::StaticStruct()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(
			&FResourceTupleCustomization::MakeInstance));
}

void FNawarakEditorModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout(FResourceTuple::StaticStruct()->GetFName()); 
}
