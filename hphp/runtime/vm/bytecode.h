/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
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

#ifndef incl_VM_BYTECODE_H_
#define incl_VM_BYTECODE_H_

#include <boost/optional.hpp>

#include "util/util.h"
#include "runtime/base/complex_types.h"
#include "runtime/base/class_info.h"
#include "runtime/base/array/array_iterator.h"

#include "runtime/vm/core_types.h"
#include "runtime/vm/class.h"
#include "runtime/vm/instance.h"
#include "runtime/vm/unit.h"
#include "runtime/vm/name_value_table.h"
#include "runtime/vm/request_arena.h"

namespace HPHP {

namespace VM {

// SETOP_BODY() would ideally be an inline function, but the header
// dependencies for concat_assign() make this unfeasible.
#define SETOP_BODY(lhs, op, rhs) do {                                         \
  switch (op) {                                                               \
  case SetOpPlusEqual: tvAsVariant(lhs) += tvCellAsCVarRef(rhs); break;       \
  case SetOpMinusEqual: tvAsVariant(lhs) -= tvCellAsCVarRef(rhs); break;      \
  case SetOpMulEqual: tvAsVariant(lhs) *= tvCellAsCVarRef(rhs); break;        \
  case SetOpDivEqual: tvAsVariant(lhs) /= tvCellAsCVarRef(rhs); break;        \
  case SetOpConcatEqual: {                                                    \
    concat_assign(tvAsVariant(lhs), tvCellAsCVarRef(rhs));                    \
    break;                                                                    \
  }                                                                           \
  case SetOpModEqual: tvAsVariant(lhs) %= tvCellAsCVarRef(rhs); break;        \
  case SetOpAndEqual: tvAsVariant(lhs) &= tvCellAsCVarRef(rhs); break;        \
  case SetOpOrEqual: tvAsVariant(lhs) |= tvCellAsCVarRef(rhs); break;         \
  case SetOpXorEqual: tvAsVariant(lhs) ^= tvCellAsCVarRef(rhs); break;        \
  case SetOpSlEqual: tvAsVariant(lhs) <<= tvCellAsCVarRef(rhs); break;        \
  case SetOpSrEqual: tvAsVariant(lhs) >>= tvCellAsCVarRef(rhs); break;        \
  default: assert(false);                                                     \
  }                                                                           \
} while (0)

class Func;

// max number of arguments for direct call to builtin
static const int kMaxBuiltinArgs = 5;


struct ExtraArgs : private boost::noncopyable {
  /*
   * Allocate an ExtraArgs structure, with arguments copied from the
   * evaluation stack.  This takes ownership of the args without
   * adjusting reference counts, so they must be discarded from the
   * stack.
   */
  static ExtraArgs* allocateCopy(TypedValue* args, unsigned nargs);

  /*
   * Allocate an ExtraArgs, without initializing any of the arguments.
   * All arguments must be initialized via getExtraArg before
   * deallocate() is called for the returned pointer.
   */
  static ExtraArgs* allocateUninit(unsigned nargs);

  /*
   * Deallocate an extraArgs structure.  Either use the one that
   * exists in a ActRec, or do it explicitly.
   */
  static void deallocate(ActRec*);
  static void deallocate(ExtraArgs*, unsigned numArgs);

  /*
   * Get the slot for extra arg i, where i = argNum - func->numParams.
   */
  TypedValue* getExtraArg(unsigned argInd) const;

private:
  ExtraArgs();
  ~ExtraArgs();

