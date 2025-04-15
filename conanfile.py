from conan import ConanFile


class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "VirtualRunEnv"

    def layout(self):
        self.folders.generators = "conan"

    def requirements(self):
        self.requires("fmt/11.0.2")
        self.requires("glfw/3.4")
        self.requires("imgui/1.91.8")
        self.requires("glad/0.1.36")

    def build_requirements(self):
        self.test_requires("catch2/3.7.0")
