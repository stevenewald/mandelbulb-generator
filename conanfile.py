from conan import ConanFile
from conan.tools.files import copy


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

    def generate(self):
        dep = self.dependencies["imgui"]
        copy(self, "imgui_impl_glfw.cpp", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_glfw.h", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_opengl3.cpp", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_opengl3.h", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_opengl3_loader.h", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")