  static void* allocMem(unsigned nargs);

private:
  TypedValue m_extraArgs[];
};

/*
 * Variable environment.
 *
 * A variable environment consists of the locals for the current function
 * (either pseudo-main, global function, or method), plus any variables that
 * are dynamically defined.
 *
 * Logically, a global function or method starts off with a variable
 * environment that contains only its locals, but a pseudo-main is handed
 * its caller's existing variable environment. Generally, however, we don't
 * create a variable environment for global functions or methods until it
 * actually needs one (i.e. if it is about to include a pseudo-main, or if
 * it uses dynamic variable lookups).
 *
 * Named locals always appear in the expected place on the stack, even after
 * a VarEnv is attached. Internally uses a NameValueTable to hook up names to
 * the local locations.
 */
class VarEnv {
 private:
  ExtraArgs* m_extraArgs;
  uint16_t m_depth;
  bool m_malloced;
  ActRec* m_cfp;
  VarEnv* m_previous;
  // TODO remove vector (#1099580).  Note: trying changing this to a
  // TinyVector<> for now increased icache misses, but maybe will be
  // feasable later (see D511561).
  std::vector<TypedValue**> m_restoreLocations;
  boost::optional<NameValueTable> m_nvTable;

 private:
  explicit VarEnv();
  explicit VarEnv(ActRec* fp, ExtraArgs* eArgs);
  VarEnv(const VarEnv&);
  VarEnv& operator=(const VarEnv&);
  ~VarEnv();

  void ensureNvt();

 public:
  /*
   * Creates a VarEnv and attaches it to the existing frame fp.
   *
   * A lazy attach works by bringing all currently existing values for
   * the names in fp->m_func into the variable environment.  This is
   * used when we need a variable environment for some caller frame
   * (because we're about to attach a callee frame using attach()) but
   * don't actually have one.
   *
   * `skipInsert' means not to insert the new VarEnv on the front of
   * g_vmContext->m_topVarEnv.  In this case the caller must
   * immediately call setPrevious() as appropriate---this is used to
   * support the debugger, creating VarEnvs for frames in the middle
   * of the ActRec chain.
   */
  static VarEnv* createLazyAttach(ActRec* fp, bool skipInsert = false);

  // Allocate a global VarEnv.  Initially not attached to any frame.
  static VarEnv* createGlobal();

  static void destroy(VarEnv*);

  /*
   * Walk the VarEnv chain.  Returns null when we're out of variable
   * environments.  You can change the chain with setPrevious (see
   * evalPHPDebugger).
   */
  VarEnv* previous() { return m_previous; }
  void setPrevious(VarEnv* p) { m_previous = p; }

  void attach(ActRec* fp);
  void detach(ActRec* fp);

  void set(const StringData* name, TypedValue* tv);
  void bind(const StringData* name, TypedValue* tv);
  void setWithRef(const StringData* name, TypedValue* tv);
  TypedValue* lookup(const StringData* name);
  TypedValue* lookupAdd(const StringData* name);
  TypedValue* lookupRawPointer(const StringData* name);
  TypedValue* lookupAddRawPointer(const StringData* name);
  bool unset(const StringData* name);

  Array getDefinedVariables() const;

  // Used for save/store m_cfp for debugger
  void setCfp(ActRec* fp) { m_cfp = fp; }
  ActRec* getCfp() const { return m_cfp; }
  bool isGlobalScope() const { return !m_previous; }

  // Access to wrapped ExtraArgs, if we have one.
  TypedValue* getExtraArg(unsigned argInd) const;
};

/**
 * An "ActRec" is a call activation record. The ordering of the fields assumes
 * that stacks grow toward lower addresses.
 *
 * For most purposes, an ActRec can be considered to be in one of three
 * possible states:
 *   Pre-live:
 *     After the FPush* instruction which materialized the ActRec on the stack
 *     but before the corresponding FCall instruction
 *   Live:
 *     After the corresponding FCall instruction but before the ActRec fields
 *     and locals/iters have been decref'd (either by return or unwinding)
 *   Post-live:
 *     After the ActRec fields and locals/iters have been decref'd
 *
 * Note that when a function is invoked by the runtime via invokeFunc(), the
 * "pre-live" state is skipped and the ActRec is materialized in the "live"
 * state.
 */
struct ActRec {
  union {
    // This pair of uint64_t's must be the first two elements in the structure
    // so that the pointer to the ActRec can also be used for RBP chaining.
    // Note that ActRec's are also x64 frames, so this is an implicit machine
    // dependency.
    TypedValue _dummyA;
    struct {
      uint64_t m_savedRbp;     // Previous hardware frame pointer/ActRec.
      uint64_t m_savedRip;     // In-TC address to return to.
    };
  };
  union {
    TypedValue _dummyB;
    struct {
      const Func* m_func;      // Function.
      uint32_t m_soff;         // Saved offset of caller from beginning of
                               //   caller's Func's bytecode.

