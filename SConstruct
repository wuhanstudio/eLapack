import os
import sys

env = Environment()

objs = []

# Lapack
objs += Glob('Lapack/Blas/*.c')
objs += Glob('Lapack/F2c/*.c')
objs += Glob('Lapack/Install/*.c')
objs += Glob('Lapack/Scr/*.c')

# Linear Algebra
objs += Glob('LinearAlgebra/*.c')

objs += Glob('./main.c')

env.Program(target = "main", source = objs, LIBS=['m'])
