    
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

# Examples
if GetDepend('ELAPACK_USING_LINSOLVE'):
	src    += Glob('Examples/rtt_linsolve.c')
if GetDepend('ELAPACK_USING_LU'):
	src    += Glob('Examples/rtt_lu.c')
if GetDepend('ELAPACK_USING_QR'):
	src    += Glob('Examples/rtt_qr.c')
if GetDepend('ELAPACK_USING_SVD'):
	src    += Glob('Examples/rtt_svd.c')
if GetDepend('ELAPACK_USING_EIG'):
	src    += Glob('Examples/rtt_eig.c')
if GetDepend('ELAPACK_USING_STATE_SPACE'):
	src    += Glob('Examples/rtt_state_space.c')
if GetDepend('ELAPACK_USING_MODEL_PREDICTIVE'):
	src    += Glob('Examples/rtt_model_predictive_control.c')

path    = [cwd + '/']
path   += [cwd + '/LinearAlgebra']
path   += [cwd + '/Lapack/Blas']
path   += [cwd + '/Lapack/F2c']
path   += [cwd + '/Lapack/Install']
path   += [cwd + '/Lapack/Scr']

LOCAL_CCFLAGS = ''

group = DefineGroup('elapack', src, depend = ['PKG_USING_ELAPACK'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