      // Bits 0-30 are the number of function args; the high bit is
      // whether this ActRec came from FPushCtor*.
      uint32_t m_numArgsAndCtorFlag;
    };
  };
  union {
    TypedValue m_r;          // Return value teleported here when the ActRec
                             //   is post-live.
    struct {
      union {
        ObjectData* m_this;    // This.
        Class* m_cls;          // Late bound class.
      };
      union {
        VarEnv* m_varEnv;       // Variable environment; only used when the
                                //   ActRec is live.
        ExtraArgs* m_extraArgs; // Light-weight extra args; used only when the
                                //   ActRec is live.
        StringData* m_invName;  // Invoked function name (used for __call);
                                //   only used when ActRec is pre-live.
      };
    };
  };

  // skip this frame if it is for a builtin function
  bool skipFrame() const;

  /**
   * Accessors for the packed m_numArgsAndCtorFlag field. We track
   * whether ActRecs came from FPushCtor* so that during unwinding we
   * can set the flag not to call destructors for objects whose
   * constructors exit via an exception.
   */

  int32_t numArgs() const {
    return m_numArgsAndCtorFlag & ~(1u << 31);
  }

  bool isFromFPushCtor() const {
    return m_numArgsAndCtorFlag & (1u << 31);
  }

  static inline uint32_t
  encodeNumArgs(uint32_t numArgs, bool isFPushCtor = false) {
    assert((numArgs & (1u << 31)) == 0);
    return numArgs | (isFPushCtor << 31);
  }

  void initNumArgs(uint32_t numArgs, bool isFPushCtor = false) {
    m_numArgsAndCtorFlag = encodeNumArgs(numArgs, isFPushCtor);
  }

  void setNumArgs(uint32_t numArgs) {
    initNumArgs(numArgs, isFromFPushCtor());
  }

  /**
   * To conserve space, we use unions for pairs of mutually exclusive
   * fields (fields that are not used at the same time). We use unions
   * for m_this/m_cls and m_varEnv/m_invName.
   *
   * The least significant bit is used as a marker for each pair of fields
   * so that we can distinguish at runtime which field is valid. We define
   * accessors below to encapsulate this logic.
   *
   * Note that m_invName is only used when the ActRec is pre-live. Thus when
   * an ActRec is live it is safe to directly access m_varEnv without using
   * accessors.
   */

#define UNION_FIELD_ACCESSORS2(name1, type1, field1, name2, type2, field2) \
  inline bool has##name1() const { \
    return field1 && !(intptr_t(field1) & 3LL); \
  } \
  inline bool has##name2() const { \
    return bool(intptr_t(field2) & 1LL); \
  } \
  inline type1 get##name1() const { \
    assert(has##name1()); \
    return field1; \
  } \
  inline type2 get##name2() const { \
    assert(has##name2()); \
    return (type2)(intptr_t(field2) & ~1LL); \
  } \
  inline void set##name1(type1 val) { \
    field1 = val; \
  } \
  inline void set##name2(type2 val) { \
    field2 = (type2)(intptr_t(val) | 1LL); \
  } \

