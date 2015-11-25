#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'kodoc'
VERSION = '7.0.1'

import waflib.extras.wurf_options


def options(opt):

    opt.load('wurf_common_tools')


def resolve(ctx):

    import waflib.extras.wurf_dependency_resolve as resolve

    ctx.load('wurf_common_tools')

    ctx.add_dependency(resolve.ResolveVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major=3))

    ctx.add_dependency(resolve.ResolveVersion(
        name='kodo',
        git_repository='github.com/steinwurf/kodo.git',
        major=34))

    ctx.add_dependency(resolve.ResolveVersion(
        name='kodo-rlnc',
        git_repository='github.com/steinwurf/kodo-rlnc.git',
        major=1),
        optional=True)

    ctx.add_dependency(resolve.ResolveVersion(
        name='kodo-fulcrum',
        git_repository='github.com/steinwurf/kodo-fulcrum.git',
        major=1),
        optional=True)

    ctx.add_dependency(resolve.ResolveVersion(
        name='kodo-reed-solomon',
        git_repository='github.com/steinwurf/kodo-reed-solomon.git',
        major=1),
        optional=True)

    # Internal dependencies
    if ctx.is_toplevel():

        ctx.add_dependency(resolve.ResolveVersion(
            name='gtest',
            git_repository='github.com/steinwurf/gtest.git',
            major=3))

    opts = ctx.opt.add_option_group('kodo-c options')

    opts.add_option(
        '--disable_rlnc', default=None, dest='disable_rlnc',
        action='store_true', help="Disable the basic RLNC codecs")

    opts.add_option(
        '--disable_fulcrum', default=None, dest='disable_fulcrum',
        action='store_true', help="Disable the Fulcrum RLNC codec")

    opts.add_option(
        '--disable_reed_solomon', default=None, dest='disable_reed_solomon',
        action='store_true', help="Disable the Reed-Solomon codec")


def configure(conf):

    conf.load("wurf_common_tools")

    conf.env['DEFINES_KODOC_COMMON'] = []

    if conf.has_tool_option('disable_rlnc') or \
       not conf.has_dependency_path('kodo-rlnc'):
        conf.env['DEFINES_KODOC_COMMON'] += ['KODOC_DISABLE_RLNC']
    if conf.has_tool_option('disable_fulcrum') or \
       not conf.has_dependency_path('kodo-fulcrum'):
        conf.env['DEFINES_KODOC_COMMON'] += ['KODOC_DISABLE_FULCRUM']
    if conf.has_tool_option('disable_reed_solomon') or \
       not conf.has_dependency_path('kkodo-reed-solomon'):
        conf.env['DEFINES_KODOC_COMMON'] += ['KODOC_DISABLE_REED_SOLOMON']

def build(bld):

    CXX = bld.env.get_flat("CXX")
    # Matches both g++ and clang++
    if 'g++' in CXX or 'clang' in CXX:
        # The -fPIC flag is required for all underlying static libraries that
        # will be included in the shared library
        bld.env.append_value('CXXFLAGS', '-fPIC')
        # Hide most of the private symbols in the shared library to decrease
        # its size and improve its load time
        bld.env.append_value('CXXFLAGS', '-fvisibility=hidden')
        bld.env.append_value('CXXFLAGS', '-fvisibility-inlines-hidden')
        bld.env.append_value('LINKFLAGS', '-fvisibility=hidden')

    bld.load("wurf_common_tools")

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_KODOC_VERSION="{}"'.format(VERSION))

    # Build the kodo-c static library
    bld.stlib(
        source=bld.path.ant_glob('src/kodoc/*.cpp'),
        target='kodoc_static',
        name='kodoc_static',
        defines=['KODOC_STATIC'],
        export_defines=['KODOC_STATIC'],
        export_includes='src',
        use=['kodo_includes', 'KODOC_COMMON'])

    # Build the kodo-c shared library
    bld.shlib(
        source=bld.path.ant_glob('src/kodoc/*.cpp'),
        target='kodoc',
        name='kodoc',
        defines=['KODOC_DLL_EXPORTS'],
        install_path=None,
        export_includes='src',
        use=['kodo_includes', 'KODOC_COMMON'])

    if bld.is_toplevel():

        bld.recurse('test')
        bld.recurse('examples/encode_decode_on_the_fly')
        bld.recurse('examples/encode_decode_simple')
        bld.recurse('examples/raw_symbols')
        bld.recurse('examples/shallow_encode_decode')
        bld.recurse('examples/sliding_window')
        bld.recurse('examples/switch_systematic_on_off')
        bld.recurse('examples/udp_sender_receiver')
        bld.recurse('examples/use_trace_layers')
        bld.recurse('benchmark/kodoc_throughput')
