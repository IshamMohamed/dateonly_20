from setuptools import setup, Extension

module = Extension(
    "dateonly_20.dateonly_20",
    sources=["dateonly_20/dateonly_20.c"],
    include_dirs=["/usr/include/python3.8"],
)

setup(
    name="dateonly_20",
    version="0.1",
    description="A package for encoding, decoding, and manipulating 20th centure dates with C-level performance.",
    author="Isham Mohamed",
    author_email="email@goes.here",
    ext_modules=[module],
    packages=["dateonly_20"],
)