#define UNION_FIELD_ACCESSORS3(name1, type1, field1, name2, type2, field2, name3, type3, field3) \
  inline bool has##name1() const { \
    return field1 && !(intptr_t(field1) & 3LL); \
  } \
  inline bool has##name2() const { \
    return bool(intptr_t(field2) & 1LL); \
  } \
  inline bool has##name3() const { \
    return bool(intptr_t(field3) & 2LL); \
  } \
  inline type1 get##name1() const { \
    assert(has##name1()); \
    return field1; \
  } \
  inline type2 get##name2() const { \
    assert(has##name2()); \
    return (type2)(intptr_t(field2) & ~1LL); \
  } \
  inline type3 get##name3() const { \
    return (type3)(intptr_t(field3) & ~2LL); \
  } \
  inline void set##name1(type1 val) { \
    field1 = val; \
  } \
  inline void set##name2(type2 val) { \
    field2 = (type2)(intptr_t(val) | 1LL); \
  } \
  inline void set##name3(type3 val) { \
    field3 = (type3)(intptr_t(val) | 2LL); \
  }

  // Note that reordering these is likely to require changes to the
  // translator.
  UNION_FIELD_ACCESSORS2(This, ObjectData*, m_this, Class, Class*, m_cls)
  static const int8_t kInvNameBit   = 0x1;
  static const int8_t kExtraArgsBit = 0x2;
  UNION_FIELD_ACCESSORS3(VarEnv, VarEnv*, m_varEnv, InvName, StringData*,
                         m_invName, ExtraArgs, ExtraArgs*, m_extraArgs)

#undef UNION_FIELD_ACCESSORS2
#undef UNION_FIELD_ACCESSORS3

  // Accessors for extra arg queries.
  TypedValue* getExtraArg(unsigned ind) const {
    assert(hasExtraArgs() || hasVarEnv());
    return hasExtraArgs() ? getExtraArgs()->getExtraArg(ind) :
           hasVarEnv()    ? getVarEnv()->getExtraArg(ind) :
           static_cast<TypedValue*>(0);
  }
};

inline int32 arOffset(const ActRec* ar, const ActRec* other) {
  return (intptr_t(other) - intptr_t(ar)) / sizeof(TypedValue);
}

inline ActRec* arAtOffset(const ActRec* ar, int32 offset) {
  return (ActRec*)(intptr_t(ar) + intptr_t(offset * sizeof(TypedValue)));
}

inline ActRec* arFromSpOffset(const ActRec *sp, int32 offset) {
  return arAtOffset(sp, offset);
}

inline void arSetSfp(ActRec* ar, const ActRec* sfp) {
  static_assert(offsetof(ActRec, m_savedRbp) == 0,
                "m_savedRbp should be at offset 0 of ActRec");
  static_assert(sizeof(ActRec*) <= sizeof(uint64_t),
                "ActRec* must be <= 64 bits");
  ar->m_savedRbp = (uint64_t)sfp;
}

template <bool crossBuiltin> Class* arGetContextClassImpl(const ActRec* ar);
#define arGetContextClass(ar)    HPHP::VM::arGetContextClassImpl<false>(ar)
#define arGetContextClassFromBuiltin(ar) \
  HPHP::VM::arGetContextClassImpl<true>(ar)

// Used by extension functions that take a PHP "callback", since they need to
// figure out the callback context once and call it multiple times. (e.g.
// array_map, array_filter, ...)
struct CallCtx {
  const Func* func;
  ObjectData* this_;
  Class* cls;
  StringData* invName;
};

static const size_t kNumIterCells = sizeof(Iter) / sizeof(Cell);
static const size_t kNumActRecCells = sizeof(ActRec) / sizeof(Cell);

struct Fault {
  enum Type : int16_t {
    UserException,
    CppException
  };

  explicit Fault()
    : m_handledCount(0)
    , m_savedRaiseOffset(kInvalidOffset)
  {}

  union {
    ObjectData* m_userException;
    Exception* m_cppException;
  };
  Type m_faultType;

  // During unwinding, this tracks the number of nested EHType_Fault
  // regions we've propagated through in a given frame.
  int16_t m_handledCount;

