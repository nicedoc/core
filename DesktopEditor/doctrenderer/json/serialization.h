#ifndef SERIALIZATION_H_
#define SERIALIZATION_H_

#include "json.h"

namespace NSJSON
{
	static JSSmart<NSJSBase::CJSValue> toJS(const IBaseValue* pValue)
	{
		IBaseValue::ValueType type = pValue->m_type;
		if (type == IBaseValue::vtUndefined)
			return NSJSBase::CJSContext::createUndefined();
		if (type == IBaseValue::vtNull)
			return NSJSBase::CJSContext::createNull();

		JSSmart<NSJSBase::CJSValue> ret;
		if (type == IBaseValue::vtObject)
		{
			const CObject* pObject = static_cast<const CObject*>(pValue);
			JSSmart<NSJSBase::CJSObject> jsObj = NSJSBase::CJSContext::createObject();
			for (const auto& entry : pObject->m_values)
			{
				JSSmart<NSJSBase::CJSValue> jsValue = toJS(entry.second);
				jsObj->set(entry.first.c_str(), jsValue);
			}
			ret = jsObj->toValue();
		}
		else if (type == IBaseValue::vtArray)
		{
			const CArray* pArray = static_cast<const CArray*>(pValue);
			JSSmart<NSJSBase::CJSArray> jsArr = NSJSBase::CJSContext::createArray(0);
			for (const IBaseValue* pArrValue : pArray->m_values)
			{
				jsArr->add(toJS(pArrValue).GetPointer());
			}
			ret = jsArr->toValue();
		}
		else if (type == IBaseValue::vtTypedArray)
		{
			const CTypedArray* pTypedArray = static_cast<const CTypedArray*>(pValue);
			JSSmart<NSJSBase::CJSTypedArray> jsTypedArr = NSJSBase::CJSContext::createUint8Array(pTypedArray->m_data, pTypedArray->m_len);
			ret = jsTypedArr->toValue();
		}
		else
		{
			// primitive type
			const CValue* pPrimitiveValue = static_cast<const CValue*>(pValue);
			switch (type) {
			case IBaseValue::vtBoolean:
				ret = NSJSBase::CJSContext::createBool(pPrimitiveValue->m_bool);
				break;
			case IBaseValue::vtInteger:
				ret = NSJSBase::CJSContext::createInt(pPrimitiveValue->m_int);
				break;
			case IBaseValue::vtDouble:
				ret = NSJSBase::CJSContext::createDouble(pPrimitiveValue->m_double);
				break;
			case IBaseValue::vtStringA:
				ret = NSJSBase::CJSContext::createString(pPrimitiveValue->m_string);
				break;
			case IBaseValue::vtStringW:
				ret = NSJSBase::CJSContext::createString(pPrimitiveValue->m_wstring);
				break;
			default:
				break;
			}
		}

		return ret;
	}
}

#endif	// SERIALIZATION_H_
