// Fill out your copyright notice in the Description page of Project Settings.

#include "SiAiJsonHandle.h"
#include "FileHelper.h"
#include "Common/SiAiHelper.h"
#include "Paths.h"
#include "JsonReader.h"

SiAiJsonHandle::SiAiJsonHandle()
{
	RecordDataFileName = FString("RecordData.json");
	ObjectAttrFileName = FString("ObjectAttribute.json");
	ResourceAttrFileName = FString("ResourceAttribute.json");

	RelativePath = FString("Res/ConfigData/");
}

void SiAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
		//获取数据
		Culture = JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume = JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume = JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));
		//获取存档数据
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));
		for (int i = 0; i < RecordDataArray.Num(); ++i) {
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
		}
	}
	else {
		SiAiHelper::Debug(FString("Deserialize Failed"));
	}
}

void SiAiJsonHandle::UpdataRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString> *RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;

	TSharedPtr<FJsonObject> CultureObject = MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture", Culture);
	TSharedPtr<FJsonValueObject> CultureValue = MakeShareable(new FJsonValueObject(CultureObject));

	TSharedPtr<FJsonObject> MusicVolumeObject = MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume", MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue = MakeShareable(new FJsonValueObject(MusicVolumeObject));

	TSharedPtr<FJsonObject> SoundVolumeObject = MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume", SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue = MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;
	for (int i = 0; i < RecordDataList->Num(); ++i) {
		TSharedPtr<FJsonObject> RecordItem = MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i), (*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordDataValue);
	}
	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData", RecordDataArray);
	TSharedPtr<FJsonValueObject> RecordDataValue = MakeShareable(new FJsonValueObject(RecordDataObject));

	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	JsonObject->SetArrayField("T", BaseDataArray);
	FString JsonStr;
	GetFStringInJsonData(JsonObject, JsonStr);

	// 去掉多余字符
	JsonStr.RemoveAt(0, 8);
	JsonStr.RemoveFromEnd(FString("}"));

	// 写入文件
	WriteFileWithJsonData(JsonStr, RelativePath, RecordDataFileName);

}

void SiAiJsonHandle::ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>> &ObjectAttrMap)
{
	FString JsonValue;
	// 读取文档函数
	LoadStringFromFile(ObjectAttrFileName, RelativePath, JsonValue);
	// 声明变量
	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	// 变量赋值
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		for (int i = 0; i < JsonParsed.Num(); i++)
		{
			TArray<TSharedPtr<FJsonValue>> ObjectAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));
			FText EN = FText::FromString(ObjectAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH = FText::FromString(ObjectAttr[1]->AsObject()->GetStringField("ZH"));
			FString ObjectTypeStr = ObjectAttr[2]->AsObject()->GetStringField("ObjectType");
			int PlantAttack = ObjectAttr[3]->AsObject()->GetIntegerField("PlantAttack");
			int MetalAttcck = ObjectAttr[4]->AsObject()->GetIntegerField("MetalAttcck");
			int AnimalAttack = ObjectAttr[5]->AsObject()->GetIntegerField("AnimalAttack");
			int AffectRange = ObjectAttr[6]->AsObject()->GetIntegerField("AffectRange");
			FString TexPath = ObjectAttr[7]->AsObject()->GetStringField("TexPath");
			// 字符串转化成对应的枚举
			EObjectType::Type ObjectType = StringToObjectType(ObjectTypeStr);
			TSharedPtr<ObjectAttribute> ObjectAttrPtr = MakeShareable(new ObjectAttribute(EN, ZH, ObjectType, PlantAttack, MetalAttcck, AnimalAttack, AffectRange, TexPath));

			ObjectAttrMap.Add(i, ObjectAttrPtr);
		}
	}
	else
	{
		SiAiHelper::Debug(FString("Deserialize Failed"));
	}
}

