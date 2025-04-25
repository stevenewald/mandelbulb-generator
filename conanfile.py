from conan import ConanFile
from conan.tools.files import copy


class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"
    options = {
        "web_build": [True, False], 
    }

    def layout(self):
        self.folders.generators = "conan"

    def requirements(self):
        self.requires("fmt/11.0.2")
        self.requires("glm/1.0.1")
        self.requires("stb/cci.20240531")
        if not self.options.web_build:
            self.requires("glfw/3.4")
            self.requires("glad/0.1.36")

    def configure(self):
        self.options["fmt"].shared=False
        self.options["stb"].shared=False
        self.options["glm"].shared=False
        if not self.options.web_build:
            self.options["glfw"].shared=False
            self.options["glad"].shared=False

