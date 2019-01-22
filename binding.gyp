{
    "targets": [{
        'target_name': '<(module_name)',
        'product_dir': '<(module_path)',
        "sources": [ "src/addon.cpp", "src/destructible.cpp" ],

        # 'variables': {
        #     'setup_py': '<(DEPTH)/setup.py',
        #     'install_py': '<(DEPTH)/install.py',
        # },

        # 'actions': [
        #     {
        #         'action_name': 'Install',
        #         'inputs': [
        #             '>(install_py)',
        #         ],
        #         'outputs': [''],
        #         'action': [
        #             'python',
        #                 '>@(_inputs)', 
        #         ],
        #     },
        #     {
        #         'action_name': 'Setup',
        #         'inputs': [
        #             '>(setup_py)',
        #         ],
        #         'outputs': [''],
        #         'action': [
        #             'python',
        #                 '>@(_inputs)', 
        #         ],
        #     },
        # ],

        'defines': [],
        'configurations': {
            'Debug': {
                'msvs_settings': {
                    'VCCLCompilerTool': {
                        'RuntimeLibrary': '3' # /MDd
                    },
                },
            },
            'Release': {
                'msvs_settings': {
                    'VCCLCompilerTool': {
                        'RuntimeLibrary': '2' # /MD
                    },
                },
            },
        },

        'conditions': [
            ['OS=="linux"', {
                "cflags": [
                    "-Wall",
                    "-Wno-implicit-fallthrough",
                    "-Wno-uninitialized",
                    "-Wno-unused-function",
                    "-Wno-unknown-warning-option",
                    "-Wno-maybe-uninitialized",
                    "-Wno-cast-function-type",
                    "-Wno-unused-result",
                    "-Wno-nonnull-compare",
                    "-Wextra",
                    "-O3"
                ],
                "cflags_c": [
                    "-std=c99",
                    "-Wno-unused-parameter",
                    "-O3"
                ],
                "cflags_cc+": [
                    "-std=c++11",
                    "-Wno-maybe-uninitialized",
                    "-Wno-cast-function-type",
                    "-Wno-unused-parameter",
                    "-Wno-unknown-warning-option",
                    "-Wno-unused-const-variable",
                    "-Wno-undefined-internal",
                    "-O3"
                ],
                "include_dirs": [],
                'libraries': [],
            }],
            ['OS=="mac"', {
                "cflags": [
                    "-std=c++11",
                ],
                "include_dirs": [],
                'libraries': [],

            }],
            ['OS=="win"', {
                "include_dirs": [],
                'libraries': []
            }]
        ],
    }]
}
