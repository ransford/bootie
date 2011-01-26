#ifndef BOOTIE_PASSES_H
#define BOOTIE_PASSES_H

#include "llvm/Pass.h"
#include "llvm/Module.h"
#include "llvm/DerivedTypes.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Debug.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Support/raw_ostream.h"
#include <map>
#include <string>

namespace llvm {
  struct BootieRenameMain : public FunctionPass {
    static char ID;
    static const std::string oldMainName;

    BootieRenameMain ();
    virtual bool runOnFunction (Function &);
  };
}

#endif // BOOTIE_PASSES_H

// vim:ts=2 sw=2
