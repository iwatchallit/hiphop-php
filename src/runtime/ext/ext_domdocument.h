/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
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

#ifndef __EXT_DOMDOCUMENT_H__
#define __EXT_DOMDOCUMENT_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<
#include <runtime/ext/ext_domdocument_includes.h>

#include <runtime/base/base_includes.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

Variant f_dom_document_create_element(CVarRef obj, CStrRef name, CStrRef value = null_string);
Variant f_dom_document_create_document_fragment(CVarRef obj);
Variant f_dom_document_create_text_node(CVarRef obj, CStrRef data);
Variant f_dom_document_create_comment(CVarRef obj, CStrRef data);
Variant f_dom_document_create_cdatasection(CVarRef obj, CStrRef data);
Variant f_dom_document_create_processing_instruction(CVarRef obj, CStrRef target, CStrRef data = null_string);
Variant f_dom_document_create_attribute(CVarRef obj, CStrRef name);
Variant f_dom_document_create_entity_reference(CVarRef obj, CStrRef name);
Variant f_dom_document_get_elements_by_tag_name(CVarRef obj, CStrRef name);
Variant f_dom_document_import_node(CVarRef obj, CObjRef importednode, bool deep = false);
Variant f_dom_document_create_element_ns(CVarRef obj, CStrRef namespaceuri, CStrRef qualifiedname, CStrRef value = null_string);
Variant f_dom_document_create_attribute_ns(CVarRef obj, CStrRef namespaceuri, CStrRef qualifiedname);
Variant f_dom_document_get_elements_by_tag_name_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname);
Variant f_dom_document_get_element_by_id(CVarRef obj, CStrRef elementid);
Variant f_dom_document_normalize_document(CVarRef obj);
Variant f_dom_document_save(CVarRef obj, CStrRef file, int64 options = 0);
Variant f_dom_document_savexml(CVarRef obj, CObjRef node = null_object, int64 options = 0);
Variant f_dom_document_validate(CVarRef obj);
Variant f_dom_document_xinclude(CVarRef obj, int64 options = 0);
Variant f_dom_document_save_html(CVarRef obj);
Variant f_dom_document_save_html_file(CVarRef obj, CStrRef file);
Variant f_dom_document_schema_validate_file(CVarRef obj, CStrRef filename);
Variant f_dom_document_schema_validate_xml(CVarRef obj, CStrRef source);
Variant f_dom_document_relaxng_validate_file(CVarRef obj, CStrRef filename);
Variant f_dom_document_relaxng_validate_xml(CVarRef obj, CStrRef source);
Variant f_dom_node_insert_before(CVarRef obj, CObjRef newnode, CObjRef refnode = null);
Variant f_dom_node_replace_child(CVarRef obj, CObjRef newchildobj, CObjRef oldchildobj);
Variant f_dom_node_remove_child(CVarRef obj, CObjRef node);
Variant f_dom_node_append_child(CVarRef obj, CObjRef newnode);
Variant f_dom_node_has_child_nodes(CVarRef obj);
Variant f_dom_node_clone_node(CVarRef obj, bool deep = false);
Variant f_dom_node_normalize(CVarRef obj);
Variant f_dom_node_is_supported(CVarRef obj, CStrRef feature, CStrRef version);
Variant f_dom_node_has_attributes(CVarRef obj);
Variant f_dom_node_is_same_node(CVarRef obj, CObjRef node);
Variant f_dom_node_lookup_prefix(CVarRef obj, CStrRef prefix);
Variant f_dom_node_is_default_namespace(CVarRef obj, CStrRef namespaceuri);
Variant f_dom_node_lookup_namespace_uri(CVarRef obj, CStrRef namespaceuri);
Variant f_dom_nodelist_item(CVarRef obj, int64 index);
Variant f_dom_namednodemap_get_named_item(CVarRef obj, CStrRef name);
Variant f_dom_namednodemap_item(CVarRef obj, int64 index);
Variant f_dom_namednodemap_get_named_item_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname);
Variant f_dom_characterdata_substring_data(CVarRef obj, int64 offset, int64 count);
Variant f_dom_characterdata_append_data(CVarRef obj, CStrRef arg);
Variant f_dom_characterdata_insert_data(CVarRef obj, int64 offset, CStrRef data);
Variant f_dom_characterdata_delete_data(CVarRef obj, int64 offset, int64 count);
Variant f_dom_characterdata_replace_data(CVarRef obj, int64 offset, int64 count, CStrRef data);
Variant f_dom_attr_is_id(CVarRef obj);
Variant f_dom_element_get_attribute(CVarRef obj, CStrRef name);
Variant f_dom_element_set_attribute(CVarRef obj, CStrRef name, CStrRef value);
Variant f_dom_element_remove_attribute(CVarRef obj, CStrRef name);
Variant f_dom_element_get_attribute_node(CVarRef obj, CStrRef name);
Variant f_dom_element_set_attribute_node(CVarRef obj, CObjRef newattr);
Variant f_dom_element_remove_attribute_node(CVarRef obj, CObjRef oldattr);
Variant f_dom_element_get_elements_by_tag_name(CVarRef obj, CStrRef name);
Variant f_dom_element_get_attribute_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname);
Variant f_dom_element_set_attribute_ns(CVarRef obj, CStrRef namespaceuri, CStrRef name, CStrRef value);
Variant f_dom_element_remove_attribute_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname);
Variant f_dom_element_get_attribute_node_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname);
Variant f_dom_element_set_attribute_node_ns(CVarRef obj, CObjRef newattr);
Variant f_dom_element_get_elements_by_tag_name_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname);
Variant f_dom_element_has_attribute(CVarRef obj, CStrRef name);
Variant f_dom_element_has_attribute_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname);
Variant f_dom_element_set_id_attribute(CVarRef obj, CStrRef name, bool isid);
Variant f_dom_element_set_id_attribute_ns(CVarRef obj, CStrRef namespaceuri, CStrRef localname, bool isid);
Variant f_dom_element_set_id_attribute_node(CVarRef obj, CObjRef idattr, bool isid);
Variant f_dom_text_split_text(CVarRef obj, int64 offset);
Variant f_dom_text_is_whitespace_in_element_content(CVarRef obj);
Variant f_dom_xpath_register_ns(CVarRef obj, CStrRef prefix, CStrRef uri);
Variant f_dom_xpath_query(CVarRef obj, CStrRef expr, CObjRef context = null_object);
Variant f_dom_xpath_evaluate(CVarRef obj, CStrRef expr, CObjRef context = null_object);
Variant f_dom_xpath_register_php_functions(CVarRef obj, CVarRef funcs = null);

