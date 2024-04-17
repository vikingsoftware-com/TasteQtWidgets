#!/usr/bin/python3

from subprocess import check_call, CalledProcessError
import os
import pathlib
import shutil
import platform
import distro
import pip
import sys
import shlex


if sys.version_info >= (3, 8):
    from importlib.metadata import version
else:
    import pkg_resources


def module_version(moduleName):
    """
        Returns the version of the module moduleName. 
        Otherwise returns the string "N/A" 
    """
    try: 
        if sys.version_info >= (3, 8):
            return(version(moduleName))
        else:
            return pkg_resources.get_distribution(moduleName).version
    except:
        return('N/A')


def module_path(moduleName):
    try:
        module = __import__(moduleName)
        return os.path.dirname(module.__file__)
    except:
        return('N/A')


class SystemInfo:
    def __init__(self):
        self.python_version = sys.version_info
        self.qt_version = module_version("PySide6")
        if self.qt_version == "N/A":
            self.qt_version = "6.5.3"
        self.qt_path = os.path.dirname(os.path.realpath(__file__)) + "/Qt"
        self.qt_base_path = os.path.join(self.qt_path, self.qt_version, "gcc_64")
        self.qt_lib_path = os.path.join(self.qt_base_path, "lib")
        self.distribution_name = distro.id()
        self.distributin_version = distro.version()
        self.source_dir = os.path.dirname(os.path.realpath(__file__))
        self.build_dir = self.source_dir + "/build"

    def python_version_str(self):
        return str(self.python_version[0]) + "." + str(self.python_version[1]) + "." + str(self.python_version[2])
    
    def print_info(self):
        print("Python version      : " + self.python_version_str())
        print("Qt/PySide version   : " + self.qt_version)
        print("Qt path             : " + self.qt_path)
        print("Distribution        : " + self.distribution_name)
        print("Distribution version: " + self.distributin_version)
        print("Source directory    : " + self.source_dir)
        print("Build  directory    : " + self.build_dir)


def check_or_raise(moduleName):
    if (module_version(moduleName) == "N/A"):
        raise RuntimeError(moduleName + " was not found. Please install it and run this script again")


def run_command(cmd, stdout=None, environ=os.environ):
    """
        Run a command - and before print the full command to stdout
        cmd is a list as it is passed to subprocess.check_call
    """
    print("- Running: '" + " ".join(cmd) + "'")
    check_call(cmd, stdout=stdout, env=environ)


def check_or_install(pkgName, version, extra_args=""):
    if (module_version(pkgName) == "N/A"):
        cmd = [sys.executable, '-m', 'pip', 'install', pkgName if not version else pkgName + "==" + version]
        if extra_args:
            cmd = cmd +shlex.split(extra_args)
        cmd = cmd + ["--break-system-packages"]
        run_command(cmd)


def apt_install(packagesNames):
    """
        packagesNames is an array of strings that contains
        the names of the packages to install using apt
    """
    try:
        run_command(['sudo', 'apt', 'install', '-y', *packagesNames], stdout=open(os.devnull,'wb'))
    except CalledProcessError as e:
        print(e.output)


def clang_check():
    config_file = '/usr/bin/llvm-config-'
    if  distro.id() == 'debian':
        if distro.version() == "10":
            config_file += '11'
            apt_install(["llvm-11", "llvm-11-dev", "libclang-11-dev", "clang-11", "patchelf", "ninja-build"])
        if distro.version() == "11":
            config_file += '13'
            apt_install(["llvm-13", "llvm-13-dev", "libclang-13-dev", "clang-13", "patchelf", "ninja-build"])

    if  distro.id() == 'ubuntu':
        if distro.version() == "20.04":
            config_file += '12'
            apt_install(["llvm-12", "llvm-12-dev", "libclang-12-dev", "clang-12", "patchelf", "ninja-build"])
            
    #Create symlink to llvm-config on /usr/bin
    try:
        os.symlink(config_file, "/usr/bin/llvm-config")
    except FileExistsError:
        print ("The symlink already exists")
    except OSError:
        run_command(['sudo', 'ln', '-s', config_file, '/usr/bin/llvm-config'])


def cmake_prepare(info, environ=os.environ):
    try:
        run_command(['cmake', '-S', info.source_dir, '-B', info.build_dir, "-DCMAKE_PREFIX_PATH=" + info.qt_base_path], environ=environ)
    except CalledProcessError as e:
        print(e.output)


def cmake_build(info, ncpus=1, environ=os.environ):
    try:
        run_command(['cmake', '--build', info.build_dir, '-j' + str(ncpus)], environ=environ)
    except CalledProcessError as e:
        print(e.output)

def cmake_install(info):
    try:
        run_command(['cmake', '--install', info.build_dir])
    except CalledProcessError as e:
        print(e.output)


def check_install_qt_dev(info):
    try:
        if not os.path.exists(info.qt_path):
            cmd = "aqt install-qt --outputdir " + info.qt_path + " --base 'https://download.qt.io' linux desktop " + info.qt_version
            run_command(shlex.split(cmd))
        return info.qt_path
    except CalledProcessError as e:
        print(e.output)


# Main
print("** Gain system info")
info = SystemInfo()
info.print_info()

print("** Check / install PySide + shiboken")
check_or_install("aqtinstall", "", "--index-url=https://download.qt.io/official_releases/QtForPython/ --trusted-host download.qt.io")
check_or_install("PySide6", info.qt_version, "--index-url=https://download.qt.io/official_releases/QtForPython/ --trusted-host download.qt.io")
check_or_install("shiboken6", info.qt_version, "--index-url=https://download.qt.io/official_releases/QtForPython/ --trusted-host download.qt.io")
check_or_install("shiboken6-generator", info.qt_version, "--index-url=https://download.qt.io/official_releases/QtForPython/ --trusted-host download.qt.io")

import aqt

print("** Check / install clang")
clang_check()

print("** Check (and install if necessary a Qt development libraries))")
check_install_qt_dev(info)

print("** Clear build directory")
# Create build directory in this script folder and change to it
build_dir = info.build_dir
if os.path.isdir(build_dir):
    shutil.rmtree(build_dir)
os.mkdir(build_dir)
#os.chdir(build_dir)

print("** Build module")
# Set LD_LIBRARY_PATH to point to Qt PySide6 Qt libraries
env_copy = os.environ.copy()
env_var = env_copy.get("LD_LIBRARY_PATH")
if env_var:
    env_copy["LD_LIBRARY_PATH"] += os.pathsep + info.qt_lib_path
else:
    env_copy["LD_LIBRARY_PATH"] = info.qt_lib_path
print("* info: using LD_LIBRARY_PATH: " + env_copy["LD_LIBRARY_PATH"])
# Building PyRequirements
cmake_prepare(info, environ=env_copy)
# Get number of cores
ncpus = os.cpu_count()
cmake_build(info, ncpus - 1, environ=env_copy)

print("** Install module")
cmake_install(info)

