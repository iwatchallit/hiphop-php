/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   | Copyright (c) 1997-2010 The PHP Group                                |
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

#ifndef __EXT_INTL_H__
#define __EXT_INTL_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/base/base_includes.h>
#include <runtime/base/zend/zend_collator.h>
#include <unicode/ucol.h> // icu
namespace HPHP {
extern const int64 q_Collator$$SORT_REGULAR;
}
namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

int64 f_intl_get_error_code();
String f_intl_get_error_message();
String f_intl_error_name(int64 error_code);
bool f_intl_is_failure(int64 error_code);
Variant f_collator_asort(CVarRef obj, VRefParam arr, int64 sort_flag = q_Collator$$SORT_REGULAR);
Variant f_collator_compare(CVarRef obj, CStrRef str1, CStrRef str2);
Variant f_collator_create(CStrRef locale);
Variant f_collator_get_attribute(CVarRef obj, int64 attr);
Variant f_collator_get_error_code(CVarRef obj);
Variant f_collator_get_error_message(CVarRef obj);
Variant f_collator_get_locale(CVarRef obj, int64 type = 0);
Variant f_collator_get_strength(CVarRef obj);
Variant f_collator_set_attribute(CVarRef obj, int64 attr, int64 val);
Variant f_collator_set_strength(CVarRef obj, int64 strength);
Variant f_collator_sort_with_sort_keys(CVarRef obj, VRefParam arr);
Variant f_collator_sort(CVarRef obj, VRefParam arr, int64 sort_flag = q_Collator$$SORT_REGULAR);
Variant f_idn_to_ascii(CStrRef domain, int64 options = 0, int64 variant = 0, VRefParam idna_info = null);
Variant f_idn_to_unicode(CStrRef domain, int64 options = 0, int64 variant = 0, VRefParam idna_info = null);
Variant f_idn_to_utf8(CStrRef domain, int64 options = 0, int64 variant = 0, VRefParam idna_info = null);
extern const int64 q_Collator$$SORT_REGULAR;
extern const int64 q_Collator$$SORT_NUMERIC;
extern const int64 q_Collator$$SORT_STRING;
extern const int64 q_Collator$$FRENCH_COLLATION;
extern const int64 q_Collator$$ALTERNATE_HANDLING;
extern const int64 q_Collator$$CASE_FIRST;
extern const int64 q_Collator$$CASE_LEVEL;
extern const int64 q_Collator$$NORMALIZATION_MODE;
extern const int64 q_Collator$$STRENGTH;
extern const int64 q_Collator$$HIRAGANA_QUATERNARY_MODE;
extern const int64 q_Collator$$NUMERIC_COLLATION;
extern const int64 q_Collator$$DEFAULT_VALUE;
extern const int64 q_Collator$$PRIMARY;
extern const int64 q_Collator$$SECONDARY;
extern const int64 q_Collator$$TERTIARY;
extern const int64 q_Collator$$DEFAULT_STRENGTH;
extern const int64 q_Collator$$QUATERNARY;
extern const int64 q_Collator$$IDENTICAL;
extern const int64 q_Collator$$OFF;
extern const int64 q_Collator$$ON;
extern const int64 q_Collator$$SHIFTED;
extern const int64 q_Collator$$NON_IGNORABLE;
extern const int64 q_Collator$$LOWER_FIRST;
extern const int64 q_Collator$$UPPER_FIRST;

///////////////////////////////////////////////////////////////////////////////
// class Collator

FORWARD_DECLARE_CLASS_BUILTIN(Collator);
class c_Collator : public ExtObjectData, public Sweepable {
 public:
  DECLARE_CLASS(Collator, Collator, ObjectData)