///////////////////////////////////////////////////////////////////////////////
// class DOMNode

FORWARD_DECLARE_CLASS(domnode);
class c_domnode : public ExtObjectData, public Sweepable {
 public:
  BEGIN_CLASS_MAP(domnode)
  END_CLASS_MAP(domnode)
  DECLARE_CLASS(domnode, DOMNode, ObjectData)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domnode();
  public: ~c_domnode();
  public: void t___construct();
  public: Variant t_appendchild(CObjRef newnode);
  public: Variant t_clonenode(bool deep = false);
  public: int64 t_getlineno();
  public: bool t_hasattributes();
  public: bool t_haschildnodes();
  public: Variant t_insertbefore(CObjRef newnode, CObjRef refnode = null);
  public: bool t_isdefaultnamespace(CStrRef namespaceuri);
  public: bool t_issamenode(CObjRef node);
  public: bool t_issupported(CStrRef feature, CStrRef version);
  public: Variant t_lookupnamespaceuri(CStrRef namespaceuri);
  public: Variant t_lookupprefix(CStrRef prefix);
  public: void t_normalize();
  public: Variant t_removechild(CObjRef node);
  public: Variant t_replacechild(CObjRef newchildobj, CObjRef oldchildobj);
  public: Variant t_c14n(bool exclusive = false, bool with_comments = false, CVarRef xpath = null, CVarRef ns_prefixes = null);
  public: Variant t_c14nfile(CStrRef uri, bool exclusive = false, bool with_comments = false, CVarRef xpath = null, CVarRef ns_prefixes = null);
  public: Variant t_getnodepath();
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domnode *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

public:
  sp_domdocument m_doc;
  xmlNodePtr m_node;
};

///////////////////////////////////////////////////////////////////////////////
// class DOMAttr

