#pragma once

#include <stdint.h>
#include "Assembly.h"
#include "MetadataCache.h"
#include "StackTrace.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-config.h"
#include "metadata/CustomAttributeCreator.h"
#include "os/Mutex.h"
#include "utils/dynamic_array.h"
#include "vm-utils/MethodDefinitionKey.h"

struct MethodInfo;
struct Il2CppClass;
struct Il2CppGenericContext;
struct Il2CppGenericInst;
struct Il2CppGenericMethod;
struct Il2CppType;
struct Il2CppString;

namespace il2cpp
{
namespace vm
{
    class GlobalMetadata
    {
    public:
        static void Register(const Il2CppCodeRegistration* const codeRegistration, const Il2CppMetadataRegistration* const metadataRegistration, const Il2CppCodeGenOptions* const codeGenOptions);
        static bool Initialize(int32_t* imagesCount, int32_t* assembliesCount);

        static void InitializeAllMethodMetadata();
        static void* InitializeRuntimeMetadata(uintptr_t* metadataPointer, bool throwOnError);
        static void InitializeStringLiteralTable();
        static void InitializeWindowsRuntimeTypeNamesTables(WindowsRuntimeTypeNameToClassMap& windowsRuntimeTypeNameToClassMap, ClassToWindowsRuntimeTypeNameMap& classToWindowsRuntimeTypeNameMap);
        static void InitializeUnresolvedSignatureTable(Il2CppUnresolvedSignatureMap& unresolvedSignatureMap);
        static void InitializeGenericMethodTable(Il2CppMethodTableMap& methodTableMap);

        static void BuildIl2CppImage(Il2CppImage* image, ImageIndex imageIndex, AssemblyIndex* imageAssemblyIndex);
        static void BuildIl2CppAssembly(Il2CppAssembly* assembly, AssemblyIndex assemblyIndex, ImageIndex* assemblyImageIndex);

        static void Clear();

        static const MethodInfo* GetAssemblyEntryPoint(const Il2CppImage* image);
        static Il2CppMetadataTypeHandle GetAssemblyTypeHandle(const Il2CppImage* image, AssemblyTypeIndex index);
        static const Il2CppAssembly* GetReferencedAssembly(const Il2CppAssembly* assembly, int32_t referencedAssemblyTableIndex, const Il2CppAssembly assembliesTable[], int assembliesCount);
        static Il2CppMetadataTypeHandle GetAssemblyExportedTypeHandle(const Il2CppImage* image, AssemblyExportedTypeIndex index);

        static Il2CppClass* GetTypeInfoFromType(const Il2CppType* type);
        static Il2CppClass* GetTypeInfoFromTypeDefinitionIndex(TypeDefinitionIndex index);
        static Il2CppClass* GetTypeInfoFromHandle(Il2CppMetadataTypeHandle handle);
        static const Il2CppType* GetInterfaceFromOffset(const Il2CppClass* klass, TypeInterfaceIndex offset);
        static Il2CppInterfaceOffsetInfo GetInterfaceOffsetInfo(const Il2CppClass* klass, TypeInterfaceOffsetIndex index);
        static Il2CppMetadataTypeHandle GetTypeHandleFromIndex(TypeDefinitionIndex typeIndex);
        static Il2CppMetadataTypeHandle GetTypeHandleFromType(const Il2CppType* type);
        static bool TypeIsNested(Il2CppMetadataTypeHandle handle);
        static bool TypeIsValueType(Il2CppMetadataTypeHandle handle);
        static bool StructLayoutPackIsDefault(Il2CppMetadataTypeHandle handle);
        static int32_t StructLayoutPack(Il2CppMetadataTypeHandle handle);
        static bool StructLayoutSizeIsDefault(Il2CppMetadataTypeHandle handle);
        static std::pair<const char*, const char*> GetTypeNamespaceAndName(Il2CppMetadataTypeHandle handle);

        static Il2CppClass* GetNestedTypeFromOffset(const Il2CppClass* klass, TypeNestedTypeIndex offset);
        static Il2CppMetadataTypeHandle GetNestedTypes(Il2CppMetadataTypeHandle handle, void** iter);

        static Il2CppMetadataCustomAttributeHandle GetCustomAttributeTypeToken(const Il2CppImage* image, uint32_t token);
        static il2cpp::metadata::CustomAttributeDataReader GetCustomAttributeDataReader(const Il2CppImage* image, uint32_t token);
        static il2cpp::metadata::CustomAttributeDataReader GetCustomAttributeDataReader(Il2CppMetadataCustomAttributeHandle handle);

        static const MethodInfo* GetMethodInfoFromMethodHandle(Il2CppMetadataMethodDefinitionHandle handle);
        static const MethodInfo* GetMethodInfoFromVTableSlot(const Il2CppClass* klass, int32_t vTableSlot);
        static const MethodInfo* GetVirtualMethodInfoFromVTableSlot(const Il2CppClass* klass, int32_t vTableSlot);