  // This is used when executing a fault handler to remember the
  // location the exception was raised at.  We will need to resume
  // throwing at the same location when it executes Unwind.  In all
  // other situations this is set to kInvalidOffset.
  Offset m_savedRaiseOffset;
};

enum UnwindStatus {
  UnwindResumeVM,
  UnwindPropagate,
};

// Interpreter evaluation stack.
class Stack {
private:
  TypedValue* m_elms;
  TypedValue* m_top;
  TypedValue* m_base; // Stack grows down, so m_base is beyond the end of
                      // m_elms.

public:
  void* getStackLowAddress() const { return m_elms; }
  void* getStackHighAddress() const { return m_base; }
  bool isValidAddress(uintptr_t v) {
    return v >= uintptr_t(m_elms) && v < uintptr_t(m_base);
  }
  void toStringElm(std::ostream& os, TypedValue* vv, const ActRec* fp)
    const;
  void toStringIter(std::ostream& os, Iter* it, bool itRef) const;
  void clearEvalStack(ActRec* fp, int32 numLocals);
  void protect();
  void unprotect();
  void requestInit();
  void requestExit();
private:
  void toStringFrag(std::ostream& os, const ActRec* fp,
                    const TypedValue* top) const;
  void toStringAR(std::ostream& os, const ActRec* fp,
                  const FPIEnt *fe, const TypedValue* top) const;
  void toStringFragAR(std::ostream& os, const ActRec* fp,
                    int offset, const TypedValue* top) const;
  void toStringFrame(std::ostream& os, const ActRec* fp,
                     int offset, const TypedValue* ftop,
                     const std::string& prefix) const;

  UnwindStatus unwindFrag(ActRec* fp, int offset, PC& pc, Fault& f);

  // Pops everything between the current stack pointer and the passed ActRec*.
  // It assumes everything there is values, not ActRecs.
  void unwindARFrag(ActRec* ar);

  // Pops everything up to and including the outermost unactivated ActRec. Since
  // it's impossible to have more than one chain of nested unactivated ActRecs
  // on the stack, this means that after this function returns, everything
  // between the stack pointer and frame pointer is a value, Iter or local.
  void unwindAR(ActRec* fp, const FPIEnt* fe);
public:
  static const int sSurprisePageSize;
  static const uint sMinStackElms;
  static void ValidateStackSize();
  Stack();
  ~Stack();

  std::string toString(const ActRec* fp, int offset,
                       std::string prefix="") const;

  UnwindStatus unwindFrame(ActRec*& fp, int offset, PC& pc, Fault f);

  bool wouldOverflow(int numCells) const;

  /*
   * top --
   * topOfStackOffset --
   *
   *   Accessors for the x64 translator. Do not play on or around.
   */
  TypedValue*& top() {
    return m_top;
  }

  static inline size_t topOfStackOffset() {
    Stack *that = 0;
    return (size_t)&that->m_top;
  }

  static TypedValue* frameStackBase(const ActRec* fp);
  static TypedValue* generatorStackBase(const ActRec* fp);

  inline size_t ALWAYS_INLINE count() const {
    return ((uintptr_t)m_base - (uintptr_t)m_top) / sizeof(TypedValue);
  }

  // Same as discard(), but meant to replace popC() iff the interpreter knows
  // for certain that decrementing a refcount is unnecessary.
  inline void ALWAYS_INLINE popX() {
    assert(m_top != m_base);
    assert(!IS_REFCOUNTED_TYPE(m_top->m_type));
    m_top++;
  }

  inline void ALWAYS_INLINE popC() {
    assert(m_top != m_base);
    assert(tvIsPlausible(m_top));
    assert(m_top->m_type != KindOfRef);
    tvRefcountedDecRefCell(m_top);
    m_top++;
  }

  inline void ALWAYS_INLINE popV() {
    assert(m_top != m_base);
    assert(m_top->m_type == KindOfRef);
    assert(m_top->m_data.pref != nullptr);
    tvDecRefRef(m_top);
    m_top++;
  }

