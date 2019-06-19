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
