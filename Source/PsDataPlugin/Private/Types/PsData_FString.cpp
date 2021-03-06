// Copyright 2015-2020 Mail.Ru Group. All Rights Reserved.

#include "Types/PsData_FString.h"

DEFINE_FUNCTION(UPsDataFStringLibrary::execSetMapProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TMAP_REF(FString, FString, Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	PsDataTools::SetByHash<TMap<FString, FString>>(Target, Hash, Value);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFStringLibrary::execGetMapProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TMAP_REF(FString, FString, Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	TMap<FString, FString>* Result = nullptr;
	PsDataTools::GetByHash(Target, Hash, Result);
	Out = *Result;
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFStringLibrary::execSetArrayProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TARRAY_REF(FString, Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	PsDataTools::SetByHash<TArray<FString>>(Target, Hash, Value);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFStringLibrary::execGetArrayProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_TARRAY_REF(FString, Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	TArray<FString>* Result = nullptr;
	PsDataTools::GetByHash(Target, Hash, Result);
	Out = *Result;
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFStringLibrary::execSetProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_PROPERTY_REF(FStrProperty, Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	PsDataTools::SetByHash<FString>(Target, Hash, Value);
	P_NATIVE_END;
}

DEFINE_FUNCTION(UPsDataFStringLibrary::execGetProperty)
{
	P_GET_OBJECT(UPsData, Target);
	P_GET_PROPERTY(FIntProperty, Hash);
	P_GET_PROPERTY_REF(FStrProperty, Out);
	P_FINISH;
	P_NATIVE_BEGIN;
	FString* Result = nullptr;
	PsDataTools::GetByHash(Target, Hash, Result);
	Out = *Result;
	P_NATIVE_END;
}

void UPsDataFStringLibrary::TypeSerialize(const UPsData* const Instance, const TSharedPtr<const FDataField>& Field, FPsDataSerializer* Serializer, const FString& Value)
{
	Serializer->WriteValue(Value);
}

FString UPsDataFStringLibrary::TypeDeserialize(const UPsData* const Instance, const TSharedPtr<const FDataField>& Field, FPsDataDeserializer* Deserializer, const FString& Value)
{
	FString Result = Value;
	if (Deserializer->ReadValue(Result))
	{
		return Result;
	}

	UE_LOG(LogData, Warning, TEXT("Can't deserialize \"%s::%s\" as \"%s\""), *Instance->GetClass()->GetName(), *Field->Name, *PsDataTools::FType<FString>::Type());
	return Value;
}