  inline void ALWAYS_INLINE popTV() {
    assert(m_top != m_base);
    assert(tvIsPlausible(m_top));
    tvRefcountedDecRef(m_top);
    m_top++;
  }

  // popAR() should only be used to tear down a pre-live ActRec. Once
  // an ActRec is live, it should be torn down using frame_free_locals()
  // followed by discardAR() or ret().
  inline void ALWAYS_INLINE popAR() {
    assert(m_top != m_base);
    ActRec* ar = (ActRec*)m_top;
    if (ar->hasThis()) decRefObj(ar->getThis());
    if (ar->hasInvName()) decRefStr(ar->getInvName());

    // This should only be used on a pre-live ActRec.
    assert(!ar->hasVarEnv());
    assert(!ar->hasExtraArgs());

    m_top += kNumActRecCells;
    assert((uintptr_t)m_top <= (uintptr_t)m_base);
  }

  inline void ALWAYS_INLINE discardAR() {
    assert(m_top != m_base);
    m_top += kNumActRecCells;
    assert((uintptr_t)m_top <= (uintptr_t)m_base);
  }

  inline void ALWAYS_INLINE ret() {
    // Leave part of the activation on the stack, since the return value now
    // resides there.
    m_top += kNumActRecCells - 1;
    assert((uintptr_t)m_top <= (uintptr_t)m_base);
  }

  inline void ALWAYS_INLINE discard() {
    assert(m_top != m_base);
    m_top++;
  }

  inline void ALWAYS_INLINE ndiscard(size_t n) {
    assert((uintptr_t)&m_top[n] <= (uintptr_t)m_base);
    m_top += n;
  }

  inline void ALWAYS_INLINE dup() {
    assert(m_top != m_base);
    assert(m_top != m_elms);
    assert(m_top->m_type != KindOfRef);
    Cell* fr = (Cell*)m_top;
    m_top--;
    Cell* to = (Cell*)m_top;
    tvDupCell(fr, to);
  }

  inline void ALWAYS_INLINE box() {
    assert(m_top != m_base);
    assert(m_top->m_type != KindOfRef);
    tvBox(m_top);
  }

  inline void ALWAYS_INLINE unbox() {
    assert(m_top != m_base);
    tvUnbox(m_top);
  }

  inline void ALWAYS_INLINE pushUninit() {
    assert(m_top != m_elms);
    m_top--;
    tvWriteUninit(m_top);
  }

  inline void ALWAYS_INLINE pushNull() {
    assert(m_top != m_elms);
    m_top--;
    tvWriteNull(m_top);
  }

  inline void ALWAYS_INLINE pushNullUninit() {
    assert(m_top != m_elms);
    m_top--;
    m_top->m_data.num = 0;
    m_top->_count = 0;
    m_top->m_type = KindOfUninit;
  }

