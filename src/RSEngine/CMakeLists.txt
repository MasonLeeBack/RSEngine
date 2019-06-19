cmake_minimum_required(VERSION 3.12.2)

project(RSEngine)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(RSEngine
  Classes/BasePart.cpp
  Classes/Camera.cpp
  Classes/EngineClass.cpp
  Classes/Folder.cpp
  Classes/Instance.cpp
  Classes/MeshPart.cpp
  Classes/Part.cpp
  Classes/Skybox.cpp
  Classes/Texture.cpp
  Core/Clipboard.cpp
  Core/Config.cpp
  Core/Console.cpp
  Core/Engine.cpp
  Core/Filesystem.cpp
  Core/GameLib.cpp
  Include/Classes/BasePart.h
  Include/Classes/Camera.h
  Include/Classes/EngineClass.h
  Include/Classes/Folder.h
  Include/Classes/Instance.h
  Include/Classes/MeshPart.h
  Include/Classes/Part.h
  Include/Classes/RSClasses.h
  Include/Classes/Skybox.h
  Include/Classes/Texture.h
  Include/Core/Clipboard.h
  Include/Core/Config.h
  Include/Core/Console.h
  Include/Core/Engine.h
  Include/Core/Filesystem.h
  Include/Core/GameLib.h
  Include/Editor/EdAssetExplorer.h
  Include/Editor/EdConsole.h
  Include/Editor/EdInstanceProperties.h
  Include/Editor/EdInstanceView.h
  Include/Editor/Editor.h
  Include/Editor/EditorComponent.h
  Include/Editor/EditorStyle.h
  Include/Editor/EdUtilities.h
  Include/Editor/EdViewport.h
  Include/Input/Gamepad.h
  Include/Input/libScePad/RSScePad.h
  Include/Input/RareInput.h
  Include/Parser/RareParser.h
  Include/Parser/tinyxml/tinyxml2.h
  Include/Render/D3D11/RSD3D11.h
  Include/Render/D3D11/RSD3D11_Buffer.h
  Include/Render/D3D11/RSD3D11_Shader.h
  Include/Render/D3D11/RSD3D11_Texture.h
  Include/Render/D3D11/RSD3D11_TypeConv.h
  Include/Render/D3D11/RSD3D11_Types.h
  Include/Render/D3D12/RSD3D12.h
  Include/Render/GNM/RSGNM.h
  Include/Render/OpenGL/RSOpenGL.h
  Include/Render/RSRender.h
  Include/Render/RSRender_Buffer.h
  Include/Render/RSRender_EditorView.h
  Include/Render/RSRender_Math.h
  Include/Render/RSRender_Shader.h
  Include/Render/RSRender_Texture.h
  Include/Render/RSRender_Types.h
  Include/Render/ThirdParty/ImGui/imconfig.h
  Include/Render/ThirdParty/ImGui/imgui.h
  Include/Render/ThirdParty/ImGui/imgui_impl_dx11.h
  Include/Render/ThirdParty/ImGui/imgui_impl_win32.h
  Include/Render/ThirdParty/ImGui/imgui_internal.h
  Include/Render/ThirdParty/ImGui/imstb_rectpack.h
  Include/Render/ThirdParty/ImGui/imstb_textedit.h
  Include/Render/ThirdParty/ImGui/imstb_truetype.h
  Include/Render/ThirdParty/stb_image.h
  Include/Render/ThirdParty/tiny_obj_loader.h
  Include/Render/Vulkan/RSVulkan.h
  Include/RSEngine.h
  Include/RSEngine_BuildMacros.h
  Include/Types/InputType.h
  Include/Types/MeshData.h
  Include/Types/RareRes.h
  Include/Types/RareTypes.h
  Include/Types/Vector2.h
  Include/Types/Vector3.h
  Include/Utils/RSEngine_GeometryGenerator.h
  Include/Utils/RSEngine_RenderPipeline.h
  Include/Utils/RSEngine_RichPresence.h
  Include/Utils/RSUtils.h
  Include/Window/WindowSystem.h
  Input/libScePad/RSScePad.cpp
  Input/RareInput.cpp
  Parser/RareParser.cpp
  Parser/tinyxml/tinyxml2.cpp
  Render/D3D11/RSD3D11.cpp
  Render/D3D11/RSD3D11_Buffer.cpp
  Render/D3D11/RSD3D11_Shader.cpp
  Render/D3D11/RSD3D11_Texture.cpp
  Render/D3D11/RSD3D11_TypeConv.cpp
  Render/D3D12/RSD3D12.cpp
  Render/GNM/RSGNM.cpp
  Render/OpenGL/RSOpenGL.cpp
  Render/RSRender.cpp
  Render/RSRender_Buffer.cpp
  Render/RSRender_EditorView.cpp
  Render/RSRender_Shader.cpp
  Render/RSRender_Texture.cpp
  Render/ThirdParty/ImGui/imgui.cpp
  Render/ThirdParty/ImGui/imgui_draw.cpp
  Render/ThirdParty/ImGui/imgui_impl_dx11.cpp
  Render/ThirdParty/ImGui/imgui_impl_win32.cpp
  Render/ThirdParty/ImGui/imgui_widgets.cpp
  Render/ThirdParty/stb_image.cpp
  Render/Vulkan/RSVulkan.cpp
  RSEngine.cpp
  Types/Vector2.cpp
  Types/Vector3.cpp
  Utils/RSEngine_GeometryGenerator.cpp
  Utils/RSEngine_RenderPipeline.cpp
  Utils/RSEngine_RichPresence.cpp
  Window/WindowSystem.cpp
)
# Preprocessor definitions
target_compile_definitions(RSEngine PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;LIBRARY_EXPORTS;>
  $<$<CONFIG:Release>:_UNICODE;>
)

# SDL check
target_compile_options(RSEngine PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(RSEngine PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(RSEngine PRIVATE
    ""
  )
endif ()

# Link libraries
set_property(TARGET RSEngine
  APPEND PROPERTY LINK_LIBRARIES
  "$<$<CONFIG:Debug>:DXGI.lib;D3DCompiler.lib;d3d11.lib;XINPUT9_1_0.lib>"
  "$<$<CONFIG:Release>:DXGI.lib;D3DCompiler.lib;d3d11.lib;XINPUT9_1_0.lib>"
)
