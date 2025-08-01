/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-present Facebook, Inc. (http://www.facebook.com)  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/runtime/vm/jit/vasm-gen.h"
#include "hphp/runtime/vm/jit/vasm-unit.h"

#include <algorithm>

namespace HPHP::jit {
///////////////////////////////////////////////////////////////////////////////


void Vunit::allocFrame(const IRInstruction* origin) {
  assertx(origin->is(DefCalleeFP));

  auto const parentFp = origin->src(1);
  auto const parentIt = fpToFrame.find(parentFp);
  assertx(parentIt != fpToFrame.end());

  auto const parent_frame = parentIt->second;
  auto const extra = origin->extra<DefCalleeFP>();
  auto const fp = origin->dst();
  auto const [it, inserted] = fpToFrame.emplace(fp, frames.size());
  if (!inserted) {
    always_assert(frames[it->second].parent == parent_frame);
    return;
  }

  for (auto f = parent_frame; f != Vframe::Top; f = frames[f].parent) {
    frames[f].inclusive_cost += extra->cost;
    frames[f].num_inner_frames++;
  }

  auto const sbToRootSbOff =
    frames[parent_frame].sbToRootSbOff +
    extra->returnSPOff.offset + kNumActRecCells - 1 +
    extra->func->numSlotsInFrame();

  frames.emplace_back(
    extra->func,
    origin->marker().bcOff(),
    sbToRootSbOff,
    parent_frame,
    extra->cost,
    0
  );
}

Vlabel Vunit::makeBlock(AreaIndex area, uint64_t weight) {
  auto i = blocks.size();
  blocks.emplace_back(area, weight);
  return Vlabel{i};
}

Vlabel Vunit::makeBlock(AreaIndex area) {
  return makeBlock(area, areaWeightFactor(area));
}

Vlabel Vunit::makeScratchBlock() {
  return makeBlock(AreaIndex::Main, 1);
}

void Vunit::freeScratchBlock(Vlabel l) {
  // This will leak blocks if anything's been added since the corresponding
  // call to makeScratchBlock(), but it's harmless.
  if (l == blocks.size() - 1) blocks.pop_back();
}

Vtuple Vunit::makeTuple(VregList&& regs) {
  auto i = tuples.size();
  tuples.emplace_back(std::move(regs));
  return Vtuple{i};
}

Vtuple Vunit::makeTuple(const VregList& regs) {
  auto i = tuples.size();
  tuples.emplace_back(regs);
  return Vtuple{i};
}

VcallArgsId Vunit::makeVcallArgs(VcallArgs&& args) {
  VcallArgsId i(vcallArgs.size());
  vcallArgs.emplace_back(std::move(args));
  return i;
}

Vreg Vunit::makeConst(Vconst vconst) {
  auto it = constToReg.find(vconst);
  if (it != constToReg.end()) return it->second;

  auto const reg = makeReg();
  constToReg.emplace(vconst, reg);
  regToConst.emplace(reg, vconst);
  return reg;
}

bool Vunit::needsRegAlloc() const {
  if (next_vr > Vreg::V0) return true;

  for (auto& block : blocks) {
    for (auto& inst : block.code) {
      if (inst.op == Vinstr::copyargs) return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////
}
