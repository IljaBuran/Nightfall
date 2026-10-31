#include "Private/pch.hpp"

#include "Private/ShaderCompiler.hpp"

namespace NF
{
    namespace
    {
        ComPtr<IDxcUtils>          pDxcUtils;
        ComPtr<IDxcCompiler3>      pDxcCompiler;
        ComPtr<IDxcIncludeHandler> pDxcIncludeHandler;
    }

    ShaderCompiler::ShaderCompiler()
    {
        WIN_CHECK(DxcCreateInstance(
            CLSID_DxcUtils,
            IID_PPV_ARGS(&pDxcUtils)
        ));

        pDxcUtils->CreateDefaultIncludeHandler(&pDxcIncludeHandler);

        WIN_CHECK(DxcCreateInstance(
            CLSID_DxcCompiler,
            IID_PPV_ARGS(&pDxcCompiler)
        ));
    }

    Optional<Shader> ShaderCompiler::Compile(StringView path, ShaderType type) noexcept
    {
        NF_ASSERT(path.length() > 0 && std::to_underlying(type) != 0);

        ComPtr<IDxcBlobEncoding> source;

        u32 codePage{ DXC_CP_UTF8 };

        WString wPath = OS::Windows::Utf8ToWide(path);

        if (WIN_FAIL(pDxcUtils->LoadFile(wPath.c_str(), &codePage, source.GetAddressOf())))
        {
            NF_LOG_WARNING("Failed to load shader file. Path: \"{}\"", path);
            return {};
        }

        DxcBuffer sourceBuffer
        {
            .Ptr{ source->GetBufferPointer() },
            .Size{ source->GetBufferSize() },
            .Encoding{ codePage }
        };

        Array<Vector<byte>, 8> blobs;
        ComPtr<IDxcBlob> pBlob;

        for (u8 i{ 1 }; i != 0; i <<= 1)
        {
            if ((static_cast<u8>(type) & i) == 0)
                continue;

            ShaderType curr{ static_cast<ShaderType>(i) };

            Vector<const WCHAR*> args
            {
            #if defined(D3D_DEBUG)
                L"-Zi",
                L"-Qembed_debug",
                L"-Od"
            #else
                L"-WX",
                L"-O3"
            #endif
            };


            Vector<DxcDefine> defines
            {
            };

            ComPtr<IDxcCompilerArgs> dxcArgs;

            WIN_CHECK(pDxcUtils->BuildArguments(
                wPath.c_str(),
                OS::Windows::Utf8ToWide(GetEntryPoint(curr)).c_str(),
                OS::Windows::Utf8ToWide(GetProfile(curr)).c_str(),
                args.data(),
                static_cast<u32>(args.size()),
                defines.data(),
                static_cast<u32>(defines.size()),
                dxcArgs.GetAddressOf()
            ));

            NF_ASSERT(dxcArgs);

            ComPtr<IDxcResult> dxcRes;

            WIN_CHECK(pDxcCompiler->Compile(
                &sourceBuffer,
                dxcArgs->GetArguments(),
                dxcArgs->GetCount(),
                pDxcIncludeHandler.Get(),
                IID_PPV_ARGS(dxcRes.GetAddressOf())
            ));

            ComPtr<IDxcBlobUtf8> dxcDiagnostics;

            WIN_CHECK(dxcRes->GetOutput(
                DXC_OUT_ERRORS,
                IID_PPV_ARGS(&dxcDiagnostics),
                nullptr
            ));

            HRESULT status{};
            WIN_CHECK(dxcRes->GetStatus(&status));

            const bool hasText{ dxcDiagnostics && dxcDiagnostics->GetStringLength() != 0 };

            if (FAILED(status))
            {
                NF_LOG_ERROR("Shader compilation failed:\n{}",
                             hasText ? dxcDiagnostics->GetStringPointer() : "(no diagnostics)");
                return {};
            }

            if (hasText)
            {
                NF_LOG_WARNING("Shader compiled with warnings:\n{}", dxcDiagnostics->GetStringPointer());
            }

            WIN_CHECK(dxcRes->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&pBlob), nullptr));

            auto& destBlob{ blobs[ShaderTypeToIndex(curr)] };

            usize blobSize{ pBlob->GetBufferSize() };

            destBlob.resize(blobSize);

            memcpy(destBlob.data(), pBlob->GetBufferPointer(), blobSize);

            pBlob.Reset();
        }

        return MakeOptional<Shader>(std::move(blobs), type);
    }
};