  #define PUSH_METHOD(name, type, field, value)                               \
  inline void ALWAYS_INLINE push##name() {                                    \
    assert(m_top != m_elms);                                                  \
    m_top--;                                                                  \
    m_top->m_data.field = value;                                              \
    m_top->_count = 0;                                                        \
    m_top->m_type = type;                                                     \
  }
  PUSH_METHOD(True, KindOfBoolean, num, 1)
  PUSH_METHOD(False, KindOfBoolean, num, 0)

  #define PUSH_METHOD_ARG(name, type, field, argtype, arg)                    \
  inline void ALWAYS_INLINE push##name(argtype arg) {                         \
    assert(m_top != m_elms);                                                  \
    m_top--;                                                                  \
    m_top->m_data.field = arg;                                                \
    m_top->_count = 0;                                                        \
    m_top->m_type = type;                                                     \
  }
  PUSH_METHOD_ARG(Int, KindOfInt64, num, int64, i)
  PUSH_METHOD_ARG(Double, KindOfDouble, dbl, double, d)

  // This should only be called directly when the caller has
  // already adjusted the refcount appropriately
  inline void ALWAYS_INLINE pushStringNoRc(StringData* s) {
    assert(m_top != m_elms);
    m_top--;
    m_top->m_data.pstr = s;
    m_top->_count = 0;
    m_top->m_type = KindOfString;
  }

  inline void ALWAYS_INLINE pushStaticString(StringData* s) {
    assert(s->isStatic()); // No need to call s->incRefCount().
    pushStringNoRc(s);
  }

  // This should only be called directly when the caller has
  // already adjusted the refcount appropriately
  inline void ALWAYS_INLINE pushArrayNoRc(ArrayData* a) {
    assert(m_top != m_elms);
    m_top--;
    m_top->m_data.parr = a;
    m_top->_count = 0;
    m_top->m_type = KindOfArray;
  }

  inline void ALWAYS_INLINE pushArray(ArrayData* a) {
    pushArrayNoRc(a);
    a->incRefCount();
  }

  inline void ALWAYS_INLINE pushStaticArray(ArrayData* a) {
    assert(a->isStatic()); // No need to call a->incRefCount().
    pushArrayNoRc(a);
  }

  // This should only be called directly when the caller has
  // already adjusted the refcount appropriately
  inline void ALWAYS_INLINE pushObjectNoRc(ObjectData* o) {
    assert(m_top != m_elms);
    m_top--;
    m_top->m_data.pobj = o;
    m_top->_count = 0;
    m_top->m_type = KindOfObject;
  }

  inline void ALWAYS_INLINE pushObject(ObjectData* o) {
    pushObjectNoRc(o);
    o->incRefCount();
  }

  inline Cell* ALWAYS_INLINE allocC() {
    assert(m_top != m_elms);
    m_top--;
    return (Cell*)m_top;
  }

  inline Var* ALWAYS_INLINE allocV() {
    assert(m_top != m_elms);
    m_top--;
    return (Var*)m_top;
  }

  inline TypedValue* ALWAYS_INLINE allocTV() {
    assert(m_top != m_elms);
    m_top--;
    return m_top;
  }

  inline ActRec* ALWAYS_INLINE allocA() {
    assert((uintptr_t)&m_top[-kNumActRecCells] >= (uintptr_t)m_elms);
    assert(kNumActRecCells * sizeof(Cell) == sizeof(ActRec));
    m_top -= kNumActRecCells;
    return (ActRec*)m_top;
  }

  inline void ALWAYS_INLINE allocI() {
    assert(kNumIterCells * sizeof(Cell) == sizeof(Iter));
    assert((uintptr_t)&m_top[-kNumIterCells] >= (uintptr_t)m_elms);
    m_top -= kNumIterCells;
  }

  inline Cell* ALWAYS_INLINE topC() {
    assert(m_top != m_base);
    assert(m_top->m_type != KindOfRef);
    return (Cell*)m_top;
  }

  inline Var* ALWAYS_INLINE topV() {
    assert(m_top != m_base);
    assert(m_top->m_type == KindOfRef);
    return (Var*)m_top;
  }

  inline TypedValue* ALWAYS_INLINE topTV() {
    assert(m_top != m_base);
    return m_top;
  }

  inline Cell* ALWAYS_INLINE indC(size_t ind) {
    assert(m_top != m_base);
    assert(m_top[ind].m_type != KindOfRef);
    return (Cell*)(&m_top[ind]);
  }

  inline TypedValue* ALWAYS_INLINE indTV(size_t ind) {
    assert(m_top != m_base);
    return &m_top[ind];
  }
  inline void ALWAYS_INLINE pushClass(Class* clss) {
    assert(m_top != m_elms);
    m_top--;
    m_top->m_data.pcls = clss;
    m_top->_count = 0;
    m_top->m_type = KindOfClass;
  }
};

///////////////////////////////////////////////////////////////////////////////
}
}

#endif // __VM_BYTECODE_H__
