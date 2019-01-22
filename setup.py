import os, sys
import glob

from distutils.core import setup, Extension
from distutils import sysconfig

cpp_args = ['-std=c++1z', '-fopenmp']

# files = glob.glob(os.path.join('src', '*.cpp'))
files = ['src/integer_model.cpp', 'src/genotype_phenotype.cpp', 'src/genotype_duplicate.cpp',
 'src/genotype_iofunc.cpp', 'src/genotype_generate.cpp', 'src/genotype_api.cpp', 'src/genotype_wrap.cpp']

# print(files)

ext_modules = [
    Extension(
    'polyo',
        files,
    include_dirs=['pybind11/include', './includes', './polyomino_core/includes'],
    language='c++',
    extra_compile_args = cpp_args,
    extra_link_args=['-lgomp']
    ),
]

setup(
    name='polyo',
    version='0.0.1',
    author='Victor Jouffrey and Alexandre Leonard',
    author_email='vicatjou@gmail.com',
    description='Effect of Gene Duplication on Evolutionary Landscape in the Integer Polyomino Model',
    ext_modules=ext_modules,
)
