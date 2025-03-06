//
// Created by david on 2025/3/6.
//

#ifndef PATCHMAPKIND_H
#define PATCHMAPKIND_H

#include <ostream>
#include <regex>

enum PatchMapKind {
  kLinkPatchMap = 0,
  kMethodIdxMap = 1,
  kClassIdxMap = 2,
  kDexIdxMap = 3,
  kLastKind = kDexIdxMap
};


inline PatchMapKind stringToPatchMapKind(const std::string& str) {
  if (str == "link patch map")
    return kLinkPatchMap;
  if (str == "method idx map")
    return kMethodIdxMap;
  if (str == "class idx map")
    return kClassIdxMap;
  if (str == "dex idx map")
    return kDexIdxMap;
  std::string exceptionCaption("Unknown kind: ");
  exceptionCaption.append(str);
  throw std::invalid_argument(exceptionCaption);
}

inline std::string PatchMapKindToString(PatchMapKind kind) {
  switch (kind) {
    case kLinkPatchMap:
      return "link patch map";
    case kMethodIdxMap:
      return "method idx map";
    case kClassIdxMap:
      return "class idx map";
    case kDexIdxMap:
      return "dex idx map";
    default:
      throw std::invalid_argument("unknown patch map kind");
  }
}
#endif //PATCHMAPKIND_H