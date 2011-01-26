/* adapted from Mementos, http://github.com/ransford/mementos */

#include "bootie/Bootie.h"
#include "bootie/Passes.h"
#include "llvm/Support/CommandLine.h"
using namespace llvm;

char BootieRenameMain::ID = 0;
static RegisterPass<BootieRenameMain> E("bootie-rename-main",
    "Renames main() to " BOOTIE_OLDMAINNAME,
    false, /* does not preserve the CFG -- XXX or does it? */
    false /* is not an analysis pass */);

static cl::opt<bool> nameAfterModule("bootie-name-main-after-module",
    cl::desc("Rename main() to _main_<module>() instead of "
      BOOTIE_OLDMAINNAME "()"),
    cl::init(false), cl::Hidden);

BootieRenameMain::BootieRenameMain () : FunctionPass(ID) {
}

bool BootieRenameMain::runOnFunction (Function &F) {
  const std::string& moduleId = F.getParent()->getModuleIdentifier();
  DEBUG(outs() << "Parent module of function: " << moduleId << "\n");
  if (F.getName() != "main")
    return false;

  // change main()'s name because Bootie provides its own main() function
  if (nameAfterModule) { // should we add a module-specific suffix?

    // strip leading path elements and file extension
    std::string m = moduleId;
    size_t slashloc = m.rfind('/');
    if (slashloc != std::string::npos)
      m = m.substr(slashloc+1);
    size_t dotloc = m.find('.');
    if (dotloc != std::string::npos)
      m = m.substr(0, dotloc);

    const std::string& newName = "_main_" + m;
    DEBUG(outs() << "Naming after module; new name is " << newName << "\n");
    F.setName(newName);
  } else {
    F.setName(oldMainName);
  }

  return true;
}

const std::string BootieRenameMain::oldMainName = BOOTIE_OLDMAINNAME;
