/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: RareParser.cpp

*/

#include <Parser/RareParser.h>
#include <Parser/tinyxml/tinyxml2.h>

#ifndef _XML_SUCCESS
#define _XML_SUCCESS(x) x.ErrorID() == 0
#endif

namespace rs {

	//externs
	extern int g_resX;
	extern int g_resY;

	namespace Renderer {
		extern bool g_Fullscreen;
	}

	void getElementInt(int* val, tinyxml2::XMLElement* element)
	{
		if (element != NULL)
			element->QueryIntText(val);
	}

	void getElementBool(bool* val, tinyxml2::XMLElement* element)
	{
		if (element != NULL)
			element->QueryBoolText(val);
	}

	void RareParser::SetEngineAttributes()
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile("RSEngine.xml");

		if (_XML_SUCCESS(doc)) {
			// Set the root to "RSEngine"
			auto* pRoot = doc.FirstChildElement("RSEngine");

			while (pRoot) {
				
				// Graphics settings
				if(1) {
					auto* pGraphicsSettings = pRoot->FirstChildElement("Graphics");

					getElementInt(&g_resX, pGraphicsSettings->FirstChildElement("ResolutionWidth"));
					getElementInt(&g_resY, pGraphicsSettings->FirstChildElement("ResolutionHeight"));
					getElementBool(&Renderer::g_Fullscreen, pGraphicsSettings->FirstChildElement("FullScreen"));

					// Fullscreen?
				}

				// Developer settings
				if (1) {
					auto* pDeveloperSettings = pRoot->FirstChildElement("Developer");

					//getElementBool(&g_enableEditor, pDeveloperSettings->FirstChildElement("EnableEditor"));
				}

				pRoot = pRoot->NextSiblingElement("RSEngine");
			}
		}
		else {
			CreateEngineAttributes();
		}
	}

	void RareParser::WriteEngineAttributes()
	{

	}

	void RareParser::CreateEngineAttributes()
	{
		tinyxml2::XMLDocument doc;
		auto* pRoot = doc.NewElement("RSEngine");
		doc.InsertFirstChild(pRoot);

		//Graphics
		if (1) {
			auto* pGraphicsSettings = doc.NewElement("Graphics");
			pRoot->InsertEndChild(pGraphicsSettings);

			auto* resolutionWidth = doc.NewElement("ResolutionWidth");
			resolutionWidth->SetText(g_resX);
			pGraphicsSettings->InsertEndChild(resolutionWidth);

			auto* resolutionHeight = doc.NewElement("ResolutionHeight");
			resolutionHeight->SetText(g_resY);
			pGraphicsSettings->InsertEndChild(resolutionHeight);

			auto* FullScreen = doc.NewElement("FullScreen");
			FullScreen->SetText(Renderer::g_Fullscreen);
			pGraphicsSettings->InsertEndChild(FullScreen);
		}

		tinyxml2::XMLError eResult = doc.SaveFile("RSEngine.xml");
	}

} // namespace rs
