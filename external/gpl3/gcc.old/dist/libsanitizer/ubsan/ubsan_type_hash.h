//===-- ubsan_type_hash.h ---------------------------------------*- C++ -*-===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Hashing of types for Clang's undefined behavior checker.
//
//===----------------------------------------------------------------------===//
#ifndef UBSAN_TYPE_HASH_H
#define UBSAN_TYPE_HASH_H

#include "sanitizer_common/sanitizer_common.h"

namespace __ubsan {

typedef uptr HashValue;

/// \brief Information about the dynamic type of an object (extracted from its
/// vptr).
class DynamicTypeInfo {
  const char *MostDerivedTypeName;
  sptr Offset;
  const char *SubobjectTypeName;

public:
  DynamicTypeInfo(const char *MDTN, sptr Offset, const char *STN)
    : MostDerivedTypeName(MDTN), Offset(Offset), SubobjectTypeName(STN) {}

  /// Determine whether the object had a valid dynamic type.
  bool isValid() const { return MostDerivedTypeName; }
  /// Get the name of the most-derived type of the object.
  const char *getMostDerivedTypeName() const { return MostDerivedTypeName; }
  /// Get the offset from the most-derived type to this base class.
  sptr getOffset() const { return Offset; }
  /// Get the name of the most-derived type at the specified offset.
  const char *getSubobjectTypeName() const { return SubobjectTypeName; }
};

/// \brief Get information about the dynamic type of an object.
DynamicTypeInfo getDynamicTypeInfoFromObject(void *Object);

/// \brief Get information about the dynamic type of an object from its vtable.
DynamicTypeInfo getDynamicTypeInfoFromVtable(void *Vtable);

/// \brief Check whether the dynamic type of \p Object has a \p Type subobject
/// at offset 0.
/// \return \c true if the type matches, \c false if not.
bool checkDynamicType(void *Object, void *Type, HashValue Hash);

const unsigned VptrTypeCacheSize = 128;

/// \brief A cache of the results of checkDynamicType. \c checkDynamicType would
/// return \c true (modulo hash collisions) if
/// \code
///   __ubsan_vptr_type_cache[Hash % VptrTypeCacheSize] == Hash
/// \endcode
extern "C" SANITIZER_INTERFACE_ATTRIBUTE
HashValue __ubsan_vptr_type_cache[VptrTypeCacheSize];

} // namespace __ubsan

#endif // UBSAN_TYPE_HASH_H
