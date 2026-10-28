#pragma once

#include "Private/D3D12/D3D12Include.hpp"
#include "Renderer/Utility.hpp"


#include <Core/STL/Vector.hpp>
#include <Core/STL/String.hpp>

namespace NF::RendererApi::D3D12
{
    [[nodiscard]]
    Vector<Utility::DisplayDesc::DisplayMode> GetDisplayModes(IDXGIOutput6* outputVer6);


}