void SiAiJsonHandle::ResourceAttrJsonRead(TMap<int, TSharedPtr<ResourceAttribute>>& ResourceAttrMap)
{
	FString JsonValue;
	LoadStringFromFile(ResourceAttrFileName, RelativePath, JsonValue);

	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		for (int i = 0; i < JsonParsed.Num(); i++) 
		{
			// 资源没有序号0,从1开始
			TArray<TSharedPtr<FJsonValue>> ResourceAttr = JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i + 1));
			FText EN = FText::FromString(ResourceAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH = FText::FromString(ResourceAttr[1]->AsObject()->GetStringField("ZH"));
			EResourceType::Type ResourceType = StringToResourceType(ResourceAttr[2]->AsObject()->GetStringField("ResourceType"));
			int HP = ResourceAttr[3]->AsObject()->GetIntegerField("HP");

			TArray<TArray<int>> FlobObjectInfoArray;
			TArray<TSharedPtr<FJsonValue>> FlobObjectInfo = ResourceAttr[4]->AsObject()->GetArrayField(FString("FlobObjectInfo"));
			for (int j = 0; j < FlobObjectInfo.Num(); ++j) {

				FString FlobObjectInfoItem = FlobObjectInfo[j]->AsObject()->GetStringField(FString::FromInt(j));
				FString ObjectIndexStr;
				FString RangeStr;
				FString RangeMinStr;
				FString RangeMaxStr;
				FlobObjectInfoItem.Split(FString("_"), &ObjectIndexStr, &RangeStr);
				RangeStr.Split(FString(","), &RangeMinStr, &RangeMaxStr);

				TArray<int> FlobObjectInfoList;

				FlobObjectInfoList.Add(FCString::Atoi(*ObjectIndexStr));
				FlobObjectInfoList.Add(FCString::Atoi(*RangeMinStr));
				FlobObjectInfoList.Add(FCString::Atoi(*RangeMaxStr));

				FlobObjectInfoArray.Add(FlobObjectInfoList);
			}

			TSharedPtr<ResourceAttribute> ResourceAttrPtr = MakeShareable(new ResourceAttribute(EN, ZH, ResourceType, HP, &FlobObjectInfoArray));
			ResourceAttrMap.Add(i + 1, ResourceAttrPtr);
		}
	}
	else
	{
		SiAiHelper::Debug(FString("Deserialize Failed"), 10.f);
	}
}

bool SiAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		// 获取绝对路径
		// FString AbsoPath = FPaths::GameContentDir() + RelaPath + FileName;
		FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		if (FPaths::FileExists(AbsoPath))
		{
			if (FFileHelper::LoadFileToString(ResultString, *AbsoPath))
			{
				return true;
			}
			else
			{
				// 加载不成功
				SiAiHelper::Debug(FString("Load Error") + AbsoPath);
			}
		}
		else
		{
			// 输出文件不存在
			SiAiHelper::Debug(FString("File Not Exist") = AbsoPath);
		}
	}
	return false;
}

bool SiAiJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject> &JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid() && JsonObj->Values.Num() > 0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), JsonWriter);
		return true;
	}
	return false;
}

bool SiAiJsonHandle::WriteFileWithJsonData(const FString &JsonStr, const FString &RelaPath, const FString &FileName)
{
	if (!JsonStr.IsEmpty() && !FileName.IsEmpty())
	{
		FString AbsoPath = FPaths::ProjectContentDir() + RelaPath + FileName;
		// 保存
		if (FFileHelper::SaveStringToFile(JsonStr, *AbsoPath))
		{
			return true;
		}
		else
		{
			SiAiHelper::Debug(FString("Save") + AbsoPath + FString("-->Failed"), 10.f);
		}
	}
	return false;
}

EObjectType::Type SiAiJsonHandle::StringToObjectType(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Normal"))) return EObjectType::Normal;
	if (ArgStr.Equals(FString("Food"))) return EObjectType::Food;
	if (ArgStr.Equals(FString("Tool"))) return EObjectType::Tool;
	if (ArgStr.Equals(FString("Weapon"))) return EObjectType::Weapon;
	return EObjectType::Normal;
}

EResourceType::Type SiAiJsonHandle::StringToResourceType(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Plant"))) return EResourceType::Plant;
	if (ArgStr.Equals(FString("Metal"))) return EResourceType::Metal;
	if (ArgStr.Equals(FString("Animal"))) return EResourceType::Animal;
	return EResourceType::Plant;
}