        static const uint8_t* GetParameterDefaultValue(const MethodInfo* method, int32_t parameterPosition, const Il2CppType** type, bool* isExplicitySetNullDefaultValue);
        static const uint8_t* GetFieldDefaultValue(const FieldInfo* field, const Il2CppType** type);
        static uint32_t GetFieldOffset(const Il2CppClass* klass, int32_t fieldIndexInType, FieldInfo* field);
        static int GetFieldMarshaledSizeForField(const FieldInfo* field);

        static Il2CppMetadataFieldInfo GetFieldInfo(const Il2CppClass* klass, TypeFieldIndex index);
        static Il2CppMetadataMethodInfo GetMethodInfo(const Il2CppClass* klass, TypeMethodIndex index);
        static Il2CppMetadataParameterInfo GetParameterInfo(const Il2CppClass* klass, Il2CppMetadataMethodDefinitionHandle handle, MethodParameterIndex index);
        static Il2CppMetadataPropertyInfo GetPropertyInfo(const Il2CppClass* klass, TypePropertyIndex index);
        static Il2CppMetadataEventInfo GetEventInfo(const Il2CppClass* klass, TypeEventIndex index);

        static Il2CppMetadataGenericContainerHandle GetGenericContainerFromGenericClass(const Il2CppGenericClass* genericClass);
        static Il2CppMetadataGenericContainerHandle GetGenericContainerFromMethod(Il2CppMetadataMethodDefinitionHandle handle);
        static Il2CppMetadataGenericParameterHandle GetGenericParameterFromType(const Il2CppType* type);
        static const MethodInfo* GetGenericInstanceMethod(const MethodInfo* genericMethodDefinition, const Il2CppGenericContext* context);
        static const Il2CppType* GetTypeFromRgctxDefinition(const Il2CppRGCTXDefinition* rgctxDef);
        static const Il2CppGenericMethod* GetGenericMethodFromRgctxDefinition(const Il2CppRGCTXDefinition* rgctxDef);
        static std::pair<const Il2CppType*, const MethodInfo*> GetConstrainedCallFromRgctxDefinition(const Il2CppRGCTXDefinition* rgctxDef);
        static Il2CppClass* GetContainerDeclaringType(Il2CppMetadataGenericContainerHandle handle);
        static Il2CppClass* GetParameterDeclaringType(Il2CppMetadataGenericParameterHandle handle);
        static Il2CppMetadataGenericParameterHandle GetGenericParameterFromIndex(Il2CppMetadataGenericContainerHandle handle, GenericContainerParameterIndex index);
        static const Il2CppType* GetGenericParameterConstraintFromIndex(Il2CppMetadataGenericParameterHandle handle, GenericParameterConstraintIndex index);
        static void MakeGenericArgType(Il2CppMetadataGenericContainerHandle containerHandle, Il2CppMetadataGenericParameterHandle paramHandle, Il2CppType* arg);
        static uint32_t GetGenericContainerCount(Il2CppMetadataGenericContainerHandle handle);
        static bool GetGenericContainerIsMethod(Il2CppMetadataGenericContainerHandle handle);
        static const char* GetGenericParameterName(Il2CppMetadataGenericParameterHandle handle);
        static Il2CppGenericParameterInfo GetGenericParameterInfo(Il2CppMetadataGenericParameterHandle handle);
        static uint16_t GetGenericParameterFlags(Il2CppMetadataGenericParameterHandle handle);
        static int16_t GetGenericConstraintCount(Il2CppMetadataGenericParameterHandle handle);
        static const Il2CppGenericMethod* GetGenericMethodFromTokenMethodTuple(const Il2CppTokenIndexMethodTuple* tuple);

        static const MethodInfo* GetMethodInfoFromCatchPoint(const Il2CppCatchPoint* cp);
        static const MethodInfo* GetMethodInfoFromSequencePoint(const Il2CppSequencePoint* cp);
        static Il2CppClass* GetTypeInfoFromTypeSourcePair(const Il2CppTypeSourceFilePair* pair);

        static Il2CppClass* GetTypeInfoFromTypeIndex(TypeIndex index, bool throwOnError = true);
        static const Il2CppType* GetIl2CppTypeFromIndex(TypeIndex index);
        static const MethodInfo* GetMethodInfoFromMethodDefinitionIndex(MethodIndex index);
        static const MethodInfo* GetVirtualMethodInfoFromMethodDefinitionIndex(MethodIndex index);

        template<typename T>
        static inline bool IsRuntimeMetadataInitialized(T item)
        {
            // Runtime metadata items are initialized to an encoded token with the low bit set
            // on startup and when initialized are a pointer to an runtime metadata item
            // So we can rely on pointer alignment being > 1 on our supported platforms
            return !((uintptr_t)item & 1);
        }

#if IL2CPP_ENABLE_NATIVE_STACKTRACES
        static void GetAllManagedMethods(std::vector<MethodDefinitionKey>& managedMethods);
#endif
    };
}
}
