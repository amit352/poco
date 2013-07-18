//
// Enum.cpp
//
// $Id: //poco/1.4/CppParser/src/Enum.cpp#1 $
//
// Library: CppParser
// Package: SymbolTable
// Module:  Enum
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/CppParser/Enum.h"
#include "Poco/CppParser/EnumValue.h"
#include "Poco/NumberFormatter.h"
#include <sstream>


using Poco::NumberFormatter;


namespace Poco {
namespace CppParser {


int Enum::_count = 0;


Enum::Enum(const std::string& name, NameSpace* pNameSpace):
	Symbol(processName(name), pNameSpace)
{
}


Enum::~Enum()
{
}


void Enum::addValue(EnumValue* pValue)
{
	poco_check_ptr (pValue);
	
	_values.push_back(pValue);
}

	
Enum::Iterator Enum::begin() const
{
	return _values.begin();
}


Enum::Iterator Enum::end() const
{
	return _values.end();
}


std::string Enum::processName(const std::string& name)
{
	if (name.empty())
	{
		std::string result("#AnonEnum");
		result.append(NumberFormatter::format0(_count++, 4));
		return result;
	}
	else return name;
}


Symbol::Kind Enum::kind() const
{
	return Symbol::SYM_ENUM;
}


std::string Enum::toString() const
{
	std::ostringstream ostr;
	ostr << "enum " << name() << "\n{\n";
	for (Iterator it = begin(); it != end(); ++it)
	{
		ostr << "\t" << (*it)->toString() << "\n";
	}
	ostr << "};";
	return ostr.str();
}


} } // namespace Poco::CppParser