  // need to implement
  public: c_Collator(const ObjectStaticCallbacks *cb = &cw_Collator);
  public: ~c_Collator();
  public: void t___construct(CStrRef locale);
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: bool t_asort(VRefParam arr, int64 sort_flag = q_Collator$$SORT_REGULAR);
  DECLARE_METHOD_INVOKE_HELPERS(asort);
  public: Variant t_compare(CStrRef str1, CStrRef str2);
  DECLARE_METHOD_INVOKE_HELPERS(compare);
  public: static Variant ti_create(const char* cls , CStrRef locale);
  public: static Variant t_create(CStrRef locale) {
    return ti_create("collator", locale);
  }
  DECLARE_METHOD_INVOKE_HELPERS(create);
  public: int64 t_getattribute(int64 attr);
  DECLARE_METHOD_INVOKE_HELPERS(getattribute);
  public: int64 t_geterrorcode();
  DECLARE_METHOD_INVOKE_HELPERS(geterrorcode);
  public: String t_geterrormessage();
  DECLARE_METHOD_INVOKE_HELPERS(geterrormessage);
  public: String t_getlocale(int64 type = 0);
  DECLARE_METHOD_INVOKE_HELPERS(getlocale);
  public: int64 t_getstrength();
  DECLARE_METHOD_INVOKE_HELPERS(getstrength);
  public: bool t_setattribute(int64 attr, int64 val);
  DECLARE_METHOD_INVOKE_HELPERS(setattribute);
  public: bool t_setstrength(int64 strength);
  DECLARE_METHOD_INVOKE_HELPERS(setstrength);
  public: bool t_sortwithsortkeys(VRefParam arr);
  DECLARE_METHOD_INVOKE_HELPERS(sortwithsortkeys);
  public: bool t_sort(VRefParam arr, int64 sort_flag = q_Collator$$SORT_REGULAR);
  DECLARE_METHOD_INVOKE_HELPERS(sort);

  // implemented by HPHP
  public: c_Collator *create(String locale);
  static const ClassPropTable os_prop_table;

 private:
  String     m_locale;
  UCollator *m_ucoll;
  intl_error m_errcode;
};
extern const int64 q_Locale$$ACTUAL_LOCALE;
extern const int64 q_Locale$$VALID_LOCALE;

///////////////////////////////////////////////////////////////////////////////
// class Locale

FORWARD_DECLARE_CLASS_BUILTIN(Locale);
class c_Locale : public ExtObjectData {
 public:
  DECLARE_CLASS(Locale, Locale, ObjectData)

  // need to implement
  public: c_Locale(const ObjectStaticCallbacks *cb = &cw_Locale);
  public: ~c_Locale();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);

  // implemented by HPHP
  public: c_Locale *create();
  static const ClassPropTable os_prop_table;


};
extern const int64 q_Normalizer$$NONE;
extern const int64 q_Normalizer$$FORM_D;
extern const int64 q_Normalizer$$NFD;
extern const int64 q_Normalizer$$FORM_KD;
extern const int64 q_Normalizer$$NFKD;
extern const int64 q_Normalizer$$FORM_C;
extern const int64 q_Normalizer$$NFC;
extern const int64 q_Normalizer$$FORM_KC;
extern const int64 q_Normalizer$$NFKC;

///////////////////////////////////////////////////////////////////////////////
// class Normalizer

FORWARD_DECLARE_CLASS_BUILTIN(Normalizer);
class c_Normalizer : public ExtObjectData, public Sweepable {
 public:
  DECLARE_CLASS(Normalizer, Normalizer, ObjectData)

  // need to implement
  public: c_Normalizer(const ObjectStaticCallbacks *cb = &cw_Normalizer);
  public: ~c_Normalizer();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: static Variant ti_isnormalized(const char* cls , CStrRef input, int64 form = q_Normalizer$$FORM_C);
  public: static Variant t_isnormalized(CStrRef input, int64 form = q_Normalizer$$FORM_C) {
    return ti_isnormalized("normalizer", input, form);
  }
  DECLARE_METHOD_INVOKE_HELPERS(isnormalized);
  public: static Variant ti_normalize(const char* cls , CStrRef input, int64 form = q_Normalizer$$FORM_C);
  public: static Variant t_normalize(CStrRef input, int64 form = q_Normalizer$$FORM_C) {
    return ti_normalize("normalizer", input, form);
  }
  DECLARE_METHOD_INVOKE_HELPERS(normalize);

  // implemented by HPHP
  public: c_Normalizer *create();
  static const ClassPropTable os_prop_table;


};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_INTL_H__
