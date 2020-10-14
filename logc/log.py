import ctypes
import inspect

# import library, where log is used:
lib = ctypes.cdll.LoadLibrary('./liblog.so')     # (linux lib_example)

# or make it visible from the python package level:
# from . import lib

# if a namespace is used, change it here: (for example ns_logc_set_*)
logc_set_min_level = lib.logc_set_min_level
logc_set_quiet = lib.logc_set_quiet
logc_base_ = lib.logc_base_


#
# Implementation:
#

logc_set_min_level.argtypes = [ctypes.c_int]
logc_set_quiet.argtypes = [ctypes.c_bool]
logc_base_.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]

TRACE = 0
DEBUG = 1
INFO = 2
WARN = 3
ERROR = 4
WTF = 5
NUM_LEVELS = 6


def set_min_level(level: int):
    logc_set_min_level(level)


def set_quiet(set: bool):
    logc_set_quiet(set)


def trace(*text, leading_text=''):
    frame = inspect.stack()[1]
    logc_base_(TRACE, leading_text.encode(), frame.filename.encode(), frame.lineno, ' '.join(text).encode())


def debug(*text, leading_text=''):
    frame = inspect.stack()[1]
    logc_base_(DEBUG, leading_text.encode(), frame.filename.encode(), frame.lineno, ' '.join(text).encode())


def info(*text, leading_text=''):
    frame = inspect.stack()[1]
    logc_base_(INFO, leading_text.encode(), frame.filename.encode(), frame.lineno, ' '.join(text).encode())


def warn(*text, leading_text=''):
    frame = inspect.stack()[1]
    logc_base_(WARN, leading_text.encode(), frame.filename.encode(), frame.lineno, ' '.join(text).encode())


def error(*text, leading_text=''):
    frame = inspect.stack()[1]
    logc_base_(ERROR, leading_text.encode(), frame.filename.encode(), frame.lineno, ' '.join(text).encode())


def wtf(*text, leading_text=''):
    frame = inspect.stack()[1]
    logc_base_(WTF, leading_text.encode(), frame.filename.encode(), frame.lineno, ' '.join(text).encode())

