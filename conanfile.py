from conans import ConanFile, CMake, tools


class LivewallpapersConan(ConanFile):
    name = "live_wallpapers"
    version = "0.1"
    license = "<Put the package license here>"
    author = "winmord winmord@yandex.ru"
    url = "https://github.com/winmord/live_wallpapers.git"
    description = "live wallpapers for Windows"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": True}
    generators = "cmake"
    build_requires = "openssl/1.1.1g", \
	                 "poco/1.10.1"

    def source(self):
        self.run("git clone url")
        # This small hack might be useful to guarantee proper /MT /MD linkage
        # in MSVC if the packaged project doesn't have variables to set it
        # properly
        tools.replace_in_file("CMakeLists.txt", "PROJECT(live_wallpapers)",
								'''PROJECT(HelloWorld)
								include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
								conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="live_wallpapers")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["live_wallpapers"]

