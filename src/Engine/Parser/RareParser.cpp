/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RareParser.cpp

*/

#include <Parser/RareParser.h>
#include <Parser/tinyxml/tinyxml2.h>
#include <Window/WindowSystem.h>

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

	void getElementUInt(unsigned int* val, tinyxml2::XMLElement* element)
	{
		if (element != NULL)
			element->QueryUnsignedText(val);
	}

	void getElementBool(bool* val, tinyxml2::XMLElement* element)
	{
		if (element != NULL)
			element->QueryBoolText(val);
	}

	void RareParser::SetEngineAttributes()
	{
		tinyxml2::XMLDocument doc;
        
        // TODO: Need to get the local document path for the platform, and
        // change the file name based on the game.
		doc.LoadFile("RSEngine.xml");

		if (_XML_SUCCESS(doc)) {
			// Set the root to "RSEngine"
			auto* pRoot = doc.FirstChildElement("RSEngine");

			while (pRoot) {
				
				// Graphics settings
				if(1) {
					auto* pGraphicsSettings = pRoot->FirstChildElement("Graphics");

					getElementUInt(&cfgBuf.windowWidth, pGraphicsSettings->FirstChildElement("ResolutionWidth"));
					getElementUInt(&cfgBuf.windowHeight, pGraphicsSettings->FirstChildElement("ResolutionHeight"));
					getElementBool(&cfgBuf.EnableFullscreen, pGraphicsSettings->FirstChildElement("FullScreen"));
					getElementBool(&Renderer::g_Fullscreen, pGraphicsSettings->FirstChildElement("FullScreen")); // TEMP TEMP

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
			CreateEngineAttributes(cfgBuf);
		}
	}

	void RareParser::WriteEngineAttributes()
	{

	}

	WindowClassConfig RareParser::getWindowConfiguration()
	{
		WindowClassConfig cfg;
		cfg.windowWidth = cfgBuf.windowWidth;
		cfg.windowHeight = cfgBuf.windowHeight;
		cfg.windowHame = "RSEngine Technical Preview";
		return cfg;
	}

	InternalConfigBuf RareParser::getConfigBuffer()
	{
		return cfgBuf;
	}

	void RareParser::CreateEngineAttributes(InternalConfigBuf cfgBuf)
	{
		tinyxml2::XMLDocument doc;
		auto* pRoot = doc.NewElement("RSEngine");
		doc.InsertFirstChild(pRoot);

		//Graphics
		if (1) {
			auto* pGraphicsSettings = doc.NewElement("Graphics");
			pRoot->InsertEndChild(pGraphicsSettings);

			auto* resolutionWidth = doc.NewElement("ResolutionWidth");
			resolutionWidth->SetText(cfgBuf.windowWidth);
			pGraphicsSettings->InsertEndChild(resolutionWidth);

			auto* resolutionHeight = doc.NewElement("ResolutionHeight");
			resolutionHeight->SetText(cfgBuf.windowHeight);
			pGraphicsSettings->InsertEndChild(resolutionHeight);

			auto* FullScreen = doc.NewElement("FullScreen");
			FullScreen->SetText(cfgBuf.EnableFullscreen);
			pGraphicsSettings->InsertEndChild(FullScreen);
		}

		tinyxml2::XMLError eResult = doc.SaveFile("RSEngine.xml");
	}

} // namespace rs
