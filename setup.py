from setuptools import setup, Extension

module = Extension(
    "dateonly_20.dateonly_20",
    sources=["dateonly_20/dateonly_20.c"],
    include_dirs=["/usr/include/python3.8"],
)

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

setup(
    name="dateonly_20",
    version="0.2",
    description="A package for encoding, decoding, and manipulating 20th centure dates with C-level performance.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    author="Isham Mohamed",
    author_email="isham.iqbal@icloud.com",
    ext_modules=[module],
    packages=["dateonly_20"],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.6",
)
