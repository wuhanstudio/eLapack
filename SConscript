    
from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.

# Lapack
src  = Glob('Lapack/Blas/*.c')
src += Glob('Lapack/F2c/*.c')
src += Glob('Lapack/Install/*.c')
src += Glob('Lapack/Scr/*.c')

# Linear Algebra
src += Glob('LinearAlgebra/*.c')

path    = [cwd + '/']
path   += [cwd + '/LinearAlgebra']
path   += [cwd + '/Lapack/Blas']
path   += [cwd + '/Lapack/F2c']
path   += [cwd + '/Lapack/Install']
path   += [cwd + '/Lapack/Scr']

LOCAL_CCFLAGS = ''

group = DefineGroup('elapack', src, depend = ['PKG_USING_ELAPACK'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
