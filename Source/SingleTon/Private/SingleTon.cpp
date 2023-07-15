// Copyright 2020 Andrew Bindraw. All Rights Reserved.

#include "SingleTon.h"


#define LOCTEXT_NAMESPACE "FSingleTonModule"

void FSingleTonModule::StartupModule()
{

}

void FSingleTonModule::ShutdownModule()
{
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSingleTonModule, SingleTon)