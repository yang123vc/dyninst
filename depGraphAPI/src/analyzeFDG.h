/*
 * Copyright (c) 1996-2009 Barton P. Miller
 *
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 *
 * This license is for research uses.  For such uses, there is no
 * charge. We define "research use" to mean you may freely use it
 * inside your organization for whatever purposes you see fit. But you
 * may not re-distribute Paradyn or parts of Paradyn, in any form
 * source or binary (including derivatives), electronic or otherwise,
 * to any other organization or entity without our permission.
 *
 * (for other uses, please contact us at paradyn@cs.wisc.edu)
 *
 * All warranties, including without limitation, any warranty of
 * merchantability or fitness for a particular purpose, are hereby
 * excluded.
 *
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 *
 * Even if advised of the possibility of such damages, under no
 * circumstances shall we (or any other person or entity with
 * proprietary rights in the software licensed hereunder) be liable
 * to you or any third party for direct, indirect, or consequential
 * damages of any character regardless of type of action, including,
 * without limitation, loss of profits, loss of use, loss of good
 * will, or computer failure or malfunction.  You agree to indemnify
 * us (and any other person or entity with proprietary rights in the
 * software licensed hereunder) for any and all liability it may
 * incur to third parties resulting from your use of Paradyn.
 */

#ifndef CONTROLFLOWFIXER_H_
#define CONTROLFLOWFIXER_H_

#include <map>

#include "Node.h"
#include "FDG.h"

#include "Operation.h"

class BPatch_basicBlock;
class BPatch_function;

namespace Dyninst {
namespace DepGraphAPI {

/**
 * The tool that creates the Flow Dependence Graph (FDG) associated with a given 
 * function (currently BPatch_function).
 */
class FDGAnalyzer {
    friend class xPDGAnalyzer;
public:
    typedef BPatch_basicBlock Block;
    typedef std::set<Block*> BlockSet;
    typedef Node::Ptr NodePtr;
    typedef std::set<NodePtr> NodeSet;

private:
    typedef BPatch_function Function;
    typedef std::map<Block*, Node::Ptr> NodeMap;
    typedef std::map<Block*, BlockSet> DependenceMap;
  
  /**
   * Analyzed function
   */
  Function *func_;
  
  /**
   * The Flow Dependence Graph
   */
  FDG::Ptr fdg;
  
  /**
   * Maps each block A to a set of Block S which A depends on (for all S, A depends on S). 
   */
  DependenceMap blockToJumps;
  
  /**
   * Set of blocks which ends with a jump/branch/return instruction.
   */
  BlockSet markedBlocks;

public:
  FDGAnalyzer(Function *f) : func_(f) {};

  /**
   * Returns the FDG created by this intraFunctionCDGCreator object.
   */
  FDG::Ptr analyze();

  ~FDGAnalyzer();

protected:
  /**
   * Returns true iff this operation is a return or exit operation.
   */
  static bool isReturnOp(const Dyninst::InstructionAPI::Operation& opType);

  /**
   * Returns true iff this operation is a branch operation (including jumps) such as jnz, jnle, etc.
   */
  static bool isBranchOp(const Dyninst::InstructionAPI::Operation& opType);
  
private:
  void createNodes(BlockSet &blocks);
  Node::Ptr makeNode(NodeMap& nodeMap, Block* block);
  void markBlocksWithJump(BlockSet &blocks);
  void findDependencies(BlockSet &blocks);
  void findBlocksRecursive(BlockSet& needThese, BlockSet& visited, Block* givenBlock);
};

};
};

#endif /* CONTROLFLOWFIXER_H_ */