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
        self.requires("glm/1.0.1")
        self.requires("stb/cci.20240531")

    def configure(self):
        self.options["fmt"].shared=False
        self.options["glfw"].shared=False
        self.options["imgui"].shared=False
        self.options["glad"].shared=False
        self.options["stb"].shared=False
        self.options["glm"].shared=False

    def generate(self):
        dep = self.dependencies["imgui"]
        copy(self, "imgui_impl_glfw.cpp", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_glfw.h", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_opengl3.cpp", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_opengl3.h", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")
        copy(self, "imgui_impl_opengl3_loader.h", src=dep.package_folder + "/res/bindings", dst=str(self.build_folder)+"/bindings")

