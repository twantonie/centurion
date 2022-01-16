from conans import ConanFile


class Centurion(ConanFile):
    name = "centurion"
    version = "6.3.0"
    # No settings/options are necessary, this is header only
    exports_sources = "src/*"
    no_copy_source = True
    requires = ["sdl/2.0.18", "sdl_ttf/2.0.15", "sdl_image/2.0.5"]
    generators = "cmake_find_package"

    def package(self):
        self.copy("*.hpp", "include/", "src/")

    def package_info(self):
        self.info.header_only = True
        self.cpp_info.defines = ["CENTURION_NO_SDL_MIXER"]
        self.cpp_info.includedirs = ['include']
