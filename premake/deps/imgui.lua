imgui = {
	source = path.join(dependencies.basePath, "imgui"),
}

function imgui.import()
    links {"imgui"}

	imgui.includes()
end

function imgui.includes()
	includedirs {
		imgui.source,
    }
end

function imgui.project()
	project "imgui"
    language "C++"

    imgui.includes()

    files {
        path.join(imgui.source, "*.cpp"),
        path.join(imgui.source, "*.h"),
        path.join(imgui.source, "backends/imgui_impl_dx11.*"),
        path.join(imgui.source, "backends/imgui_impl_win32.*"),
    }

    warnings "Off"
    kind "StaticLib"
end

deps.imgui = imgui