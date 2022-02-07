import numpy
import platform

from setuptools import setup, Extension

PY_LIMITED_API = "0x03070000"
PY_LIMITED_API_VERSION = (3, 7)

# Workaround to make "pip wheel" build correct ABI3 wheels
if platform.python_implementation() == "CPython":
    try:
        import wheel.bdist_wheel
    except ImportError:
        cmdclass = {}
    else:

        class bdist_wheel(wheel.bdist_wheel.bdist_wheel):
            def finalize_options(self) -> None:
                self.py_limited_api = (
                    f"cp{PY_LIMITED_API_VERSION[0]}{PY_LIMITED_API_VERSION[1]}"
                )
                super().finalize_options()

        cmdclass = {"bdist_wheel": bdist_wheel}
else:
    cmdclass = {}
setup_args = dict(
    ext_modules=[
        Extension(
            "minilsap._lsap",
            ["src/_lsap/rectangular_lsap.cpp", "src/_lsap/_lsap_module.cpp"],
            py_limited_api=True,
            include_dirs=[numpy.get_include()],
            extra_compile_args=["-std=c++11", "-Wall"],
            define_macros=[("Py_LIMITED_API", PY_LIMITED_API), ("PY_SSIZE_T_CLEAN", 1)],
        )
    ],
    cmdclass=cmdclass,
)
setup(**setup_args)
