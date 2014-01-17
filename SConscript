import platform
from os import path,walk

def getSuffixedFiles(fpath, fsuffix):
    #fpath = path.join("..", fpath);
    filelist = []
    for (dirpath, dirnames, filenames) in walk(fpath):
        filelist += Glob(path.join(dirpath, fsuffix))
    return filelist

Import("env")

if platform.linux_distribution()[0] == "Darwin":
    install_dir = path.join("/", "opt", "local", "include")
else:
    install_dir = path.join("/", "usr", "local", "include")

testfiles   = getSuffixedFiles("test", "*.cpp")
incfiles    = getSuffixedFiles("include", "*.hpp")

env.Append(CPPPATH=["include", "/opt/local/include"])
#env.Append(LIBS=["boost_unit_test_framework-mt"])
env.Append(LIBPATH=["/usr/local/lib", "/opt/local/lib"])

env.Command(
    path.join(install_dir, "semver",  "version.hpp"), 
    path.join("include", "semver", "version.hpp"),
    [
        Mkdir(path.join(install_dir, "semver")),
        Copy(path.join(install_dir, "semver",  "version.hpp"), path.join("include", "semver", "version.hpp"))
    ]
)

env.Install(dir = [ path.join("build", "include", "semver") ], source = [ path.join("include", "semver", "version.hpp") ])
env.Alias("install", [ path.join(install_dir) ])
env.Program(target = path.join("build", "semvar-test"), source = testfiles)
