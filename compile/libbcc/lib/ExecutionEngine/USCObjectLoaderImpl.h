/*
 * Copyright 2012, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BCC_EXECUTION_ENGINE_UNKNOWN_OBJECT_LOADER_IMPL_H
#define BCC_EXECUTION_ENGINE_UNKNOWN_OBJECT_LOADER_IMPL_H

#include "ObjectLoaderImpl.h"

namespace bcc {

class USCObjectLoaderImpl : public ObjectLoaderImpl {
public:
  USCObjectLoaderImpl() : ObjectLoaderImpl() { };

  virtual bool load(const void *pMem, size_t pMemSize) { return true; };

  virtual bool relocate(SymbolResolverInterface &pResolver) { return true; };

  virtual bool prepareDebugImage(void *pDebugImg, size_t pDebugImgSize) { return true; };

  virtual void *getSymbolAddress(const char *pName) const { return (void*)0xDEADBAAD; };

  virtual size_t getSymbolSize(const char *pName) const { return 0; };

  virtual bool getSymbolNameList(android::Vector<const char *>& pNameList,
                                 ObjectLoader::SymbolType pType) const { return false; };

  ~USCObjectLoaderImpl() {};
};

} // end namespace bcc

#endif // BCC_EXECUTION_ENGINE_UNKNOWN_OBJECT_LOADER_IMPL_H
