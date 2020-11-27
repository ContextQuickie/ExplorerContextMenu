/***********************************************************************************************************************
 MIT License

 Copyright(c) 2020 Roland Reinl

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files(the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions :

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
***********************************************************************************************************************/

/***********************************************************************************************************************
 INCLUDES
***********************************************************************************************************************/
#include <stdint.h>
#include "ExplorerContextMenu.h"
#include "JavaExplorerContextMenuEntry.h"
#include "explorercontextmenu_menu_ExplorerContextMenu.h"
#include "explorercontextmenu_menu_ExplorerContextMenuEntry.h"

using namespace std;
using namespace ContextQuickie;
/***********************************************************************************************************************
 DEFINES
***********************************************************************************************************************/

/***********************************************************************************************************************
 TYPES
***********************************************************************************************************************/

/***********************************************************************************************************************
 LOCAL CONSTANTS
***********************************************************************************************************************/

/***********************************************************************************************************************
 LOCAL VARIABLES
***********************************************************************************************************************/

/***********************************************************************************************************************
 LOCAL FUNCTION DECLARATIONS
***********************************************************************************************************************/

/***********************************************************************************************************************
 IMPLEMENTATION
***********************************************************************************************************************/
JNIEXPORT void JNICALL Java_explorercontextmenu_menu_ExplorerContextMenu_getEntries(JNIEnv* env, jobject instance, jobjectArray paths)
{
  uint32_t pathsCount = env->GetArrayLength(paths);
  vector<wstring> convertedPaths;
  for (uint32_t pathIndex = 0; pathIndex < pathsCount; pathIndex++)
  {
    jstring jstringPath = (jstring) env->GetObjectArrayElement(paths, pathIndex);
    const jchar* jcharPath = env->GetStringChars(jstringPath, JNI_FALSE);
    convertedPaths.push_back((wchar_t*)jcharPath);
    env->ReleaseStringChars(jstringPath, jcharPath);
  }

  ExplorerContextMenu* menu = new ExplorerContextMenu (convertedPaths, true);
  JavaExplorerContextMenuEntry wrapper(env, instance);
  wrapper.SetNativeHandle(menu);
  wrapper.CopyEntries(*menu);
}

JNIEXPORT void JNICALL Java_explorercontextmenu_menu_ExplorerContextMenu_deleteUnmanagedInstance(JNIEnv* env, jobject instance)
{
  JavaExplorerContextMenuEntry javaEntry(env, instance);
  ExplorerContextMenu* menu = (ExplorerContextMenu*)javaEntry.GetNativeHandle();
  if (menu != nullptr)
  {
    delete menu;
  }
}

JNIEXPORT void JNICALL Java_explorercontextmenu_menu_ExplorerContextMenuEntry_executeNativeCommand(JNIEnv* env, jobject instance, jboolean executeSynchronous)
{
  JavaExplorerContextMenuEntry javaEntry(env, instance);
  ExplorerContextMenuEntry* entry = javaEntry.GetNativeHandle();
  if (entry != nullptr)
  {
    entry->ExecuteCommand(executeSynchronous);
  }
}

/***********************************************************************************************************************
 EOF
***********************************************************************************************************************/