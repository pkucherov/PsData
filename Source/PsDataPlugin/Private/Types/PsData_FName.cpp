// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#include "Types/PsData_FName.h"

DEFINE_FUNCTION(UPsDataFNameLibrary::execSetMapProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TMAP_REF(FString, FName, Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	PsDataTools::SetByHash<TMap<FString, FName>>(Target, Hash, Value);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFNameLibrary::execGetMapProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TMAP_REF(FString, FName, Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	TMap<FString, FName>* Result = nullptr;
	PsDataTools::GetByHash(Target, Hash, Result);
	Out = *Result;
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFNameLibrary::execSetArrayProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TARRAY_REF(FName, Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	PsDataTools::SetByHash<TArray<FName>>(Target, Hash, Value);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFNameLibrary::execGetArrayProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TARRAY_REF(FName, Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	TArray<FName>* Result = nullptr;
	PsDataTools::GetByHash(Target, Hash, Result);
	Out = *Result;
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFNameLibrary::execSetProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_PROPERTY(FNameProperty, Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	PsDataTools::SetByHash<FName>(Target, Hash, Value);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFNameLibrary::execGetProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_PROPERTY_REF(FNameProperty, Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	FName* Result = nullptr;
	PsDataTools::GetByHash(Target, Hash, Result);
	Out = *Result;
	P_NATIVE_END;
}

void UPsDataFNameLibrary::TypeSerialize(const UPsData* const Instance, const TSharedPtr<const FDataField>& Field, FPsDataSerializer* Serializer, const FName& Value)
{
	Serializer->WriteValue(Value.ToString().ToLower());
}

FName UPsDataFNameLibrary::TypeDeserialize(const UPsData* const Instance, const TSharedPtr<const FDataField>& Field, FPsDataDeserializer* Deserializer, const FName& Value)
{
	FString String;
	if (!Deserializer->ReadValue(String))
	{
		UE_LOG(LogData, Warning, TEXT("Can't deserialize \"%s::%s\" as \"%s\""), *Instance->GetClass()->GetName(), *Field->Name, *PsDataTools::FType<FName>::Type())
	}
	FString LowercaseString = String.ToLower();
	if (LowercaseString == TEXT("none"))
	{
		return NAME_None;
	}
	return FName(*LowercaseString);
}