FORWARD_DECLARE_CLASS(domattr);
class c_domattr : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domattr)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domattr)
  DECLARE_CLASS(domattr, DOMAttr, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domattr();
  public: ~c_domattr();
  public: void t___construct(CStrRef name, CStrRef value = null_string);
  public: bool t_isid();
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domattr *create(String name, String value = null_string);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMCharacterData

FORWARD_DECLARE_CLASS(domcharacterdata);
class c_domcharacterdata : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domcharacterdata)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domcharacterdata)
  DECLARE_CLASS(domcharacterdata, DOMCharacterData, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domcharacterdata();
  public: ~c_domcharacterdata();
  public: void t___construct();
  public: bool t_appenddata(CStrRef arg);
  public: bool t_deletedata(int64 offset, int64 count);
  public: bool t_insertdata(int64 offset, CStrRef data);
  public: bool t_replacedata(int64 offset, int64 count, CStrRef data);
  public: String t_substringdata(int64 offset, int64 count);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domcharacterdata *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMComment

FORWARD_DECLARE_CLASS(domcomment);
class c_domcomment : public c_domcharacterdata {
 public:
  BEGIN_CLASS_MAP(domcomment)
  RECURSIVE_PARENT_CLASS(domcharacterdata)
  END_CLASS_MAP(domcomment)
  DECLARE_CLASS(domcomment, DOMComment, domcharacterdata)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domcomment();
  public: ~c_domcomment();
  public: void t___construct(CStrRef value = null_string);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domcomment *create(String value = null_string);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMText

FORWARD_DECLARE_CLASS(domtext);
class c_domtext : public c_domcharacterdata {
 public:
  BEGIN_CLASS_MAP(domtext)
  RECURSIVE_PARENT_CLASS(domcharacterdata)
  END_CLASS_MAP(domtext)
  DECLARE_CLASS(domtext, DOMText, domcharacterdata)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domtext();
  public: ~c_domtext();
  public: void t___construct(CStrRef value = null_string);
  public: bool t_iswhitespaceinelementcontent();
  public: Variant t_splittext(int64 offset);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domtext *create(String value = null_string);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMCdataSection

FORWARD_DECLARE_CLASS(domcdatasection);
class c_domcdatasection : public c_domtext {
 public:
  BEGIN_CLASS_MAP(domcdatasection)
  RECURSIVE_PARENT_CLASS(domtext)
  END_CLASS_MAP(domcdatasection)
  DECLARE_CLASS(domcdatasection, DOMCdataSection, domtext)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domcdatasection();
  public: ~c_domcdatasection();
  public: void t___construct(CStrRef value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domcdatasection *create(String value);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMDocument

FORWARD_DECLARE_CLASS(domdocument);
class c_domdocument : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domdocument)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domdocument)
  DECLARE_CLASS(domdocument, DOMDocument, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domdocument();
  public: ~c_domdocument();
  public: void t___construct(CStrRef version = null_string, CStrRef encoding = null_string);
  public: Variant t_createattribute(CStrRef name);
  public: Variant t_createattributens(CStrRef namespaceuri, CStrRef qualifiedname);
  public: Variant t_createcdatasection(CStrRef data);
  public: Variant t_createcomment(CStrRef data);
  public: Variant t_createdocumentfragment();
  public: Variant t_createelement(CStrRef name, CStrRef value = null_string);
  public: Variant t_createelementns(CStrRef namespaceuri, CStrRef qualifiedname, CStrRef value = null_string);
  public: Variant t_createentityreference(CStrRef name);
  public: Variant t_createprocessinginstruction(CStrRef target, CStrRef data = null_string);
  public: Variant t_createtextnode(CStrRef data);
  public: Variant t_getelementbyid(CStrRef elementid);
  public: Variant t_getelementsbytagname(CStrRef name);
  public: Variant t_getelementsbytagnamens(CStrRef namespaceuri, CStrRef localname);
  public: Variant t_importnode(CObjRef importednode, bool deep = false);
  public: Variant t_load(CStrRef filename, int64 options = 0);
  public: Variant t_loadhtml(CStrRef source);
  public: Variant t_loadhtmlfile(CStrRef filename);
  public: Variant t_loadxml(CStrRef source, int64 options = 0);
  public: void t_normalizedocument();
  public: bool t_registernodeclass(CStrRef baseclass, CStrRef extendedclass);
  public: bool t_relaxngvalidate(CStrRef filename);
  public: bool t_relaxngvalidatesource(CStrRef source);
  public: Variant t_save(CStrRef file, int64 options = 0);
  public: Variant t_savehtml();
  public: Variant t_savehtmlfile(CStrRef file);
  public: Variant t_savexml(CObjRef node = null_object, int64 options = 0);
  public: bool t_schemavalidate(CStrRef filename);
  public: bool t_schemavalidatesource(CStrRef source);
  public: bool t_validate();
  public: Variant t_xinclude(int64 options = 0);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domdocument *create(String version = null_string, String encoding = null_string);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

public:
  bool m_formatoutput;
  bool m_validateonparse;
  bool m_resolveexternals;
  bool m_preservewhitespace;
  bool m_substituteentities;
  bool m_stricterror;
  bool m_recover;
  Array m_classmap;
  Array m_orphans;
  bool m_owner;
};

///////////////////////////////////////////////////////////////////////////////
// class DOMDocumentFragment

FORWARD_DECLARE_CLASS(domdocumentfragment);
class c_domdocumentfragment : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domdocumentfragment)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domdocumentfragment)
  DECLARE_CLASS(domdocumentfragment, DOMDocumentFragment, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domdocumentfragment();
  public: ~c_domdocumentfragment();
  public: void t___construct();
  public: bool t_appendxml(CStrRef data);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domdocumentfragment *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMDocumentType

FORWARD_DECLARE_CLASS(domdocumenttype);
class c_domdocumenttype : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domdocumenttype)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domdocumenttype)
  DECLARE_CLASS(domdocumenttype, DOMDocumentType, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domdocumenttype();
  public: ~c_domdocumenttype();
  public: void t___construct();
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domdocumenttype *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMElement

FORWARD_DECLARE_CLASS(domelement);
class c_domelement : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domelement)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domelement)
  DECLARE_CLASS(domelement, DOMElement, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domelement();
  public: ~c_domelement();
  public: void t___construct(CStrRef name, CStrRef value = null_string, CStrRef namespaceuri = null_string);
  public: String t_getattribute(CStrRef name);
  public: Variant t_getattributenode(CStrRef name);
  public: Object t_getattributenodens(CStrRef namespaceuri, CStrRef localname);
  public: String t_getattributens(CStrRef namespaceuri, CStrRef localname);
  public: Object t_getelementsbytagname(CStrRef name);
  public: Object t_getelementsbytagnamens(CStrRef namespaceuri, CStrRef localname);
  public: bool t_hasattribute(CStrRef name);
  public: bool t_hasattributens(CStrRef namespaceuri, CStrRef localname);
  public: bool t_removeattribute(CStrRef name);
  public: Variant t_removeattributenode(CObjRef oldattr);
  public: Variant t_removeattributens(CStrRef namespaceuri, CStrRef localname);
  public: Variant t_setattribute(CStrRef name, CStrRef value);
  public: Variant t_setattributenode(CObjRef newattr);
  public: Variant t_setattributenodens(CObjRef newattr);
  public: Variant t_setattributens(CStrRef namespaceuri, CStrRef name, CStrRef value);
  public: Variant t_setidattribute(CStrRef name, bool isid);
  public: Variant t_setidattributenode(CObjRef idattr, bool isid);
  public: Variant t_setidattributens(CStrRef namespaceuri, CStrRef localname, bool isid);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domelement *create(String name, String value = null_string, String namespaceuri = null_string);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMEntity

FORWARD_DECLARE_CLASS(domentity);
class c_domentity : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domentity)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domentity)
  DECLARE_CLASS(domentity, DOMEntity, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domentity();
  public: ~c_domentity();
  public: void t___construct();
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domentity *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMEntityReference

FORWARD_DECLARE_CLASS(domentityreference);
class c_domentityreference : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domentityreference)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domentityreference)
  DECLARE_CLASS(domentityreference, DOMEntityReference, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domentityreference();
  public: ~c_domentityreference();
  public: void t___construct(CStrRef name);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domentityreference *create(String name);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMNotation

FORWARD_DECLARE_CLASS(domnotation);
class c_domnotation : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domnotation)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domnotation)
  DECLARE_CLASS(domnotation, DOMNotation, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domnotation();
  public: ~c_domnotation();
  public: void t___construct();
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domnotation *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMProcessingInstruction

FORWARD_DECLARE_CLASS(domprocessinginstruction);
class c_domprocessinginstruction : public c_domnode {
 public:
  BEGIN_CLASS_MAP(domprocessinginstruction)
  RECURSIVE_PARENT_CLASS(domnode)
  END_CLASS_MAP(domprocessinginstruction)
  DECLARE_CLASS(domprocessinginstruction, DOMProcessingInstruction, domnode)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domprocessinginstruction();
  public: ~c_domprocessinginstruction();
  public: void t___construct(CStrRef name, CStrRef value = null_string);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domprocessinginstruction *create(String name, String value = null_string);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMNodeIterator

FORWARD_DECLARE_CLASS(domnodeiterator);
class c_domnodeiterator : public ExtObjectData, public Sweepable {
 public:
  BEGIN_CLASS_MAP(domnodeiterator)
  PARENT_CLASS(iterator)
  END_CLASS_MAP(domnodeiterator)
  DECLARE_CLASS(domnodeiterator, DOMNodeIterator, ObjectData)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domnodeiterator();
  public: ~c_domnodeiterator();
  public: void t___construct();
  public: Variant t_current();
  public: Variant t_key();
  public: Variant t_next();
  public: Variant t_rewind();
  public: Variant t_valid();
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domnodeiterator *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

public:
  void reset_iterator(dom_iterable *objmap);

  dom_iterable *m_objmap;
  ArrayIter *m_iter;
  int m_index;
  Object m_curobj;
};

///////////////////////////////////////////////////////////////////////////////
// class DOMNamedNodeMap

FORWARD_DECLARE_CLASS(domnamednodemap);
class c_domnamednodemap : public ExtObjectData, public dom_iterable {
 public:
  BEGIN_CLASS_MAP(domnamednodemap)
  PARENT_CLASS(iteratoraggregate)
  END_CLASS_MAP(domnamednodemap)
  DECLARE_CLASS(domnamednodemap, DOMNamedNodeMap, ObjectData)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domnamednodemap();
  public: ~c_domnamednodemap();
  public: void t___construct();
  public: Variant t_getnameditem(CStrRef name);
  public: Variant t_getnameditemns(CStrRef namespaceuri, CStrRef localname);
  public: Variant t_item(int64 index);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t_getiterator();
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domnamednodemap *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMNodeList

FORWARD_DECLARE_CLASS(domnodelist);
class c_domnodelist : public ExtObjectData, public dom_iterable {
 public:
  BEGIN_CLASS_MAP(domnodelist)
  PARENT_CLASS(iteratoraggregate)
  END_CLASS_MAP(domnodelist)
  DECLARE_CLASS(domnodelist, DOMNodeList, ObjectData)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domnodelist();
  public: ~c_domnodelist();
  public: void t___construct();
  public: Variant t_item(int64 index);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t_getiterator();
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domnodelist *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMException

FORWARD_DECLARE_CLASS(domexception);
class c_domexception : public c_exception {
 public:
  BEGIN_CLASS_MAP(domexception)
  RECURSIVE_PARENT_CLASS(exception)
  END_CLASS_MAP(domexception)
  DECLARE_CLASS(domexception, DOMException, exception)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domexception();
  public: ~c_domexception();
  public: void t___construct(CStrRef message = "", int64 code = 0);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domexception *create(String message = "", int64 code = 0);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMImplementation

FORWARD_DECLARE_CLASS(domimplementation);
class c_domimplementation : public ExtObjectData {
 public:
  BEGIN_CLASS_MAP(domimplementation)
  END_CLASS_MAP(domimplementation)
  DECLARE_CLASS(domimplementation, DOMImplementation, ObjectData)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domimplementation();
  public: ~c_domimplementation();
  public: void t___construct();
  public: Variant t_createdocument(CStrRef namespaceuri = null_string, CStrRef qualifiedname = null_string, CObjRef doctypeobj = null_object);
  public: Variant t_createdocumenttype(CStrRef qualifiedname = null_string, CStrRef publicid = null_string, CStrRef systemid = null_string);
  public: bool t_hasfeature(CStrRef feature, CStrRef version);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domimplementation *create();
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

};

///////////////////////////////////////////////////////////////////////////////
// class DOMXPath

FORWARD_DECLARE_CLASS(domxpath);
class c_domxpath : public ExtObjectData, public Sweepable {
 public:
  BEGIN_CLASS_MAP(domxpath)
  END_CLASS_MAP(domxpath)
  DECLARE_CLASS(domxpath, DOMXPath, ObjectData)
  DECLARE_INVOKES_FROM_EVAL
  ObjectData* dynCreate(CArrRef params, bool init = true);

  // need to implement
  public: c_domxpath();
  public: ~c_domxpath();
  public: void t___construct(CVarRef doc);
  public: Variant t_evaluate(CStrRef expr, CObjRef context = null_object);
  public: Variant t_query(CStrRef expr, CObjRef context = null_object);
  public: bool t_registernamespace(CStrRef prefix, CStrRef uri);
  public: Variant t_registerphpfunctions(CVarRef funcs = null);
  public: Variant t___get(Variant name);
  public: Variant doGet(Variant v_name, bool error);
  public: Variant t___set(Variant name, Variant value);
  public: Variant t___destruct();

  // implemented by HPHP
  public: c_domxpath *create(Variant doc);
  public: void dynConstruct(CArrRef Params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: virtual void destruct();

 public:
  xmlNodePtr m_node;
  sp_domdocument m_doc;
  Array m_node_list;
  int m_registerPhpFunctions;
  Array m_registered_phpfunctions;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_DOMDOCUMENT_H__
