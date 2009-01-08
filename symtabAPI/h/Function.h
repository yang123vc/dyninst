/*
 * Copyright (c) 1996-2007 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/************************************************************************
 * $Id: Symbol.h,v 1.20 2008/11/03 15:19:24 jaw Exp $
 * Symbol.h: symbol table objects.
************************************************************************/

#if !defined(_Function_h_)
#define _Function_h_

#include "Annotatable.h"

namespace Dyninst{
namespace SymtabAPI{

class Symbol;


class Function : public AnnotatableSparse 
{
   public:
      SYMTAB_EXPORT Function();

      SYMTAB_EXPORT static Function *createFunction(Symbol *sym);

      SYMTAB_EXPORT Offset   getAddress() const;
      SYMTAB_EXPORT Module * getModule() const;

      /***** Symbol Collection Management *****/
      SYMTAB_EXPORT bool addSymbol(Symbol *sym);
      SYMTAB_EXPORT bool removeSymbol(Symbol *sym);
      SYMTAB_EXPORT bool getAllSymbols(std::vector<Symbol *>&syms) const;
      SYMTAB_EXPORT Symbol * getFirstSymbol() const;

      /***** Symbol naming *****/
      SYMTAB_EXPORT const vector<std::string> &getAllMangledNames();
      SYMTAB_EXPORT const vector<std::string> &getAllPrettyNames();
      SYMTAB_EXPORT const vector<std::string> &getAllTypedNames();
      SYMTAB_EXPORT bool addMangledName(std::string name, bool isPrimary = false);
      SYMTAB_EXPORT bool addPrettyName(std::string name, bool isPrimary = false);
      SYMTAB_EXPORT bool addTypedName(std::string name, bool isPrimary = false);

      /***** Return Type Information *****/
      SYMTAB_EXPORT Type  * getReturnType() const;
      SYMTAB_EXPORT bool	setReturnType(Type *);

      /***** IA64-Specific Frame Pointer Information *****/
      SYMTAB_EXPORT bool  setFramePtrRegnum(int regnum);
      SYMTAB_EXPORT int   getFramePtrRegnum() const;

      /***** Local Variable Information *****/
      SYMTAB_EXPORT bool findLocalVariable(std::vector<localVar *>&vars, std::string name);
      SYMTAB_EXPORT bool getLocalVariables(std::vector<localVar *>&vars);
      SYMTAB_EXPORT bool getParams(std::vector<localVar *>&params);

      /* internal helper functions */
      bool addLocalVar(localVar *);
      bool addParam(localVar *);

   private:
      Offset        address_;
      Module*       module_;
      Type          *retType_;
      int           framePtrRegNum_;

      std::vector<Symbol *> symbols_;

      std::vector<std::string> mangledNames_;
      std::vector<std::string> prettyNames_;
      std::vector<std::string> typedNames_;
};


}
}

#endif
