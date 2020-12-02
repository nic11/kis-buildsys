#!/usr/bin/env python3
#coding: utf-8

import json
import pathlib
import sys

with open(sys.argv[1]) as f:
    funcs = json.load(f)['functions']

output_dir = pathlib.Path(sys.argv[2])

with open(output_dir / 'index.h', 'w') as f:
    print('#pragma once', file=f)
    for func in funcs:
        func_return = func['return_type']
        func_name = func['name']
        func_params = func['params']
        func_expr = func['expression']
        print(f'{func_return} {func_name}({func_params})', file=f)
        print('{ return ' + func_expr + '; }', file=f)
