set_xmakever("2.8.1")

includes("vendor/BaseLibrary")

set_allowedplats("windows", "linux")
set_arch("x64")

set_languages("cxx20", "c17")

add_rules("plugin.vsxmake.autoupdate")

if is_plat("windows") then
  add_defines("UNICODE=1", "_UNICODE=1")
  add_cxflags("/bigobj", "/utf-8", {tools = {"clang_cl", "cl"}})
  add_cxflags("/MP", {tools = {"cl"}})
  add_defines("_CRT_SECURE_NO_WARNINGS=1", "WIN32_LEAN_AND_MEAN=1", "NOMINMAX=1", "WINVER=_WIN32_WINNT_WIN10", "_WIN32_WINNT=_WIN32_WINNT_WIN10", "NTDDI=NTDDI_WIN10_19H1")
end

if is_plat("linux") then
  add_cxflags("-stdlib=libc++", {tools = {"clang"}})
end

local vsRuntime = "MD"

set_policy("check.auto_ignore_flags", true)
set_policy("build.across_targets_in_parallel", true)
set_policy("build.ccache", true)
set_policy("build.warning", true)

if is_mode("debug") then
  add_defines("_DEBUG")
  set_symbols("debug")
  set_optimize("none")
  set_warnings("all")
  set_policy("build.optimization.lto", false)

  --add_cxflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})
  --add_mxflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})
  --add_ldflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})
  --add_shflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})

  --add_cxflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})
  --add_mxflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})
  --add_ldflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})
  --add_shflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})

  vsRuntime = vsRuntime.."d"
elseif is_mode("releasedbg") then
  add_defines("_DEBUG")
  set_symbols("debug")
  set_optimize("fastest")
  set_warnings("all")
  set_policy("build.optimization.lto", true)

  --add_cxflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})
  --add_mxflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})
  --add_ldflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})
  --add_shflags("-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", {tools = {"clang", "gnu"}})

  --add_cxflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})
  --add_mxflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})
  --add_ldflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})
  --add_shflags("/fsanitize=address", {tools = {"clang_cl", "cl"}})

  vsRuntime = vsRuntime.."d"
elseif is_mode("release") then
  add_defines("NDEBUG")
  set_symbols("hidden")
  set_strip("all")
  set_optimize("fastest")
  set_warnings("all", "error")
  set_policy("build.optimization.lto", true)
end

add_cxflags("-Wno-microsoft-include", "-Wno-unused-command-line-argument", "-Wno-pragma-system-header-outside-header", {tools = {"clang_cl", "clang"}})

add_requireconfs("**", { configs = { debug = is_mode("debug"), shared = false } })

if is_plat("windows") then
  set_runtimes(vsRuntime);
  --add_requireconfs("**", { configs = { cxflags = "/fsanitize=address", mxflags = "/fsanitize=address", ldflags = "/fsanitize=address", shflags = "/fsanitize=address" } })
end

if is_plat("linux") then
  --add_requireconfs("**", { configs = { cxflags = "-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", mxflags = "-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", ldflags = "-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak", shflags = "-fsanitize=address -fsanitize=hwaddress -fsanitize=thread -fsanitize=undefined -fsanitize=memory -fsanitize=leak" } })
end

target("Glacier1AudioLibrary")
  set_version("0.1.0")
  set_kind("static")

  add_deps("BaseLibrary", { public = true })

  add_includedirs("include", {public = true})

  add_headerfiles("include/Feldarian/G1AL/**.hpp")
  add_files("src/G1AL/**.cpp")
target_end()
